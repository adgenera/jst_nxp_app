/* ***************************** includes " " ******************************* */
#include "Gpt.h"
#include "Gpt_Cfg.h"

#include <CoSyst.h>

#if (GPT_DEV_ERROR_DETECT == STD_ON)
//#include "Det.h"
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */


#ifdef JUKEN_DEBUG_GPT
#include "Pwm_Cfg.h"
#endif /* JUKEN_DEBUG_GPT */

//#pragma CONST_SEG ROM_CONST

/* ***************************** # defines ********************************** */
#define GPT_VENDOR_ID_C        99 /**<\brief CoSyst VendorID */
#define GPT_AR_MAJOR_VERSION_C 3  /**<\brief AUTOSAR major version */
#define GPT_AR_MINOR_VERSION_C 1  /**<\brief AUTOSAR minor version */
#define GPT_AR_PATCH_VERSION_C 0  /**<\brief AUTOSAR patch version */
#define GPT_SW_MAJOR_VERSION_C 0U  /**<\brief SW major version */
#define GPT_SW_MINOR_VERSION_C 1U  /**<\brief SW minor version */
#define GPT_SW_PATCH_VERSION_C 7U  /**<\brief SW patch version */

#if((GPT_SW_MAJOR_VERSION_C != GPT_SW_MAJOR_VERSION) || \
    (GPT_SW_MINOR_VERSION_C != GPT_SW_MINOR_VERSION) || \
    (GPT_SW_PATCH_VERSION_C != GPT_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt.c and Gpt.h are different."
#endif /* (GPT_SW_MAJOR_VERSION_C != GPT_SW_MAJOR_VERSION) || ... */


#if (GPT_ROM_OPTIMIZATION == STD_ON)
#define GPT_TIM0_TIE_ENABLE(gpt_ch)       *((uint8* const) GPT_TIMER_REG_TIM0TIE_UI16 ) |= (uint8) (0x02U)
#define GPT_TIM0_TIE_DISABLE(gpt_ch)      *((uint8* const) GPT_TIMER_REG_TIM0TIE_UI16 ) &= (uint8) (~(0x02U))
#define GPT_TIM0_TFLG_RESET(gpt_ch)       *((uint8* const) GPT_TIMER_REG_TIM0TFLG1_UI16 ) |= (uint8) (0x02U)
#define GPT_TIM0_TCX_SET_EXPIRE(gpt_ch)   *((uint16* const) gpt_channelPeriodRegisters_aui16[(gpt_ch)]) = (uint16)(*((uint16* const)GPT_TIMER_REG_TIM0TCNT_UI16) + gpt_channelState_as[(gpt_ch)].period_ui16)
#else
#define GPT_TIM0_TIE_ENABLE(gpt_ch)       *((uint8* const) GPT_TIMER_REG_TIM0TIE_UI16 ) |= (uint8) (0x1 << gpt_ch)
#define GPT_TIM0_TIE_DISABLE(gpt_ch)      *((uint8* const) GPT_TIMER_REG_TIM0TIE_UI16 ) &= (uint8) (~(0x1 << gpt_ch))
#define GPT_TIM0_TFLG_RESET(gpt_ch)       *((uint8* const) GPT_TIMER_REG_TIM0TFLG1_UI16 ) |= (uint8) (0x1 << gpt_ch)
#define GPT_TIM0_TCX_SET_EXPIRE(gpt_ch)   *((uint16* const) gpt_channelPeriodRegisters_aui16[gpt_ch]) = (uint16)(*((uint16* const)GPT_TIMER_REG_TIM0TCNT_UI16) + gpt_channelState_as[gpt_ch].period_ui16)
#endif


/* ***************************** module global data ************************** */
extern const Gpt_DriverConfigType gpt_driverConfig_s;

#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/** \b Description: Driver status of the GPT module. */
static Std_ModuleStatusReturnType gpt_moduleState_e;
#endif

/** \b Description: Status array of the GPT channels. */
static volatile Gpt_ChannelStatusType gpt_channelState_as[GPT_NUMBER_OF_CHANNELS];


/* Register address tables */
static uint16 * const gpt_channelPeriodRegisters_aui16[GPT_NUMBER_OF_CHANNELS] =
{
#if (GPT_ROM_OPTIMIZATION == STD_OFF)
   (uint16 * const) GPT_TIMER_REG_TIM0TC0_UI16,
#endif
   (uint16 * const) GPT_TIMER_REG_TIM0TC1_UI16,
#if (GPT_ROM_OPTIMIZATION == STD_OFF)
   (uint16 * const) GPT_TIMER_REG_TIM0TC2_UI16,
   (uint16 * const) GPT_TIMER_REG_TIM0TC3_UI16,
   (uint16 * const) GPT_TIMER_REG_TIM0TC4_UI16,
   (uint16 * const) GPT_TIMER_REG_TIM0TC5_UI16,
   (uint16 * const) GPT_TIMER_REG_TIM0TC6_UI16,
   (uint16 * const) GPT_TIMER_REG_TIM0TC7_UI16
#endif
};


/* ***************************** module local functions *********************** */
#if (GPT_TIM0_ISR0_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT0 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_0 (void);
#endif

#if (GPT_TIM0_ISR1_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT1 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_1 (void);
#endif

#if (GPT_TIM0_ISR2_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT2 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_2 (void);
#endif

#if (GPT_TIM0_ISR3_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT3 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_3 (void);
#endif

#if (GPT_TIM0_ISR4_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT4 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_4 (void);
#endif

#if (GPT_TIM0_ISR5_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT5 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_5 (void);
#endif

#if (GPT_TIM0_ISR6_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT6 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_6 (void);
#endif

#if (GPT_TIM0_ISR7_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT7 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_7 (void);
#endif


/* ***************************** module global functions ********************* */
#pragma CODE_SEG DEFAULT

#if (GPT_VERSION_INFO_API == STD_ON)
/**
 *  \brief Retrieve the version info of the GPT module.
 *
 *  \param [in]  ---
 *  \param [out] VersionInfo = Pointer where version information should be stored.
 *  \return      ---
 */
void Gpt_GetVersionInfo (
   Std_VersionInfoType *VersionInfo_ps)
{
   /* ------ variables declaration ------ */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
   /* Check if version info is a NULL pointer */
   if(VersionInfo_ps == NULL_PTR)
   {
      Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_VERSION_INFO_API_ID, GPT_E_PARAM_POINTER);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
      /* fill version info structure with module information */
      VersionInfo_ps->moduleID = GPT_MODULE_ID;
      VersionInfo_ps->instanceID = GPT_INSTANCE_ID;
      VersionInfo_ps->sw_major_version = GPT_SW_MAJOR_VERSION;
      VersionInfo_ps->sw_minor_version = GPT_SW_MINOR_VERSION;
      VersionInfo_ps->sw_patch_version = GPT_SW_PATCH_VERSION;
   }
}
#endif /* GPT_VERSION_INFO_API == STD_ON */

