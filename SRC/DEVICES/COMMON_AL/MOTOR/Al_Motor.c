#include "Version.h"

#include "Al_Motor_PBcfg.h"
#include "Al_Motor.h"
#include "Al_Motor_Cfg.h"
#include "Cdd_Motor.h"
#include "Cdd_Motor_Cfg.h"
#include "EcuM.h"

#if (AL_MOTOR_DEV_ERROR_DETECT == STD_ON)
//#include "Det.h"
#endif

/* ***************************** # defines ********************************** */
#define AL_MOTOR_VENDOR_ID_C        99 /**<\brief CoSyst VendorID */
#define AL_MOTOR_AR_MAJOR_VERSION_C 3  /**<\brief AUTOSAR major version */
#define AL_MOTOR_AR_MINOR_VERSION_C 1  /**<\brief AUTOSAR minor version */
#define AL_MOTOR_AR_PATCH_VERSION_C 0  /**<\brief AUTOSAR patch version */
#define AL_MOTOR_SW_MAJOR_VERSION_C 1  /**<\brief SW major version */
#define AL_MOTOR_SW_MINOR_VERSION_C 0  /**<\brief SW minor version */
#define AL_MOTOR_SW_PATCH_VERSION_C 0  /**<\brief SW patch version */
#define AL_MOTOR_INSTANCE_ID_C      1  /**<\brief Instance id */

/* version check */
#if(AL_MOTOR_VENDOR_ID_C != AL_MOTOR_VENDOR_ID)
#error "Al_Motor.c and Al_Motor.h have different vendor ids."
#endif /* AL_MOTOR_VENDOR_ID_C != AL_MOTOR_VENDOR_ID */

#if((AL_MOTOR_AR_MAJOR_VERSION_C != AL_MOTOR_AR_MAJOR_VERSION) || \
    (AL_MOTOR_AR_MINOR_VERSION_C != AL_MOTOR_AR_MINOR_VERSION) || \
    (AL_MOTOR_AR_PATCH_VERSION_C != AL_MOTOR_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Al_Motor.c and Al_Motor.h are different."
#endif   /* (AL_MOTOR_AR_MAJOR_VERSION_C != AL_MOTOR_AR_MAJOR_VERSION) || ... */

#if((AL_MOTOR_SW_MAJOR_VERSION_C != AL_MOTOR_SW_MAJOR_VERSION) || \
    (AL_MOTOR_SW_MINOR_VERSION_C != AL_MOTOR_SW_MINOR_VERSION) || \
    (AL_MOTOR_SW_PATCH_VERSION_C != AL_MOTOR_SW_PATCH_VERSION))
#error "Software Version Numbers of Al_Motor.c and Al_Motor.h are different."
#endif /* (AL_MOTOR_SW_MAJOR_VERSION_C != AL_MOTOR_SW_MAJOR_VERSION) || ... */

#define AL_MOTOR_CRITICAL_ENV_NORMAL             0x00u
#define AL_MOTOR_CRITICAL_SET_VOLTAGE_FLAG       0x01u
#define AL_MOTOR_CRITICAL_SET_TEMPERATURE_FLAG   0x02u
#define AL_MOTOR_CRITICAL_RESET_VOLTAGE_FLAG     AL_MOTOR_CRITICAL_SET_TEMPERATURE_FLAG
#define AL_MOTOR_CRITICAL_RESET_TEMPERATURE_FLAG AL_MOTOR_CRITICAL_SET_VOLTAGE_FLAG

/* ***************************** module data ************************** */

#if (AL_MOTOR_MODULE_STATE_API == STD_ON)
static volatile Std_ModuleStatusReturnType al_motor_moduleState_e = MODULE_UNINIT;
#endif

static Al_Motor_OperationStateEnum al_motor_opState_e = AL_MOTOR_OPSTATE_UNDEF;
//static Al_Motor_OperationSubStateCalibEnum al_motor_opSubStateCalib_e = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
static Al_Motor_OperationSubStateCalibEnum al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_NR_SIZE] = { AL_MOTOR_OPSUBSTATE_CALIB_UNDEF };


static Al_Motor_OperationSubStateStelltestEnum al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_UNDEF;


static uint16 al_motor_event_e = (uint16)AL_MOTOR_EVENT_UNDEF;

static volatile uint8 al_motor_calibrationDone_ui8 = (uint8) FALSE;

/**
 * When the calibration is triggered from Production Mode, the state machine
 * usually continues with a transition to the run mode or sleep mode, depending
 * on an existing run mode request.
 * By setting this flag to TRUE, the state machine continues in production mode
 * after re-calibration. */
static uint8 al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_FALSE;

/* STELLGLIEDTEST ***************************************************** */
static Al_Motor_Event_StellTestEnum al_motor_eventStellTestReq_e = AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF;
static Al_Motor_Event_StellTestEnum al_motor_resultStellTestComplete_e = AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF;

/* ******************************************************************** */

/* EEPROM configurations */
static const uint8 *al_motor_EEresetDirection_pui8;

/** Critical environment flags */
static uint8 al_motor_criticalEnvironment_ui8 = AL_MOTOR_CRITICAL_ENV_NORMAL;

#if (SYSTEM_BUILD_TYPE == SYSTEM_BUILD_TYPE_DEBUG)
static uint8 al_motor_INJECT_ENABLE_ui8 = (uint8) FALSE;
static uint8 al_motor_INJECT_NORMALTEMP_EVT_ui8 = (uint8) FALSE;
static uint8 al_motor_INJECT_OVERTEMP_EVT_ui8 = (uint8) FALSE;
static uint8 al_motor_INJECT_NORMALVOLT_EVT_ui8 = (uint8) FALSE;
static uint8 al_motor_INJECT_UNDERVOLT_EVT_ui8 = (uint8) FALSE;
static uint8 al_motor_INJECT_OVERVOLT_EVT_ui8 = (uint8) FALSE;
#endif

/* ***************************** module function definitions ********** */
static Cdd_Motor_DirectionEnum Al_Motor_GetResetDirection (Cdd_Motor_MotorNumberEnum motor_e, const uint32 usedHalfRound_ui32);

static void Al_Motor_CalibrationStateMgmt (Cdd_Motor_MotorNumberEnum motor_e);

static void Al_Motor_StellgliedtestStateMgmt (Cdd_Motor_MotorNumberEnum motor_e);

static void Al_Motor_RunStateMgmt (Cdd_Motor_MotorNumberEnum motor_e);

static void Al_Motor_SleepStateMgmt (Cdd_Motor_MotorNumberEnum motor_e);

static void Al_Motor_RunModeTransition (void);

static void Al_Motor_SleepModePrepareTransition (void);

static void Al_Motor_SleepModeTransition (void);

static void Al_Motor_ProductionModeRequestTransition (void);

static void Al_Motor_ProductionModeTransition (void);

static void Al_Motor_StellgliedtestModeTransition (void);

static void Al_Motor_CriticalStateTransition (void);


#if (AL_MOTOR_DEINIT_API == STD_ON)
static void Al_Motor_ShutdownTransition (void);
#endif


static uint32 uSteps_ui32 = 0;

/* ***************************** external global data ************************* */


/* ***************************** global data ******************************** */


/* ***************************** module functions ********************* */
/**
 *  \brief Internal function to return the configured reset direction
 *
 * \param [in]
 * \param [out]
 * \return      CDD_MOTOR_DIR_FORWARD
 *              CDD_MOTOR_DIR_BACKWARD
 */
static Cdd_Motor_DirectionEnum Al_Motor_GetResetDirection (Cdd_Motor_MotorNumberEnum motor_e, const uint32 usedHalfRound_ui32)
{
   Cdd_Motor_DirectionEnum retDir_e;

   if (*al_motor_EEresetDirection_pui8 == AL_MOTOR_RESET_DIRECTION_CLOCKWISE)
   {
      retDir_e = CDD_MOTOR_DIR_FORWARD;
   }
   else if (*al_motor_EEresetDirection_pui8 == AL_MOTOR_RESET_DIRECTION_COUNTER_CLOCKWISE)
   {
      retDir_e = CDD_MOTOR_DIR_BACKWARD;
   }
   else /* AL_MOTOR_RESET_DIRECTION_SHORTEST */
   {
      uint32 currentPos_ui32;

      currentPos_ui32 = Cdd_Motor_GetPositionCurrentUsed(motor_e);

      /* Check direction for shortest way to TOP position */
      if (currentPos_ui32 < usedHalfRound_ui32)
      {
         /* Set drive direction clockwise */
         retDir_e = CDD_MOTOR_DIR_BACKWARD;
      }
      else
      {
         /* Set drive direction counter clockwise */
         retDir_e = CDD_MOTOR_DIR_FORWARD;
      }
   }

   return retDir_e;
}

/**
 *  \brief Function to calibrate pointers
 *
 *  \req #CS_REQ_000040 - At startup, the software shall execute a "pointer initialization"
 *
 *  \param [in]  motor_e
 *  \param [out] ---
 *  \return      ---
 */
