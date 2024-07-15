#ifndef ECUM_H
#define ECUM_H

/* ***************************** includes < > ******************************* */
#include "Version.h"
#include <Gpt.h>

/* ***************************** includes " " ******************************* */
#include "EcuM_Cfg.h"

#if (ECUM_DEV_ERROR_DETECTION == STD_ON)
    //#include "Det.h"
#endif /* (ECUM_DEV_ERROR_DETECTION == STD_ON) */


/* ***************************** typedefs *********************************** */

/* data type for a function pointer to a main function */
typedef void(*Ecum_CallbackType)(void);


/* ***************************** # defines ********************************** */

#define ECUM_VENDOR_ID             (99)   /**<\brief CoSyst VendorID */
#define ECUM_INSTANCE_ID           (1)    /**<\brief Instance id */
#define ECUM_AR_MAJOR_VERSION      (3)    /**<\brief AUTOSAR major version */
#define ECUM_AR_MINOR_VERSION      (1)    /**<\brief AUTOSAR minor version */
#define ECUM_AR_PATCH_VERSION      (0)    /**<\brief AUTOSAR patch version */
#define ECUM_SW_MAJOR_VERSION      (1)    /**<\brief Software major version */
#define ECUM_SW_MINOR_VERSION      (1)    /**<\brief Software minor version */
#define ECUM_SW_PATCH_VERSION      (3)    /**<\brief Software patch version */

#if (ECUM_DEV_ERROR_DETECTION == STD_ON)
#define ECUM_INIT_API_ID           ((uint8)0x00) /**<\brief API ID of the Ecum_Init function */
#define ECUM_START_API_ID          ((uint8)0x01) /**<\brief API ID of the Ecum_Start function */
#define ECUM_MAIN_API_ID           ((uint8)0x02) /**<\brief API ID of the Ecum_Main function */
#define ECUM_TIMER_ISR_ID          ((uint8)0x03) /**<\brief ISR ID of the Ecum_TimerISR function */
#define ECUM_VERSIN_INFO_API_ID    ((uint8)0x04) /**<\brief API ID of the Ecum_GetVersionInfo function */
#define ECUM_MODE_TRANSITION_ID    ((uint8)0x05) /**<\brief ID of the function Ecum_ModeTransition */

#define ECUM_E_PARAM_CONFIG        ((uint8)0x01) /**<\brief Error code: incorrect config pointer */
#define ECUM_E_PARAM_POINTER       ((uint8)0x02) /**<\brief Error code: null parameter pointer */
#define ECUM_E_UNINIT              ((uint8)0x03) /**<\brief Error code: Module not initialized */
#define ECUM_E_DEFAULT_ROUTE       ((uint8)0x04) /**<\brief Error code: default route was used in switch case directive */
#define ECUM_E_OVERLOAD_DETECTED   ((uint8)0x05) /**<\brief Error code: Overload is detected */
#define ECUM_E_ALREADY_INIT        ((uint8)0x06) /**<\brief Error code: Module is already initialised */
#define ECUM_E_FNCT_PTR_NULL_PTR   ((uint8)0x07)

#endif /* ECUM_DEV_ERROR_DETECTION == STD_ON */

/* ***************************** enums ************************************** */

/**
 * \brief States of the module
 */
typedef enum
{
	ECUM_UNINIT = 0,       /* Module uninitialized */
	ECUM_INIT   = 1        /* Module initialized */
} Ecum_ModuleStatusEnum;


/**
 * \brief Data type for the description of the status of the ECU Manager
 */
typedef enum
{
    ECUM_STATE_INIT = 0,                /* ECU is in 'Init State' */
    ECUM_STATE_STARTUP_PRE_OS,          /* ECU is in 'Startup State' */
    ECUM_STATE_STARTUP_POST_OS,         /* ECU is in 'Startup State' */
#if (ECUM_DEINIT_API == STD_ON)
    ECUM_STATE_SHUTDOWN,                /* ECU is in 'Shutdown State' */
#endif
    ECUM_STATE_RUN,                     /* ECU is in 'Init Hardware State' */
    ECUM_STATE_SLEEP,                   /* ECU is in 'Sleep Mode' */
    ECUM_STATE_OFF,
    ECUM_STATE_ENUM_SIZE
} Ecum_StateMachineEnum;


#if (ECUM_DEINIT_API == STD_ON)
typedef enum
{
    ECUM_STATE_SHUTDOWN_PENDING,
    ECUM_STATE_SHUTDOWN_REBOOT,
    ECUM_STATE_SHUTDOWN_HALT,
};
#endif

/**
 * \brief Data type for the description of the status of the ECU Manager
 */
typedef enum
{
    ECUM_DONT_RUN_MAIN_FUNC     = 0,    /* don't call main function */
    ECUM_RUN_MAIN_FUNC          = 1     /* do call main function */
} Ecum_RunStatusType;