/*
 *  \brief Initialize the GPT module.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_Init (void)
{
   /* ------ variables declaration ------ */
   /* Index used to cycle through channels */
   uint8 idx_ui8;
   uint8 channelId_ui8;

   /* ----- init internal variables ----- */
   channelId_ui8 = (uint8) 0U;

   /* ----------- source code ----------- */
#if(GPT_DEV_ERROR_DETECT == STD_ON)
   /* Check if module is already initialized */
   if(gpt_moduleState_e == MODULE_INITIALIZED)
   {
      //Det_ReportError(GPT_MODULE_ID,
      //         GPT_INSTANCE_ID,
      //         GPT_INIT_API_ID,
      //         GPT_E_ALREADY_INITIALIZED);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
      /* ------------------------------------------- */
      /* Initialize prescaler clock select registers */
      /* ------------------------------------------- */

      /* GPT_TIMER_REG_TIM0TSCR1_UI16, bit PRECISION TIMER (Bit 4, bit pos 3) may be written ONCE ONLY *
       * Therefore it's written in the end                                                             *
       */

      /* Initialize TIM0 channel registers before configuring individually */

      /* Timer Input Capture/Output Compare Select register */
      *((uint8* const ) GPT_TIMER_REG_TIM0TIOS_UI16 ) = (uint8) 0U;

      /* Timer Interrupt Enable register */
      *((uint8* const ) GPT_TIMER_REG_TIM0TIE_UI16 ) = (uint8) 0U;

      /* Main Timer Interrupt Flag 1 register */
      *((uint8* const ) GPT_TIMER_REG_TIM0TFLG1_UI16 ) = (uint8) 0U;

#if (GPT_ROM_OPTIMIZATION == STD_OFF)
      for (idx_ui8 = (uint8) 0U; idx_ui8 < (uint8) GPT_NUMBER_OF_CHANNELS; idx_ui8++)
      {
         /* Timer Input Capture/Output Compare Register 0 - 7 */
         *(gpt_channelPeriodRegisters_aui16[idx_ui8]) = (uint16) 0U;

         /* Timer Input Capture/Output Compare Select register */
         *((uint8* const ) GPT_TIMER_REG_TIM0TIOS_UI16 ) |= (uint8) (0x1 << idx_ui8);

         /* clear time out flag and enable interrupt if notification is STD_ON */
         /* Reset Main Timer Interrupt Flag 1 register */
         GPT_TIM0_TFLG_RESET( idx_ui8);

         gpt_channelState_as[idx_ui8].period_ui16 = (Gpt_ValueType)0U;
#if (GPT_NOTIFICATION_API == STD_ON)
         gpt_channelState_as[idx_ui8].notify_e = GPT_NOTIFICATION_OFF;
#endif
      }
#else
      /* Timer Input Capture/Output Compare Register 0 - 7 */
      *(gpt_channelPeriodRegisters_aui16[GPT_0_CHANNEL_1]) = (uint16) 0U;

      /* Timer Input Capture/Output Compare Select register */
      *((uint8* const ) GPT_TIMER_REG_TIM0TIOS_UI16 ) |= (uint8) (0x02U);

      /* clear time out flag and enable interrupt if notification is STD_ON */
      /* Reset Main Timer Interrupt Flag 1 register */
      GPT_TIM0_TFLG_RESET( 1 );

      gpt_channelState_as[GPT_0_CHANNEL_1].period_ui16 = (Gpt_ValueType)0U;
#if (GPT_NOTIFICATION_API == STD_ON)
         gpt_channelState_as[GPT_0_CHANNEL_1].notify_e = GPT_NOTIFICATION_OFF;
#endif
#endif

      /* Set timer base clock */
      *((uint8*) GPT_TIMER_REG_TIM0PTPSR_UI16 ) = gpt_driverConfig_s.prcsnTimerPrescale_ui8;

      /*  */
      *((uint8*) GPT_TIMER_REG_TIM0TSCR2_UI16 ) = (uint8) ((uint8) 0U
               | (gpt_driverConfig_s.prescaler_e << GPT_TIM0TSCR2_PR_BITPOS));

      /* Configure timer and start
       * GPT_TIMER_REG_TIM0TSCR1_UI16, bit PRECISION TIMER (Bit 4, bit pos 3) may be written ONCE ONLY
       * Therefore it's written here
       */
      *((uint8* const) GPT_TIMER_REG_TIM0TSCR1_UI16 ) = (uint8) ((uint8) 0U
               | ((gpt_driverConfig_s.prcsnTimerMode_e & 0x1) << GPT_TIM0TSCR1_PRNT_BITPOS)
               | ((gpt_driverConfig_s.freezeInFreezeMode_e & 0x1) << GPT_TIM0TSCR1_TSFRZ_BITPOS)
               | ((gpt_driverConfig_s.stopInWaitMode_e & 0x1) << GPT_TIM0TSCR1_TSWAI_BITPOS)
               | (0x1 << GPT_TIM0TSCR1_TEN_BITPOS));

      /* -------------------------------- */
      /* Set driver status to initialized */
      /* -------------------------------- */
#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
      gpt_moduleState_e = MODULE_INITIALIZED;
#endif

#ifdef JUKEN_DEBUG_GPT
      *((uint8 * const)PWM_PORT_P_DATA_DIR_REG_ADR_UI16) |= 128;

      Gpt_StartTimer (GPT_0_CHANNEL_7, 1);
#endif /* JUKEN_DEBUG_GPT */
   }
}

