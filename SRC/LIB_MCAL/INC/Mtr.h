#ifndef MTR_H
#define MTR_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include "Mtr_Cfg.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define MTR_VENDOR_ID        99  /**<\brief CoSyst VendorID */
#define MTR_AR_MAJOR_VERSION 3   /**<\brief AUTOSAR major version */
#define MTR_AR_MINOR_VERSION 1   /**<\brief AUTOSAR minor version */
#define MTR_AR_PATCH_VERSION 0   /**<\brief AUTOSAR patch version */
#define MTR_SW_MAJOR_VERSION 1   /* Software major version */
#define MTR_SW_MINOR_VERSION 0   /* Software minor version */
#define MTR_SW_PATCH_VERSION 0   /* Software patch version */
#define MTR_INSTANCE_ID      1   /* Instance id */


#if (MTR_DEV_ERROR_DETECT == STD_ON)
/* DET Module API ID's */
#define MTR_INIT_API_ID                 (uint8)0x00
#define MTR_DEINIT_API_ID               (uint8)0x01
#define MTR_SET_DUTYCYCLE_API_ID        (uint8)0x02
#define MTR_SET_PERIODANDDUTY_API_ID    (uint8)0x03
#define MTR_SET_OUTPUTTOIDLE_API_ID     (uint8)0x04
#define MTR_GET_OUTPUTSTATE_API_ID      (uint8)0x05
#define MTR_DISABLE_NOTIFICATION_API_ID (uint8)0x06
#define MTR_ENABLE_NOTIFICATION_API_ID  (uint8)0x07
#define MTR_GET_VERSION_INFO_API_ID     (uint8)0x08
#define MTR_SET_CHANNELSTATUS_API_ID    (uint8)0x09

/* DET Module error ID's */
#define MTR_E_PARAM_CONFIG          (uint8)0x10  /**<\brief API Mtr_Init service called with wrong parameter */
#define MTR_E_UNINIT                (uint8)0x11  /**<\brief API service used without module initialization */
#define MTR_E_PARAM_CHANNEL         (uint8)0x12  /**<\brief API service used with an invalid channel Identifier */
#define MTR_E_PERIOD_UNCHANGEABLE   (uint8)0x13  /**<\brief Usage of unauthorized MTR service on MTR channel configured a fixed period */
#define MTR_E_ALREADY_INITIALIZED   (uint8)0x14  /**<\brief API Mtr_Init service called while the MTR driver has already been initialised */
#define MTR_E_PARAM_MODE            (uint8)0x15  /**<\brief API service used with invalid register access, channel configured as 16 Bit Channel */
#define MTR_E_NULLPOINTER           (uint8)0x16  /**<\brief Interrupt Timer overflow Function Callback Timer is NULL */
//#define MTR_E_NOT_INITIALIZED            /* Error ID: multiple call of Mtr_DeInit() */
#endif /* MTR_DEV_ERROR_DETECT == STD_ON */

/* CAUTION!! When changing check cdd illum lcfg! */
#define MTR_CTRL_MCPER              1270UL

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config typedefs ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef uint16 Mtr_CtrlPeriodType;
typedef uint16 Mtr_ChannelDutyCycleType;
typedef uint8 Mtr_ChannelPolarityStateType;
typedef uint8 Mtr_ChannelNumberType;


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 *  \brief Type for PWM prescaler settings
 *
 *  Type defines the prescaler values for clock source A and B
 */
typedef enum
{
   MTR_CTRL_MCPRE_FBUS_DIV_1 = 0,
   MTR_CTRL_MCPRE_FBUS_DIV_2 = 1,
   MTR_CTRL_MCPRE_FBUS_DIV_4 = 2,
   MTR_CTRL_MCPRE_FBUS_DIV_8 = 3,
   MTR_CTRL_MCPRE_SIZE = 4
} Mtr_CtrlPrescalerType;

/**
 *  \brief Type for controller module stop behavior
 *
 *  Defines the behavior for the modules clock in controller waot mode
 */
typedef enum
{
   MTR_CTRL_WAIT_MODE_STAY_AWAKE = 0,
   MTR_CTRL_WAIT_MODE_STOP = 1,
   MTR_CTRL_WAIT_MODE_SIZE = 2
} Mtr_CtrlWaitModeType;

/**
 *  \brief Type for PWM resolution mode
 *
 *  Defines the resolution mode for all MTR PWM channels
 */
