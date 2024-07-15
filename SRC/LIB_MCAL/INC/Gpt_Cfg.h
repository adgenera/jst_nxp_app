#ifndef GPT_CFG_H
#define GPT_CFG_H

/* ***************************** includes " " ******************************* */
#include <Std_Types.h>
#include "ProjectSettings.h"

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void Ecum_RunTimerISR (void);
#pragma CODE_SEG DEFAULT

/* ***************************** typedefs *********************************** */

/* ***************************** # defines ********************************** */
#define GPT_CFG_VENDOR_ID        99 /**<\brief CoSyst VendorID */
#define GPT_CFG_AR_MAJOR_VERSION 3  /**<\brief AUTOSAR major version */
#define GPT_CFG_AR_MINOR_VERSION 1  /**<\brief AUTOSAR minor version */
#define GPT_CFG_AR_PATCH_VERSION 0  /**<\brief AUTOSAR patch version */
#define GPT_CFG_SW_MAJOR_VERSION 0  /**<\brief Software major version */
#define GPT_CFG_SW_MINOR_VERSION 1  /**<\brief Software minor version */
#define GPT_CFG_SW_PATCH_VERSION 0  /**<\brief Software patch version */


/* --- General Module Configuration --- */

/** \b Description: Switches development error detection on/off.
<br>\b Range: STD_ON/STD_OFF
<br>STD_ON:  enable Deveopment Error Detection
<br>STD_OFF: disable Deveopment Error Detection */
#define GPT_DEV_ERROR_DETECT              PROJECT_SETTINGS_GLOBAL_DET_SWITCH

/** \b Description: Switches function Gpt_GetVersionInfo() on/off.
<br>\b Range: STD_ON/STD_OFF
<br>STD_ON:  enable function Gpt_GetVersionInfo()
<br>STD_OFF: disable function Gpt_GetVersionInfo() */
#define GPT_VERSION_INFO_API              PROJECT_SETTINGS_GLOBAL_VERSION_API

/** \b Description: Switches function Gpt_DeInit() on/off.
<br>\b Range: STD_ON/STD_OFF
<br>STD_ON:  enable function Gpt_DeInit()
<br>STD_OFF: disable function Gpt_DeInit() */
#define GPT_DEINIT_API                    PROJECT_SETTINGS_GLOBAL_DEINIT_API


/** \b Description: Switches module state info feature on/off.
<br>\b Range:
<br>STD_ON:  enable module state info function
<br>STD_OFF: disable module state info function
<br> \b Example:*/
#define GPT_MODULE_STATE_API              PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API

#define GPT_ROM_OPTIMIZATION              STD_OFF


/**
 *  \brief Type for Gpt channel mode.
 *
 *  This type defines a range of specific status for Gpt channel mode types.
 */
#define GPT_CH_MODE_CONTINUOUS         0
#define GPT_CH_MODE_ONESHOT            1

#define GPT_TIM0_CH0_OPMODE            GPT_CH_MODE_ONESHOT
#define GPT_TIM0_CH1_OPMODE            GPT_CH_MODE_CONTINUOUS
#define GPT_TIM0_CH2_OPMODE            GPT_CH_MODE_ONESHOT
#define GPT_TIM0_CH3_OPMODE            GPT_CH_MODE_ONESHOT
#define GPT_TIM0_CH4_OPMODE            GPT_CH_MODE_ONESHOT
#define GPT_TIM0_CH5_OPMODE            GPT_CH_MODE_ONESHOT
#define GPT_TIM0_CH6_OPMODE            GPT_CH_MODE_ONESHOT
#define GPT_TIM0_CH7_OPMODE            GPT_CH_MODE_ONESHOT

#define GPT_TIM0_CH0_INTERRUPT         STD_ON
#define GPT_TIM0_CH1_INTERRUPT         STD_OFF
#define GPT_TIM0_CH2_INTERRUPT         STD_OFF
#define GPT_TIM0_CH3_INTERRUPT         STD_OFF
#define GPT_TIM0_CH4_INTERRUPT         STD_OFF
#define GPT_TIM0_CH5_INTERRUPT         STD_OFF
#define GPT_TIM0_CH6_INTERRUPT         STD_OFF
#define GPT_TIM0_CH7_INTERRUPT         STD_OFF

#define GPT_TIM0_CH1_CBCK              Ecum_RunTimerISR

#if (defined GPT_TIM0_CH0_CBCK)
#undef GPT_TIM0_CH0_CBCK
#endif
#if (defined GPT_TIM0_CH2_CBCK)
#undef GPT_TIM0_CH2_CBCK
#endif
#if (defined GPT_TIM0_CH3_CBCK)
#undef GPT_TIM0_CH3_CBCK
#endif
#if (defined GPT_TIM0_CH4_CBCK)
#undef GPT_TIM0_CH4_CBCK
#endif
#if (defined GPT_TIM0_CH5_CBCK)
#undef GPT_TIM0_CH5_CBCK
#endif
#if (defined GPT_TIM0_CH6_CBCK)
#undef GPT_TIM0_CH6_CBCK
#endif
#if (defined GPT_TIM0_CH7_CBCK)
#undef GPT_TIM0_CH7_CBCK
#endif