#if (GPT_DEINIT_API == STD_ON)
/**
 *  \brief Reset the GPT module.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_DeInit (void)
{
   /* ------ variables declaration ------ */
   /* Index to cycle through channels */
   uint8 idx_ui8;

   /* ----- init internal variables ----- */
   idx_ui8 = (uint8) 0U;

   /* ----------- source code ----------- */
#if(GPT_DEV_ERROR_DETECT == STD_ON)
   /* Check if module is not yet initialized */
   if(gpt_moduleState_e == MODULE_UNINIT)
   {
      Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_API_ID, GPT_E_UNINIT);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
#if (GPT_NOTIFICATION_API == STD_ON)
      for (idx_ui8 = (uint8) 0U; idx_ui8 < (uint8) GPT_NUMBER_OF_CHANNELS; idx_ui8++)
      {
         /* Disable the group notification for all channels */
         Gpt_DisableNotification ((Gpt_ChannelType) idx_ui8);
      }
#endif /* GPT_NOTIFICATION_API == STD_ON */

      /* DeInitialize TIM0 channel registers before configuring individually */

      /* Timer Input Capture/Output Compare Select register */
      *((uint8*) GPT_TIMER_REG_TIM0TIOS_UI16 ) = (uint8) 0U;

      /* Timer Interrupt Enable register */
      *((uint8*) GPT_TIMER_REG_TIM0TIE_UI16 ) = (uint8) 0U;

      /* Main Timer Interrupt Flag 1 register */
      *((uint8*) GPT_TIMER_REG_TIM0TFLG1_UI16 ) = (uint8) 0U;

      for (idx_ui8 = (uint8)0U; idx_ui8 < (uint8) GPT_NUMBER_OF_CHANNELS; idx_ui8++)
      {
         /* Timer Input Capture/Output Compare Register 0 - 7 */
         *(gpt_channelPeriodRegisters_aui16[idx_ui8]) = (uint16) 0U;

         /* ------------------------------- */
         /* Uninitialize channel status array */
         /* ------------------------------- */
         /* Copy and initialize channel properties */
         /* fill channels with information */

         /* copy channel ID information */
         gpt_channelState_as[idx_ui8].id_e = (Gpt_ChannelType) 0U;
         gpt_channelState_as[idx_ui8].period_ui16 = (uint16) 0U;

         /* copy callback function information */
         gpt_channelState_as[idx_ui8].cbckISR_pv = NULL_PTR;
      }

      *((uint8*) GPT_TIMER_REG_TIM0TSCR1_UI16 ) = (uint8) 0U;
      *((uint8*) GPT_TIMER_REG_TIM0PTPSR_UI16 ) = (uint8) 0U;
      *((uint8*) GPT_TIMER_REG_TIM0TSCR2_UI16 ) = (uint8) 0U;

      /* Set driver status to uninitialized */
      gpt_moduleState_e = MODULE_UNINIT;
   }
}
#endif /* GPT_DEINIT_API == STD_ON */


