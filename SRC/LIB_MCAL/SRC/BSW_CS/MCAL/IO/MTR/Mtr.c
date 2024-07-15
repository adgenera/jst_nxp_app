/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Mtr.h"
#include "Mtr_Lcfg.h"

/* ***************************** # defines ********************************** */
#define MTR_VENDOR_ID_C        99 /**<\brief CoSyst VendorID */
#define MTR_AR_MAJOR_VERSION_C 3  /**<\brief AUTOSAR major version */
#define MTR_AR_MINOR_VERSION_C 1  /**<\brief AUTOSAR minor version */
#define MTR_AR_PATCH_VERSION_C 0  /**<\brief AUTOSAR patch version */
#define MTR_SW_MAJOR_VERSION_C 1  /**<\brief SW major version */
#define MTR_SW_MINOR_VERSION_C 0  /**<\brief SW minor version */
#define MTR_SW_PATCH_VERSION_C 0  /**<\brief SW patch version */

/* version check */
#if (MTR_VENDOR_ID_C != MTR_VENDOR_ID)
#error "Mtr.c and Mtr.h have different vendor ids."
#endif /* MTR_VENDOR_ID_C != MTR_VENDOR_ID */

#if ((MTR_AR_MAJOR_VERSION_C != MTR_AR_MAJOR_VERSION) || \
     (MTR_AR_MINOR_VERSION_C != MTR_AR_MINOR_VERSION) || \
     (MTR_AR_PATCH_VERSION_C != MTR_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Mtr.c and Mtr.h are different."
#endif   /* (MTR_AR_MAJOR_VERSION_C != MTR_AR_MAJOR_VERSION) || ... */

#if ((MTR_SW_MAJOR_VERSION_C != MTR_SW_MAJOR_VERSION) || \
     (MTR_SW_MINOR_VERSION_C != MTR_SW_MINOR_VERSION) || \
     (MTR_SW_PATCH_VERSION_C != MTR_SW_PATCH_VERSION))
#error "Software Version Numbers of Mtr.c and Mtr.h are different."
#endif /* (MTR_SW_MAJOR_VERSION_C != MTR_SW_MAJOR_VERSION) || ... */

/* ***************************** modul global data ************************** */

#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/* @brief Contains the status of the mtr driver */
static Std_ModuleStatusReturnType mtr_moduleState_e = MODULE_UNINIT;
#endif

/* @brief Array for the configuration of the pwm channels */
static Mtr_ChannelConfigType mtr_channelConfig_as[MTR_USED_NUMBER_OF_CHANNELS];

/* Struct contains pointer to the register of the mtr module */
volatile const Mtr_RegisterType mtr_register_s =
{
   (uint8 * const ) MTR_CTRL_MCCTL0_ADR_UI16,
   (uint8 * const ) MTR_CTRL_MCCTL1_ADR_UI16,
   (uint16 * const ) MTR_CTRL_MCPER_ADR_UI16
};

/* Array contains pointer to the pwm channel period register */
volatile const uint8* const mtr_channelConfigReg_apui8[] =
{
   (uint8 * const ) MTR_CTRL_MCCC0_ADR_UI16,
   (uint8 * const ) MTR_CTRL_MCCC1_ADR_UI16,
   (uint8 * const ) MTR_CTRL_MCCC2_ADR_UI16,
   (uint8 * const ) MTR_CTRL_MCCC3_ADR_UI16,
};

/* Array contains pointer to the pwm channel duty cycle register */
volatile const uint16* const mtr_channelDutyCycleReg_apui16[] =
{
   (uint16 * const ) MTR_CTRL_MCDC0_ADR_UI16,
   (uint16 * const ) MTR_CTRL_MCDC1_ADR_UI16,
   (uint16 * const ) MTR_CTRL_MCDC2_ADR_UI16,
   (uint16 * const ) MTR_CTRL_MCDC3_ADR_UI16,
};

