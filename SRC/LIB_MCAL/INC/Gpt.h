#ifndef GPT_H
#define GPT_H

/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include <Std_Types.h>
#include "Gpt_Cfg.h"


/* ***************************** # defines ********************************** */
#define GPT_VENDOR_ID        99           /**<\brief CoSyst VendorID */
#define GPT_AR_MAJOR_VERSION 3            /**<\brief AUTOSAR major version */
#define GPT_AR_MINOR_VERSION 1            /**<\brief AUTOSAR minor version */
#define GPT_AR_PATCH_VERSION 0            /**<\brief AUTOSAR patch version */
#define GPT_SW_MAJOR_VERSION 0U            /**<\brief Software major version */
#define GPT_SW_MINOR_VERSION 1U            /**<\brief Software minor version */
#define GPT_SW_PATCH_VERSION 7U            /**<\brief Software patch version */
#define GPT_INSTANCE_ID      0U            /**<\brief Instance id */

/* GPT API IDs */
#define GPT_GET_VERSION_INFO_API_ID             ((uint8)0x00)
#define GPT_INIT_API_ID                         ((uint8)0x01)
#define GPT_DEINIT_API_ID                       ((uint8)0x02)
#define GPT_GET_TIME_ELAPSED_API_ID             ((uint8)0x03)
#define GPT_GET_TIME_REMAINING_API_ID           ((uint8)0x04)
#define GPT_START_TIMER_API_ID                  ((uint8)0x05)
#define GPT_STOP_TIMER_API_ID                   ((uint8)0x06)
#define GPT_ENABLE_NOTIFICATION_API_ID          ((uint8)0x07)
#define GPT_DISABLE_NOTIFICATION_API_ID         ((uint8)0x08)
#define GPT_SET_MODE_API_ID                     ((uint8)0x09)
#define GPT_DISABLE_WAKEUP_API_ID               ((uint8)0x0A)
#define GPT_ENABLE_WAKEUP_API_ID                ((uint8)0x0B)
#define GPT_CHECK_WAKEUP_API_ID                 ((uint8)0x0C)
#define GPT_CHECK_INIT_STATE_API_ID             ((uint8)0x0D)

/* [GPT065] Autosar conformance Error classification */
#define GPT_E_UNINIT                            ((uint8)0x0A)
#define GPT_E_BUSY                              ((uint8)0x0B)
#define GPT_E_NOT_STARTED                       ((uint8)0x0C)
#define GPT_E_ALREADY_INITIALIZED               ((uint8)0x0D)
#define GPT_E_PARAM_CHANNEL                     ((uint8)0x14)
#define GPT_E_PARAM_VALUE                       ((uint8)0x15)
#define GPT_E_PARAM_POINTER                     ((uint8)0x16)
#define GPT_E_PARAM_CONFIG                      ((uint8)0x1E)
#define GPT_E_PARAM_MODE                        ((uint8)0x1F)


/* ********************************* typedefs ************************************** */
/* ********************************* typedefs ************************************** */
typedef uint8 Gpt_MicroTimeValue; /**<\brief Type for micro time register    */
typedef uint16 Gpt_ValueType; /**<\brief Type for timer value            */
typedef void (*Gpt_CallBackFunc) (void); /**<\brief Type for callback notification  */

/* *********************************** enums *************************************** */

/** \b Description: Type for channel naming.
 *
 *  This type defines all channel names and the number of usable hardware channels.
 */
typedef enum
{
#if (GPT_ROM_OPTIMIZATION == STD_OFF)
    GPT_0_CHANNEL_0 = 0,
#endif
    GPT_0_CHANNEL_1,
#if (GPT_ROM_OPTIMIZATION == STD_OFF)
    GPT_0_CHANNEL_2,
    GPT_0_CHANNEL_3,
    GPT_0_CHANNEL_4,
    GPT_0_CHANNEL_5,
    GPT_0_CHANNEL_6,
    GPT_0_CHANNEL_7,
#endif
    GPT_NUMBER_OF_CHANNELS
} Gpt_ChannelType;

/**
 *  \brief Type for GPT prescaler.
 *  <br> This type defines possible values for the GPT clock prescaler.
 */
typedef enum
{
    GPT_PRESCALER_1 = 0,

    GPT_PRESCALER_2,
    GPT_PRESCALER_4,
    GPT_PRESCALER_8,
    GPT_PRESCALER_16,
    GPT_PRESCALER_32,
    GPT_PRESCALER_64,
    GPT_PRESCALER_128
} Gpt_PrescalerValueType;


/**
 *  \brief Type for gpt notification mode.
 *
 *  This type defines a range of specific status for Gpt interrupt notification.
 */
typedef enum
{
    GPT_NOTIFICATION_OFF = 0,
    GPT_NOTIFICATION_ON
} Gpt_NotifyEnableType;

/**
 *  \brief Type for gpt channel micro time base.
 *
 *  This type defines a range of specific status for the micro time base of a GPT channel.
 */
typedef enum
{
    GPT_CHANNEL_MUX_0 = 0,
    GPT_CHANNEL_MUX_1
} Gpt_MicroTimeBaseType;

/**
 *  \brief Type for the behavour of the gpt clock generator when in wait mode.
 *
 *  This type defines a range of specific status for the behavour when in wait mode.
 */
typedef enum
{
    GPT_STOP_IN_WAIT_DISABLED = 0,
    GPT_STOP_IN_WAIT_ENABLED
} Gpt_StopInWaitMode;