#if (GPT_MODULE_STATE_API == STD_ON)
/*
 *  \brief Returns module state
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      Driver state: MODULE_UNINIT
 *                             MODULE_INITIALIZED
 */
Std_ModuleStatusReturnType Gpt_GetModuleStatus (void)
{
   return gpt_moduleState_e;
}
#endif /* (GPT_MODULE_STATE_API == STD_ON) */


/**
 *  \brief  Starts the selected timer channel with specified start value.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [in]  value_ui16 = Start value for the count down register.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_StartTimer (const Gpt_ChannelType channel_e, const Gpt_ValueType value_ui16)
{
#if(GPT_DEV_ERROR_DETECT == STD_ON)
   /* Check if Channel is valid */
   if(channel_e >= GPT_NUMBER_OF_CHANNELS)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_API_ID, GPT_E_PARAM_CHANNEL);
   }
   /* Check if driver is initialized */
   else if(gpt_moduleState_e == MODULE_UNINIT)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_API_ID, GPT_E_UNINIT);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
      /* save Value in channel runtime configuration before copy config */
      gpt_channelState_as[channel_e].period_ui16 = value_ui16;

      /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
      GPT_TIM0_TCX_SET_EXPIRE (channel_e);

      /* Reset main timer interrupt flag 1 register */
      GPT_TIM0_TFLG_RESET (channel_e);

      /* Enable timer interrupt */
      GPT_TIM0_TIE_ENABLE (channel_e);
   }
}

/**
 *  \brief  Stops the selected timer channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return
 */
void Gpt_StopTimer (const Gpt_ChannelType channel_e)
{
#if(GPT_DEV_ERROR_DETECT == STD_ON)
   /* Check if channel is valid */
   if(channel_e >= GPT_NUMBER_OF_CHANNELS)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_STOP_TIMER_API_ID, GPT_E_PARAM_CHANNEL);
   }
   /* Check if Driver is initialized */
   else if(gpt_moduleState_e == MODULE_UNINIT)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_STOP_TIMER_API_ID, GPT_E_UNINIT);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
      /* Timer Interrupt Enable register */
      GPT_TIM0_TIE_DISABLE (channel_e);
      /* Reset timer interrupt flag 1 register */
      GPT_TIM0_TFLG_RESET (channel_e);
   }
}