#if 0 /* UNUSED */
volatile const Mtr_IoMapping mtr_ioMapping[] =
{
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 0 },
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 1 },
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 2 },
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 3 },
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 4 },
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 5 },
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 6 },
{ (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16, (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16, 7 } };

/* pointer to the data Register of port P */
uint8* const mtr_portPDataReg_pui8 = (uint8 * const ) MTR_PORT_V_DATA_REG_ADR_UI16;
/* pointer to the input Register of port P */
uint8* const mtr_portPInputReg_pui8 = (uint8 * const ) MTR_PORT_V_INPUT_REG_ADR_UI16;
/* pointer to the data direction register of port P */
uint8* const mtr_portPDataDirReg_pui8 = (uint8 * const ) MTR_PORT_V_DATA_DIR_REG_ADR_UI16;
#endif

/* ***************************** global data ******************************** */

static Mtr_ConfigType * mtr_config_ps;

/* ***************************** modul global functions ********************* */

/* ***************************** global functions *************************** */
void update_Mtr_TimerCounterOverflowInterruptFp (void(*Mtr_TimerCounterOverflowInterruptFp)(void))
{
	mtr_config_ps->mtr_generalConfiguration_ps->timerOverflow_fp = Mtr_TimerCounterOverflowInterruptFp;
}

/*
 *  \brief Service for MTR initialization.
 *
 *  \param [in]  ---
 *
 *  \param [out] ---
 *  \return      ---
 */
void Mtr_Init (void)
{
   /* -- variables declaration ---------------- */
   uint8 mtr_CfgName_ui8;
   uint8 mtr_channelId_ui8;

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */

   /* Get pointer to link time configuration*/
   mtr_config_ps = (Mtr_ConfigType*) Mtr_GetLcfgData ();

#if (MTR_DEV_ERROR_DETECT == STD_ON)
   if (mtr_moduleState_e == MODULE_INITIALIZED)
   {
      //(void) Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID,
      //         MTR_INIT_API_ID, MTR_E_ALREADY_INITIALIZED);
   }
   else if (mtr_config_ps == NULL_PTR) /* Safety request */
   {
      //(void) Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID,
      //        MTR_INIT_API_ID, MTR_E_PARAM_CONFIG);
   }
   else
#endif /* MTR_DEV_ERROR_DETECT == STD_ON */
   {
      *(mtr_register_s.regMCtl_0_pui8) = (uint8) ((uint8) 0U
                  | (mtr_config_ps->mtr_generalConfiguration_ps->timerOVF_e & MCCTL0_MCTOIF_MASK)
                  | (((mtr_config_ps->mtr_generalConfiguration_ps->dither_e) << 2) & MCCTL0_DITH_MASK)
                  | (((mtr_config_ps->mtr_generalConfiguration_ps->resMode_e) << 3) & MCCTL0_FAST_MASK)
                  | (((mtr_config_ps->mtr_generalConfiguration_ps->waitMode_e) << 4) & MCCTL0_MCSWAI_MASK)
                  | (((mtr_config_ps->mtr_generalConfiguration_ps->prescaler_e) << 5) & MCCTL0_MCPRE_MASK));

      *(mtr_register_s.regMCtl_1_pui8) = (uint8) ((uint8) 0U
                  | ((mtr_config_ps->mtr_generalConfiguration_ps->timerEn_e) & MCCTL1_MCTOIE_MASK)
                  | (((mtr_config_ps->mtr_generalConfiguration_ps->reciric_e) << 7) & MCCTL1_RECIRC_MASK));

      *(mtr_register_s.regMPer_pui16) = (uint16) (((uint16) mtr_config_ps->mtr_generalConfiguration_ps->period_t)
                  & MCPER_P_MASK);

      /* Preinitialize all channels with zeros */
      for (mtr_channelId_ui8 = 0; mtr_channelId_ui8 < MTR_CHANNEL_ID_SIZE; mtr_channelId_ui8++)
      {
         *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_channelId_ui8]) = (uint8) 0;

         /* Motor controller duty register is initialized */
         /* Preinitialize with zeros */
         *((uint16 * const ) mtr_channelDutyCycleReg_apui16[mtr_channelId_ui8]) = (uint16) 0;
      }

#if (MTR_ISR_API == STD_ON)
      /* Configure Interrupt */
      if ( mtr_config_ps->mtr_generalConfiguration_ps->timerEn_e == MTR_CTRL_MCTOIE_ENABLE )
      {
         if (mtr_config_ps->mtr_generalConfiguration_ps->timerOverflow_fp != ((Mtr_TimerCounterOverflowInterruptFp)NULL_PTR) )
         {
            *(mtr_register_s.regMCtl_1_pui8) |= (uint8) MCCTL1_MCTOIE_MASK; /* Enable Interrupt */
         }
         else
         {
#if (MTR_DEV_ERROR_DETECT == STD_ON)
            //(void) Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID,
            //         MTR_INIT_API_ID, MTR_E_NULLPOINTER);
#endif
            /* Produce Strange Errors */
         }
      }
#endif

      /* Configure channels */
      for (mtr_CfgName_ui8 = 0; mtr_CfgName_ui8 < mtr_config_ps->mtr_usedNumberOfChannels_ui8; mtr_CfgName_ui8++)
      {
         mtr_channelId_ui8 = mtr_config_ps->mtr_channelConfiguration_pas[mtr_CfgName_ui8].id_ui8;

         /* --------------- Initialize idle state ---------------- */
         /* Write init values in modul global config */
         /* Channel ID */
         mtr_channelConfig_as[mtr_CfgName_ui8].id_ui8 = mtr_config_ps->mtr_channelConfiguration_pas[mtr_CfgName_ui8].id_ui8;
         /* Bridge mode */
         mtr_channelConfig_as[mtr_CfgName_ui8].bridge_mode_e = mtr_config_ps->mtr_channelConfiguration_pas[mtr_CfgName_ui8].bridge_mode_e;
         /* Alignment */
         mtr_channelConfig_as[mtr_CfgName_ui8].align_e = mtr_config_ps->mtr_channelConfiguration_pas[mtr_CfgName_ui8].align_e;
         /* Delay */
         mtr_channelConfig_as[mtr_CfgName_ui8].delay_e = mtr_config_ps->mtr_channelConfiguration_pas[mtr_CfgName_ui8].delay_e;
         /* Duty cycle */
         mtr_channelConfig_as[mtr_CfgName_ui8].duty_cyle_ui16 = mtr_config_ps->mtr_channelConfiguration_pas[mtr_CfgName_ui8].duty_cyle_ui16;
         /* Auto start */
         mtr_channelConfig_as[mtr_CfgName_ui8].autostart_ui8 = mtr_config_ps->mtr_channelConfiguration_pas[mtr_CfgName_ui8].autostart_ui8;

         /* Configure all values except duty cycle and align */
         *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_channelId_ui8]) =
                     (uint8) ((((mtr_channelConfig_as[mtr_CfgName_ui8].bridge_mode_e << MTR_CTRL_MCCC_MCOM_BITNUM )
                                 & MTR_CTRL_MCCC_MCOM_MASK )
                                 | ((mtr_channelConfig_as[mtr_CfgName_ui8].delay_e << MTR_CTRL_MCCC_CD_BITNUM )
                                             & MTR_CTRL_MCCC_CD_MASK )) & (~MTR_CTRL_MCCC_MCAM_MASK ));

         /* ------------- Initialize registers already done ------------- */
         /* auto start pwm if configured */
         if (mtr_channelConfig_as[mtr_CfgName_ui8].autostart_ui8 == (uint8) STD_ON)
         {
            if (mtr_config_ps->mtr_generalConfiguration_ps->resMode_e == MTR_CTRL_PWM_RESOLUTION_NORMAL)
            {
               /* Normal resolution */
               *((uint16 * const ) mtr_channelDutyCycleReg_apui16[mtr_channelId_ui8]) =
                           mtr_channelConfig_as[mtr_CfgName_ui8].duty_cyle_ui16 & MTR_CTRL_MCDC_D0_D10_S_MASK_UI16;
            }
            else
            {
               /* Fast mode */
               *((uint16 * const ) mtr_channelDutyCycleReg_apui16[mtr_channelId_ui8]) =
                           mtr_channelConfig_as[mtr_CfgName_ui8].duty_cyle_ui16 & MTR_CTRL_MCDC_FAST_D2_D8_S_MASK_UI16;
            }

            /* activate channel last - register MCAM bits were set to zero before */
            *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_channelId_ui8]) |=
                        ((mtr_channelConfig_as[mtr_CfgName_ui8].align_e << MTR_CTRL_MCCC_MCAM_BITNUM )
                                    & MTR_CTRL_MCCC_MCAM_MASK );
         }
      }