static void Al_Motor_CalibrationStateMgmt (Cdd_Motor_MotorNumberEnum motor_e)
{
   uint32 currentPos_ui32;
   switch (al_motor_opSubStateCalib_e[motor_e])
   {
      case AL_MOTOR_OPSUBSTATE_CALIB_START:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
            //Cdd_Motor_ZD_CalibrateZeroToActivePosition(motor_e);
            //Cdd_Motor_RunToPositionAbsolute(motor_e, (uint32) 0uL);
            //Cdd_Motor_RunDistance(motor_e, CDD_MOTOR_DIR_BACKWARD, AL_MOTOR_STATECALIB_FIRSTBACK_UI16, (uint8) 0u);

            /* Next level */
            //al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_FIRST_REWARD;
        	al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_FINISHED;
         }
         else
         {
            /* do nothing */
         }

         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_FIRST_REWARD:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
             /* Wenn Zero Point Detect bei Position 0/0 schon an ist,
              * ein St�ck zur�ckfahren um den Zero Detect Bereich voll zu erfassen */
            if (Cdd_Motor_ZD_IsCurrentPositionInZeroWindow(motor_e) == (uint8)TRUE)
            {
               Cdd_Motor_RunDistanceFullSteps(motor_e, (uint16) 2u);

               /* Next level ^^ �o� */
               al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_SECOND_REWARD;
            }
            else
            {
//               Cdd_Motor_ZD_CalibrateZeroToActivePosition ();
               Cdd_Motor_ZD_EnableDetection (motor_e);
               Cdd_Motor_SetDirectionReq(motor_e, CDD_MOTOR_DIR_FORWARD);
               Cdd_Motor_RunDistanceFullSteps (motor_e, AL_MOTOR_STATECALIB_FIRSTFWD_UI16);
               al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_SEARCH_ZERO;
               Cdd_Motor_ZD_DeleteResult (motor_e);
            }
         }
         else
         {
            /* do nothing */
         }

         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_SECOND_REWARD:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
            Cdd_Motor_ZD_EnableDetection (motor_e);
            Cdd_Motor_SetDirectionReq(motor_e, CDD_MOTOR_DIR_FORWARD);
            Cdd_Motor_RunDistanceFullSteps (motor_e, (sint16)(AL_MOTOR_STATECALIB_FIRSTFWD_UI16));

            /* Next level ^^ �o� */
            al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_SEARCH_ZERO;
         }
         else
         {
            ; /* do nothing */
         }
         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_SEARCH_ZERO:
      {
         if (Cdd_Motor_ZD_IsDetectionCompleteAndValid(motor_e) == (uint8)TRUE)
         {
            Cdd_Motor_ZD_DisableDetection (motor_e);

            /* Drive to next full step position */
            Cdd_Motor_RunToNextFullStep (motor_e);

            /* Next level ^^ �o� */
            al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_ZERO_WINDOW_DETECTED;
         }
         /* Motor runs till position 45 with first command, so should be enough from point of timing */
         else
         {
            currentPos_ui32 = Cdd_Motor_GetFullStepPositionAbsolute(motor_e);
            if ((currentPos_ui32 > AL_MOTOR_STATECALIB_ENDPOS) &&
                     currentPos_ui32 <= AL_MOTOR_STATECALIB_FIRSTCP_UI16)
            {
               Cdd_Motor_RunToPosition(motor_e, (uint32) AL_MOTOR_STATECALIB_ENDPOS * (uint32)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);
            }
            else
            {
               ; /* do nothing */
            }
         }


         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_ZERO_WINDOW_DETECTED:
      {
         /* go back to zero position if current end position reached */
         if (Cdd_Motor_ReachedFinalPosition(motor_e) == (uint8)TRUE)
         {
            if (Cdd_Motor_GetFullStepPositionAbsolute(motor_e) > CDD_MOTOR_RNDS_THRSH_HALF_UI16)
            {
               Cdd_Motor_SetDirectionReq(motor_e, CDD_MOTOR_DIR_FORWARD);
            }
            else
            {
               Cdd_Motor_SetDirectionReq(motor_e, CDD_MOTOR_DIR_BACKWARD);
            }
            Cdd_Motor_RunToPosition (motor_e, ((uint32)CDD_MOTOR_RNDS_THRSH_UI16 - (uint32) 1uL) * (uint32)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);

            /* Next level ^^ �o� */
            al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_ZERO_POS_REACHED;
         }
         else
         {
            ; /* wait to reach full step position */
         }

         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_ZERO_POS_REACHED:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
            Cdd_Motor_SetDirectionReq(motor_e, CDD_MOTOR_DIR_FORWARD);
            Cdd_Motor_RunToPosition (motor_e, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);

            /* Next level ^^ �o� */
            al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_FINALLY_FWD;
         }
         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_FINALLY_FWD:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
            /* Next level ^^ �o� */
        	 al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_FINISHED;
         }
         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_FINISHED:
      {
         /* FINISH - await calibration end */
         asm(nop); /*lint !e960 */
         break;
      }

      case AL_MOTOR_OPSUBSTATE_CALIB_UNDEF:
      default:
      {
         /* DET ERROR could be triggered here if enabled */
         /* This may not happen - however back to start */
    	  al_motor_opSubStateCalib_e[motor_e] = AL_MOTOR_OPSUBSTATE_CALIB_START;

         break;
      }
   }
}


/**
 * \brief State management for Stellgliedtest
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */
static void Al_Motor_StellgliedtestStateMgmt (Cdd_Motor_MotorNumberEnum motor_e)
{
   uint16 targetPos_ui16 = (uint16) 0u;
   uint16 maximumFS_ui16 = 0u;

   /** \req CS_REQ_BY634_5_000301 The device's analogue pointer moves directly the shortest way to the TOP position. */
   /** \req CS_REQ_BY634_5_000374  */
   /** \req CS_REQ_BY634_5_000375  */
   /** \req CS_REQ_BY634_5_000378 The device's analogue pointer (dial for compass) moves the defined way (shortest way/clockwise/counter-clockwise) back to TOP position. */

   switch (al_motor_stellgliedtestState_e)
   {
      case AL_MOTOR_OPSUBSTATE_STELLTEST_IDLE:
      {
         /* Get maximum number of fullsteps */
         maximumFS_ui16 = (uint16)Cdd_Motor_GetMaximumFullStepUsed(motor_e) / CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE;

         /* Handle incoming requests */
         if ((al_motor_eventStellTestReq_e & AL_MOTOR_EVENT_STELLTEST_REQ_TOP) != AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF) /*lint !e655 !e9029 !e9027 */
         {
            Cdd_Motor_DirectionEnum resetDir_e;
            uint32 usedHalfRound_ui32;

            /* delete requested event */
            al_motor_eventStellTestReq_e &= (~((uint16)AL_MOTOR_EVENT_STELLTEST_REQ_TOP)); /*lint !e641, !e64 !e9029 !e9027 !e9034 */
            /* define next state */
            al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_TOP;

            /* perform state transition */
            /* Determine movement direction */
            usedHalfRound_ui32 = ((uint32) Cdd_Motor_GetMaximumFullStepUsed (motor_e) / (uint32) 2uL);
            resetDir_e = Al_Motor_GetResetDirection (motor_e, usedHalfRound_ui32);
            Cdd_Motor_SetDirectionReq(motor_e, resetDir_e);

            /* drive pointer to TOP position */
            Cdd_Motor_RunToFullStepPosition (motor_e, (uint16)AL_MOTOR_STELLTEST_POSITION_TOP);
         }
         else if ((al_motor_eventStellTestReq_e & AL_MOTOR_EVENT_STELLTEST_REQ_TOP_LEFT) != AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF) /*lint !e655 !e9029 !e9027  */
         {
            /* delete requested event */
            al_motor_eventStellTestReq_e &= (~AL_MOTOR_EVENT_STELLTEST_REQ_TOP_LEFT); /*lint !e641, !e64 !e9029 !e9027 !e9034 */
            /* define next state */
            al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_TOP_LEFT;

            /* perform state transition */
            /* determine TOP LEFT position */
#if (AL_MOTOR_STELLTEST_POSITION_TOP < AL_MOTOR_STELLTEST_POSITION_TOP_LEFT_DELTA)
            targetPos_ui16 = (uint16)(maximumFS_ui16 - (uint16)AL_MOTOR_STELLTEST_POSITION_TOP_LEFT_DELTA);
#else
            targetPos_ui16 = (uint16)AL_MOTOR_STELLTEST_POSITION_TOP - (uint16)AL_MOTOR_STELLTEST_POSITION_TOP_LEFT_DELTA;
#endif

            /* Set drive direction counter clockwise */
            Cdd_Motor_SetDirectionReq (motor_e, CDD_MOTOR_DIR_BACKWARD);

            /* drive to TOP LEFT position */
            Cdd_Motor_RunToFullStepPosition (motor_e, targetPos_ui16);
         }
         else if ((al_motor_eventStellTestReq_e & AL_MOTOR_EVENT_STELLTEST_REQ_TOP_RIGHT) != AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF) /*lint !e655 !e9029 !e9027 */
         {
            /* delete requested event */
            al_motor_eventStellTestReq_e &= (~AL_MOTOR_EVENT_STELLTEST_REQ_TOP_RIGHT); /*lint !e641, !e64 !e9027 !e9034*/
            /* define next state */
            al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_TOP_RIGHT;

            /* perform state transition */
            /* determine TOP LEFT position */
            targetPos_ui16 = (uint16)AL_MOTOR_STELLTEST_POSITION_TOP + (uint16)AL_MOTOR_STELLTEST_POSITION_TOP_RIGHT_DELTA;
            if (targetPos_ui16 >= maximumFS_ui16)
            {
               targetPos_ui16 -= maximumFS_ui16;
            }
            else
            {
               ; /* do nothing */
            }

            /* Set drive direction counter clockwise */
            Cdd_Motor_SetDirectionReq (motor_e, CDD_MOTOR_DIR_FORWARD);

            /* drive pointer to TOP RIGHT position */
            Cdd_Motor_RunToFullStepPosition (motor_e, targetPos_ui16);
         }
         else
         {
            /* delete all illegal events */
            al_motor_eventStellTestReq_e &= (~(AL_MOTOR_EVENT_STELLTEST_REQ_TOP | AL_MOTOR_EVENT_STELLTEST_REQ_TOP_LEFT
                     | AL_MOTOR_EVENT_STELLTEST_REQ_TOP_RIGHT)); /*lint !e655, !e641, !e64 !e9027 !e9029 !e9034 */

            /* nothing else to do */
         }

         break;
      }

      case AL_MOTOR_OPSUBSTATE_STELLTEST_TOP:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
            /* define next state */
            al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_IDLE;
            /* set result marker */
            al_motor_resultStellTestComplete_e |= AL_MOTOR_EVENT_STELLTEST_REQ_TOP; /*lint !e655 !e9027*/
         }
         break;
      }
      case AL_MOTOR_OPSUBSTATE_STELLTEST_TOP_LEFT:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
            /* define next state */
            al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_IDLE;
            /* set result marker */
            al_motor_resultStellTestComplete_e |= AL_MOTOR_EVENT_STELLTEST_REQ_TOP_LEFT; /*lint !e655 !e9027*/
         }
         break;
      }
      case AL_MOTOR_OPSUBSTATE_STELLTEST_TOP_RIGHT:
      {
         if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8)TRUE)
         {
            /* define next state */
            al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_IDLE;
            /* set result marker */
            al_motor_resultStellTestComplete_e |= AL_MOTOR_EVENT_STELLTEST_REQ_TOP_RIGHT; /*lint !e655 !e9027*/
         }
         break;
      }

      case AL_MOTOR_OPSUBSTATE_STELLTEST_UNDEF:
      case AL_MOTOR_OPSUBSTATE_STELLTEST_SIZE:
      default:
      {
         /* Back to start */
         al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_IDLE;

         break;
      }
   }
}

