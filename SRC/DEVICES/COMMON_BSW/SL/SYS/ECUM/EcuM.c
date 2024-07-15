/* ***************************** includes *********************************** */
#include "Version.h"

#include <Dio.h>
#include <Port.h>
#include <Mcu.h>

#include "EcuM.h"
#include "EcuM_Cfg.h"
#include "Isr_VectorTable.h"
#include "Wdg.h"
#include "API.h"

/* ***************************** typedefs *********************************** */

/* ***************************** # defines ********************************** */
#define ECUM_VENDOR_ID_C          (99)   /**<\brief CoSyst VendorID_C */
#define ECUM_AR_MAJOR_VERSION_C   (3)    /**<\brief AUTOSAR major version */
#define ECUM_AR_MINOR_VERSION_C   (1)    /**<\brief AUTOSAR minor version */
#define ECUM_AR_PATCH_VERSION_C   (0)    /**<\brief AUTOSAR patch version */
#define ECUM_SW_MAJOR_VERSION_C   (1)    /**<\brief Software major_c version */
#define ECUM_SW_MINOR_VERSION_C   (1)    /**<\brief Software minor_c version */
#define ECUM_SW_PATCH_VERSION_C   (3)    /**<\brief Software patch_c version */

#define ECUM_INSTANCE_ID_C        (1)    /**<\brief Instance ID */


/* ***************************** # makros *********************************** */

#if(ECUM_VENDOR_ID_C != ECUM_VENDOR_ID)
#error "Ecum.c and Ecum.h have different vendor id's."
#endif /* ECUM_VENDOR_ID_C != ECUM_VENDOR_ID */

#if((ECUM_AR_MAJOR_VERSION_C != ECUM_AR_MAJOR_VERSION) || \
    (ECUM_AR_MINOR_VERSION_C != ECUM_AR_MINOR_VERSION) || \
    (ECUM_AR_PATCH_VERSION_C != ECUM_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Cdd_Motor.c and Cdd_Motor.h are different."
#endif   /* (CDD_MOTOR_AR_MAJOR_VERSION_C != CDD_MOTOR_AR_MAJOR_VERSION) || ... */

#if((ECUM_SW_MAJOR_VERSION_C != ECUM_SW_MAJOR_VERSION) || \
    (ECUM_SW_MINOR_VERSION_C != ECUM_SW_MINOR_VERSION) || \
    (ECUM_SW_PATCH_VERSION_C != ECUM_SW_PATCH_VERSION))
#error "Software Version Numbers of Ecum.c and Ecum.h are different."
#endif /* (ECUM_SW_MAJOR_VERSION_C != ECUM_SW_MAJOR_VERSION) || ... */

/* ***************************** modul global data ************************** */

#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/** Variable stores the initialization status of the ECU module */
static volatile Ecum_ModuleStatusEnum ecum_moduleState_e = ECUM_UNINIT;
#endif

/** current mode of state machine */
static volatile Ecum_StateMachineEnum ecum_stateMachine_e;

static uint32 ecum_triggerIndication_ui32;

/** Variable contains the number of configured main functions at run time */
static uint8 usedNumOfMainFunc_ui8;


/** pointer to the configuration of the current mode */
static const Ecum_ModeConfigType* ecum_cfgMode_ps = NULL_PTR;

/** Variable contains the configuration of the timer, as well as the callback functions at initialization */
static Ecum_MainFuncConfigType ecum_runTimer_as[ECUM_MAX_NUM_OF_MAIN_FUNC];

/** Variable signalizing that a new cycle began */
static boolean ecum_trigger_b;

/** Variable contains sleep mode request */
static volatile boolean ecum_sleepRequested_b;
static volatile boolean ecum_sleepFallASleepAllowed_b;

/** Variable contains run mode request */
static volatile boolean ecum_runRequested_b;

#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
/** Variable contains latest running time for each defined main function **/
static Gpt_ValueType ecum_actRunningTimeArray_aui16[ECUM_MAX_NUM_OF_MAIN_FUNC];