#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
      /* Set driver status to initialized */
      mtr_moduleState_e = MODULE_INITIALIZED;
#endif
   }
}

#if (MTR_DEINIT_API == STD_ON)
/**
 *  \brief Service for PWM De-Initialization \n
 *  \n
 *  PWM010: The function Pwm_DeInit shall de-initialize the PWM module. \n
 *  \n
 *  PWM011: The function Pwm_DeInit shall set the state of the PWM output \n
 *  signals to the idle state. \n
 *
 *  PWM012: The function Pwm_DeInit shall disable PWM interrupts and PWM signal
 *  edge notifications.
 *
 *  PWM080: The function Pwm_DeInit shall be pre compile time configurable
 *  On/Off by the configuration parameter: PwmDeInitApi.
 *
 *  Regarding error detection, the requirements PWM117 and PWM051 are applicable
 *  to the function Pwm_DeInit.
 *
 *  \param [in]  ---
 *  \param [out] ---
 *  \return      E_OK:     on success
 *               E_NOT_OK: else
 */
Std_ReturnType Mtr_DeInit (void)
{
   /* --- local variable declaration --- */
   Std_ReturnType ret_t = E_OK;
   uint8 mtr_ChCtr_ui8;
   uint8 mtr_currChId_ui8;

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
#if (MTR_DEV_ERROR_DETECT == STD_ON)
   if (mtr_moduleState_e != MODULE_INITIALIZED) /* Safety request */
   {
      Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID,
                  MTR_DEINIT_API_ID, MTR_E_UNINIT);
      ret_t = E_NOT_OK;
   }
   else /* MTR_DEV_ERROR_DETECT == STD_ON */