static void Al_Motor_RunStateMgmt (Cdd_Motor_MotorNumberEnum motor_e)
{
   uint32 uSteps_ui32 = (uint32) 0uL;
   boolean newPosition_b = FALSE;
   Cdd_Motor_DirectionEnum dir_e = CDD_MOTOR_DIR_FORWARD;

   /* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */
   DISABLE_ALL_INTERRUPTS(); /*lint !e960 */
   
   newPosition_b = Al_MotorPos_Calculate (motor_e, &dir_e, &uSteps_ui32);
   /* set direction and new target position */
   if (newPosition_b == (boolean)TRUE)
   {
	  Cdd_Motor_SetSpeedFac(motor_e, CDD_MOTOR_SPEED_270DEG);
	  Cdd_Motor_SetDirectionReq (motor_e, dir_e);
      Cdd_Motor_RunToPosition (motor_e, uSteps_ui32);
   }
   else
   {
      ; /* do nothing */
   }

   ENABLE_ALL_INTERRUPTS(); /*lint !e960 */
   /* END OF UNINTERRUPTABLE SEQUENCE *************************************** */
}


/**
 *  \brief Function configure the motor for the Sleep State
 *
 */
static void Al_Motor_SleepStateMgmt (Cdd_Motor_MotorNumberEnum motor_e)
{
#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
   uint32 targetPos_ui32 = (uint32) 0uL;
   boolean newPosition_b;
   Cdd_Motor_DirectionEnum dir_e = CDD_MOTOR_DIR_FORWARD;

   /* Calculate direction and new target position */
   //newPosition_b = Al_MotorPos_CalculateSleep (motor_e, &dir_e, &targetPos_ui32);

   if (newPosition_b == (boolean)TRUE)
   {
      Cdd_Motor_SetDirectionReq (motor_e, dir_e);
      Cdd_Motor_RunToPosition (motor_e, targetPos_ui32);
   }
#endif

   if (Cdd_Motor_ReachedFinalPosition (motor_e) == (uint8) TRUE) /*lint !e9007 */
   {
      if (Cdd_Motor_GetUStepPosition (motor_e) == (uint8)0u)
      {
         Cdd_Motor_StopPWM (motor_e);

         if ((al_motor_event_e & (uint16) AL_MOTOR_EVENT_SLEEPMODE_REQUEST) == (uint16) AL_MOTOR_EVENT_SLEEPMODE_REQUEST)
         {
            /* Delete event */
            al_motor_event_e &= (~((uint16) AL_MOTOR_EVENT_SLEEPMODE_REQUEST));
            /* Acknowledge sleep request */
            //Al_App_Ctrl_SleepModeChangeAllowedResponse (AL_APP_CTRL_APP_MOTOR);
         }
      }
      else
      {
         /*  && (Cdd_Motor_GetPartStepPosition () == (uint8) 0u) */
         uint32 currentPos_ui32;

         Cdd_Motor_SetDirectionReq (motor_e, CDD_MOTOR_DIR_FORWARD);
         currentPos_ui32 = Cdd_Motor_GetPositionCurrentUsed (motor_e);
         Cdd_Motor_RunToPosition (motor_e, currentPos_ui32);
      }
   }
   else
   {
      ; /* wait for reaching final position */
   }
}


/**
 *  \brief Function configure the motor for the Calibration State
 *
 */
void Al_Motor_CalibrationModeTransition (void)
{
   /* Reset calibration mode */
   al_motor_calibrationDone_ui8 = (uint8) FALSE;


#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
   
#else   
//HHSS
   (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_CALIBRATION);

   /* Change full step counter mode to absolute positioning */
   Cdd_Motor_ChangeDefaultFullStepCounter (CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_CALIBRATION);

   /* MVH: YES this is correct!
    * Zero detection has to be disabled first, will be enabled during calibration drive */
   Cdd_Motor_ZD_DisableDetection (CDD_MOTOR_MTR_HHSS);

   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_CALIBRATION);

   if (Cdd_Motor_GetPartStepPosition(CDD_MOTOR_MTR_HHSS) != (uint8)0U)
   {
      Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_BACKWARD);
      Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_HHSS);
   }
   
   al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] = AL_MOTOR_OPSUBSTATE_CALIB_START;
   
//MM
   (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_CALIBRATION);

   /* Change full step counter mode to absolute positioning */
   Cdd_Motor_ChangeDefaultFullStepCounter (CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_CALIBRATION);

   /* MVH: YES this is correct!
    * Zero detection has to be disabled first, will be enabled during calibration drive */
   Cdd_Motor_ZD_DisableDetection (CDD_MOTOR_MTR_MM);

   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_CALIBRATION);

   if (Cdd_Motor_GetPartStepPosition(CDD_MOTOR_MTR_MM) != (uint8)0U)
   {
      Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_BACKWARD);
      Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_MM);
   }
 
   al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] = AL_MOTOR_OPSUBSTATE_CALIB_START;

#endif

   al_motor_opState_e = AL_MOTOR_OPSTATE_CALIBRATION;
   
}


/**
 *  \brief Function configure the motor for the Run State
 *
 */
static void Al_Motor_RunModeTransition (void)
{
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
	//HHSS	
	   if (al_motor_criticalEnvironment_ui8 == AL_MOTOR_CRITICAL_ENV_NORMAL)
	   {
	      /* Change full step counter mode to absolute positioning */
	      Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_RUN);

	      /* Change request will start on next second tick */
	      Cdd_Motor_ZD_EnableDetection(CDD_MOTOR_MTR_HHSS);

	      Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_RUN);

	#if (DEVICE_TYPE == DEVICE_OAT)
	      /** \req CS_REQ_BY634_5_000185   "[GAU_INACTIVE] The OAT's pointer stays at top position" */
	      Al_Motor_ResetSignals();
	#elif (DEVICE_TYPE == DEVICE_STOPWATCH)
	      /** \req CS_REQ_BY634_5_000094   "[GAU_ACTIVE ; INIT] The stopwatch's analogue pointer moves to the top 60/0 s position, if not already there." */
	      al_motor_opSubStateRun_e = AL_MOTOR_OPSUBSTATE_RUN_INIT;
	#endif

	      (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_RUN);
	      al_motor_opState_e = AL_MOTOR_OPSTATE_RUN;
	   }
	   else
	   {
	      Al_Motor_CriticalStateTransition ();
	   }
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
   //MM   
	  if (al_motor_criticalEnvironment_ui8 == AL_MOTOR_CRITICAL_ENV_NORMAL)
	  {
		 /* Change full step counter mode to absolute positioning */
		 Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_RUN);

		 /* Change request will start on next second tick */
		 Cdd_Motor_ZD_EnableDetection(CDD_MOTOR_MTR_MM);

		 Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_RUN);

   #if (DEVICE_TYPE == DEVICE_OAT)
		 /** \req CS_REQ_BY634_5_000185   "[GAU_INACTIVE] The OAT's pointer stays at top position" */
		 Al_Motor_ResetSignals();
   #elif (DEVICE_TYPE == DEVICE_STOPWATCH)
		 /** \req CS_REQ_BY634_5_000094   "[GAU_ACTIVE ; INIT] The stopwatch's analogue pointer moves to the top 60/0 s position, if not already there." */
		 al_motor_opSubStateRun_e = AL_MOTOR_OPSUBSTATE_RUN_INIT;
   #endif

		 (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_RUN);
		 al_motor_opState_e = AL_MOTOR_OPSTATE_RUN;
	  }
	  else
	  {
		 Al_Motor_CriticalStateTransition ();
	  }

#else
	//HHSS	
	   if (al_motor_criticalEnvironment_ui8 == AL_MOTOR_CRITICAL_ENV_NORMAL)
	   {
		  /* Change full step counter mode to absolute positioning */
		  Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_RUN);
	
		  /* Change request will start on next second tick */
		  Cdd_Motor_ZD_EnableDetection(CDD_MOTOR_MTR_HHSS);
	
		  Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_RUN);
	
		  (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_RUN);
		  al_motor_opState_e = AL_MOTOR_OPSTATE_RUN;
	   }
	   else
	   {
		  Al_Motor_CriticalStateTransition ();
	   }
	   
	//MM   
	   if (al_motor_criticalEnvironment_ui8 == AL_MOTOR_CRITICAL_ENV_NORMAL)
	   {
		  /* Change full step counter mode to absolute positioning */
		  Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_RUN);
	
		  /* Change request will start on next second tick */
		  Cdd_Motor_ZD_EnableDetection(CDD_MOTOR_MTR_MM);
	
		  Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_RUN);
	
		  (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_RUN);
		  al_motor_opState_e = AL_MOTOR_OPSTATE_RUN;
	   }
	   else
	   {
		  Al_Motor_CriticalStateTransition ();
	   }

#endif
   
   //Al_App_Ctrl_RunModeChangeAllowedResponse(AL_APP_CTRL_APP_MOTOR);
}


/**
 *  \brief Function configure the motor for the Sleep Mode
 *
 */
static void Al_Motor_SleepModePrepareTransition (void)
{
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
	//HHSS	
		#if ((DEVICE_TYPE != DEVICE_CENTRAL_DISPLAY))
		   Cdd_Motor_DirectionEnum resetDir_e;
		   uint32 usedHalfRound_ui32;
		
		   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_RUN);
		
		   /* perform state transition */
		   /* Determine movement direction */
		   usedHalfRound_ui32 = ((uint32)Cdd_Motor_GetMaximumFullStepUsed(CDD_MOTOR_MTR_HHSS) / (uint32) 2uL);
		   resetDir_e = Al_Motor_GetResetDirection(CDD_MOTOR_MTR_HHSS, usedHalfRound_ui32);
		   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, resetDir_e);
		   Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_HHSS, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
		
		#if (DEVICE_TYPE == DEVICE_STOPWATCH)
		   /* Stop timer to prevent timer event callbacks during sleep mode */
		   //Cdd_FakePrtc_StopTimer();
		#endif
		#endif
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
	//MM
		#if ((DEVICE_TYPE != DEVICE_CENTRAL_DISPLAY))
		   Cdd_Motor_DirectionEnum resetDir_e;
		   uint32 usedHalfRound_ui32;
		
		   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_RUN);
		
		   /* perform state transition */
		   /* Determine movement direction */
		   usedHalfRound_ui32 = ((uint32)Cdd_Motor_GetMaximumFullStepUsed(CDD_MOTOR_MTR_MM) / (uint32) 2uL);
		   resetDir_e = Al_Motor_GetResetDirection(CDD_MOTOR_MTR_MM, usedHalfRound_ui32);
		   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, resetDir_e);
		   Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_MM, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
		
		#if (DEVICE_TYPE == DEVICE_STOPWATCH)
		   /* Stop timer to prevent timer event callbacks during sleep mode */
		   //Cdd_FakePrtc_StopTimer();
		#endif
		#endif
