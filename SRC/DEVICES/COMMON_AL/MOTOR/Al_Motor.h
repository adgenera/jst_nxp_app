#ifndef AL_MOTOR_H
#define AL_MOTOR_H

/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include "Version.h"

#include "Al_Motor_Cfg.h"
#include "Cdd_Motor.h"
#include "Cdd_IIC.h"

/* ***************************** typedefs *********************************** */

/* ***************************** # defines ********************************** */
#define AL_MOTOR_VENDOR_ID        99  /**<\brief CoSyst VendorID */
#define AL_MOTOR_AR_MAJOR_VERSION 3   /**<\brief AUTOSAR major version */
#define AL_MOTOR_AR_MINOR_VERSION 1   /**<\brief AUTOSAR minor version */
#define AL_MOTOR_AR_PATCH_VERSION 0   /**<\brief AUTOSAR patch version */
#define AL_MOTOR_SW_MAJOR_VERSION 1   /**<\brief Software major version */
#define AL_MOTOR_SW_MINOR_VERSION 0   /**<\brief Software minor version */
#define AL_MOTOR_SW_PATCH_VERSION 0   /**<\brief Software patch version */
#define AL_MOTOR_INSTANCE_ID      1   /* Instance id */

#define AL_MOTOR_INIT_API_ID   ((uint8)0x00u)

#define AL_MOTOR_E_ALREADY_INITIALIZED ((uint8)0x00U)
#define AL_MOTOR_E_EEPROM_READ_ERROR   ((uint8)0x01U)

#define AL_MOTOR_RESET_DIRECTION_SHORTEST             (uint8)0u
#define AL_MOTOR_RESET_DIRECTION_CLOCKWISE            (uint8)1u
#define AL_MOTOR_RESET_DIRECTION_COUNTER_CLOCKWISE    (uint8)2u

#define AL_MOTOR_PRODUCTION_MODE_CALIBRATION_TRUE     (uint8)0x5Au
#define AL_MOTOR_PRODUCTION_MODE_CALIBRATION_FALSE    (uint8)0x0u

// Timeout at 20 seconds on all devices
#define AL_MOTOR_CALIBRATION_TIMEOUT_THRESHOLD_UI16   (uint16) 200u

typedef void (*Al_Motor_CallbackType) (void);

/* ***************************** enums ************************************** */

typedef enum
{
   AL_MOTOR_OPSTATE_UNDEF = 0,
   AL_MOTOR_OPSTATE_UNCALIBRATED,
   AL_MOTOR_OPSTATE_CALIBRATION,
   AL_MOTOR_OPSTATE_TRANSITION_TO_PRODUCTION,
   AL_MOTOR_OPSTATE_PRODUCTION,
   AL_MOTOR_OPSTATE_RUN,
   AL_MOTOR_OPSTATE_SLEEP_PREPARE,
   AL_MOTOR_OPSTATE_SLEEP,
   AL_MOTOR_OPSTATE_CRITICAL_TEMP,
   AL_MOTOR_OPSTATE_UNDER_VOLTAGE,
   AL_MOTOR_OPSTATE_OVER_VOLTAGE,
#if (AL_MOTOR_DEINIT_API == STD_ON)
   ,
   AL_MOTOR_OPSTATE_SHUTDOWN
#endif
   AL_MOTOR_OPSTATE_SIZE
} Al_Motor_OperationStateEnum;

typedef enum
{
   AL_MOTOR_OPSUBSTATE_CALIB_UNDEF = 0,
   AL_MOTOR_OPSUBSTATE_CALIB_START,
   AL_MOTOR_OPSUBSTATE_CALIB_FIRST_SEARCH_BW,
   AL_MOTOR_OPSUBSTATE_CALIB_FIRST_SEARCH_FW,
   AL_MOTOR_OPSUBSTATE_CALIB_SECOND_SEARCH_FW,
   AL_MOTOR_OPSUBSTATE_CALIB_SEARCH_ZERO_FIRST_SEARCH,
   AL_MOTOR_OPSUBSTATE_CALIB_SEARCH_ZERO_SECOND_SEARCH,
   AL_MOTOR_OPSUBSTATE_CALIB_SEARCH_ZERO_THIRD_SEARCH,
   AL_MOTOR_OPSUBSTATE_CALIB_ZERO_WINDOW_DETECTED,
   AL_MOTOR_OPSUBSTATE_CALIB_ZERO_POS_REACHED,
   AL_MOTOR_OPSUBSTATE_CALIB_FINALLY_FWD,
   AL_MOTOR_OPSUBSTATE_CALIB_FINISHED
} Al_Motor_OperationSubStateCalibEnum;

