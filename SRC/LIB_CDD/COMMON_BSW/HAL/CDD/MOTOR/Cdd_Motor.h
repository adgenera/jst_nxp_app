#ifndef CDD_MOTOR_H
#define CDD_MOTOR_H

/* ***************************** includes < > ******************************* */
#include <Mtr.h>

/* ***************************** includes " " ******************************* */
#include "Version.h"
#include "Cdd_Motor_Cfg.h"

/* ***************************** typedefs *********************************** */

/* ***************************** # defines ********************************** */
#define CDD_MOTOR_VENDOR_ID 99       /**<\brief CoSyst VendorID */
#define CDD_MOTOR_AR_MAJOR_VERSION 3 /**<\brief AUTOSAR major version */
#define CDD_MOTOR_AR_MINOR_VERSION 1 /**<\brief AUTOSAR minor version */
#define CDD_MOTOR_AR_PATCH_VERSION 0 /**<\brief AUTOSAR patch version */
#define CDD_MOTOR_SW_MAJOR_VERSION 1 /**<\brief Software major version */
#define CDD_MOTOR_SW_MINOR_VERSION 1 /**<\brief Software minor version */
#define CDD_MOTOR_SW_PATCH_VERSION 0 /**<\brief Software patch version */
#define CDD_MOTOR_INSTANCE_ID 1      /* Instance id */

#define CDD_MOTOR_INIT_API_ID ((uint8)0x00u)

#define CDD_MOTOR_E_ALREADY_INITIALIZED ((uint8)0x00u)
#define CDD_MOTOR_EEPROM_READ_ERROR ((uint8)0x01u)

/* #define CDD_MOTOR_SS_RUN_MASK_UI8               (uint8)1U */
#define CDD_MOTOR_RISING_MASK_UI8 (uint8)2U
#define CDD_MOTOR_FALLING_MASK_UI8 (uint8)4U
#define CDD_MOTOR_BOTH_MASK_UI8 (uint8)6U

#define CDD_MOTOR_ZERO_WIDTH_INVALID_UI8 (uint8)0xFFu
#define CDD_MOTOR_ZERO_POSITION_INVALID_UI32 (uint32)0xFFFFFFFFuL
// #define CDD_MOTOR_MTR_NR_SIZE           1u

#define CDD_MOTOR_INVALID_POS_UI32 (uint32)0xFFFFFFFFuL

/* ***************************** enums ************************************** */
typedef enum
{
   CDD_MOTOR_DIR_UNDEF = 0,
   CDD_MOTOR_DIR_FORWARD,
   CDD_MOTOR_DIR_BACKWARD,
   CDD_MOTOR_DIR_SIZE
} Cdd_Motor_DirectionEnum;

typedef enum
{
// #if defined(USE_MOTOR_NB) && ((USE_MOTOR_NB == 1) || (USE_MOTOR_NB == 2))
#if defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 1)
   CDD_MOTOR_MTR_HHSS = 0,
#elif defined(USE_MOTOR_NB) && (USE_MOTOR_NB == 2)
   CDD_MOTOR_MTR_MM = 0,
#else
   CDD_MOTOR_MTR_HHSS = 0,
   CDD_MOTOR_MTR_MM,
#endif
   CDD_MOTOR_MTR_NR_SIZE
} Cdd_Motor_MotorNumberEnum;

typedef enum
{
   CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE = 0,
   CDD_MOTOR_USED_FSTEP_CTR_RELATIVE = 1
} Cdd_Motor_UsedFullStepModeEnum;

typedef enum
{
   /* DO NOT CHANGE THE ORDER OF THE FIRST TWO ELEMENTS !!! */
   CDD_MOTOR_STEPMODE_UNDEF = 0,
   CDD_MOTOR_STEPMODE_STOP,
   /* ONLY RUN MODES FROM HERE BELOW */
   CDD_MOTOR_STEPMODE_MICRO_FAST,
   CDD_MOTOR_STEPMODE_MICRO_SLOW,
   CDD_MOTOR_STEPMODE_SIZE
} Cdd_Motor_StepModeEnum;

typedef enum
{
   CDD_MOTOR_SPEED_1000US = 29,
   CDD_MOTOR_SPEED_363US = 10,
   CDD_MOTOR_SPEED_297US = 8,
   CDD_MOTOR_SPEED_231US = 6,
   CDD_MOTOR_SPEED_198US = 5,
   CDD_MOTOR_SPEED_165US = 4,
   CDD_MOTOR_SPEED_270DEG = 3,
   CDD_MOTOR_NBR_OF_SPEEDS = 253
} Cdd_Motor_SpeedEnum;