#else
	//HHSS	
		#if ((DEVICE_TYPE != DEVICE_CENTRAL_DISPLAY))
		   Cdd_Motor_DirectionEnum resetDir_e;
		   uint32 usedHalfRound_ui32;
		
		   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_RUN);
		
		   /* perform state transition */
		   /* Determine movement direction */
		   usedHalfRound_ui32 = ((uint32)Cdd_Motor_GetMaximumFullStepUsed(CDD_MOTOR_MTR_HHSS) / (uint32) 2uL);
		   resetDir_e = Al_Motor_GetResetDirection(CDD_MOTOR_MTR_HHSS, usedHalfRound_ui32);
		   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, resetDir_e);
		   Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_HHSS, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
		#endif
		  
	//MM
		#if ((DEVICE_TYPE != DEVICE_CENTRAL_DISPLAY))
		   Cdd_Motor_DirectionEnum resetDir_e;
		   uint32 usedHalfRound_ui32;
		
		   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_RUN);
		
		   /* perform state transition */
		   /* Determine movement direction */
		   usedHalfRound_ui32 = ((uint32)Cdd_Motor_GetMaximumFullStepUsed(CDD_MOTOR_MTR_MM) / (uint32) 2uL);
		   resetDir_e = Al_Motor_GetResetDirection(CDD_MOTOR_MTR_MM, usedHalfRound_ui32);
		   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, resetDir_e);
		   Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_MM, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
		
		#if (DEVICE_TYPE == DEVICE_STOPWATCH)
		   /* Stop timer to prevent timer event callbacks during sleep mode */
		   //Cdd_FakePrtc_StopTimer();
		#endif
		#endif

#endif
	   
   al_motor_opState_e = AL_MOTOR_OPSTATE_SLEEP_PREPARE;
}


/**
 *  \brief Function configure the motor for the Sleep Mode
 *
 */
static void Al_Motor_SleepModeTransition (void)
{
	
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
//HHSS	
   /* Change full step counter mode to absolute positioning */
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_SLEEP);

   Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_HHSS);

   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_SLEEP);
   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);

   (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_SLEEP);
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
//MM
  /* Change full step counter mode to absolute positioning */
  Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_SLEEP);

  Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_MM);

  Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_SLEEP);
  Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);

  (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_SLEEP);	
#else
//HHSS	
   /* Change full step counter mode to absolute positioning */
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_SLEEP);

   Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_HHSS);

   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_SLEEP);
   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);

   (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_SLEEP);

//MM
   /* Change full step counter mode to absolute positioning */
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_SLEEP);

   Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_MM);

   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_SLEEP);
   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);

   (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_SLEEP);

#endif
   
   al_motor_opState_e = AL_MOTOR_OPSTATE_SLEEP;
}


/**
 *  \brief Function configure the motor for the Production Mode
 *
 */
static void Al_Motor_ProductionModeRequestTransition (void)
{
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
//HHSS	
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_PRODUCTION_REQUEST);

   /* If not at a stable fullstep position, drive the pointers to next fullstep position */
   if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_HHSS) != (uint8)0U)
   {
	  /* Only in clockwise direction the virtual position equals the physical position */
	  Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
	  Cdd_Motor_RunToNextFullStep(CDD_MOTOR_MTR_HHSS);
   }
   else
   {
	  /* Already at a fullstep position, nothing to do */
   }

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
   //MM
      Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_PRODUCTION_REQUEST);

      /* If not at a stable fullstep position, drive the pointers to next fullstep position */
      if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_MM) != (uint8)0U)
      {
         /* Only in clockwise direction the virtual position equals the physical position */
         Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
         Cdd_Motor_RunToNextFullStep(CDD_MOTOR_MTR_MM);
      }
      else
      {
         /* Already at a fullstep position, nothing to do */
      }
	
#else
//HHSS	
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_PRODUCTION_REQUEST);

   /* If not at a stable fullstep position, drive the pointers to next fullstep position */
   if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_HHSS) != (uint8)0U)
   {
      /* Only in clockwise direction the virtual position equals the physical position */
      Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
      Cdd_Motor_RunToNextFullStep(CDD_MOTOR_MTR_HHSS);
   }
   else
   {
      /* Already at a fullstep position, nothing to do */
   }
   
//MM
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_PRODUCTION_REQUEST);

   /* If not at a stable fullstep position, drive the pointers to next fullstep position */
   if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_MM) != (uint8)0U)
   {
      /* Only in clockwise direction the virtual position equals the physical position */
      Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
      Cdd_Motor_RunToNextFullStep(CDD_MOTOR_MTR_MM);
   }
   else
   {
      /* Already at a fullstep position, nothing to do */
   }

#endif
   
   al_motor_opState_e = AL_MOTOR_OPSTATE_TRANSITION_TO_PRODUCTION;
}


/**
 *  \brief Function configure the motor for the Production Mode
 *
 */
static void Al_Motor_ProductionModeTransition (void)
{
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
	//HHSS
		/* Change full step counter mode to absolute positioning */
	   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_PRODUCTION);

	   Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_HHSS);

	   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
	   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_PRODUCTION);

	   (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_PRODUCTION);

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
   //MM

	  /* Change full step counter mode to absolute positioning */
	  Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_PRODUCTION);

	  Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_MM);

	  Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
	  Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_PRODUCTION);

	  (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_PRODUCTION);
	
#else
//HHSS
	/* Change full step counter mode to absolute positioning */
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_PRODUCTION);

   Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_HHSS);

   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_PRODUCTION);

   (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_PRODUCTION);

//MM
   /* Change full step counter mode to absolute positioning */
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_PRODUCTION);

   Cdd_Motor_ZD_DisableDetection(CDD_MOTOR_MTR_MM);

   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_PRODUCTION);

   (void) Cdd_Motor_SetSpeedFac (CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_PRODUCTION);


#endif
   
   //Al_App_Ctrl_ProductionModeChangeAllowedResponse(AL_APP_CTRL_APP_MOTOR);
   al_motor_opState_e = AL_MOTOR_OPSTATE_PRODUCTION;
}


/**
 *  \brief Function configure the motor for the Stellgliedtest Mode
 *
 */
static void Al_Motor_StellgliedtestModeTransition (void)
{
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
	//HHSS
		Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_STELLTEST);
		
		Cdd_Motor_ZD_EnableDetection (CDD_MOTOR_MTR_HHSS);
		Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_STELLTEST);
		Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
		
		(void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_STELLTEST);

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
	//MM
		Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_STELLTEST);
		
		Cdd_Motor_ZD_EnableDetection (CDD_MOTOR_MTR_MM);
		Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_STELLTEST);
		Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
		
		(void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_STELLTEST);
	
#else
	//HHSS
		Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_STELLTEST);
		
		Cdd_Motor_ZD_EnableDetection (CDD_MOTOR_MTR_HHSS);
		Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_STELLTEST);
		Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
		
		(void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_STELLTEST);

	//MM
		Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_STELLTEST);
		
		Cdd_Motor_ZD_EnableDetection (CDD_MOTOR_MTR_MM);
		Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_STELLTEST);
		Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
		
		(void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_STELLTEST);

#endif

	
   /* Clear all states */
   al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_IDLE;

   /* Do NOT clear the request flags: al_motor_eventStellTestReq_e */
   /* Clear all result flags */
   al_motor_resultStellTestComplete_e = AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF;

   /* Give status back to application control */
   //Al_App_Ctrl_StellgliedtestModeChangeAllowedResponse (AL_APP_CTRL_APP_MOTOR);

   /* set next motor opState to AL_MOTOR_OPSTATE_STELLGLIEDTEST */
   al_motor_opState_e = AL_MOTOR_OPSTATE_STELLGLIEDTEST;
}


/**
 *  \brief Function configure the motor for the Critical Temp State
 *
 */
static void Al_Motor_CriticalStateTransition (void)
{
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
//HHSS	
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_EXCEPTION);

   Cdd_Motor_ZD_DisableDetection (CDD_MOTOR_MTR_HHSS);

   if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_HHSS) != (uint8)0U)
   {
	  /* Only in clockwise direction virtual and physical positions are equal */
	  Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
	  Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_HHSS);
   }
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_EXCEPTION);
   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);

   (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_EXCEPTION);

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
//MM
      Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_EXCEPTION);

      Cdd_Motor_ZD_DisableDetection (CDD_MOTOR_MTR_MM);

      if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_MM) != (uint8)0U)
      {
         /* Only in clockwise direction virtual and physical positions are equal */
         Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
         Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_MM);
      }
      Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_EXCEPTION);
      Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);

      (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_EXCEPTION);

#else
//HHSS	
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_HHSS, AL_MOTOR_DEF_FULL_STEP_COUNTER_EXCEPTION);

   Cdd_Motor_ZD_DisableDetection (CDD_MOTOR_MTR_HHSS);

   if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_HHSS) != (uint8)0U)
   {
      /* Only in clockwise direction virtual and physical positions are equal */
      Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
      Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_HHSS);
   }
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_EXCEPTION);
   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);

   (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_HHSS, AL_MOTOR_SLOWDOWN_FAC_EXCEPTION);

//MM
   Cdd_Motor_ChangeDefaultFullStepCounter(CDD_MOTOR_MTR_MM, AL_MOTOR_DEF_FULL_STEP_COUNTER_EXCEPTION);

   Cdd_Motor_ZD_DisableDetection (CDD_MOTOR_MTR_MM);

   if (Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_MM) != (uint8)0U)
   {
      /* Only in clockwise direction virtual and physical positions are equal */
      Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
      Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_MM);
   }
   Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_EXCEPTION);
   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);

   (void) Cdd_Motor_SetSpeedFac(CDD_MOTOR_MTR_MM, AL_MOTOR_SLOWDOWN_FAC_EXCEPTION);

#endif
   
   /* Set overtemp state */
   al_motor_opState_e = AL_MOTOR_OPSTATE_CRITICAL_TEMP;
}


/* ***************************** global functions *************************** */
/**
 *  \brief Function to initialize the motor
 *
 */
void Al_Motor_Init (void)
{
al_motor_opState_e = AL_MOTOR_OPSTATE_UNCALIBRATED;
      
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
      al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
      al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;

#else      
      al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
      al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
#endif

      al_motor_stellgliedtestState_e = AL_MOTOR_OPSUBSTATE_STELLTEST_UNDEF;

      al_motor_event_e = (uint16) AL_MOTOR_EVENT_UNDEF;

      al_motor_calibrationDone_ui8 = (uint8) FALSE;

      al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_FALSE;

      al_motor_eventStellTestReq_e = AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF;
      al_motor_resultStellTestComplete_e = AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF;
}

#if (AL_MOTOR_DEINIT_API == STD_ON)
/**
 *  \brief Service for module deinitialization
 * *
 *  Regarding error detection, the requirements PWM117 and PWM051 are applicable
 *  to the function Pwm_DeInit.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
void Al_Motor_DeInit (void)
{
   /* --- local variable declaration --- */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