/**
 * \brief Data type define the poll status of the bctrl main functions
 */
typedef enum
{
	ECUM_FUNCTION_CYCLIC_POLL     = 0,   /* Associated main function's call is cyclic polling  */
	ECUM_FUNCTION_NON_CYCLIC_POLL = 1    /* Associated main function's call is polling */
} Ecum_FunctionCyclicPollType;


/**
 * \brief Data type define the state of the called bctrl main function
 */
typedef enum
{
	ECUM_FUNCTION_PENDING = 0,          /* Called function is in progress */
	ECUM_FUNCTION_DONE    = 1           /* Called function is completely processed */
} Ecum_Result_PollFunctionType;


/* ***************************** structs ************************************ */

typedef uint16 EcumTriggerIndType;


/**
 * \brief Configuration data type describes the configuration of a bcrl main function call
 */
typedef struct
{
	Ecum_CallbackType             callback;		   /* Pointer to call-back function */
	uint16                        callCycle_ui16;   /* Call cycle in timer ticks */
	uint16                        callTrigger_ui16; /* Call trigger in timer ticks */
} Ecum_MainFuncConfigType;

/**
 * \brief Configuration data type describes the configuration of a MainFunction call
 */
typedef struct
{
	uint16                    initialTimerTicks_ui16;  /* Call cycle in timer ticks */
	uint8                     usedNumOfMainFunc_ui8;   /* Number of used MainFunctions */
	Ecum_MainFuncConfigType const *  mainFuncConfig_as;       /* Array contains all MainFunktionen that will be called */
} Ecum_ModeConfigType;


/**
 * \brief Configuration data type describes the configuration of a ECU Manager
 */
typedef struct
{
   const Gpt_ChannelType usedTimerChannel_e;             /* index of the timer channel */
   const Ecum_ModeConfigType cfgNormalMode_s;            /* contains the configuration of the 'Normal Mode' and 'Production Mode' */
   const Ecum_ModeConfigType cfgSleepMode_s;             /* contains the configuration of the 'Sleep Mode' */
} Ecum_ConfigType;


/* ***************************** global data ******************************** */
extern const Ecum_ConfigType ecum_initialConfiguration_s;
extern const uint8 ecum_initFunctionPtrSIZE_ui8;
extern const Ecum_CallbackType ecum_initFunctionPtr_apf[];

/* **************************** module global prototypes ******************** */

/* ***************************** global prototypes ************************** */

/**
* \brief Function to initialize the ECUM module.
*
* Initializes the ECUM module.
*
* \param [in]  ---
* \param [out] ---
* \return      ---
*/
void Ecum_Init (void);


/**
* \brief Function to start the ECU Manager.
*
* Starts the ECUM module.
*
* \param [in]  ---
* \param [out] ---
* \return      ---
*/
void Ecum_Start (void);


/**
* \brief MainFunction of the ECU Manager.
*
* MainFunction of the ECUM module.
*
* \param [in]  ---
* \param [out] ---
* \return      ---
*/
void Ecum_MainFunction (void);


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
void Ecum_RunTimerISR (void);
#pragma CODE_SEG DEFAULT

/**
 * \brief Request Sleep Mode
 */
void Ecum_RequestSleepMode (void);


#pragma CODE_SEG __NEAR_SEG NON_BANKED

/**
 * \brief Request Run Mode
 */
void Ecum_RequestRunMode (void);
#pragma CODE_SEG DEFAULT


/**
 * \brief Request Production Mode
 */
void Ecum_RequestProductionMode (void);

/**
 * \brief Request Production Mode
 */
void Ecum_ExitProductionMode (void);

/**
 * \brief Notification that change to sleep mode is ok
 */
void Ecum_AlMotor_SleepModeChangeIllumOkNotify (void);


#if (ECUM_DEINIT_API == STD_ON)
/**
 * \brief Notification that change to shutdown mode is ok
 */
void Ecum_AlMotor_ShutdownModeChangeOkNotify (void);
#endif

/**
 * \brief Notification to fall asleep again
 */
void Ecum_FallASleepNotify (void);


/**
 * \brief Notification to reset the MCU
 */
void Ecum_ResetRequest (void);

#if(TEST_UNITTEST_ACTIVE == 1)
/**
* \brief Returns value of ecum_maxLoad_ui16
*
* \param [in]  ---
* \param [out] ---
* \return      value of ecum_maxLoad_ui16
*/
uint16 Ecum_GetMaxLoad (void);
#endif


#if(ECUM_VERSION_INFO_API == STD_ON)
/**
* \brief This service returns the version information of this module .
*
* \param [in]  ---
* \param [out] versioninfo = Pointer to where to store the version
*                            information of this module .
* \return      ---
*/
void Ecum_GetVersionInfo
(
   Std_VersionInfoType * const versioninfo
);
#endif /* ECUM_VERSION_INFO_API == STD_ON */


#endif /* ECUM_H */