typedef enum
{
   MTR_CTRL_PWM_RESOLUTION_NORMAL = 0,
   MTR_CTRL_PWM_RESOLUTION_FAST = 1,
   MTR_CTRL_PWM_RESOLUTION_SIZE = 2
} Mtr_CtrlPwmResModeType;

/**
 *  \brief Type for driver dither feature
 *
 *  Enables/disables dither feature
 */
typedef enum
{
   MTR_CTRL_DITHER_FEATURE_DISABLED = 0,
   MTR_CTRL_DITHER_FEATURE_ENABLED = 1,
   MTR_CTRL_DITHER_FEATURE_SIZE = 2
} Mtr_CtrlDitherFeatType;

/**
 *  \brief Type for controller time counter overflow flag
 *
 *  e
 */
typedef enum
{
   MTR_CTRL_MCTOIF_NOT_OCCURED = 0,
   MTR_CTRL_MCTOIF_OCCURED = 1,
   MTR_CTRL_MCTOIF_SIZE = 2
} Mtr_CtrlMCTOIFType;

typedef enum
{
   MTR_CTRL_RECIRC_HIGH = 0,
   MTR_CTRL_RECIRC_LOW = 1,
   MTR_CTRL_RECIRC_SIZE = 2
} Mtr_CtrlRecircType;

typedef enum
{
   MTR_CTRL_MCTOIE_DISABLE = 0,
   MTR_CTRL_MCTOIE_ENABLE = 1,
   MTR_CTRL_MCTOIE_SIZE = 2
} Mtr_CtrlMCTOIEType;

typedef enum
{
   MTR_MCCC_MCOM_HALF_HB_MP = 0,
   MTR_MCCC_MCOM_HALF_HB_PM = 1,
   MTR_MCCC_MCOM_FULL_HB = 2,
   MTR_MCCC_MCOM_Dual_FULL_HB = 3,
   MTR_MCCC_MCOM_SIZE = 4
} Mtr_CtrlChBridgeModeType;

typedef enum
{
   MTR_MCCC_MCAM_DISABLED = 0,
   MTR_MCCC_MCAM_LEFT = 1,
   MTR_MCCC_MCAM_RIGHT = 2,
   MTR_MCCC_MCAM_CENTER = 3,
   MTR_MCCC_MCAM_SIZE = 4
} Mtr_CtrlChAlignType;

/**
 *  \brief Type for MTR channel delay configuration
 *
 *  Type for MTR channel delay configuration
 */
typedef enum
{
   MTR_MCCC_CD_0 = 0,
   MTR_MCCC_CD_1 = 1,
   MTR_MCCC_CD_2 = 2,
   MTR_MCCC_CD_3 = 3,
   MTR_MCCC_CD_SIZE = 4
} Mtr_CtrlChDelayType;

/**
 *  \brief Type for MTR channel numbers
 *
 *  Type defines the channel numbers
 */
typedef enum
{
   MTR_CHANNEL_ID_0 = 0,
   MTR_CHANNEL_ID_1 = 1,
   MTR_CHANNEL_ID_2 = 2,
   MTR_CHANNEL_ID_3 = 3,
   MTR_CHANNEL_ID_SIZE = 4
} Mtr_ChannelIdType;

/**
*  \brief Type for channel names
*
*  This type defines all channel names
*/
typedef enum
{
    MTR_MTR1_COIL0_CHANNEL_0 = 0,
    MTR_MTR1_COIL1_CHANNEL_1,
    MTR_MTR2_COIL0_CHANNEL_2,
    MTR_MTR2_COIL1_CHANNEL_3,
    MTR_USED_NUMBER_OF_CHANNELS         /* Do not change this parameter */
} Mtr_ChannelNameType;

typedef enum
{
   MTR_CHANNEL_ACTIVE = 0,
   MTR_CHANNEL_INACTIVE,
   MTR_CHANNEL_NBR_OF_STATES
}Mtr_ChannelStatusType;


typedef void(*Mtr_TimerCounterOverflowInterruptFp)(void);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config struct ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 *  \brief Container for Channel settings
 *
 *  This type of data structure containing the configuration data for the MTR channels
 */
typedef struct
{
   Mtr_CtrlPrescalerType prescaler_e;
   Mtr_CtrlWaitModeType waitMode_e;
   Mtr_CtrlPwmResModeType resMode_e;
   Mtr_CtrlDitherFeatType dither_e;
   Mtr_CtrlMCTOIFType timerOVF_e;
   Mtr_CtrlRecircType reciric_e;
   Mtr_CtrlMCTOIEType timerEn_e;
   Mtr_CtrlPeriodType period_t;
   Mtr_TimerCounterOverflowInterruptFp timerOverflow_fp;
} Mtr_GeneralConfigType;