#if (AL_MOTOR_DEV_ERROR_DETECT == STD_ON)
   if (al_motor_moduleState_e != AL_MOTOR_MODULE_STATE_INITIALIZED) /* Safety request */
   {
      Det_ReportError(AL_MOTOR_MODULE_ID, AL_MOTOR_INSTANCE_ID,
               AL_MOTOR_DEINIT_API_ID, AL_MOTOR_E_UNINIT);
   }
   else /* AL_MOTOR_DEV_ERROR_DETECT == STD_ON */
#endif
   {
      al_motor_moduleState_e = AL_MOTOR_MODULE_STATE_UNINITIALIZED;
   }
}

#endif /* AL_MOTOR_DEINIT_API == STD_ON */


#if (AL_MOTOR_VERSION_INFO_API == STD_ON)
/*
 *  \brief This service returns the version information of this module.
 *
 *  The function Mtr_GetVersionInfo shall return the version information
 *  of the module. The version information includes:
 *  - Module ID
 *  - Vendor ID
 *  - Vendor specific version numbers (BSW00407)
 *
 *  \param [in]  ---
 *  \param [out] versioninfo = Pointer to where to store the version
 *                             information of this module.
 *  \return      ---
 */
void Al_Motor_GetVersionInfo (Std_VersionInfoType *versioninfo)
{
   /* ----------- source code ----------- */
   versioninfo->vendorID = AL_MOTOR_VENDOR_ID;
   versioninfo->moduleID = AL_MOTOR_MODULE_ID;
   versioninfo->instanceID = AL_MOTOR_INSTANCE_ID;
   versioninfo->sw_major_version = AL_MOTOR_SW_MAJOR_VERSION;
   versioninfo->sw_minor_version = AL_MOTOR_SW_MINOR_VERSION;
   versioninfo->sw_patch_version = AL_MOTOR_SW_PATCH_VERSION;
}
#endif /* AL_MOTOR_VERSION_INFO_API == STD_ON */


/**
 *  \brief Function to control the stepper motors
 *
 */
/**
\dot
digraph G {
AL_MOTOR_OPSTATE_UNDEF -> AL_MOTOR_OPSTATE_UNCALIBRATED;
AL_MOTOR_OPSTATE_UNCALIBRATED -> AL_MOTOR_OPSTATE_CALIBRATION;
AL_MOTOR_OPSTATE_CALIBRATION -> AL_MOTOR_OPSTATE_RUN;
AL_MOTOR_OPSTATE_CALIBRATION -> AL_MOTOR_OPSTATE_CRITICAL_TEMP;
AL_MOTOR_OPSTATE_CALIBRATION -> AL_MOTOR_OPSTATE_UNDER_VOLTAGE;
AL_MOTOR_OPSTATE_CALIBRATION -> AL_MOTOR_OPSTATE_OVER_VOLTAGE;
AL_MOTOR_OPSTATE_CALIBRATION -> AL_MOTOR_OPSTATE_SLEEP;
AL_MOTOR_OPSTATE_RUN -> AL_MOTOR_OPSTATE_SLEEP;
AL_MOTOR_OPSTATE_RUN -> AL_MOTOR_OPSTATE_PRODUCTION;
AL_MOTOR_OPSTATE_RUN -> AL_MOTOR_OPSTATE_CRITICAL_TEMP;
AL_MOTOR_OPSTATE_RUN -> AL_MOTOR_OPSTATE_UNDER_VOLTAGE;
AL_MOTOR_OPSTATE_RUN -> AL_MOTOR_OPSTATE_OVER_VOLTAGE;
AL_MOTOR_OPSTATE_PRODUCTION -> AL_MOTOR_OPSTATE_RUN;
AL_MOTOR_OPSTATE_SLEEP -> AL_MOTOR_OPSTATE_RUN;
AL_MOTOR_OPSTATE_SLEEP -> AL_MOTOR_OPSTATE_CRITICAL_TEMP;
AL_MOTOR_OPSTATE_SLEEP -> AL_MOTOR_OPSTATE_UNDER_VOLTAGE;
AL_MOTOR_OPSTATE_SLEEP -> AL_MOTOR_OPSTATE_OVER_VOLTAGE;
AL_MOTOR_OPSTATE_CRITICAL_TEMP -> AL_MOTOR_OPSTATE_RUN;
AL_MOTOR_OPSTATE_UNDER_VOLTAGE -> AL_MOTOR_OPSTATE_RUN;
AL_MOTOR_OPSTATE_OVER_VOLTAGE -> AL_MOTOR_OPSTATE_RUN;
}
\enddot
*/

void Al_Motor_MainFunction (void)
{
#if (SYSTEM_BUILD_TYPE == SYSTEM_BUILD_TYPE_DEBUG)
   if (al_motor_INJECT_ENABLE_ui8 == (uint8) TRUE)
   {
      if (al_motor_INJECT_NORMALTEMP_EVT_ui8 == (uint8)TRUE)
      {
         Al_Motor_TempNormalEvtNotify ();
      }
      else if (al_motor_INJECT_OVERTEMP_EVT_ui8 == (uint8) TRUE)
      {
         Al_Motor_TempCriticalEvtNotify ();
      }

      if (al_motor_INJECT_NORMALVOLT_EVT_ui8 == (uint8) TRUE)
      {
         Al_Motor_NormalVoltageEvtNotify ();
      }
      else if (al_motor_INJECT_OVERVOLT_EVT_ui8 == (uint8) TRUE)
      {
         Al_Motor_OverVoltageEvtNotify ();
      }
      else if (al_motor_INJECT_UNDERVOLT_EVT_ui8 == (uint8) TRUE)
      {
         Al_Motor_UnderVoltageEvtNotify ();
      }
   }
#endif

#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
   //MMSS   
      if (Cdd_Motor_ZD_IsDetectionEnabled(CDD_MOTOR_MTR_HHSS)) /*lint !e9036*/
      {
         Cdd_Motor_ZD_PerformWindowCheck (CDD_MOTOR_MTR_HHSS);
      }
      else
      {
         ; /* do nothing */
      }
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
  //MM   
	 if (Cdd_Motor_ZD_IsDetectionEnabled(CDD_MOTOR_MTR_MM)) /*lint !e9036*/
	 {
		Cdd_Motor_ZD_PerformWindowCheck (CDD_MOTOR_MTR_MM);
	 }
	 else
	 {
		; /* do nothing */
	 }   
#else
//MMSS   
   if (Cdd_Motor_ZD_IsDetectionEnabled(CDD_MOTOR_MTR_HHSS)) /*lint !e9036*/
   {
      Cdd_Motor_ZD_PerformWindowCheck (CDD_MOTOR_MTR_HHSS);
   }
   else
   {
      ; /* do nothing */
   }
   
//MM   
   if (Cdd_Motor_ZD_IsDetectionEnabled(CDD_MOTOR_MTR_MM)) /*lint !e9036*/
   {
      Cdd_Motor_ZD_PerformWindowCheck (CDD_MOTOR_MTR_MM);
   }
   else
   {
      ; /* do nothing */
   }

#endif

#if (AL_MOTOR_DEINIT_API == STD_ON)
   /* check for shutdown request */
   if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_SHUTDOWNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_SHUTDOWNMODE_REQUEST)
   {
      /* Delete event */
      al_motor_event_e = AL_MOTOR_EVENT_UNDEF;

      if (al_motor_opState_e != AL_MOTOR_OPSTATE_SHUTDOWN)
      {
         Al_Motor_ShutdownTransition ();
      }
   }
   /*  */
   else