typedef enum
{
   CDD_MOTOR_ZERO_DET_STATE_INITIAL = 0,
   CDD_MOTOR_ZERO_DET_STATE_DETECTING_FIRST,
   CDD_MOTOR_ZERO_DET_STATE_DETECTING_SECOND,
   CDD_MOTOR_ZERO_DET_STATE_DETECTION_VALIDATE
} Cdd_Motor_ZeroDetectionStateEnum;

/* ***************************** structs ************************************ */

typedef struct
{
   const Mtr_ChannelNameType channelCoil_0_ui8;
   const Mtr_ChannelNameType channelCoil_1_ui8;
   const uint32 uStepMaximumRelative_ui32;
   const uint32 uStepMaximumAbsolute_ui32;
   const uint16 *const coil_0_Slow_ui16;
   const uint16 *const coil_1_Slow_ui16;
   const uint16 *const coil_0_Fast_ui16;
   const uint16 *const coil_1_Fast_ui16;
} Cdd_Motor_MotorConfigType;

/**
 *  \brief Motordata struct
 *
 *  This type contain initialization data for every Motor.
 */

typedef struct
{
   volatile uint8 currPosLevel0_ui8;
   uint32 currPosLevel1_ui32;
   uint32 trgtPosLevel1_ui32;

   const uint32 *usedUStepMaximum_pui32;
   Cdd_Motor_UsedFullStepModeEnum usedFullStep_e;

   const uint16 *usedPatternCoil_0_ui16;
   const uint16 *usedPatternCoil_1_ui16;

   Cdd_Motor_DirectionEnum dir_e;
   Cdd_Motor_DirectionEnum dirChangeReq_e;

   Cdd_Motor_StepModeEnum stepMode_e;
   Cdd_Motor_StepModeEnum stepModeChangeReq_e;

#if ((defined CDD_MOTOR_GEAR_PLAY_COMPENSATION_API) && (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON))
   uint8 gearPlayCompensation_ui8;
#endif

   uint16 isrTargetNbrOfPeriodes_ui16;
   uint8 isrIsRunning_ui8;
   uint16 isrPeriodeCounter_ui16;
} Cdd_Motor_RunTimeDataType;

typedef struct
{
   uint32 windowStart_ui32;
   uint32 windowEnd_ui32;
   uint8 windowSize_ui8;
   uint8 windowSizeLeftMiddle_ui8;
} Cdd_Motor_ZeroDetectionResultType;

typedef struct
{
   uint32 posAbsolute_ui32;
   Cdd_Motor_DirectionEnum dir_e;
   uint8 ctr_ui8;
} Cdd_Motor_DebounceType;

typedef struct
{
   uint32 pos_ui32;
   Cdd_Motor_DirectionEnum dir_e;
   uint8 valid_ui8;
} Cdd_Motor_ZeroDetectionPosType;

typedef struct
{
   Cdd_Motor_ZeroDetectionPosType rising_s;
   Cdd_Motor_ZeroDetectionPosType falling_s;
   Cdd_Motor_ZeroDetectionResultType lastResult_s;
   Cdd_Motor_ZeroDetectionStateEnum state_e;
   uint8 enabled_ui8;
} Cdd_Motor_ZeroDetectionType;

/* ***************************** global data ******************************** */

/* ***************************** modul global prototypes ******************** */

/* ***************************** global prototypes ************************** */
void Cdd_Motor_Init(void);

#if (CDD_MOTOR_DEINIT_API == STD_ON)
void Cdd_Motor_DeInit(void);
#endif /* CDD_MOTOR_DEINIT_API == STD_ON */

#if (CDD_MOTOR_VERSION_INFO_API == STD_ON)
void Cdd_Motor_GetVersionInfo(
    Std_VersionInfoType *versioninfo);
#endif /* CDD_MOTOR_VERSION_INFO_API == STD_ON */

Std_ReturnType Cdd_Motor_SetSpeedFac(const Cdd_Motor_MotorNumberEnum motor_e, const Cdd_Motor_SpeedEnum targetSpeed_e);

Cdd_Motor_StepModeEnum Cdd_Motor_GetStepMode(const Cdd_Motor_MotorNumberEnum motor_e);

void Cdd_Motor_SetStepMode(const Cdd_Motor_MotorNumberEnum motor_e, const Cdd_Motor_StepModeEnum stepMode_e);

void Cdd_Motor_SetDirectionReq(const Cdd_Motor_MotorNumberEnum motor_e, const Cdd_Motor_DirectionEnum dir_e);

Cdd_Motor_DirectionEnum Cdd_Motor_GetDirection(const Cdd_Motor_MotorNumberEnum motor_e);
uint8 Cdd_Motor_GetUStepPosition(const Cdd_Motor_MotorNumberEnum motor_e);

void Cdd_Motor_ChangeDefaultFullStepCounter(const Cdd_Motor_MotorNumberEnum motor_e, const Cdd_Motor_UsedFullStepModeEnum counterTyp_e);