#define GPT_TIM0_ISR0_API					STD_OFF
#define GPT_TIM0_ISR1_API					STD_ON
#define GPT_TIM0_ISR2_API					STD_OFF
#define GPT_TIM0_ISR3_API					STD_OFF
#define GPT_TIM0_ISR4_API					STD_OFF
#define GPT_TIM0_ISR5_API					STD_OFF
#define GPT_TIM0_ISR6_API					STD_OFF
#define GPT_TIM0_ISR7_API					STD_OFF


/** \b Description: Switches function Gpt_Enable/DisableNotification() on/off.
<br>\b Range: STD_ON/STD_OFF
<br>STD_ON:  enable function Gpt_Enable/DisableNotification()
<br>STD_OFF: disable function Gpt_Enable/DisableNotification() */
#define GPT_NOTIFICATION_API              STD_ON

/** \b Description: Switches function Gpt_SetPeriode() on/off.
<br>\b Range: STD_ON/STD_OFF
<br>STD_ON:  enable function Gpt_SetPeriode()
<br>STD_OFF: disable function Gpt_SetPeriode() */
#define GPT_SET_PERIODE_API               STD_ON

/** \b Description: Switches function Gpt_GetTimeElapsed() on/off.
<br>\b Range: STD_ON/STD_OFF
<br>STD_ON:  enable function Gpt_GetTimeElapsed()
<br>STD_OFF: disable function Gpt_GetTimeElapsed() */
#define GPT_GET_TIME_ELAPSED_API          (STD_ON)

/* Definition for commenting out the variable gpt_channelStatusRegisters_aui32 */
#define GPT_STATUS_REGISTER_USED          STD_OFF


#define GPT_TIM0TSCR1_PRNT_BITPOS           3
#define GPT_TIM0TSCR1_TSFRZ_BITPOS          5
#define GPT_TIM0TSCR1_TSWAI_BITPOS          6
#define GPT_TIM0TSCR1_TEN_BITPOS            7

#define GPT_TIM0TSCR2_PR_BITPOS             0
#define GPT_TIM0TSCR2_TCRE_BITPOS           3
#define GPT_TIM0TSCR2_TOI_BITPOS            7

/* --- GPT Register address configuration --- */

/* Base addresses */
/** \b Description: Register base addresses <TAUJ0_base>. */
#define GPT_1_BASE_ADDRESS_UI16               ((uint16)0x400U)
#define GPT_0_BASE_ADDRESS_UI16               ((uint16)0x05C0)

/* Address offsets - prescaler registers */