/**
 *  \brief Type for the behavour of the gpt clock counter when in freeze mode.
 *
 *  This type defines a range of specific status for the behavour when in freeze mode.
 */
typedef enum
{
    GPT_COUNTER_FREEZE_DISABLED = 0,
    GPT_COUNTER_FREEZE_ENABLED
} Gpt_FreezeInFreezeMode;

/**
 *  \brief Type for Gpt channel status.
 *
 *  This type defines a range of specific status for a Gpt channel.
 */
typedef enum
{
    GPT_INITIALIZED = 0,
    GPT_RUNNING,
    GPT_STOPPED,
    GPT_EXPIRED
} Gpt_ChannelOpModeType;

typedef enum
{
    GPT_PRECISION_TIMER_DISABLED = 0,
    GPT_PRECISION_TIMER_ENABLED = 1
} Gpt_PrecisionTimerMode;

/* **************************** macros ************************************** */

/* ***************************** structs ************************************ */
/**
 *  \brief Contains channel status information.
 *
 *  This type contains information about the channel status.
 */
typedef struct
{
    Gpt_ValueType period_ui16;         /**<\brief Channel prescaler. */
#if (GPT_NOTIFICATION_API == STD_ON)
    Gpt_NotifyEnableType notify_e;     /**<\brief Notify ON/OFF. */
#endif
} Gpt_ChannelStatusType;

/**
 *  \brief contains driver configuration
 *
 *  This type contains configuration for the Gpt driver
 */
typedef struct
{
    Gpt_StopInWaitMode stopInWaitMode_e;            /**<\brief clk generator stops when in wait mode */
    Gpt_FreezeInFreezeMode freezeInFreezeMode_e;    /**<\brief counters are freezed at breakpoint */
    Gpt_PrescalerValueType prescaler_e;             /**<\brief Prescaler  */
    Gpt_PrecisionTimerMode prcsnTimerMode_e;        /**<\brief Precision Timer */
    uint8 prcsnTimerPrescale_ui8;                   /**<\brief Precision Timer Prescaler */

} Gpt_DriverConfigType;


/* ***************************** global data ******************************** */

/* ***************************** local prototypes *************************** */

/* ***************************** global prototypes ************************** */
#if (GPT_VERSION_INFO_API == STD_ON)
/**
 *  \brief Retrieve the version info of the GPT module.
 *
 *  \param [in]  ---
 *  \param [out] VersionInfo = Pointer where version information should be stored.
 *  \return      ---
 */
void Gpt_GetVersionInfo (Std_VersionInfoType * const VersionInfo_ps);
#endif /* GPT_VERSION_INFO_API == STD_ON */

/**
 *  \brief Initialize the GPT module.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_Init (void);

#if (GPT_DEINIT_API == STD_ON)
/**
 *  \brief Reset the GPT module.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_DeInit (void);
#endif /* GPT_DEINIT_API == STD_ON */


#if (GPT_MODULE_STATE_API == STD_ON)
/*
* \brief This service returns the status of this module (DO NOT CHANGE).
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: MODULE_UNINIT, MODULE_DEINITIALIZED, MODULE_INITIALIZED
*/
Std_ModuleStatusReturnType Gpt_GetModuleStatus (void);
#endif /* (GPT_MODULE_STATE_API == STD_ON) */


/**
 *  \brief  Starts the selected timer channel with specified start value.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [in]  value_ui16 = Start value for the count down register.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_StartTimer (const Gpt_ChannelType channel_e, const Gpt_ValueType value_ui16);

/**
 *  \brief  Stops the selected timer channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return
 */
void Gpt_StopTimer (const Gpt_ChannelType channel_e);

#if (GPT_SET_PERIODE_API == STD_ON)
/**
 *  \brief  Enables the notification function of a timer channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_SetPeriode (const Gpt_ChannelType channel_e, const Gpt_ValueType value_ui16);
#endif

#if (GPT_NOTIFICATION_API == STD_ON)
/**
 *  \brief  Enables the notification function of a timer channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_EnableNotification (const Gpt_ChannelType channel_e);

/**
 *  \brief  Disables the notification function for a channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_DisableNotification (const Gpt_ChannelType channel_e);
#endif /* GPT_NOTIFICATION_API == STD_ON */

#if (GPT_GET_TIME_ELAPSED_API == STD_ON)
/**
 *  \brief  Returns the Timer value for a channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_GetTimeElapsed(Gpt_ValueType *value_ui16);
#endif /* GPT_GET_TIME_ELAPSED_API == STD_ON */

#if (GPT_TIM0_ISR0_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_0 (void);
#pragma CODE_SEG DEFAULT
#endif

#if (GPT_TIM0_ISR1_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_1 (void);
#pragma CODE_SEG DEFAULT
#endif

#if (GPT_TIM0_ISR2_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_2 (void);
#pragma CODE_SEG DEFAULT
#endif

#if (GPT_TIM0_ISR3_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_3 (void);
#pragma CODE_SEG DEFAULT
#endif

#if (GPT_TIM0_ISR4_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_4 (void);
#pragma CODE_SEG DEFAULT
#endif

#if (GPT_TIM0_ISR5_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_5 (void);
#pragma CODE_SEG DEFAULT
#endif

#if (GPT_TIM0_ISR6_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_6 (void);
#pragma CODE_SEG DEFAULT
#endif

#if (GPT_TIM0_ISR7_API == STD_ON)
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_7 (void);
#pragma CODE_SEG DEFAULT
#endif

#endif /* GPT_H */