#if (GPT_SET_PERIODE_API == STD_ON)
/**
 *  \brief  Enables the notification function of a timer channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_SetPeriode (const Gpt_ChannelType channel_e, const Gpt_ValueType value_ui16)
{
   /* save Value in channel runtime configuration before copy config it will be used by expiring the timer next time*/
   gpt_channelState_as[channel_e].period_ui16 = value_ui16;
}
#endif

#if (GPT_NOTIFICATION_API == STD_ON)
/**
 *  \brief  Enables the notification function of a timer channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_EnableNotification (const Gpt_ChannelType channel_e)
{
   /* ------ variables declaration ------ */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
#if(GPT_DEV_ERROR_DETECT == STD_ON)
   /* Check if channel is valid */
   if(channel_e >= GPT_NUMBER_OF_CHANNELS)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_API_ID, GPT_E_PARAM_CHANNEL);
   }
   /* Check if driver is initialized */
   else if(gpt_moduleState_e == MODULE_UNINIT)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFICATION_API_ID, GPT_E_UNINIT);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
      gpt_channelState_as[channel_e].notify_e = GPT_NOTIFICATION_ON;
   }
}

/**
 *  \brief  Disables the notification function for a channel.
 *
 *  \param [in]  channel_e = Numeric ID of the channel.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_DisableNotification (const Gpt_ChannelType channel_e)
{
   /* ------ variables declaration ------ */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
#if(GPT_DEV_ERROR_DETECT == STD_ON)
   /* Check if channel is valid */
   if(channel_e >= GPT_NUMBER_OF_CHANNELS)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFICATION_API_ID, GPT_E_PARAM_CHANNEL);
   }
   /* Check if driver is initialized */
   else if (gpt_moduleState_e == MODULE_UNINIT)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFICATION_API_ID, GPT_E_UNINIT);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
      gpt_channelState_as[channel_e].notify_e = GPT_NOTIFICATION_OFF;
   }
}
#endif /* GPT_***_API == STD_ON */

#if (GPT_GET_TIME_ELAPSED_API == STD_ON)
/**
 *  \brief  Returns the Timer value for a channel.
 *
 *  \param [in]  value_pui16 = Value of Timer0 register.
 *  \param [out] ---
 *  \return      ---
 */
void Gpt_GetTimeElapsed(Gpt_ValueType *value_pui16)
{
   /* ------ variables declaration ------ */
	Gpt_ValueType *gpt_regPtr_pui16;

   /* ----- init internal variables ----- */
	gpt_regPtr_pui16 = (Gpt_ValueType*) GPT_TIMER_REG_TIM0TCNT_UI16;
   /* ----------- source code ----------- */
#if(GPT_DEV_ERROR_DETECT == STD_ON)
   if(gpt_moduleState_e == MODULE_UNINIT)
   {
      //Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFICATION_API_ID, GPT_E_UNINIT);
   }
   else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
   {
      *value_pui16 = *gpt_regPtr_pui16;
   }
}
#endif /* GPT_GET_TIME_ELAPSED_API == STD_ON */

#if (GPT_TIM0_ISR0_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT0 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_0 (void)
{
#if (GPT_TIM0_CH0_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif
   /* Main Timer Interrupt Flag 1 register */
   GPT_TIM0_TFLG_RESET (GPT_0_CHANNEL_0);

   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_0);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH0_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_0);
#endif

#if(GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH0_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_0].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH0_CBCK();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */

#if (GPT_TIM0_CH0_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
}
#endif

#if (GPT_TIM0_ISR1_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT1 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_1 (void)
{
   /* Clear Interrupt Bit to allow nested Interrupts */
   asm(CLI);
#if (GPT_TIM0_CH1_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif
   /* Main Timer Interrupt Flag 1 register */
   GPT_TIM0_TFLG_RESET(GPT_0_CHANNEL_1);

   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_1);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH1_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_1);
#endif

#if (GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH1_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_1].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH1_CBCK ();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */
#if (GPT_TIM0_CH1_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
}
#endif

#if (GPT_TIM0_ISR2_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT2 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_2 (void)
{
   /* Clear Interrupt Bit to allow nested Interrupts */
   asm(CLI);
#if (GPT_TIM0_CH2_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif
   /* Main Timer Interrupt Flag 1 register */
   *((uint8*) GPT_TIMER_REG_TIM0TFLG1_UI16 ) |= (uint8) (0x1 << GPT_0_CHANNEL_2);

   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_2);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH2_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_2);
#endif