/*** TIM1TIOS - Timer Input Capture/Output Compare Select; 0x00000400 ***/
#define GPT_TIMER_REG_TIM1TIOS_UI16         (uint16)(GPT_1_BASE_ADDRESS_UI16)        /* 8 Bit  */
/*** TIM1CFORC - Timer Compare Force Register; 0x00000401 ***/
#define GPT_TIMER_REG_TIM1CFORC_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x1)  /* 8 Bit  */
/*** TIM1OC7M - Output Compare 7 Mask Register; 0x00000402 ***/
#define GPT_TIMER_REG_TIM1OC7M_UI16         (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x2)  /* 8 Bit  */
/*** TIM1OC7D - Output Compare 7 Data Register; 0x00000403 ***/
#define GPT_TIMER_REG_TIM1OC7D_UI16         (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x3)  /* 8 Bit  */
/*** TIM1TCNT - Timer Count Register; 0x00000404 ***/
#define GPT_TIMER_REG_TIM1TCNT_UI16         (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x4)  /* 16 Bit */
/*** TIM1TSCR1 - Timer System Control Register1; 0x00000406 ***/
#define GPT_TIMER_REG_TIM1TSCR1_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x6)  /* 8 Bit  */
/*** TIM1TTOV - Timer Toggle On Overflow Register; 0x00000407 ***/
#define GPT_TIMER_REG_TIM1TTOV_UI16         (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x7)  /* 8 Bit  */
/*** TIM1TCTL1 - Timer Control Register 1; 0x00000408 ***/
#define GPT_TIMER_REG_TIM1TCTL1_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x8)  /* 8 Bit  */
/*** TIM1TCTL2 - Timer Control Register 2; 0x00000409 ***/
#define GPT_TIMER_REG_TIM1TCTL2_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x9)  /* 8 Bit  */
/*** TIM1TCTL3 - Timer Control Register 3; 0x0000040A ***/
#define GPT_TIMER_REG_TIM1TCTL3_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0xA)  /* 8 Bit  */
/*** TIM1TCTL4 - Timer Control Register 4; 0x0000040B ***/
#define GPT_TIMER_REG_TIM1TCTL4_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0xB)  /* 8 Bit  */
/*** TIM1TIE - Timer Interrupt Enable Register; 0x0000040C ***/
#define GPT_TIMER_REG_TIM1TIE_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0xC)  /* 8 Bit  */
/*** TIM1TSCR2 - Timer System Control Register 2; 0x0000040D ***/
#define GPT_TIMER_REG_TIM1TSCR2_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0xD)  /* 8 Bit  */
/*** TIM1TFLG1 - Main Timer Interrupt Flag 1; 0x0000040E ***/
#define GPT_TIMER_REG_TIM1TFLG1_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0xE)  /* 8 Bit  */
/*** TIM1TFLG2 - Main Timer Interrupt Flag 2; 0x0000040F ***/
#define GPT_TIMER_REG_TIM1TFLG2_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0xF)  /* 8 Bit  */
/*** TIM1TC0 - Timer Input Capture/Output Compare Register 0; 0x00000410 ***/
#define GPT_TIMER_REG_TIM1TC0_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x10) /* 16 Bit */
/*** TIM1TC1 - Timer Input Capture/Output Compare Register 1; 0x00000412 ***/
#define GPT_TIMER_REG_TIM1TC1_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x12) /* 16 Bit */
/*** TIM1TC2 - Timer Input Capture/Output Compare Register 2; 0x00000414 ***/
#define GPT_TIMER_REG_TIM1TC2_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x14) /* 16 Bit */
/*** TIM1TC3 - Timer Input Capture/Output Compare Register 3; 0x00000416 ***/
#define GPT_TIMER_REG_TIM1TC3_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x16) /* 16 Bit */
/*** TIM1TC4 - Timer Input Capture/Output Compare Register 4; 0x00000418 ***/
#define GPT_TIMER_REG_TIM1TC4_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x18) /* 16 Bit */
/*** TIM1TC5 - Timer Input Capture/Output Compare Register 5; 0x0000041A ***/
#define GPT_TIMER_REG_TIM1TC5_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x1A) /* 16 Bit */
/*** TIM1TC6 - Timer Input Capture/Output Compare Register 6; 0x0000041C ***/
#define GPT_TIMER_REG_TIM1TC6_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x1C) /* 16 Bit */
/*** TIM1TC7 - Timer Input Capture/Output Compare Register 7; 0x0000041E ***/
#define GPT_TIMER_REG_TIM1TC7_UI16          (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x1E) /* 16 Bit */
/*** TIM1PACTL - 16-Bit Pulse Accumulator A Control Register; 0x00000420 ***/
#define GPT_TIMER_REG_TIM1PACTL_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x20) /* 8 Bit  */
/*** TIM1PAFLG - Pulse Accumulator A Flag Register; 0x00000421 ***/
#define GPT_TIMER_REG_TIM1PAFLG_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x21) /* 8 Bit  */
/*** TIM1PACNT - Pulse Accumulators Count Register; 0x00000422 ***/
#define GPT_TIMER_REG_TIM1PACNT_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x22) /* 16 Bit */
/*** TIM1OCPD - Output Compare Pin Disconnect Register; 0x0000042C ***/
#define GPT_TIMER_REG_TIM1OCPD_UI16         (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x2C) /* 8 Bit  */
/*** TIM1PTPSR - Precision Timer Prescaler Select Register; 0x0000042E ***/
#define GPT_TIMER_REG_TIM1PTPSR_UI16        (uint16)(GPT_1_BASE_ADDRESS_UI16 + 0x2E) /* 8 Bit  */