#endif
   {
      /* Disable all PWM Channels before resetting MCPER to avoid a peak */
      for (mtr_ChCtr_ui8 = 0; mtr_ChCtr_ui8 < MTR_USED_NUMBER_OF_CHANNELS; mtr_ChCtr_ui8++)
      {
         /* Get Channel ID */
         mtr_currChId_ui8 = mtr_channelConfig_as[mtr_ChCtr_ui8].id_ui8;

         /* Stop channel output - write zeros */
         *((uint16 * const ) mtr_channelConfigReg_apui8[mtr_currChId_ui8]) = (uint8) 0;

         /* Reset motor controller duty register - write zeros */
         *((uint16 * const ) mtr_channelDutyCycleReg_apui16[mtr_currChId_ui8]) = (uint16) 0;

         /* IO mapping for output ports */
         /* Set data direction of port hardware to output state */
         *(mtr_ioMapping[mtr_currChId_ui8].dirRegister_pui8) |= (0x01
                 << mtr_ioMapping[mtr_currChId_ui8].bit_ui8);

         *(mtr_ioMapping[mtr_currChId_ui8].dataRegister_pui8) &= ~((uint8) (0x01
                 << mtr_ioMapping[mtr_currChId_ui8].bit_ui8));
      }

      /* Reset motor controller configuration */
      /* Reset period register after channels were disabled to avoid a peak */
      *(mtr_register_s.regMPer_pui16) = (uint16) 0U;
      /* Reset config registers */
      *(mtr_register_s.regMCtl_0_pui8) = (uint8) 0U;
      *(mtr_register_s.regMCtl_1_pui8) = (uint8) 0U;

      mtr_moduleState_e = MODULE_UNINIT;
   }

   return ret_t;
}

#endif /* MTR_DEINIT_API == STD_ON */


#if (MTR_SET_DUTY_CYCLE_NORMAL_API == STD_ON)
/**
 *  \brief Service sets the duty cycle of the PWM channel.
 *
 *  The function Pwm_SetDutyCycle shall set the duty cycle of the PWM channel.
 *
 *  \req #CS_REQ_000052 - The software shall control both stepper motors by PWM-Outputs of the MCU via internal drivers
 *
 *  \param [in]  ChannelNummer =  Numeric identifier of the PWM
 *  \param [in]  DutyCycle  =  Min=0x0000
 *                             Max=0x8000
 *  \param [out] ---
 *  \return      ---
 */