typedef enum
{
   AL_MOTOR_OPSUBSTATE_RUN_INIT = 0,
   AL_MOTOR_OPSUBSTATE_RUN_NOT_RUNNING_RESET,
   AL_MOTOR_OPSUBSTATE_RUN_NOT_RUNNING_NO_RESET,
   AL_MOTOR_OPSUBSTATE_RUN_RUNNING
} Al_Motor_OperationSubStateRunEnum;

typedef enum
{
   AL_MOTOR_EVENT_UNDEF = 0,
   AL_MOTOR_EVENT_RUNMODE_REQUEST = 1,
   AL_MOTOR_EVENT_SLEEPMODE_REQUEST = 2,
   AL_MOTOR_EVENT_PRODUCTIONMODE_REQUEST = 4,
   AL_MOTOR_EVENT_SHUTDOWNMODE_REQUEST = 8,
   AL_MOTOR_EVENT_RTC_TIMESYNC_NOTIFY = 16,
   AL_MOTOR_EVENT_TEMP_NORMAL_NOTIFY = 32,
   AL_MOTOR_EVENT_TEMP_CRITICAL_NOTIFY = 64,
   AL_MOTOR_EVENT_VOLT_NORMAL_NOTIFY = 128,
   AL_MOTOR_EVENT_VOLT_UNDER_NOTIFY = 256,
   AL_MOTOR_EVENT_VOLT_OVER_NOTIFY = 512
} Al_Motor_EventBitEnum;

/* ***************************** structs ************************************ */

typedef struct
{
   boolean zeroDetectionEnabled_b;
   Cdd_Motor_StepModeEnum stepMode_e;
   Cdd_Motor_UsedFullStepModeEnum fullStepConf_e;
   Cdd_Motor_DirectionEnum mtrDir_e;
   uint8 slowDownFactor_ui8;

   Al_Motor_CallbackType notifyFunc;
   Al_Motor_CallbackType entryCheckCondFunc;
   Al_Motor_CallbackType transitionFunc;

   Al_Motor_OperationStateEnum newOpState_e;
} Al_Motor_StateConfType;

/* ***************************** global data ******************************** */

/* ***************************** module global prototypes ******************** */

/* ***************************** global prototypes ************************** */
void Al_Motor_Init (void);

#if (AL_MOTOR_DEINIT_API == STD_ON)
void Al_Motor_DeInit (void);
#endif /* AL_MOTOR_DEINIT_API == STD_ON */

#if (AL_MOTOR_VERSION_INFO_API == STD_ON)
void Al_Motor_GetVersionInfo (Std_VersionInfoType *versioninfo);
#endif /* AL_MOTOR_VERSION_INFO_API == STD_ON */

void Al_Motor_MainFunction (void);


Al_Motor_OperationStateEnum Al_Motor_GetOpState(void);


/* NOTIFY CALLBACK FUNCTIONS */
/**
 * \brief Request Change To Run Mode
 */
void Al_Motor_RunModeRequest (void);

/**
 * \brief Request Change To Sleep Mode
 */
void Al_Motor_SleepModeRequest (void);

/**
 * \brief Request Change To Production Mode
 */
void Al_Motor_ProductionModeRequest (void);

/**
 * \brief Request re-calibration
 */
void Al_Motor_RequestCalibration(void);

/**
 *  \brief Function configure the motor for the Calibration State
 *
 */
void Al_Motor_CalibrationModeTransition (void);

#if (AL_MOTOR_DEINIT_API == STD_ON)
/**
 * \brief Request Change To Shutdown Mode
 */
void Al_Motor_ShutdownModeRequest (void);
#endif /* #if (AL_MOTOR_DEINIT_API == STD_ON) */


/**
 * \brief Notification about temperature returned to normal mode.
 */
void Al_Motor_TempNormalEvtNotify (void);

/**
 * \brief Notification about temperature raised maximum threshold
 */
void Al_Motor_TempCriticalEvtNotify (void);


/**
 * \brief Notification that time of RTC has changed
 */
void Al_Motor_RTCSyncEvtNotify (void);

/**
 * \brief Notification about voltage returned to normal status.
 */
void Al_Motor_NormalVoltageEvtNotify (void);

/**
 * \brief Notification about voltage is in a critical status.
 */
void Al_Motor_UnderVoltageEvtNotify (void);


/**
 * \brief Notification about voltage is in a critical status.
 */
void Al_Motor_OverVoltageEvtNotify (void);

#endif /* AL_MOTOR_H */