#endif

   if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST) /*lint !e655 */
   {
      /* Delete all events */
      al_motor_event_e = (uint16)AL_MOTOR_EVENT_UNDEF;

      Al_Motor_ProductionModeRequestTransition ();
   }
   /* Stop operation on over temperature except in production mode */
   else if (((al_motor_event_e & (uint16)AL_MOTOR_EVENT_VOLT_UNDER_NOTIFY) == (uint16)AL_MOTOR_EVENT_VOLT_UNDER_NOTIFY) ||
            ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_TEMP_CRITICAL_NOTIFY) == (uint16)AL_MOTOR_EVENT_TEMP_CRITICAL_NOTIFY) ||
            ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_VOLT_OVER_NOTIFY) == (uint16)AL_MOTOR_EVENT_VOLT_OVER_NOTIFY ) ) /*lint !e655 */
   {
      /* Delete events */
      al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_TEMP_CRITICAL_NOTIFY | (uint16)AL_MOTOR_EVENT_VOLT_UNDER_NOTIFY | (uint16)AL_MOTOR_EVENT_VOLT_OVER_NOTIFY)); /*lint !e655 */

      if ((al_motor_opState_e != AL_MOTOR_OPSTATE_CRITICAL_TEMP) &&
          (al_motor_opState_e != AL_MOTOR_OPSTATE_UNDER_VOLTAGE) &&
          (al_motor_opState_e != AL_MOTOR_OPSTATE_OVER_VOLTAGE)  &&
          (al_motor_opState_e != AL_MOTOR_OPSTATE_SLEEP) &&
          (al_motor_opState_e != AL_MOTOR_OPSTATE_SLEEP_PREPARE))
      {
   	  
         Al_Motor_CriticalStateTransition ();

      }
   }
   else if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_STELLGLIEDTESTMODE_REQUEST)
            == (uint16) AL_MOTOR_EVENT_STELLGLIEDTESTMODE_REQUEST)
   {
      if ((AL_MOTOR_OPSTATE_UNCALIBRATED == al_motor_opState_e) || (AL_MOTOR_OPSTATE_CALIBRATION == al_motor_opState_e))
      {
         /* Only keep Stellgliedtest mode request */
         al_motor_event_e = (uint16)AL_MOTOR_EVENT_STELLGLIEDTESTMODE_REQUEST;
      }
      else
      {
         /* Delete all events */
         al_motor_event_e = (uint16)AL_MOTOR_EVENT_UNDEF;

         if (al_motor_opState_e != AL_MOTOR_OPSTATE_STELLGLIEDTEST)
         {
            Al_Motor_StellgliedtestModeTransition ();
         }
         else
         {
            /* nothing to be done */
         }
      }
   }
   else
   {
      /* do nothing */
   }
   
   switch (al_motor_opState_e)
   {
      case AL_MOTOR_OPSTATE_UNCALIBRATED:
      {
         Al_Motor_CalibrationModeTransition ();
         break;
      }

      case AL_MOTOR_OPSTATE_CALIBRATION:
      {
         static uint16 al_motor_calibCntr_ui16 = (uint16)0U;
         uint8 result_ui8 = 0U;

         /* Always accept RUN mode request during calibration to avoid any blocking behaviour in RUN_REQUEST state of APP CTRL */
         if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) /*lint !e655 */
         {
            //Al_App_Ctrl_RunModeChangeAllowedResponse(AL_APP_CTRL_APP_MOTOR);
         }

#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
	 //HHSS
				 Al_Motor_CalibrationStateMgmt (CDD_MOTOR_MTR_HHSS);
		
				 /* Timeout for CALIBRATION
				  * Count up timeout if motor does not move anymore
				  */
				 result_ui8 = Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS);
				 if (result_ui8 == (uint8)TRUE)
				 {
					al_motor_calibCntr_ui16++;
				 }
				 else
				 {
					al_motor_calibCntr_ui16 = (uint16) 0u;
				 }
		
		#if ((defined TEST_ERRORHANDLER_1_ZERODETECTION) && (TEST_ERRORHANDLER_1_ZERODETECTION == 1))
				 al_motor_calibCntr_ui16 = AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16 + (uint16) 1u;
				 al_motor_opSubStateCalib_e = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
		#endif
				 /* Timeout handling for zero detection fail */
				 if (al_motor_calibCntr_ui16 >= AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16)
				 {
					al_motor_calibCntr_ui16 = (uint16)0U;
		
					if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] != AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
					{
					   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_BACKWARD);
					   Cdd_Motor_RunToFullStepPosition (CDD_MOTOR_MTR_HHSS, (uint16)0U);
					   al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] = AL_MOTOR_OPSUBSTATE_CALIB_FINISHED;
					   ErrH_Errorhandling(ErrH_E_ZERO_DETECT_FAILED);
					}
				 }
		
				 if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] == AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
				 {
					al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
		
					al_motor_calibrationDone_ui8 = (uint8)TRUE;
		
					if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
					{
					   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
					   Al_Motor_RunModeTransition ();
					}
					else if (al_motor_returnToProductionMode_ui8 == AL_MOTOR_PRODUCTION_MODE_CALIBRATION_TRUE)
					{
					   al_motor_event_e = (uint16) AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST;
					}
					else
					{
					   /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
					   Al_Motor_SleepModePrepareTransition ();
					}
					/* Always reset this flag after finished calibration */
					al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_FALSE;	
				 }
				 else
				 {
					/* do nothing */
				 }    
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
	 //MM		 
				 Al_Motor_CalibrationStateMgmt (CDD_MOTOR_MTR_MM);
		
				 /* Timeout for CALIBRATION
				  * Count up timeout if motor does not move anymore
				  */
				 result_ui8 = Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM);
				 if (result_ui8 == (uint8)TRUE)
				 {
					al_motor_calibCntr_ui16++;
				 }
				 else
				 {
					al_motor_calibCntr_ui16 = (uint16) 0u;
				 }
		
		#if ((defined TEST_ERRORHANDLER_1_ZERODETECTION) && (TEST_ERRORHANDLER_1_ZERODETECTION == 1))
				 al_motor_calibCntr_ui16 = AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16 + (uint16) 1u;
				 al_motor_opSubStateCalib_e = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
		#endif
				 /* Timeout handling for zero detection fail */
				 if (al_motor_calibCntr_ui16 >= AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16)
				 {
					al_motor_calibCntr_ui16 = (uint16)0U;
		
					if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] != AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
					{
					   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_BACKWARD);
					   Cdd_Motor_RunToFullStepPosition (CDD_MOTOR_MTR_MM, (uint16)0U);
					   al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] = AL_MOTOR_OPSUBSTATE_CALIB_FINISHED;
					   ErrH_Errorhandling(ErrH_E_ZERO_DETECT_FAILED);
					}
				 }
		
				 if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] == AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
				 {
					al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
		
					al_motor_calibrationDone_ui8 = (uint8)TRUE;
		
					if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
					{
					   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
					   Al_Motor_RunModeTransition ();
					}
					else if (al_motor_returnToProductionMode_ui8 == AL_MOTOR_PRODUCTION_MODE_CALIBRATION_TRUE)
					{
					   al_motor_event_e = (uint16) AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST;
					}
					else
					{
					   /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
					   //Al_Motor_SleepModePrepareTransition ();
					}
					/* Always reset this flag after finished calibration */
					al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_FALSE;
				 }
				 else
				 {
					/* do nothing */
				 }         
#else
//HHSS
			 Al_Motor_CalibrationStateMgmt (CDD_MOTOR_MTR_HHSS);
	
			 /* Timeout for CALIBRATION
			  * Count up timeout if motor does not move anymore
			  */
			 result_ui8 = Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS);
			 if (result_ui8 == (uint8)TRUE)
			 {
				al_motor_calibCntr_ui16++;
			 }
			 else
			 {
				al_motor_calibCntr_ui16 = (uint16) 0u;
			 }
	
	#if ((defined TEST_ERRORHANDLER_1_ZERODETECTION) && (TEST_ERRORHANDLER_1_ZERODETECTION == 1))
			 al_motor_calibCntr_ui16 = AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16 + (uint16) 1u;
			 al_motor_opSubStateCalib_e = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
	#endif
			 /* Timeout handling for zero detection fail */
			 if (al_motor_calibCntr_ui16 >= AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16)
			 {
				al_motor_calibCntr_ui16 = (uint16)0U;
	
				if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] != AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
				{
				   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_BACKWARD);
				   Cdd_Motor_RunToFullStepPosition (CDD_MOTOR_MTR_HHSS, (uint16)0U);
				   al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] = AL_MOTOR_OPSUBSTATE_CALIB_FINISHED;
				}
			 }
	
			 if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] == AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
			 {
				al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_HHSS] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
	
				al_motor_calibrationDone_ui8 = (uint8)TRUE;
	
				if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
				{
				   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
				   Al_Motor_RunModeTransition ();
				}
				else if (al_motor_returnToProductionMode_ui8 == AL_MOTOR_PRODUCTION_MODE_CALIBRATION_TRUE)
				{
				   al_motor_event_e = (uint16) AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST;
				}
				else
				{
				   /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
				   //Al_Motor_SleepModePrepareTransition ();
				}
				/* Always reset this flag after finished calibration */
				al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_FALSE;	
			 }
			 else
			 {
				/* do nothing */
			 }      

//MM		 
			 Al_Motor_CalibrationStateMgmt (CDD_MOTOR_MTR_MM);
	
			 /* Timeout for CALIBRATION
			  * Count up timeout if motor does not move anymore
			  */
			 result_ui8 = Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM);
			 if (result_ui8 == (uint8)TRUE)
			 {
				al_motor_calibCntr_ui16++;
			 }
			 else
			 {
				al_motor_calibCntr_ui16 = (uint16) 0u;
			 }
	
	#if ((defined TEST_ERRORHANDLER_1_ZERODETECTION) && (TEST_ERRORHANDLER_1_ZERODETECTION == 1))
			 al_motor_calibCntr_ui16 = AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16 + (uint16) 1u;
			 al_motor_opSubStateCalib_e = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
	#endif
			 /* Timeout handling for zero detection fail */
			 if (al_motor_calibCntr_ui16 >= AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16)
			 {
				al_motor_calibCntr_ui16 = (uint16)0U;
	
				if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] != AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
				{
				   Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_BACKWARD);
				   Cdd_Motor_RunToFullStepPosition (CDD_MOTOR_MTR_MM, (uint16)0U);
				   al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] = AL_MOTOR_OPSUBSTATE_CALIB_FINISHED;
				}
			 }
	
			 if (al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] == AL_MOTOR_OPSUBSTATE_CALIB_FINISHED)
			 {
				al_motor_opSubStateCalib_e[CDD_MOTOR_MTR_MM] = AL_MOTOR_OPSUBSTATE_CALIB_UNDEF;
	
				al_motor_calibrationDone_ui8 = (uint8)TRUE;
	
				if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
				{
				   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
				   Al_Motor_RunModeTransition ();
				}
				else if (al_motor_returnToProductionMode_ui8 == AL_MOTOR_PRODUCTION_MODE_CALIBRATION_TRUE)
				{
				   al_motor_event_e = (uint16) AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST;
				}
				else
				{
				   /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
				   //Al_Motor_SleepModePrepareTransition ();
				}
				/* Always reset this flag after finished calibration */
				al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_FALSE;
			 }
			 else
			 {
				/* do nothing */
			 }

#endif
			 
			 al_motor_opState_e = AL_MOTOR_OPSTATE_RUN;

         break;
      }

      case AL_MOTOR_OPSTATE_RUN:
      {
         //if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
         //{
         //   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));

            //Al_App_Ctrl_RunModeChangeAllowedResponse(AL_APP_CTRL_APP_MOTOR);
         //}
         //else if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_SLEEPMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_SLEEPMODE_REQUEST)
         //{
            /* \req #CS_REQ_000024 - The software shall wait until the next exact minute is reached before entering operational state "inactive" */
            /* \req #CS_REQ_000031 - If the software is in operational state "inactive", the software shall hold the seconds clock pointer at zero position */

            /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
            //Al_Motor_SleepModePrepareTransition();
         //}
         //else
         //{
			#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)			
						 Al_Motor_RunStateMgmt (CDD_MOTOR_MTR_HHSS);
			
			#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)			
						 Al_Motor_RunStateMgmt (CDD_MOTOR_MTR_MM);
						 
			#else					 
						 Al_Motor_RunStateMgmt (CDD_MOTOR_MTR_HHSS);
						 Al_Motor_RunStateMgmt (CDD_MOTOR_MTR_MM);	
			#endif

         break;
         //}
      }

      case AL_MOTOR_OPSTATE_SLEEP_PREPARE:
      {
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
//HHSS    	  
	   /* check if a runmode-request was received while driving to zero position */
	   if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
	   {
		  /* Delete event */
		  al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
		  /* change to run mode */
		  Al_Motor_RunModeTransition ();
	   }
	   /* If not on zero, drive to zero deg pos, also check if arrived at target */
	   else if ((Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_HHSS) == (uint8)0U) &&
				(Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8)TRUE)) /*lint !e9007 */
	   {
			 /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
			 Al_Motor_SleepModeTransition ();
	   }
	   else
	   {
#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
		  /* Continue running until sleep mode condition is valid */
		  Al_Motor_RunStateMgmt(CDD_MOTOR_MTR_HHSS);
#else
		  /* Nothing to do */
		  if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8)TRUE)
		  {
			 Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
			 Cdd_Motor_RunToPosition(CDD_MOTOR_MTR_HHSS, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
		  }
#endif
	   }
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
//MM		   
	   /* check if a runmode-request was received while driving to zero position */
	   if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
	   {
		  /* Delete event */
		  al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
		  /* change to run mode */
		  Al_Motor_RunModeTransition ();
	   }
	   /* If not on zero, drive to zero deg pos, also check if arrived at target */
	   else if ((Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_MM) == (uint8)0U) &&
				(Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8)TRUE)) /*lint !e9007 */
	   {
			 /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
			 Al_Motor_SleepModeTransition ();
	   }
	   else
	   {
#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
		  /* Continue running until sleep mode condition is valid */
		  Al_Motor_RunStateMgmt(CDD_MOTOR_MTR_MM);
#else
		  /* Nothing to do */
		  if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8)TRUE)
		  {
			 Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
			 Cdd_Motor_RunToPosition(CDD_MOTOR_MTR_MM, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
		  }
#endif

	   }