void Mtr_SetDutyCycle (
   const Mtr_ChannelNameType chName_t,
   const Mtr_ChannelDutyCycleType dutyCycle_t)
{
   /* --- local variable declaration --- */
   uint8 mtr_channelId_ui8;

   /* ----- init internal variables ----- */
   mtr_channelId_ui8 = (uint8) 0U;

   /* ----------- source code ----------- */
#if (MTR_DEV_ERROR_DETECT == STD_ON)
   if (mtr_moduleState_e != MODULE_INITIALIZED) /* Savety request */
   {
      //Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID, MTR_SET_DUTYCYCLE_API_ID, MTR_E_UNINIT);
   }
   else
#endif /*MTR_DEV_ERROR_DETECT == STD_ON */
   {
      /* Get corresponding Channel ID from module global channel configuration */
      mtr_channelId_ui8 = mtr_channelConfig_as[chName_t].id_ui8;

      /* Write Duty Cycle as 16 bit access to the two corresponding concatenated 8 bit Registers */
      /* Normal resolution */
      *((uint16 * const ) mtr_channelDutyCycleReg_apui16[mtr_channelId_ui8]) = (dutyCycle_t
                  & MTR_CTRL_MCDC_D0_D10_S_MASK_UI16 );

      /* activate channel last - register MCAM bits were set to zero before */
      *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_channelId_ui8]) |= ((mtr_channelConfig_as[chName_t].align_e
                  << MTR_CTRL_MCCC_MCAM_BITNUM ) & MTR_CTRL_MCCC_MCAM_MASK );
   }
}
#endif /* MTR_SET_DUTY_CYCLE_NORMAL_API == STD_ON */

/**
 *  \brief Service to deactivate/activate PWM channel.
 *
 *  The function Mtr_SetChanelStatus shall activate/deactivate the coresponding PWM Channel
 *
 *  \param [in]  ChannelNummer =  Numeric identifier of the PWM
 *  \param [in]  ChannelStatus  = MTR_CHANNEL_ACTIVE
 *                                MTR_CHANNEL_INACTIVE
 *  \return      Return =         E_OK
 *                                E_NOT_OK
 */
Std_ReturnType Mtr_SetChannelStatus(const Mtr_ChannelNameType chName_t, const Mtr_ChannelStatusType chStatus_t)
{
   /* --- local variable declaration --- */
   uint8 mtr_channelId_ui8;
   Std_ReturnType rtn_e = E_NOT_OK;

   /* ----------- source code ----------- */
#if (MTR_DEV_ERROR_DETECT == STD_ON)
   if (mtr_moduleState_e != MODULE_INITIALIZED) /* Savety request */
   {
      //Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID, MTR_SET_CHANNELSTATUS_API_ID, MTR_E_UNINIT);
   }
   else
#endif /*MTR_DEV_ERROR_DETECT == STD_ON */
   {
      mtr_channelId_ui8 = mtr_channelConfig_as[chName_t].id_ui8;
      switch (chStatus_t)
      {
         case MTR_CHANNEL_ACTIVE:
         {
            /* Activate Channel with aligment */
            *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_channelId_ui8]) |= ((mtr_channelConfig_as[chName_t].align_e
                        << MTR_CTRL_MCCC_MCAM_BITNUM ) & MTR_CTRL_MCCC_MCAM_MASK );
            rtn_e = E_OK;
         }
         break;
         case MTR_CHANNEL_INACTIVE:
         {
            /* Disable Channel */
            *((uint8 * const ) mtr_channelConfigReg_apui8[chName_t]) &= (uint8) (~MTR_CTRL_MCCC_MCAM_MASK );
            rtn_e = E_OK;
         }
         break;
         default:
         {
            rtn_e = E_NOT_OK;
         }
         break;
      }
   }
   return rtn_e;
}

#if (MTR_SET_DUTY_CYCLE_FAST_API == STD_ON)
/*
 *  \brief Service sets the duty cycle of the PWM channel.
 *
 *  The function Pwm_SetDutyCycle shall set the duty cycle of the PWM channel.
 *
 *  \param [in]  ChannelNummer =  Numeric identifier of the PWM
 *  \param [in]  DutyCycle  =  Min=0x0000
 *                             Max=0x8000
 *  \param [out] ---
 *  \return      ---
 */