/**
 *  \brief Container for Channel settings
 *
 *  This type of data structure containing the configuration data for the MTR channels
 */
typedef struct
{
   Mtr_ChannelNumberType id_ui8;
   Mtr_CtrlChBridgeModeType bridge_mode_e;
   Mtr_CtrlChAlignType align_e;
   Mtr_CtrlChDelayType delay_e;
   Mtr_ChannelDutyCycleType duty_cyle_ui16;
   uint8 autostart_ui8;
} Mtr_ChannelConfigType;

/**
 *  \brief Container for Register settings
 *
 *  This type of data structure containing pointers to the configuration register of MTR module
 */
typedef struct
{
   uint8* regMCtl_0_pui8;
   uint8* regMCtl_1_pui8;
   uint16* regMPer_pui16;
} Mtr_RegisterType;

/**
 *  \brief Container for IO Pin Mapping
 *
 *  This type of data structure contains pointers to data and direction registers and corresponding bit of pwm channel
 */
typedef struct
{
   uint8* dataRegister_pui8;
   uint8* dirRegister_pui8;
   uint8 bit_ui8;
} Mtr_IoMapping;

/**
 *  \brief Container for Channel Group settings
 *
 *  This type of data structure containing the initialization data for the MTR driver
 */
typedef struct
{
   Mtr_GeneralConfigType volatile *mtr_generalConfiguration_ps;
   Mtr_ChannelConfigType const *mtr_channelConfiguration_pas;
   uint8 const mtr_usedNumberOfChannels_ui8;
} Mtr_ConfigType;


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 * \brief Function to initialize the MSN module.
 *
 * Initializes the MSN module.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */
void Mtr_Init (void);

/*
 * \brief Function to deinitialize the MTR module.
 *
 * Deinitializes the MTR module.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      E_OK: Deinitialization done
 *              E_NOT_OK: Something went wrong during deinitialization
 */
Std_ReturnType Mtr_DeInit (void);


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
Std_ModuleStatusReturnType Mtr_GetModuleStatus (void);
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */


#if (MTR_SET_DUTY_CYCLE_NORMAL_API == STD_ON)
extern void Mtr_SetDutyCycle (const Mtr_ChannelNameType chName_t, const Mtr_ChannelDutyCycleType dutyCycle_t);
#endif /* MTR_SET_DUTY_CYCLE_NORMAL_API == STD_ON */

Std_ReturnType Mtr_SetChannelStatus(const Mtr_ChannelNameType chName_t, const Mtr_ChannelStatusType chStatus_t);

#if (MTR_ISR_API == STD_ON)
Std_ReturnType Mtr_SetMotorInterrupt(Mtr_CtrlMCTOIEType irqStatus_e);
#endif

/*
 * \brief Function to update Mtr_ISR.
 *
 * Initializes the MSN module.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void update_Mtr_TimerCounterOverflowInterruptFp (void(*Mtr_TimerCounterOverflowInterruptFp)(void));

#if (MTR_SET_DUTY_CYCLE_FAST_API == STD_ON)
void Mtr_SetDutyCycleFast (
   const Mtr_ChannelNameType chName_t,
   const Mtr_ChannelDutyCycleType dutyCycle_t);
#endif /* MTR_SET_DUTY_CYCLE_FAST_API == STD_ON */

#if (MTR_SET_OUTPUT_TO_IDLE_API == STD_ON)
extern void Mtr_SetOutputToIdle (const Mtr_ChannelNameType chName_t);
#endif /* MTR_SET_OUTPUT_TO_IDLE_API == STD_ON */


#if (MTR_MODULE_STATE_API == STD_ON)
Std_ModuleStatusReturnType Mtr_GetModuleStatus (void);
#endif /* (MTR_MODULE_STATE_API == STD_ON) */


#if ((defined MTR_VERSION_INFO_API ) && (MTR_VERSION_INFO_API == STD_ON))
void Mtr_GetVersionInfo (Std_VersionInfoType *versioninfo);
#endif /* MTR_VERSION_INFO_API == STD_ON */

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void Mtr_ISR(void);
#pragma CODE_SEG DEFAULT

#endif /* MTR_H */