void Cdd_Motor_StopPWM(const Cdd_Motor_MotorNumberEnum motor_e);

void Cdd_Motor_RunDistanceFullSteps(const Cdd_Motor_MotorNumberEnum motor_e, uint16 position_ui16);

#if (CDD_MOTOR_RUN_RELATIVE_API == STD_ON)
void Cdd_Motor_RunDistance(const Cdd_Motor_MotorNumberEnum motor_e, const Cdd_Motor_DirectionEnum dir_e, const uint16 fStep_ui16, const uint8 uStep_ui8);
#endif

void Cdd_Motor_RunToNextFullStep(const Cdd_Motor_MotorNumberEnum motor_e);
void Cdd_Motor_RunToFullStepPosition(const Cdd_Motor_MotorNumberEnum motor_e, uint16 pos_ui16);

#if (CDD_MOTOR_RUN_TO_POSITION_API == STD_ON)
void Cdd_Motor_RunToPosition(const Cdd_Motor_MotorNumberEnum motor_e, const uint32 newPos_ui32);
void Cdd_Motor_RunToPositionAbsolute(const Cdd_Motor_MotorNumberEnum motor_e, const uint32 newPos_ui32);
#endif /* (CDD_MOTOR_RUN_TO_POSITION_API == STD_ON) */

uint8 Cdd_Motor_GetPartStepPosition(const Cdd_Motor_MotorNumberEnum motor_e);
uint16 Cdd_Motor_GetFullStepPositionUsed(const Cdd_Motor_MotorNumberEnum motor_e);
uint16 Cdd_Motor_GetFullStepPositionAbsolute(const Cdd_Motor_MotorNumberEnum motor_e);

uint32 Cdd_Motor_GetPositionCurrentUsed(const Cdd_Motor_MotorNumberEnum motor_e);
uint32 Cdd_Motor_GetPositionCurrentAbsolute(const Cdd_Motor_MotorNumberEnum motor_e);
uint32 Cdd_Motor_GetPositionTargetUsed(const Cdd_Motor_MotorNumberEnum motor_e);
uint32 Cdd_Motor_GetPositionTargetAbsolute(const Cdd_Motor_MotorNumberEnum motor_e);

uint8 Cdd_Motor_GetPartStepTarget(const Cdd_Motor_MotorNumberEnum motor_e);
uint16 Cdd_Motor_GetFullStepTargetUsed(const Cdd_Motor_MotorNumberEnum motor_e);
uint16 Cdd_Motor_GetFullStepTargetFullPartAbsolute(const Cdd_Motor_MotorNumberEnum motor_e);
uint32 Cdd_Motor_GetMaximumFullStepUsed(const Cdd_Motor_MotorNumberEnum motor_e);

uint8 Cdd_Motor_ReachedFinalPosition(const Cdd_Motor_MotorNumberEnum motor_e);

void Cdd_Motor_ZD_CalibrateZeroToActivePosition(const Cdd_Motor_MotorNumberEnum motor_e);
Std_ReturnType Cdd_Motor_ZD_CalibrateZeroToWindow(const Cdd_Motor_MotorNumberEnum motor_e);
void Cdd_Motor_ZD_DeleteResult(const Cdd_Motor_MotorNumberEnum motor_e);
void Cdd_Motor_ZD_DisableDetection(const Cdd_Motor_MotorNumberEnum motor_e);
void Cdd_Motor_ZD_EnableDetection(const Cdd_Motor_MotorNumberEnum motor_e);
boolean Cdd_Motor_ZD_IsDetectionEnabled(const Cdd_Motor_MotorNumberEnum motor_e);
uint8 Cdd_Motor_ZD_IsCurrentPositionInZeroWindow(const Cdd_Motor_MotorNumberEnum motor_e);
uint8 Cdd_Motor_ZD_IsDetectionCompleteAndValid(const Cdd_Motor_MotorNumberEnum motor_e);
uint8 Cdd_Motor_ZD_GetDistanceZeroPositionAndLeftWindowEdge(const Cdd_Motor_MotorNumberEnum motor_e);
uint8 Cdd_Motor_ZD_GetWindowSize(const Cdd_Motor_MotorNumberEnum motor_e);
void Cdd_Motor_ZD_PerformWindowCheck(const Cdd_Motor_MotorNumberEnum motor_e);

void Cdd_Motor_RunMotorISR(void);

#pragma optimize_for_size off
#pragma opt_lifetimes on
void Cdd_Motor_RunMotorISR_HHSS(void);
#pragma opt_lifetimes off
#pragma optimize_for_size on

#pragma optimize_for_size off
#pragma opt_lifetimes on
void Cdd_Motor_RunMotorISR_MM(void);
#pragma opt_lifetimes off
#pragma optimize_for_size on

#endif /* CDD_MOTOR_H */