/** Variable contains max running time for each defined main function **/
static Gpt_ValueType ecum_maxRunningTimeArray_aui16[ECUM_MAX_NUM_OF_MAIN_FUNC];
#endif /* PROJECT_TIME_MEASUREMENT_SWITCH */

#if (PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH == STD_ON)
/** Variable contains start value of the GptTimer and is set in the begin of the Timer Interrupt  */
static Gpt_ValueType ecum_loadStartValue_ui16;

/** Variable contains end value of the GptTimer and is set in the end of the CallFunctions when ecum_triggerIndication_ui32 == 0*/
static Gpt_ValueType ecum_loadEndValue_ui16;

/** Flag which is set in the timer ISR to show that the load measuring is started */
static boolean ecum_loadMeasuringStarted_b;

/** Variable contains load for current cycle */
static Gpt_ValueType ecum_actLoad_ui16;

/** Variable contains max load of all cycles **/
static Gpt_ValueType ecum_maxLoad_ui16;
#endif /* PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH */

/* ***************************** module function definitions ********** */
static void Ecum_CallFunctions (void);
static void Ecum_ModeTransition(void);
static void Ecum_RunModeTransition(void);
static void Ecum_SleepModeTransition(void);

/* ****************************** module functions ********************************* */

static void Ecum_CallFunctions (void)
{
   /* ------ Variable deceleration ------- */
   uint8 locCtr_ui8;
#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
   Gpt_ValueType startValue_ui16;
   Gpt_ValueType endValue_ui16;
#endif /* PROJECT_TIME_MEASUREMENT_SWITCH */

   /* ------ Variable initialisation ------- */
   locCtr_ui8 = (uint8) 0U;
#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
    startValue_ui16 = (uint16)0U;
   endValue_ui16   = (uint16)0U;
#endif /* PROJECT_TIME_MEASUREMENT_SWITCH */

   /* ------ Source code ------- */
   /* iterate through bit mask and look if a main function is runnable */
   for (locCtr_ui8 = (uint8)0U; locCtr_ui8 < usedNumOfMainFunc_ui8; locCtr_ui8++) /*lint !e838: Previously assigned value to variable 'locCtr_ui8' has not been used -> coding guidelines says that variables after declaration have to be initialized */
   {
      /* Main function is runnable? */
      if ((ecum_triggerIndication_ui32 & (uint32)((uint32)((uint32)1U << locCtr_ui8))) != (uint32)0U)
      {
#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
         /* load current Timer value in startValue_ui16 */
         Gpt_GetTimeElapsed(&startValue_ui16);
#endif /* PROJECT_TIME_MEASUREMENT_SWITCH */

         /* call main function */
         ecum_runTimer_as[locCtr_ui8].callback();

#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
         /* load current Timer value in endValue_ui16 */
         Gpt_GetTimeElapsed(&endValue_ui16);

         /* No timer overflow occurred? */
         if(endValue_ui16 >= startValue_ui16)
         {
            /*calculate runtime for current task ->  set to zero in Timer ISR */
            ecum_actRunningTimeArray_aui16[locCtr_ui8] = endValue_ui16 - startValue_ui16;
         }
         else
         {
            /* Timer overflow! calculate runtime for current task ->  set to zero in Timer ISR */
            ecum_actRunningTimeArray_aui16[locCtr_ui8] = ((Gpt_ValueType)ECUM_TIMER_OVERFLOW_VALUE - startValue_ui16) + endValue_ui16;
         }

         /* new maximum reached? */
         if(ecum_actRunningTimeArray_aui16[locCtr_ui8] > ecum_maxRunningTimeArray_aui16[locCtr_ui8])
         {
            /* Saving new maximum running time value */
            ecum_maxRunningTimeArray_aui16[locCtr_ui8] = ecum_actRunningTimeArray_aui16[locCtr_ui8];
         }
         else
         {
            /* it's not the maximum, do nothing */
            ;
         }
#endif /* PROJECT_TIME_MEASUREMENT_SWITCH */
         /* clear bit of the main function that run before */
         ecum_triggerIndication_ui32 &= (uint32)(~((uint32)((uint32)1U << locCtr_ui8)));
      }
      else
      {
         /* not runnable, do nothing */
      }
   }

#if (PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH == STD_ON)
   /* load measuring started (in TimerISR)? */
   if(ecum_loadMeasuringStarted_b == (boolean)TRUE)
   {
      /* all main function has been finished? */
      if(ecum_triggerIndication_ui32 == (uint32)0)
      {
         /* load current Timer value in ecum_loadEndValue_ui16 */
         Gpt_GetTimeElapsed(&ecum_loadEndValue_ui16);
         /* No timer overflow occurred? */
         if(ecum_loadEndValue_ui16 >= ecum_loadStartValue_ui16)
         {
            /* calculate load for current cycle */
            ecum_actLoad_ui16 = ecum_loadEndValue_ui16 - ecum_loadStartValue_ui16;
         }
         else
         {
            /* Timer overflow! Calculate load for current cycle */
            ecum_actLoad_ui16 = ( (Gpt_ValueType)ECUM_TIMER_OVERFLOW_VALUE - ecum_loadStartValue_ui16) + ecum_loadEndValue_ui16;
         }
         /* new maximum reached? */
         if(ecum_actLoad_ui16 > ecum_maxLoad_ui16)
         {
           /* Saving new maximum load value */
           ecum_maxLoad_ui16 = ecum_actLoad_ui16;
         }
         else
         {
            /* it's not the maximum, do nothing */
            ;
         }
         /* time measuring can be started again */
         ecum_loadMeasuringStarted_b = FALSE;
      }
      else
      {
         /* main functions are not finished, do nothing */
         ;
      }
   }
   else
   {
      /* load measuring is not started, do nothing */
      ;
   }
#endif /* PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH */
}