void Mtr_SetDutyCycleFast (
   const Mtr_ChannelNameType chName_t,
   const Mtr_ChannelDutyCycleType dutyCycle_t)
{
   /* --- local variable declaration --- */
   uint8 mtr_channelId_ui8;

   /* ----- init internal variables ----- */
   mtr_channelId_ui8 = (uint8) 0U;

   /* ----------- source code ----------- */
#if (MTR_DEV_ERROR_DETECT == STD_ON)
   if (mtr_moduleState_e != MODULE_INITIALIZED) /* Savety request */
   {
      Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID, MTR_SET_DUTYCYCLE_API_ID, MTR_E_UNINIT);
   }
   else
#endif /*MTR_DEV_ERROR_DETECT == STD_ON */
   {
      /* Get corresponding Channel ID from module global channel configuration */
      mtr_channelId_ui8 = mtr_channelConfig_as[chName_t].id_ui8;

      /* Write Duty Cycle as 16 bit access to the two corresponding concatenated 8 bit Registers */
      /* Fast mode */
      *((uint16 * const ) mtr_channelDutyCycleReg_apui16[mtr_channelId_ui8]) = (dutyCycle_t
                  & MTR_CTRL_MCDC_FAST_D2_D8_S_MASK_UI16 );

      /* Deactivate channel to take configuration over */
      *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_channelId_ui8]) &= (uint8) (~MTR_CTRL_MCCC_MCAM_MASK );

      asm(nop);

      /* activate channel last - register MCAM bits were set to zero before */
      *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_channelId_ui8]) |= ((mtr_channelConfig_as[chName_t].align_e
                  << MTR_CTRL_MCCC_MCAM_BITNUM ) & MTR_CTRL_MCCC_MCAM_MASK );
   }
}
#endif /* MTR_SET_DUTY_CYCLE_FAST_API == STD_ON */


#if (MTR_SET_OUTPUT_TO_IDLE_API == STD_ON)
/*
 *  \brief Service sets the PWM output to the configured Idle state.
 *
 *  PWM021: The function Mtr_SetOutputToIdle shall set immediately the PWM
 *  output to the configured Idle state.
 *
 *  Regarding error detection, the requirements PWM117, PWM047 and PWM051 are
 *  applicable to the function Mtr_SetOutputToIdle.
 *
 *  PWM084: The function Mtr_SetOutputToIdle shall be pre compile time
 *  configurable On/Off by the configuration parameter: PwmSetOutputToIdle.
 *
 *  PWM086: After the call of the function Mtr_SetOutputToIdle, variable period
 *  type channels shall be reactivated either using the Api
 *  Mtr_SetPeriodAndDuty() to activate the PWM channel with the new passed
 *  period or Api Mtr_SetDutyCycle() to activate the PWM channel with the old
 *  period.
 *
 *  PWM119: After the call of the function Mtr_SetOutputToIdle, fixed period
 *  typechannels shall be reactivated using only the API Api Mtr_SetDutyCycle()
 *  to activate the PWM channel with the old period.
 *
 *  \param [in]  ChannelNummer =  Numeric identifier of the PWM
 *
 *  \param [out] ---
 *  \return      ---
 */
void Mtr_SetOutputToIdle (const Mtr_ChannelNameType chName_t)
{
   /* --- local variable declaration --- */
   uint8 mtr_currChId_ui8;

   /* --- init modul global variables --- */
   mtr_currChId_ui8 = (uint8) 0U;

   /* ----------- source code ----------- */
#if (MTR_DEV_ERROR_DETECT == STD_ON)
   if (mtr_moduleState_e != MODULE_INITIALIZED) /* Savety request */
   {
      Det_ReportError(MTR_MODULE_ID, MTR_INSTANCE_ID, MTR_SET_OUTPUTTOIDLE_API_ID,
                  MTR_E_UNINIT);
   }
   else
#endif
   {
      /* We know which channel id the name belongs to */
      /* Get Channel ID */
      mtr_currChId_ui8 = mtr_channelConfig_as[chName_t].id_ui8;

      /* Stop channel output - write zeros */
      *((uint8 * const ) mtr_channelConfigReg_apui8[mtr_currChId_ui8]) &= (uint8) (~MTR_CTRL_MCCC_MCAM_MASK );

      /* Reset motor controller duty register - write zeros */
      *((uint16 * const ) mtr_channelDutyCycleReg_apui16[mtr_currChId_ui8]) = (uint16) 0U;

//        /* IO mapping for output ports */
//        /* Set data direction of port hardware to output state */
//        *(mtr_ioMapping[mtr_currChId_ui8].dirRegister_pui8) |= (0x01
//                << mtr_ioMapping[mtr_currChId_ui8].bit_ui8);
//
//        *(mtr_ioMapping[mtr_currChId_ui8].dataRegister_pui8) &= ~((uint8) (0x01
//                << mtr_ioMapping[mtr_currChId_ui8].bit_ui8));
   }
}
#endif /* MTR_SET_OUTPUT_TO_IDLE_API == STD_ON */