#if(GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH2_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_2].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH2_CBCK ();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */
#if (GPT_TIM0_CH2_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
}
#endif

#if (GPT_TIM0_ISR3_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT0 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_3 (void)
{
   /* Clear Interrupt Bit to allow nested Interrupts */
   asm(CLI);
#if (GPT_TIM0_CH3_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif
   /* Main Timer Interrupt Flag 1 register */
   GPT_TIM0_TFLG_RESET (GPT_0_CHANNEL_3);

   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_3);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH3_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_3);
#endif

#if(GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH3_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_3].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH3_CBCK ();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */
#if (GPT_TIM0_CH3_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
}
#endif


#if (GPT_TIM0_ISR4_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT4 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_4 (void)
{
   /* Clear Interrupt Bit to allow nested Interrupts */
   asm(CLI);
#if (GPT_TIM0_CH4_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif
   /* Main Timer Interrupt Flag 1 register */
   GPT_TIM0_TFLG_RESET (GPT_0_CHANNEL_4);

   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_4);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH4_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_4);
#endif

#if(GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH4_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_4].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH4_CBCK ();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */
#if (GPT_TIM0_CH4_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
}
#endif


#if (GPT_TIM0_ISR5_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT5 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_5 (void)
{
   /* Clear Interrupt Bit to allow nested Interrupts */
   asm(CLI);
#if (GPT_TIM0_CH5_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif

   /* Main Timer Interrupt Flag 1 register */
   GPT_TIM0_TFLG_RESET (GPT_0_CHANNEL_5);

   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_5);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH5_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_5);
#endif

#if(GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH5_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_5].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH5_CBCK ();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */
#if (GPT_TIM0_CH5_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
}
#endif


#if (GPT_TIM0_ISR6_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT6 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_6 (void)
{
   /* Clear Interrupt Bit to allow nested Interrupts */
   asm(CLI);
#if (GPT_TIM0_CH6_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif
   /* Main Timer Interrupt Flag 1 register */
   GPT_TIM0_TFLG_RESET (GPT_0_CHANNEL_6);

   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_6);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH6_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_6);
#endif

#if(GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH6_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_6].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH6_CBCK ();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */
#if (GPT_TIM0_CH6_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
}
#endif


#if (GPT_TIM0_ISR7_API == STD_ON)
/**
 *  \brief Interrupt service routine of the PIT7 timer channel.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      ---
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ISR_Periodic_IRQ_TIM0_7 (void)
{
   /* Clear Interrupt Bit to allow nested Interrupts */
   asm(CLI);
   /* Main Timer Interrupt Flag 1 register */
   GPT_TIM0_TFLG_RESET (GPT_0_CHANNEL_7);

#ifdef JUKEN_DEBUG_GPT

   if ((*((uint8 * const ) PWM_PORT_P_DATA_REG_ADR_UI16) & 128) == 128)
   {
      *((uint8 * const ) PWM_PORT_P_DATA_REG_ADR_UI16) &= ~128;
   }
   else
   {
      *((uint8 * const ) PWM_PORT_P_DATA_REG_ADR_UI16) |= 128;
   }
   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_7);

#else
#if (GPT_TIM0_CH1_INTERRUPT == STD_ON)
   DISABLE_ALL_INTERRUPTS();
#endif
   /* Set expire time index - it is copied from gpt_channelState_as[channel_e].period_ui16 */
   GPT_TIM0_TCX_SET_EXPIRE (GPT_0_CHANNEL_7);

   /* Stop timer channel if it is in one-shot-mode */
#if (GPT_TIM0_CH7_OPMODE == GPT_CH_MODE_ONESHOT)
   /* Disable Timer Interrupt Enable register */
   GPT_TIM0_TIE_DISABLE (GPT_0_CHANNEL_7);
#endif

#if(GPT_NOTIFICATION_API == STD_ON)
#if (defined GPT_TIM0_CH7_CBCK)
   /* Call configured notification callback function, if notification is activated */
   if (gpt_channelState_as[GPT_0_CHANNEL_7].notify_e == GPT_NOTIFICATION_ON)
   {
      GPT_TIM0_CH7_CBCK ();
   }
#endif
#endif /* GPT_NOTIFICATION_API == STD_ON */
#if (GPT_TIM0_CH7_INTERRUPT == STD_ON)
   ENABLE_ALL_INTERRUPTS();
#endif
#endif /* JUKEN_DEBUG_GPT */
}
#endif

#pragma CODE_SEG DEFAULT