/**
 * \brief Common actions for mode transitions
 */
static void Ecum_ModeTransition(void)
{
   /* ------ variables declaration ------ */
   uint8 locCtr_ui8;
   /* ------ variables initialisation ------ */
   locCtr_ui8 = (uint8)0U;

   if(ecum_cfgMode_ps != NULL_PTR)
   {
      Gpt_DisableNotification(ecum_initialConfiguration_s.usedTimerChannel_e);
      Gpt_StopTimer(ecum_initialConfiguration_s.usedTimerChannel_e);

      usedNumOfMainFunc_ui8 = ecum_cfgMode_ps->usedNumOfMainFunc_ui8;

      /* load for each configured main function the parameters */
      for(locCtr_ui8 = (uint8)0U; locCtr_ui8 < usedNumOfMainFunc_ui8; locCtr_ui8++) /*lint !e838: Previously assigned value to variable 'locCtr_ui8' has not been used -> coding guidelines says that variables after declaration have to be initialized */
      {
         ecum_runTimer_as[locCtr_ui8].callCycle_ui16 = ecum_cfgMode_ps->mainFuncConfig_as[locCtr_ui8].callCycle_ui16;
         ecum_runTimer_as[locCtr_ui8].callback = ecum_cfgMode_ps->mainFuncConfig_as[locCtr_ui8].callback;
         ecum_runTimer_as[locCtr_ui8].callTrigger_ui16 = ecum_cfgMode_ps->mainFuncConfig_as[locCtr_ui8].callTrigger_ui16;
      }
      /* no ready tasks */
      ecum_triggerIndication_ui32 = (uint32)0U;

      /* reconfigure timer */
      Gpt_StartTimer(ecum_initialConfiguration_s.usedTimerChannel_e, ecum_cfgMode_ps->initialTimerTicks_ui16);
      Gpt_EnableNotification(ecum_initialConfiguration_s.usedTimerChannel_e);
   }
   else
   {
      /* something is wrong, do not change the mode! */
#if(ECUM_DEV_ERROR_DETECTION == STD_ON)
      /* something is wrong */
      //Det_ReportError(ECUM_MODULE_ID, (uint8)ECUM_INSTANCE_ID, ECUM_MODE_TRANSITION_ID, ECUM_E_PARAM_POINTER);
#endif
   }

}

/**
 * \brief Perform transition to the Normal Mode
 */