#else
//HHSS    	  
		   /* check if a runmode-request was received while driving to zero position */
		   if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
		   {
			  /* Delete event */
			  al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
			  /* change to run mode */
			  Al_Motor_RunModeTransition ();
		   }
		   /* If not on zero, drive to zero deg pos, also check if arrived at target */
		   else if ((Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_HHSS) == (uint8)0U) &&
					(Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8)TRUE)) /*lint !e9007 */
		   {
				 /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
				 Al_Motor_SleepModeTransition ();
		   }
		   else
		   {
	#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
			  /* Continue running until sleep mode condition is valid */
			  Al_Motor_RunStateMgmt(CDD_MOTOR_MTR_HHSS);
	#else
			  /* Nothing to do */
			  if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8)TRUE)
			  {
				 Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
				 Cdd_Motor_RunToPosition(CDD_MOTOR_MTR_HHSS, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
			  }
	#endif
		   }

//MM		   
		   /* check if a runmode-request was received while driving to zero position */
		   if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
		   {
			  /* Delete event */
			  al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));
			  /* change to run mode */
			  Al_Motor_RunModeTransition ();
		   }
		   /* If not on zero, drive to zero deg pos, also check if arrived at target */
		   else if ((Cdd_Motor_GetUStepPosition(CDD_MOTOR_MTR_MM) == (uint8)0U) &&
					(Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8)TRUE)) /*lint !e9007 */
		   {
				 /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
				 Al_Motor_SleepModeTransition ();
		   }
		   else
		   {
	#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
			  /* Continue running until sleep mode condition is valid */
			  Al_Motor_RunStateMgmt(CDD_MOTOR_MTR_MM);
	#else
			  /* Nothing to do */
			  if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8)TRUE)
			  {
				 Cdd_Motor_SetDirectionReq(CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
				 Cdd_Motor_RunToPosition(CDD_MOTOR_MTR_MM, (uint32) AL_MOTOR_STELLTEST_POSITION_TOP);
			  }
	#endif

		   }
#endif	   

		   break;
      }
		 
      case AL_MOTOR_OPSTATE_SLEEP:
      {
         /* Start RTC Callback for HHMM / minute */
         /* Set next minute on corresponding wakeup */
         /* Check time to be sure */

         if ((al_motor_event_e & (uint16) AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16) AL_MOTOR_EVENT_RUNMODE_REQUEST)
         {
            /* Delete event */
            al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST));

            /* change to run mode */
            Al_Motor_RunModeTransition ();

         }
         else
         {           	
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
                //Al_Motor_SleepStateMgmt (CDD_MOTOR_MTR_HHSS);

#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
                //Al_Motor_SleepStateMgmt (CDD_MOTOR_MTR_MM);

#else
               //Al_Motor_SleepStateMgmt (CDD_MOTOR_MTR_HHSS);
               //Al_Motor_SleepStateMgmt (CDD_MOTOR_MTR_MM);
#endif           
         }

         break;
      }

      case AL_MOTOR_OPSTATE_OVER_VOLTAGE:
      case AL_MOTOR_OPSTATE_UNDER_VOLTAGE:
      case AL_MOTOR_OPSTATE_CRITICAL_TEMP:
      {
         if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_SLEEPMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_SLEEPMODE_REQUEST)
         {
            /* \req #CS_REQ_000024 - The software shall wait until the next exact minute is reached before entering operational state "inactive" */
            /* \req #CS_REQ_000031 - If the software is in operational state "inactive", the software shall hold the seconds clock pointer at zero position */

            /* MavonHinten: Do NOT delete sleep mode request - this is done in sleep mode */
            //Al_Motor_SleepModePrepareTransition();
         }
         else if (al_motor_criticalEnvironment_ui8 == AL_MOTOR_CRITICAL_ENV_NORMAL)
         {
            /* When calibration was finished, return to normal operation */
            if (al_motor_calibrationDone_ui8 == (uint8)TRUE)
            {
            	Al_Motor_RunModeTransition ();
            }
            else
            {
            	Al_Motor_CalibrationModeTransition ();
            }
         }
         else
         {
             /* \req  #CS_REQ_000062 - If the temperature limits are over taken, the software shall disable the "zero detection" digital outputs for hour/minute and seconds pointer */
             /* \req  #CS_REQ_000076 - If temperature > MAX_SM_TEMP, the software shall disable the power of both stepper motors */
             /* IF FULL STEP POS REACHED SWITCH OFF PWM */
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
//HHSS        	 
		 if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8) TRUE) /*lint !e9007 */
		 {
			if (Cdd_Motor_GetUStepPosition (CDD_MOTOR_MTR_HHSS) == (uint8) 0u)
			{
			   Cdd_Motor_StopPWM (CDD_MOTOR_MTR_HHSS);
			}
			else
			{
			   /*  && (Cdd_Motor_GetPartStepPosition () == (uint8) 0u) */
			   uint32 currentPos_ui32;

			   Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
			   currentPos_ui32 = Cdd_Motor_GetPositionCurrentUsed (CDD_MOTOR_MTR_HHSS);
			   Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_HHSS, currentPos_ui32);
			}
		  }
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
//MM            
		 if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8) TRUE) /*lint !e9007 */
		 {
			if (Cdd_Motor_GetUStepPosition (CDD_MOTOR_MTR_MM) == (uint8) 0u)
			{
			   Cdd_Motor_StopPWM (CDD_MOTOR_MTR_MM);
			}
			else
			{
			   /*  && (Cdd_Motor_GetPartStepPosition () == (uint8) 0u) */
			   uint32 currentPos_ui32;

			   Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
			   currentPos_ui32 = Cdd_Motor_GetPositionCurrentUsed (CDD_MOTOR_MTR_MM);
			   Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_MM, currentPos_ui32);
			}
		  }        	 
#else       	 
//HHSS        	 
		if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8) TRUE) /*lint !e9007 */
		{
		   if (Cdd_Motor_GetUStepPosition (CDD_MOTOR_MTR_HHSS) == (uint8) 0u)
		   {
			  Cdd_Motor_StopPWM (CDD_MOTOR_MTR_HHSS);
		   }
		   else
		   {
			  /*  && (Cdd_Motor_GetPartStepPosition () == (uint8) 0u) */
			  uint32 currentPos_ui32;

			  Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_HHSS, CDD_MOTOR_DIR_FORWARD);
			  currentPos_ui32 = Cdd_Motor_GetPositionCurrentUsed (CDD_MOTOR_MTR_HHSS);
			  Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_HHSS, currentPos_ui32);
		   }
		 }
            
//MM            
		if (Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8) TRUE) /*lint !e9007 */
		{
		   if (Cdd_Motor_GetUStepPosition (CDD_MOTOR_MTR_MM) == (uint8) 0u)
		   {
			  Cdd_Motor_StopPWM (CDD_MOTOR_MTR_MM);
		   }
		   else
		   {
			  /*  && (Cdd_Motor_GetPartStepPosition () == (uint8) 0u) */
			  uint32 currentPos_ui32;

			  Cdd_Motor_SetDirectionReq (CDD_MOTOR_MTR_MM, CDD_MOTOR_DIR_FORWARD);
			  currentPos_ui32 = Cdd_Motor_GetPositionCurrentUsed (CDD_MOTOR_MTR_MM);
			  Cdd_Motor_RunToPosition (CDD_MOTOR_MTR_MM, currentPos_ui32);
		   }
		 }

#endif
             else
             {
                /* Final position not yet reached */
             }
         }

         break;
      }

      case AL_MOTOR_OPSTATE_TRANSITION_TO_PRODUCTION:
      {
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
//HHSS
		Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_PRODUCTION);
		
		if ((Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8)TRUE) && (Cdd_Motor_GetStepMode(CDD_MOTOR_MTR_HHSS) == CDD_MOTOR_STEPMODE_STOP))
		{
		 Al_Motor_ProductionModeTransition ();
		}
		
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
//MM
Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_PRODUCTION);

        if ((Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8)TRUE) && (Cdd_Motor_GetStepMode(CDD_MOTOR_MTR_MM) == CDD_MOTOR_STEPMODE_STOP))
        {
           Al_Motor_ProductionModeTransition ();
        }
        
#else
//HHSS        
         Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_HHSS, AL_MOTOR_STEPMODE_PRODUCTION);

         if ((Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_HHSS) == (uint8)TRUE) && (Cdd_Motor_GetStepMode(CDD_MOTOR_MTR_HHSS) == CDD_MOTOR_STEPMODE_STOP))
         {
            Al_Motor_ProductionModeTransition ();
         }

//MM
         Cdd_Motor_SetStepMode (CDD_MOTOR_MTR_MM, AL_MOTOR_STEPMODE_PRODUCTION);

         if ((Cdd_Motor_ReachedFinalPosition (CDD_MOTOR_MTR_MM) == (uint8)TRUE) && (Cdd_Motor_GetStepMode(CDD_MOTOR_MTR_MM) == CDD_MOTOR_STEPMODE_STOP))
         {
            Al_Motor_ProductionModeTransition ();
         }

#endif
         break;
      }

      case AL_MOTOR_OPSTATE_PRODUCTION:
      {
         /* drive clock to 11:45h */
         if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)
         {
        	 Al_Motor_CalibrationModeTransition ();
         }
         else
         {
            /* delete irrelevant events */
            al_motor_event_e = (uint16)AL_MOTOR_EVENT_UNDEF;
         }
         break;
      }

      case AL_MOTOR_OPSTATE_STELLGLIEDTEST:
      {
         if ((al_motor_event_e & (uint16) AL_MOTOR_EVENT_STELLGLIEDTESTMODE_REQUEST)
                  == (uint16) AL_MOTOR_EVENT_STELLGLIEDTESTMODE_REQUEST)
         {
            /* Delete event */
            al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_STELLGLIEDTESTMODE_REQUEST)); /*lint !e655 */
            /* Acknowledge sleep request */
            //Al_App_Ctrl_StellgliedtestModeChangeAllowedResponse (AL_APP_CTRL_APP_MOTOR);
         }
         else if ((al_motor_event_e & (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST) == (uint16) AL_MOTOR_EVENT_RUNMODE_REQUEST) /*lint !e655 */
         {
            /* Delete event */
            al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)); /*lint !e655 */

            /* change to run mode */
            Al_Motor_RunModeTransition ();
         }
         else
         {
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
        	 //Al_Motor_StellgliedtestStateMgmt (CDD_MOTOR_MTR_HHSS);
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
             //Al_Motor_StellgliedtestStateMgmt (CDD_MOTOR_MTR_MM);     	 
#else
             //Al_Motor_StellgliedtestStateMgmt (CDD_MOTOR_MTR_HHSS);
             //Al_Motor_StellgliedtestStateMgmt (CDD_MOTOR_MTR_MM);
#endif
           
            /* nothing to be done */
         }

         break;
      }

