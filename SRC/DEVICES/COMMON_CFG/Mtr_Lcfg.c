/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "Version.h"
#include <Mtr.h>
#include <Mtr_Lcfg.h>
#include "Cdd_Motor.h"
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define MTR_LCFG_SW_MAJOR_VERSION_C (0)  /* SW major version */
#define MTR_LCFG_SW_MINOR_VERSION_C (0)  /* SW minor version */
#define MTR_LCFG_SW_PATCH_VERSION_C (1)  /* SW patch version */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #makros --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* version check */
#if((MTR_LCFG_SW_MAJOR_VERSION_C != MTR_LCFG_SW_MAJOR_VERSION) || \
    (MTR_LCFG_SW_MINOR_VERSION_C != MTR_LCFG_SW_MINOR_VERSION) || \
    (MTR_LCFG_SW_PATCH_VERSION_C != MTR_LCFG_SW_PATCH_VERSION))
   #error "Software Version Numbers of MTR_Lcfg.c and MTR_Lcfg.h are different."
#endif /* (LINPHY_LCFG_SW_MAJOR_VERSION_C != LINPHY_LCFG_SW_MAJOR_VERSION) || ... */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #defines -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal typedefs  ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal enums  ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal structs  -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config internal data (const) --------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

volatile Mtr_GeneralConfigType mtr_generalConfiguration_s =
{
    MTR_CTRL_MCPRE_FBUS_DIV_1,          /* Mtr_CtrlPrescalerType     prescaler_e */
    MTR_CTRL_WAIT_MODE_STAY_AWAKE,      /* Mtr_CtrlWaitModeType      waitMode_e */
    MTR_CTRL_PWM_RESOLUTION_NORMAL,     /* Mtr_CtrlPwmResModeType    resMode_e */
    MTR_CTRL_DITHER_FEATURE_DISABLED,   /* Mtr_CtrlDitherFeatType    dither_e */
    MTR_CTRL_MCTOIF_NOT_OCCURED,        /* Mtr_CtrlMCTOIFType        timerOVF_e */
    MTR_CTRL_RECIRC_LOW,                /* Mtr_CtrlRecircType        reciric_e */
    MTR_CTRL_MCTOIE_DISABLE,            /* Mtr_CtrlMCTOIEType        timerEn_e */
    (uint16)MTR_CTRL_MCPER,             /* Mtr_CtrlPeriodType        period_t */
    &Cdd_Motor_RunMotorISR         		/* Mtr_TimerCounterOverflowInterruptFp   timerOverflow_fp */
};