static void Ecum_RunModeTransition (void)
{
   /* load configuration for next state */
   ecum_stateMachine_e = ECUM_STATE_RUN;
   ecum_cfgMode_ps = &ecum_initialConfiguration_s.cfgNormalMode_s;

   ecum_runRequested_b = (boolean) FALSE;
   /* perform common actions */
   Ecum_ModeTransition();
}


/**
 * \brief Perform transition to the Sleep Mode
 */
static void Ecum_SleepModeTransition (void)
{
   /* load configuration for next state */
   ecum_stateMachine_e = ECUM_STATE_SLEEP;
   ecum_cfgMode_ps = &ecum_initialConfiguration_s.cfgSleepMode_s;

   ecum_sleepRequested_b = (boolean) FALSE;
   /* perform common actions */
   Ecum_ModeTransition();
}

/* ***************************** global functions *************************** */

/**
 * \brief Function to initialize the ECUM module.
 *
 * Initializes the ECUM module.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */
void Ecum_Init (void)
{
   /* ------ variables declaration ------ */
#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
   uint8 indexCounter_ui8;
#endif /* PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH */

   /* --- init module global variables --- */

   /* ----- init internal variables ----- */
#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
   indexCounter_ui8 = (uint8)0;
#endif /* PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH */

   /* ----------- source code ----------- */

#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
   /* check if EcuM Module is already initialised */
   if(ecum_moduleState_e == ECUM_INIT)
   {
   /* Development Error Detection */
#if(ECUM_DEV_ERROR_DETECTION == STD_ON)
      //Det_ReportError(ECUM_MODULE_ID, (uint8)ECUM_INSTANCE_ID, ECUM_INIT_API_ID, ECUM_E_ALREADY_INIT);
#endif /* (ECUM_DEV_ERROR_DETECTION == STD_ON) */
   }
   else
#endif /* PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON */
   {
#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
      /* EcuM Module is now initialised */
      ecum_moduleState_e = ECUM_INIT;
#endif /* PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON */

      /* initialise global variables */
      ecum_sleepRequested_b = (boolean)FALSE;
      ecum_runRequested_b =   (boolean)FALSE;

      ecum_cfgMode_ps =             NULL_PTR;
      ecum_triggerIndication_ui32 = (uint32)0;
      ecum_trigger_b = (boolean)FALSE;

      ecum_stateMachine_e = ECUM_STATE_INIT;

#if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
      /* initialise global variables for time measuring */
      for(indexCounter_ui8 = (uint8)0; indexCounter_ui8 < (uint8)ECUM_MAX_NUM_OF_MAIN_FUNC; indexCounter_ui8++)
      {
         ecum_actRunningTimeArray_aui16[indexCounter_ui8] =     (Gpt_ValueType)0;
         ecum_maxRunningTimeArray_aui16[indexCounter_ui8] =     (Gpt_ValueType)0;
         ecum_runTimer_as[indexCounter_ui8].callback  =          NULL_PTR;
         ecum_runTimer_as[indexCounter_ui8].callCycle_ui16 =    (uint16)0;
         ecum_runTimer_as[indexCounter_ui8].callTrigger_ui16 =  (uint16)0;
      }
#endif /* PROJECT_TIME_MEASUREMENT_SWITCH */

#if (PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH == STD_ON)
      /* initialise global variables for load measuring */
      ecum_loadStartValue_ui16 =    (Gpt_ValueType)0;
      ecum_loadEndValue_ui16 =      (Gpt_ValueType)0;
      ecum_loadMeasuringStarted_b = (boolean)FALSE;
      ecum_actLoad_ui16 =           (Gpt_ValueType)0;
      ecum_maxLoad_ui16 =           (Gpt_ValueType)0;
#endif /* PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH */
   }
}

/**
 * \brief Function to start the ECU Manager.
 *
 * Starts the ECUM module.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */
void Ecum_Start (void)
{
   /* ------ variables declaration ------ */

   /* --- init modul global variables --- */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */

   /* Development Error Detection */
#if(ECUM_DEV_ERROR_DETECTION == STD_ON)
   /* check if modul is initialized */
   if(ecum_moduleState_e != ECUM_INIT)
   {
      //Det_ReportError(ECUM_MODULE_ID,(uint8)ECUM_INSTANCE_ID,ECUM_START_API_ID,ECUM_E_PARAM_CONFIG);
   }
   else
#endif /* (ECUM_DEV_ERROR_DETECTION == STD_ON) */
   {
      /**************************** Mcu initialization *********************************/
      ISR_Set_PriorityLevel(); /*lint !e522: Highest operation, function 'ISR_Set_PriorityLevel', lacks side-effects -> direct writing to registers */

      /* initialize the MCU with 8 MHz oscillator */
      Mcu_Init ();
      /* initializing of the PORT module */
      Port_Init ();

      ecum_stateMachine_e = ECUM_STATE_STARTUP_PRE_OS;
   }
}

/**
 * \brief MainFunction of the ECU Manager.
 *
 * MainFunction of the ECUM module.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */
/**
\dot
digraph G {
ECUM_STATE_INIT -> ECUM_STATE_STARTUP_PRE_OS;
ECUM_STATE_STARTUP_PRE_OS -> ECUM_STATE_STARTUP_POST_OS;
ECUM_STATE_STARTUP_POST_OS -> ECUM_STATE_RUN;
ECUM_STATE_RUN -> ECUM_STATE_SLEEP;
ECUM_STATE_RUN -> ECUM_STATE_PRODUCTION;
ECUM_STATE_SLEEP -> ECUM_STATE_RUN;
ECUM_STATE_PRODUCTION -> ECUM_STATE_RUN;
ECUM_STATE_WAKEUP;
ECUM_STATE_SHUTDOWN;
ECUM_STATE_OFF;
}
\enddot
*/
void Ecum_MainFunction (void)
{
   /* ------ variables declaration ------ */
#if (ECUM_DEINIT_API == STD_ON)
   uint8 locCtr_ui8;
#endif
   uint8 ctr_ui8;

   /* --- init modul global variables --- */

   /* ----- init internal variables ----- */
#if (ECUM_DEINIT_API == STD_ON)
   locCtr_ui8 = (uint8) 0U;
#endif
   ctr_ui8 = (uint8) 0U;

   #if ((defined TEST_ERRORHANDLER_6_ECUM) && (TEST_ERRORHANDLER_6_ECUM == 1))
   ecum_stateMachine_e=5;
   #endif
   if(ecum_trigger_b == (boolean)TRUE)
   {
      ecum_trigger_b = (boolean)FALSE;
      for (ctr_ui8 = (uint8)0U; ctr_ui8 < usedNumOfMainFunc_ui8; ctr_ui8++) /*lint !e838: Previously assigned value to variable 'ctr_ui8' has not been used -> coding guidelines says that variables after declaration have to be initialized */
      {
         /* iterating through call time of all main functions */
   #if (PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON)
         /* reset the measured runtime value for the next cycle */
         ecum_actRunningTimeArray_aui16[ctr_ui8] = (Gpt_ValueType)0;
   #endif /* PROJECT_TIME_MEASUREMENT_SWITCH == STD_ON */
         if (ecum_runTimer_as[ctr_ui8].callCycle_ui16 != (uint16)0U)
         {
            /* callCycle_ui16 is not zero, normal case. Zero should never be reached! */
            if (ecum_runTimer_as[ctr_ui8].callCycle_ui16 == ecum_runTimer_as[ctr_ui8].callTrigger_ui16)
            {
               /* the main function should be called in this cycle, a bit is shifted in the mask, that indicates Ecum_CallFunctions() that the task is ready for running */
               ecum_triggerIndication_ui32 |= (uint32)((uint32)1U << ctr_ui8);
            }
            else
            {
               /* do nothing */
            }

            if (ecum_runTimer_as[ctr_ui8].callCycle_ui16 > (uint16)1U)
            {
               /* decrement value */
               ecum_runTimer_as[ctr_ui8].callCycle_ui16--;
            }
            else
            {
               /* callCycle_ui16 is 1, reset callCycle_ui16 */
               if (ecum_cfgMode_ps != NULL_PTR)
               {
                  ecum_runTimer_as[ctr_ui8].callCycle_ui16 = ecum_cfgMode_ps->mainFuncConfig_as[ctr_ui8].callCycle_ui16;
               }
               else
               {
                  /* point to NULL_PTR! */
   #if(ECUM_DEV_ERROR_DETECTION == STD_ON)
                  //Det_ReportError(ECUM_MODULE_ID, (uint8)ECUM_INSTANCE_ID, ECUM_TIMER_ISR_ID, ECUM_E_PARAM_POINTER);
   #endif
                  /* do nothing */
                  ;
               }
            }

         }
         else
         {
            /* callCycle_ui16 is zero, it's a special case! Function is called every cycle */
            ecum_triggerIndication_ui32 |= (uint32)((uint32)1U << ctr_ui8);
         }
      }
   }

   switch (ecum_stateMachine_e)
   {
      case ECUM_STATE_STARTUP_PRE_OS: /* Modul is in ECUM_STATE_INIT_BASIC_SW */
      {
         DISABLE_ALL_INTERRUPTS(); /*lint !e960 */
         /* Call the function pointer to the configured initialization functions of the other modules *
          * The modules will be initialized in the configured order, started at position zero.        */

         for (ctr_ui8 = (uint8) 0U; ctr_ui8 < ecum_initFunctionPtrSIZE_ui8; ctr_ui8++)
         {
            /* If development error detection is switched on, every pointer will be checked whether it is *
             * a NULL pointer or not. If this is the case, an error will be forwarded to the DET module.  */
#if (ECUM_DEV_ERROR_DETECTION == STD_ON)
            if(ecum_initFunctionPtr_apf[ctr_ui8] == NULL_PTR)
            {
               //Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_INIT_API_ID, ECUM_E_FNCT_PTR_NULL_PTR);
            }
            else
            {
               /* do nothing */
            }
#endif /* ECUM_DEV_ERROR_DETECT == STD_ON */
            ecum_initFunctionPtr_apf[ctr_ui8] ();
         }

         ENABLE_ALL_INTERRUPTS(); /*lint !e960 */

         /* Ecum_MainFunction: START OS */
         ecum_stateMachine_e = ECUM_STATE_STARTUP_POST_OS;

         break;
      }

      case ECUM_STATE_STARTUP_POST_OS: /* module is in post initialization */
      {
         Ecum_RunModeTransition();
         break;
      }

      case ECUM_STATE_RUN: /* module is in normal run mode */
      {
         /* Checks if runnable main functions are available and calls them */
         Ecum_CallFunctions();

         if (ecum_sleepRequested_b == (boolean) TRUE)
         {
            //Ecum_SleepModeTransition ();
         }
         break;
      }

      case ECUM_STATE_SLEEP:
      {
         /* *** ONLY REQUIRED FOR CLOCK ***
          * Watchdog is active in sleep mode for clock only
          * Therefore enable all trigger indications
          * Clock wakes up in sleep mode every second to update time and trigger watchdog
          * *** ONLY REQUIRED FOR CLOCK ***
          * */

         /* Checks if runnable main functions are available and calls them */
         Ecum_CallFunctions();

         /* fall asleep is allowed? */
         if (ecum_sleepFallASleepAllowed_b == (boolean)TRUE)
         {
            /* reset fall asleep allowed flag */
            ecum_sleepFallASleepAllowed_b = (boolean)FALSE;

            /* Enable LIN wakeup interrupt */
            DISABLE_ALL_INTERRUPTS(); /*lint !e960 */
            //Lin_EnableWakeupISR();
            ENABLE_ALL_INTERRUPTS(); /*lint !e960 */

            /** \req CS_REQ_BY634_5_000011   The controller enters MCU stop-mode after a LIN communication timeout (LIN_TIMEOUT). */
            /** \req CS_REQ_BY634_5_000012   The controller enters to MCU stop-mode if a broadcast command goto-sleep is received by LIN. */
            Mcu_SetStopMode();

            /* Disable LIN wakeup interrupt */
            DISABLE_ALL_INTERRUPTS(); /*lint !e960 */
            //Lin_DisableWakeupISR();
            ENABLE_ALL_INTERRUPTS(); /*lint !e960 */

            /* Inform application control we are up and running again */
            //Al_App_Ctrl_EcumWakeupIndication();
         }

         if ((boolean)TRUE == ecum_runRequested_b)
         {
            //ErrH_BehaviorAfterWakeup();
            //Ecum_RunModeTransition();
         }
         break;
      }

#if (ECUM_DEINIT_API == STD_ON)
      case ECUM_STATE_SHUTDOWN: /* Module is in ECUM_STATE_SHUTDOWN */
      {
         /* Call the function pointer to the configured deinitialization functions of the other modules *
          * The modules will be deinitialized in the configured order, started at position zero.        */
         for (locCtr_ui8 = (uint8) 0U; locCtr_ui8 < ecum_initialConfiguration_s.numberOfDeinitFncts_ui8; locCtr_ui8++)
         {
            /* If development error detection is switched on, every pointer will be checked whether it is *
             * a NULL pointer or not. If this is the case, an error will be forwarded to the DET module.  */
#if (ECUM_DEV_ERROR_DETECTION == STD_ON)
            if(ecum_initialConfiguration_s.deinitFnctPtr_papf[locCtr_ui8] == NULL_PTR)
            {
               Det_ReportError(ECUM_MODULE_ID, (uint8)ECUM_INSTANCE_ID, ECUM_MAIN_TASK_API_ID, ECUM_E_FNCT_PTR_NULL_PTR);
            }
            else
            {
               /* do nothing */
            }
#endif /* ECUM_DEV_ERROR_DETECT == STD_ON */

            ecum_initialConfiguration_s.deinitFnctPtr_papf[locCtr_ui8] ();
            /* Call function to notify an external module over the current deinitialization state */
            if (lcfgConfigPtr_ps->deinitStateNotification_pf != NULL_PTR )
            {
               lcfgConfigPtr_ps->deinitStateNotification_pf ();
            }
            else
            {
               ; /* do nothing */
            }
         }

         break;
      }
#endif /* ECUM_DEINIT_API */
      case (ECUM_STATE_INIT):
      case (ECUM_STATE_OFF):
      case (ECUM_STATE_ENUM_SIZE):
      default:
      {
#if(ECUM_DEV_ERROR_DETECTION == STD_ON)
         //Det_ReportError(ECUM_MODULE_ID, (uint8)ECUM_INSTANCE_ID, ECUM_MAIN_API_ID, ECUM_E_DEFAULT_ROUTE);
#endif /* ECUM_DEV_ERROR_DETECT == STD_ON */
         //ErrH_Errorhandling(ErrH_E_ECUM_STATE_ERROR);
         #if ((defined TEST_ERRORHANDLER_ENABLED) && (TEST_ERRORHANDLER_ENABLED == 1))
         ErrH_Errorhandlingtest(0);
         #endif
         break;
      }
   }
}