#if (AL_MOTOR_DEINIT_API == STD_ON)
         case AL_MOTOR_OPSTATE_SHUTDOWN:
         {
            /* Wait for needles reaching zero position */
            if (Cdd_Motor_GetFullStepPositionAbsolute () == 0)
            {
               Ecum_AlMotor_ShutdownModeChangeOkNotify ();
               al_motor_opState_e = AL_MOTOR_OPSTATE_UNDEF;
            }

            /* delete irrelevant events */
            al_motor_event_e = AL_MOTOR_EVENT_UNDEF;

            break;
         }
#endif

      case AL_MOTOR_OPSTATE_UNDEF:
      case AL_MOTOR_OPSTATE_SIZE:
      default:
      {
         /* DET ERROR could be triggered here if enabled */
         al_motor_opState_e = AL_MOTOR_OPSTATE_RUN;
         asm (nop);  /*lint !e960 */
         break;
      }
   }
}


/**
 *  \brief Returns the module state machine's state
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      AL_MOTOR_OPSTATE_UNDEF
                 AL_MOTOR_OPSTATE_UNCALIBRATED
                 AL_MOTOR_OPSTATE_CALIBRATION
                 AL_MOTOR_OPSTATE_TRANSITION_TO_PRODUCTION,
                 AL_MOTOR_OPSTATE_PRODUCTION
                 AL_MOTOR_OPSTATE_RUN
                 AL_MOTOR_OPSTATE_SLEEP_PREPARE
                 AL_MOTOR_OPSTATE_SLEEP
                 AL_MOTOR_OPSTATE_CRITICAL_TEMP
                 AL_MOTOR_OPSTATE_UNDER_VOLTAGE
                 AL_MOTOR_OPSTATE_OVER_VOLTAGE
                 AL_MOTOR_OPSTATE_STELLGLIEDTEST
 */
Al_Motor_OperationStateEnum Al_Motor_GetOpState (void)
{
   return al_motor_opState_e;
}


/*********************************************************************************************** *
 * Request and notification callbacks                                                            *
 *********************************************************************************************** */

/**
 * \brief Request Change To Run Mode
 */
void Al_Motor_RunModeRequest (void)
{
   /* In order to that request all prior mode requests shall be deleted*/
   /* Add new mode request */
   al_motor_event_e |= (uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST; /*lint !e655 */
   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_SLEEPMODE_REQUEST)); /*lint !e655 */
}

/**
 * \brief Request Change To Sleep Mode
 */
void Al_Motor_SleepModeRequest (void)
{
   /* In order to that request all prior mode requests shall be deleted*/
   /* Add new mode request */
   al_motor_event_e |= (uint16)AL_MOTOR_EVENT_SLEEPMODE_REQUEST; /*lint !e655 */
   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_RUNMODE_REQUEST)); /*lint !e655 */
}

/**
 * \brief Request Change To Stellgliedtest Mode
 */
void Al_Motor_StellgliedtestModeRequest (void)
{
   /* In order to that request all prior mode requests shall be deleted*/
   /* Add new mode request */
   al_motor_event_e = (uint16)AL_MOTOR_EVENT_STELLGLIEDTESTMODE_REQUEST;
}


/**
 * \brief Request Change To Production Mode
 */
void Al_Motor_ProductionModeRequest (void)
{
   /* In order to that request all prior mode requests shall be deleted*/
   /* Add new mode request */
   al_motor_event_e = (uint16)AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST;
}

/**
 * \brief Request re-calibration
 */
//void Al_Motor_RequestCalibration (void)
//{
//   /* only allowed in production mode */
//   if (al_motor_opState_e == AL_MOTOR_OPSTATE_PRODUCTION)
//   {
//      Al_Motor_CalibrationModeTransition ();
//      al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_TRUE;
//   }
//}

void Al_Motor_RequestCalibration (void)
{
   /* only allowed in production mode */
   if (al_motor_opState_e == AL_MOTOR_OPSTATE_PRODUCTION)
   {
      Al_Motor_CalibrationModeTransition ();
      al_motor_returnToProductionMode_ui8 = AL_MOTOR_PRODUCTION_MODE_CALIBRATION_TRUE;
   }
}

#if (AL_MOTOR_DEINIT_API == STD_ON)
/**
 * \brief Request Change To Shutdown Mode
 */
void Al_Motor_ShutdownModeRequest (void)
{
   /* Add new mode request */
   al_motor_event_e = AL_MOTOR_EVENT_SHUTDOWNMODE_REQUEST;
}
#endif /* #if (AL_MOTOR_DEINIT_API == STD_ON) */


/**
 * \brief Notification about temperature raised maximum threshold
 */
void Al_Motor_TempCriticalEvtNotify (void)
{
   al_motor_event_e |= (uint16)AL_MOTOR_EVENT_TEMP_CRITICAL_NOTIFY;
   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_TEMP_NORMAL_NOTIFY));
   al_motor_criticalEnvironment_ui8 |= AL_MOTOR_CRITICAL_SET_TEMPERATURE_FLAG;
}


/**
 * \brief Notification about temperature returned to normal mode.
 */
void Al_Motor_TempNormalEvtNotify (void)
{
   al_motor_event_e |= (uint16)AL_MOTOR_EVENT_TEMP_NORMAL_NOTIFY;
   al_motor_event_e &= (~((uint16)AL_MOTOR_EVENT_TEMP_CRITICAL_NOTIFY));
   al_motor_criticalEnvironment_ui8 &= AL_MOTOR_CRITICAL_RESET_TEMPERATURE_FLAG;
}


/**
 * \brief Notification that time of RTC has changed
 */
void Al_Motor_RTCSyncEvtNotify (void)
{
   al_motor_event_e |= (uint16)AL_MOTOR_EVENT_RTC_TIMESYNC_NOTIFY;
}


/**
 * \brief Notification about voltage returned to normal status.
 */
void Al_Motor_NormalVoltageEvtNotify (void)
{
   al_motor_event_e |= (uint16) AL_MOTOR_EVENT_VOLT_NORMAL_NOTIFY;
   al_motor_event_e &= (~((uint16) AL_MOTOR_EVENT_VOLT_UNDER_NOTIFY | (uint16) AL_MOTOR_EVENT_VOLT_OVER_NOTIFY));
   al_motor_criticalEnvironment_ui8 &= AL_MOTOR_CRITICAL_RESET_VOLTAGE_FLAG;
}


/**
 * \brief Notification about voltage is in a critical status.
 */
void Al_Motor_UnderVoltageEvtNotify (void)
{
   al_motor_event_e |= (uint16) AL_MOTOR_EVENT_VOLT_UNDER_NOTIFY;
   al_motor_event_e &= (~((uint16) AL_MOTOR_EVENT_VOLT_NORMAL_NOTIFY | (uint16) AL_MOTOR_EVENT_VOLT_OVER_NOTIFY));
   al_motor_criticalEnvironment_ui8 |= AL_MOTOR_CRITICAL_SET_VOLTAGE_FLAG;
}


/**
 * \brief Notification about voltage is in a critical status.
 */
void Al_Motor_OverVoltageEvtNotify (void)
{
   al_motor_event_e |= (uint16) AL_MOTOR_EVENT_VOLT_OVER_NOTIFY;
   al_motor_event_e &= (~((uint16) AL_MOTOR_EVENT_VOLT_NORMAL_NOTIFY | (uint16) AL_MOTOR_EVENT_VOLT_UNDER_NOTIFY));
   al_motor_criticalEnvironment_ui8 |= AL_MOTOR_CRITICAL_SET_VOLTAGE_FLAG;
}


/**
 * \brief Request function to trigger StellGlied test specific functionality
 *
 * \param [in]  stellTestReq_e
 * \param [out] ---
 * \return      ---
 */
void Al_Motor_StellgliedtestSubModeRequest (Al_Motor_Event_StellTestEnum stellTestReq_e)
{
   switch (stellTestReq_e)
   {
      case AL_MOTOR_EVENT_STELLTEST_REQ_TOP:
      case AL_MOTOR_EVENT_STELLTEST_REQ_TOP_LEFT:
      case AL_MOTOR_EVENT_STELLTEST_REQ_TOP_RIGHT:
      {
         /* set motor sequence 1 TRUE/FALSE */
         al_motor_eventStellTestReq_e |= stellTestReq_e; /*lint !e655 !e9027*/

         break;
      }

      case AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF:
      default:
      {
         break;
      }
   }
}


/**
 * \brief Getter function to check the status of the motor sequence
 *
 * \param [in]  al_motor_stellTestReq_e
 * \param [out] ---
 * \return al_motor_return_value_b
 */
boolean Al_Motor_StellgliedtestSubModeGetResult (Al_Motor_Event_StellTestEnum stellTestReqComplete_e)
{
   boolean ret_b = (boolean) FALSE;

   switch (stellTestReqComplete_e)
   {
      case AL_MOTOR_EVENT_STELLTEST_REQ_TOP:
      case AL_MOTOR_EVENT_STELLTEST_REQ_TOP_LEFT:
      case AL_MOTOR_EVENT_STELLTEST_REQ_TOP_RIGHT:
      {
         if ((stellTestReqComplete_e & al_motor_resultStellTestComplete_e) == stellTestReqComplete_e) /*lint !e655 !e9027 !e9029 */
         {
            ret_b = (boolean) TRUE;
         }
         else
         {
            ret_b = (boolean) FALSE;
         }

         break;
      }

      case AL_MOTOR_EVENT_STELLTEST_REQ_UNDEF:
      default:
      {
         break;
      }
   }

   /* Get status chosen sequence variable */
   return ret_b;
}

/**
 * \brief Reset result of StellgliedTest
 *
 * \param [in]  al_motor_stellTestReq_e
 * \param [out] ---
 * \return ---
 */
void Al_Motor_StellgliedtestSubModeResetResult (Al_Motor_Event_StellTestEnum stellTestReqComplete_e)
{
   al_motor_resultStellTestComplete_e &= ~(stellTestReqComplete_e); /*lint !e641, !e64 !e9027 !e9034*/
}