/** The Period-Value also defines the amount of minor time-quantas. To get
    a proper duty-cycle you have to make sure to have enough time-quantas per period.

    e.g.
    DutyCycle = 0x4000 -> 50% -> Period-Value has to be at least 2.
    DutyCycle = 0x0400 ->  5% -> Period-Value has to be at least 20.

    (way more is recommended. To get rid of rounding errors and interrupt caused
     deviations, the Period-Value should be as high as possible)
*/
const Mtr_ChannelConfigType mtr_channelConfiguration_as[MTR_USED_NUMBER_OF_CHANNELS] =
{
    /* MTR_MTR1_COIL0_CHANNEL_0 */
    {
        (Mtr_ChannelNumberType)MTR_CHANNEL_ID_0,               /* ChannelID [Number of the associated PWM Pin] */
        MTR_MCCC_MCOM_Dual_FULL_HB,     /* Bridge Mode */
        MTR_MCCC_MCAM_LEFT,             /* Align */
        MTR_MCCC_CD_0,                  /* Delay */
        0,                              /* DutyCycle:
                                         * Normal Mode: positive: 0x0    -  0x7FF (D0 - D10 = bits 0-10)
                                         *              negative: 0x8000 - 0x87FF (D0 - D10 = bits 0-10, bit 15 sign)
                                         * Fast Mode:   positive: 0x0    - 0x7F00 (D2 - D8  = bits 8-14)
                                         *              negative: 0x8000 - 0xFF00 (D2 - D8  = bits 8-14, bit 15 sign)
                                         **/
        STD_OFF                         /* AUTO START - Activate after init: STD_OFF / STD_ON */
    },
    /* MTR_MTR1_COIL1_CHANNEL_1 */
    {
       (Mtr_ChannelNumberType)MTR_CHANNEL_ID_1,               /* ChannelID [Number of the associated PWM Pin] */
        MTR_MCCC_MCOM_Dual_FULL_HB,     /* Bridge Mode */
        MTR_MCCC_MCAM_LEFT,             /* Align */
        MTR_MCCC_CD_0,                  /* Delay */
        0,                              /* DutyCycle:
                                         * Normal Mode: positive: 0x0    -  0x7FF (D0 - D10 = bits 0-10)
                                         *              negative: 0x8000 - 0x87FF (D0 - D10 = bits 0-10, bit 15 sign)
                                         * Fast Mode:   positive: 0x0    - 0x7F00 (D2 - D8  = bits 8-14)
                                         *              negative: 0x8000 - 0xFF00 (D2 - D8  = bits 8-14, bit 15 sign)
                                         **/
        STD_OFF                         /* AUTO START - Activate after init: STD_OFF / STD_ON */
    },
    /* MTR_MTR2_COIL0_CHANNEL_2 */
    {
       (Mtr_ChannelNumberType)MTR_CHANNEL_ID_2,               /* ChannelID [Number of the associated PWM Pin] */
        MTR_MCCC_MCOM_Dual_FULL_HB,     /* Bridge Mode */
        MTR_MCCC_MCAM_LEFT,             /* Align */
        MTR_MCCC_CD_0,                  /* Delay */
        0,                              /* DutyCycle:
                                         * Normal Mode: positive: 0x0    -  0x7FF (D0 - D10 = bits 0-10)
                                         *              negative: 0x8000 - 0x87FF (D0 - D10 = bits 0-10, bit 15 sign)
                                         * Fast Mode:   positive: 0x0    - 0x7F00 (D2 - D8  = bits 8-14)
                                         *              negative: 0x8000 - 0xFF00 (D2 - D8  = bits 8-14, bit 15 sign)
                                         **/
        STD_OFF                         /* AUTO START - Activate after init: STD_OFF / STD_ON */
    },
    /* MTR_MTR2_COIL1_CHANNEL_3 */
    {
       (Mtr_ChannelNumberType)MTR_CHANNEL_ID_3,               /* ChannelID [Number of the associated PWM Pin] */
#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
        MTR_MCCC_MCOM_Dual_FULL_HB,     /* Bridge Mode */
#elif (DEVICE_TYPE == DEVICE_COMPASS)
        MTR_MCCC_MCOM_Dual_FULL_HB,     /* Bridge Mode */
#elif (DEVICE_TYPE == DEVICE_OAT)
        MTR_MCCC_MCOM_HALF_HB_MP,        /* Bridge Mode */
#elif (DEVICE_TYPE == DEVICE_STOPWATCH)
        MTR_MCCC_MCOM_HALF_HB_MP,        /* Bridge Mode */
#endif
        MTR_MCCC_MCAM_LEFT,             /* Align */
        MTR_MCCC_CD_0,                  /* Delay */
        0,                              /* DutyCycle:
                                         * Normal Mode: positive: 0x0    -  0x7FF (D0 - D10 = bits 0-10)
                                         *              negative: 0x8000 - 0x87FF (D0 - D10 = bits 0-10, bit 15 sign)
                                         * Fast Mode:   positive: 0x0    - 0x7F00 (D2 - D8  = bits 8-14)
                                         *              negative: 0x8000 - 0xFF00 (D2 - D8  = bits 8-14, bit 15 sign)
                                         **/
        STD_OFF                         /* AUTO START - Activate after init: STD_OFF / STD_ON */
    }
};


Mtr_ConfigType mtr_initialConfiguration_s =
{
    &mtr_generalConfiguration_s,
    mtr_channelConfiguration_as,
    (uint8)MTR_USED_NUMBER_OF_CHANNELS
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global data (Userdata) (const) ------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config function (internal use only)--------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 * \brief Function to get the pointer to link-time configuration .
 *
 * Standardized function for reading out the link time configuration.
 *
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      pointer to module configuration
 */
const Mtr_ConfigType * Mtr_GetLcfgData (void)
{
   return (&mtr_initialConfiguration_s);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal functions (static) --------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global functions (Userfunctions) ----------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