/**
 * \brief Callback function that is called from the GPT Module.
 *
 * Callback function that is called from the GPT Module to get the right timings.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void Ecum_RunTimerISR (void)
{
   /* ------ variables declaration ------ */

   /* --- init modul global variables --- */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
   /* Overload detection */
   if( ecum_triggerIndication_ui32 != (uint32)0 )
   {
#if (PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH == STD_ON)
      if( ecum_loadMeasuringStarted_b == (boolean)TRUE)
      {
         /* The load was not calculated yet, saving the overload value, should be around 1000 for 1ms timer */
         Gpt_GetTimeElapsed(&ecum_loadEndValue_ui16);
         /* No timer overflow occurred? */
         if(ecum_loadEndValue_ui16 >= ecum_loadStartValue_ui16)
         {
            /* calculate load for current cycle */
            ecum_actLoad_ui16 = ecum_loadEndValue_ui16 - ecum_loadStartValue_ui16;
         }
         else
         {
            /* Timer overflow! Calculate load for current cycle */
            ecum_actLoad_ui16 = ( (Gpt_ValueType)ECUM_TIMER_OVERFLOW_VALUE - ecum_loadStartValue_ui16) + ecum_loadEndValue_ui16;
         }
         /* new maximum reached? */
         if(ecum_actLoad_ui16 > ecum_maxLoad_ui16)
         {
            /* Saving maximum load value */
            ecum_maxLoad_ui16 = ecum_actLoad_ui16;
         }
         else
         {
            /* do nothing */
            ;
         }
      }
#endif /* PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH == STD_ON */
#if(ECUM_DEV_ERROR_DETECTION == STD_ON)
      //Det_ReportError(ECUM_MODULE_ID, (uint8)ECUM_INSTANCE_ID, ECUM_TIMER_ISR_ID, ECUM_E_OVERLOAD_DETECTED);
#endif /* ECUM_DEV_ERROR_DETECT == STD_ON */
   }
   else
   {
      /* no overload, do nothing, everything is ok */
      ;
   }