/*** TIM0TIOS - Timer Input Capture/Output Compare Select; 0x000005C0 ***/
#define GPT_TIMER_REG_TIM0TIOS_UI16         (uint16)(GPT_0_BASE_ADDRESS_UI16)        /* 8 Bit  */
/*** TIM0CFORC - Timer Compare Force Register; 0x000005C1 ***/
#define GPT_TIMER_REG_TIM0CFORC_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x1)  /* 8 Bit  */
/*** TIM0OC7M - Output Compare 7 Mask Register; 0x000005C2 ***/
#define GPT_TIMER_REG_TIM0OC7M_UI16         (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x2)  /* 8 Bit  */
/*** TIM0OC7D - Output Compare 7 Data Register; 0x000005C3 ***/
#define GPT_TIMER_REG_TIM0OC7D_UI16         (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x3)  /* 8 Bit  */
/*** TIM0TCNT - Timer Count Register; 0x000005C4 ***/
#define GPT_TIMER_REG_TIM0TCNT_UI16         (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x4)  /* 16 Bit */
/*** TIM0TSCR1 - Timer System Control Register1; 0x000005C6 ***/
#define GPT_TIMER_REG_TIM0TSCR1_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x6)  /* 8 Bit  */
/*** TIM0TTOV - Timer Toggle On Overflow Register; 0x000005C7 ***/
#define GPT_TIMER_REG_TIM0TTOV_UI16         (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x7)  /* 8 Bit  */
/*** TIM0TCTL1 - Timer Control Register 1; 0x000005C8 ***/
#define GPT_TIMER_REG_TIM0TCTL1_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x8)  /* 8 Bit  */
/*** TIM0TCTL2 - Timer Control Register 2; 0x000005C9 ***/
#define GPT_TIMER_REG_TIM0TCTL2_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x9)  /* 8 Bit  */
/*** TIM0TCTL3 - Timer Control Register 3; 0x000005CA ***/
#define GPT_TIMER_REG_TIM0TCTL3_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0xA)  /* 8 Bit  */
/*** TIM0TCTL4 - Timer Control Register 4; 0x000005CB ***/
#define GPT_TIMER_REG_TIM0TCTL4_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0xB)  /* 8 Bit  */
/*** TIM0TIE - Timer Interrupt Enable Register; 0x000005CC ***/
#define GPT_TIMER_REG_TIM0TIE_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0xC)  /* 8 Bit  */
/*** TIM0TSCR2 - Timer System Control Register 2; 0x000005CD ***/
#define GPT_TIMER_REG_TIM0TSCR2_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0xD)  /* 8 Bit  */
/*** TIM0TFLG1 - Main Timer Interrupt Flag 1; 0x000005CE ***/
#define GPT_TIMER_REG_TIM0TFLG1_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0xE)  /* 8 Bit  */
/*** TIM0TFLG2 - Main Timer Interrupt Flag 2; 0x000005CF ***/
#define GPT_TIMER_REG_TIM0TFLG2_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0xF)  /* 8 Bit  */
/*** TIM0TC0 - Timer Input Capture/Output Compare Register 0; 0x000005D0 ***/
#define GPT_TIMER_REG_TIM0TC0_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x10) /* 16 Bit */
/*** TIM0TC1 - Timer Input Capture/Output Compare Register 1; 0x000005D2 ***/
#define GPT_TIMER_REG_TIM0TC1_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x12) /* 16 Bit */
/*** TIM0TC2 - Timer Input Capture/Output Compare Register 2; 0x000005D4 ***/
#define GPT_TIMER_REG_TIM0TC2_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x14) /* 16 Bit */
/*** TIM0TC3 - Timer Input Capture/Output Compare Register 3; 0x000005D6 ***/
#define GPT_TIMER_REG_TIM0TC3_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x16) /* 16 Bit */
/*** TIM0TC4 - Timer Input Capture/Output Compare Register 4; 0x000005D8 ***/
#define GPT_TIMER_REG_TIM0TC4_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x18) /* 16 Bit */
/*** TIM0TC5 - Timer Input Capture/Output Compare Register 5; 0x000005DA ***/
#define GPT_TIMER_REG_TIM0TC5_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x1A) /* 16 Bit */
/*** TIM0TC6 - Timer Input Capture/Output Compare Register 6; 0x000005DC ***/
#define GPT_TIMER_REG_TIM0TC6_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x1C) /* 16 Bit */
/*** TIM0TC7 - Timer Input Capture/Output Compare Register 7; 0x000005DE ***/
#define GPT_TIMER_REG_TIM0TC7_UI16          (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x1E) /* 16 Bit */
/*** TIM0PACTL - 16-Bit Pulse Accumulator A Control Register; 0x000005E0 ***/
#define GPT_TIMER_REG_TIM0PACTL_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x20) /* 8 Bit  */
/*** TIM0PAFLG - Pulse Accumulator A Flag Register; 0x000005E1 ***/
#define GPT_TIMER_REG_TIM0PAFLG_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x21) /* 8 Bit  */
/*** TIM0PACNT - Pulse Accumulators Count Register; 0x000005E2 ***/
#define GPT_TIMER_REG_TIM0PACNT_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x22) /* 16 Bit */
/*** TIM0OCPD - Output Compare Pin Disconnect Register; 0x000005EC ***/
#define GPT_TIMER_REG_TIM0OCPD_UI16         (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x2C) /* 8 Bit  */
/*** TIM0PTPSR - Precision Timer Prescaler Select Register; 0x000005EE ***/
#define GPT_TIMER_REG_TIM0PTPSR_UI16        (uint16)(GPT_0_BASE_ADDRESS_UI16 + 0x2E) /* 8 Bit  */

/* ***************************** enums ************************************** */


#endif /* GPT_CFG_H */