Std_ReturnType Mtr_SetMotorInterrupt(Mtr_CtrlMCTOIEType irqStatus_e)
{
   Std_ReturnType rtn_e = (uint8) E_NOT_OK;
   if (irqStatus_e == MTR_CTRL_MCTOIE_ENABLE)
   {
      if (mtr_config_ps->mtr_generalConfiguration_ps->timerOverflow_fp != ((Mtr_TimerCounterOverflowInterruptFp)NULL_PTR) )
      {
         /* Enable Interrupt */
         *(mtr_register_s.regMCtl_1_pui8) |= (uint8) MCCTL1_MCTOIE_MASK; /* Enable Interrupt */
         rtn_e = (uint8) E_OK;
      }
   }
   else
   {
      /* Disable Interrupt */
      *(mtr_register_s.regMCtl_1_pui8) &= ~((uint8) MCCTL1_MCTOIE_MASK); /* Enable Interrupt */
   }
   return rtn_e;
}


#if (MTR_ISR_API == STD_ON)
/*
* \brief This service is the Motor Periode Interrupt
*
* If the motor interrupt is enabled, this function gets called after each motor periode
* * \param [in]  ---
* \param [out] ---
* \return      Module Status: MODULE_UNINIT, MODULE_DEINITIALIZED, MODULE_INITIALIZED
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void Mtr_ISR(void)
{
#if 0
   *( (uint8*) 0x2c0) |= 0b00010000;
#endif
   /* Clear Interrupt Flag */
   *(mtr_register_s.regMCtl_0_pui8) |= (uint8) MCCTL0_MCTOIF_MASK;
   mtr_config_ps->mtr_generalConfiguration_ps->timerOverflow_fp();
#if 0
   *( (uint8*) 0x2c0) &= 0b11101111;
#endif
}
#pragma CODE_SEG DEFAULT
#endif

#if (MTR_MODULE_STATE_API == STD_ON)
/*
* \brief This service returns the status of this module (DO NOT CHANGE).
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: MODULE_UNINIT, MODULE_DEINITIALIZED, MODULE_INITIALIZED
*/
Std_ModuleStatusReturnType Mtr_GetModuleStatus (void)
{
   /* -- source code -------------------------- */
   return(mtr_moduleState_e);
}
#endif /* (MTR_MODULE_STATE_API == STD_ON) */


#if (MTR_VERSION_INFO_API == STD_ON)
/*
 *  \brief This service returns the version information of this module.
 *
 *  PWM068: The function Mtr_GetVersionInfo shall return the version information
 *  of the module. The version information includes:
 *  - Module ID
 *  - Vendor ID
 *  - Vendor specific version numbers (BSW00407)
 *
 *  PWM114: If source code for caller and callee of Mtr_GetVersionInfo is
 *  avalible, the PWM module should realize Mtr_GetVersionInfo as a
 *  macro, defined in the modules header file.
 *
 *  PWM069 The function Mtr_GetVersionInfo is pre-compile time configurable
 *  On/Off by the configuration parameter PwmVersionInfoApi.
 *
 *  \param [in]  ---
 *  \param [out] versioninfo = Pointer to where to store the version
 *                             information of this module.
 *  \return      ---
 */
void Mtr_GetVersionInfo (Std_VersionInfoType * const versioninfo)
{
   /* ----------- source code ----------- */
   versioninfo->vendorID = MTR_VENDOR_ID;
   versioninfo->moduleID = MTR_MODULE_ID;
   versioninfo->instanceID = MTR_INSTANCE_ID;
   versioninfo->sw_major_version = MTR_SW_MAJOR_VERSION;
   versioninfo->sw_minor_version = MTR_SW_MINOR_VERSION;
   versioninfo->sw_patch_version = MTR_SW_PATCH_VERSION;
}
#endif /* MTR_VERSION_INFO_API == STD_ON */