#if (PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH == STD_ON)
   /* start load measuring, the timer ISR is also measured! */
   Gpt_GetTimeElapsed(&ecum_loadStartValue_ui16);

   /* load measurement started */
   ecum_loadMeasuringStarted_b = (boolean)TRUE;
#endif /* PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH */

   /* signalling that a new cycle begins */
   ecum_trigger_b = (boolean)TRUE;
}
#pragma CODE_SEG DEFAULT

void Ecum_RequestSleepMode (void)
{
   ecum_sleepRequested_b = (boolean) TRUE;
   /* Reset opposite request to ensure proper behaviour -> ticket #221 */
   ecum_runRequested_b = (boolean) FALSE;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void Ecum_RequestRunMode (void)
{
   ecum_runRequested_b = (boolean) TRUE;
   /* Reset opposite request to ensure proper behaviour -> ticket #221 */
   ecum_sleepRequested_b = (boolean) FALSE;
}
#pragma CODE_SEG DEFAULT


#if (ECUM_DEINIT_API == STD_ON)
void Ecum_AlMotor_ShutdownModeChangeOkNotify (void)
{

}
#endif

void Ecum_FallASleepNotify (void)
{
   ecum_sleepFallASleepAllowed_b = (boolean) TRUE;
}

#if(TEST_UNITTEST_ACTIVE == 1)
/**
* \brief Returns value of ecum_maxLoad_ui16
*
* \param [in]  ---
* \param [out] ---
* \return      value of ecum_maxLoad_ui16
*/
uint16 Ecum_GetMaxLoad (void)
{
   return ecum_maxLoad_ui16;
}
#endif


#if(ECUM_VERSION_INFO_API == STD_ON)
/**
 * \brief This service returns the version information of this module .
 *
 * \param [in]  ---
 * \param [out] versioninfo = Pointer where the version is stored to
 *                            information of this module .
 * \return      ---
 */
void Ecum_GetVersionInfo (Std_VersionInfoType *versioninfo)
{
   /* ------ variables declaration ------ */

   /* --- init modul global variables --- */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
   if( versioninfo == NULL_PTR )
   {
#if(ECUM_DEV_ERROR_DETECTION == STD_ON)
         Det_ReportError(ECUM_MODULE_ID, (uint8)ECUM_INSTANCE_ID, ECUM_VERSIN_INFO_API_ID, ECUM_E_PARAM_POINTER);
#endif /* ECUM_DEV_ERROR_DETECT == STD_ON */
   }
   else
   {
      versioninfo->vendorID = (uint16)ECUM_VENDOR_ID;
      versioninfo->moduleID = (uint16)ECUM_MODULE_ID;
      versioninfo->instanceID = (uint8)ECUM_INSTANCE_ID;
      versioninfo->sw_major_version = (uint8)ECUM_SW_MAJOR_VERSION;
      versioninfo->sw_minor_version = (uint8)ECUM_SW_MINOR_VERSION;
      versioninfo->sw_patch_version = (uint8)ECUM_SW_PATCH_VERSION;
   }
}
#endif /* ECUM_VERSION_INFO_API == STD_ON */
