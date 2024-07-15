#ifndef MTR_CFG_H
#define MTR_CFG_H
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include "ProjectSettings.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- Compiler switches/Register defines/Pre-compile-Config  (#defines) -------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define MTR_CFG_VENDOR_ID        99  /**<\brief CoSyst VendorID */
#define MTR_CFG_AR_MAJOR_VERSION 3   /**<\brief AUTOSAR major version */
#define MTR_CFG_AR_MINOR_VERSION 1   /**<\brief AUTOSAR minor version */
#define MTR_CFG_AR_PATCH_VERSION 0   /**<\brief AUTOSAR patch version */
#define MTR_CFG_SW_MAJOR_VERSION 1   /**<\brief Software major version */
#define MTR_CFG_SW_MINOR_VERSION 0   /**<\brief Software minor version */
#define MTR_CFG_SW_PATCH_VERSION 0   /**<\brief Software patch version */


#define MTR_CTRL_BASE_REGISTER_UI16    (uint16)0xA40

/** \b Description: Motor Controller Control Register 0
 * <br>\b  Range:
 * <br> \b Example:*/
#define MTR_CTRL_MCCTL0_ADR_UI16       (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x0)


/** \b Description: Motor Controller Control Register 1
 * <br>\b  Range:
 * <br> \b Example:*/
#define MTR_CTRL_MCCTL1_ADR_UI16       (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x1)


/** \b Description: Motor Controller Period Register
 * <br>\b  Range:
 * <br> \b Example:*/
#define MTR_CTRL_MCPER_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x2)


/** \b Description: Motor Controller Channel Control Registers
 * <br>\b  Range:
 * <br> \b Example:*/
#define MTR_CTRL_MCCC0_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x10)
#define MTR_CTRL_MCCC1_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x11)
#define MTR_CTRL_MCCC2_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x12)
#define MTR_CTRL_MCCC3_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x13)


#define MTR_CTRL_MCCC_CD_BITNUM        (uint8)0U
#define MTR_CTRL_MCCC_CD_MASK          (uint8)3U
#define MTR_CTRL_MCCC_MCAM_BITNUM      (uint8)4U
#define MTR_CTRL_MCCC_MCAM_MASK        (uint8)48U
#define MTR_CTRL_MCCC_MCOM_BITNUM      (uint8)6U
#define MTR_CTRL_MCCC_MCOM_MASK        (uint8)192U

/** \b Description: Motor Controller Duty Cycle Registers
 * <br>\b  Range:
 * <br> \b Example:*/
#define MTR_CTRL_MCDC0_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x20)
#define MTR_CTRL_MCDC1_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x22)
#define MTR_CTRL_MCDC2_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x24)
#define MTR_CTRL_MCDC3_ADR_UI16        (uint16)(MTR_CTRL_BASE_REGISTER_UI16 + 0x26)


#define MTR_CTRL_MCDC_D0_D10_S_MASK_UI16        (uint16)0x87FF
#define MTR_CTRL_MCDC_FAST_D2_D8_S_MASK_UI16    (uint16)0xFF00
#define MTR_CTRL_MCDC_S_MASK_UI16               (uint16)0x8000
#define MTR_CTRL_MCDC_D0_D10_MASK_UI16          (uint16)0x7FF
#define MTR_CTRL_MCDC_D2_D8_MASK_UI16           (uint16)0x7F00

/* defines for output idle state */
#define MTR_PORT_V_DATA_REG_ADR_UI16      (uint16)(0x0360) /* PTP  (0x02F0) PTP */
#define MTR_PORT_V_INPUT_REG_ADR_UI16     (uint16)(0x0361) /* PTIP (0x02F1) PTP Input */
#define MTR_PORT_V_DATA_DIR_REG_ADR_UI16  (uint16)(0x0362) /* DDRP (0x02F2) PTP Data Dir */


/* MASKS for registers */
#define MCCTL0_MCTOIF_MASK              1U
#define MCCTL0_DITH_MASK                4U
#define MCCTL0_FAST_MASK                8U
#define MCCTL0_MCSWAI_MASK              16U
#define MCCTL0_MCPRE0_MASK              32U
#define MCCTL0_MCPRE1_MASK              64U
#define MCCTL0_MCPRE_MASK               96U
#define MCCTL0_MCPRE_BITNUM             5U

#define MCCTL1_MCTOIE_MASK              1U
#define MCCTL1_RECIRC_MASK              128U

#define MCPER_P_MASK                    2047U



/** \b Description: Switches deinit feature on/off.
<br>\b Range:
<br>STD_ON:  enable Deinitialization function
<br>STD_OFF: disable Deinitialization function
<br> \b Example:*/
#define MTR_DEINIT_API                 PROJECT_SETTINGS_GLOBAL_DEINIT_API

/** \b Description: Switches module state info feature on/off.
<br>\b Range:
<br>STD_ON:  enable module state info function
<br>STD_OFF: disable module state info function
<br> \b Example:*/
#define MTR_MODULE_STATE_API           STD_OFF

/** \b Description: Switches set duty cycle feature on/off.
<br>\b Range:
<br>STD_ON:  enable function to set duty cycle
<br>STD_OFF: disable function to set duty cycle
<br> \b Example:*/
#define MTR_SET_DUTY_CYCLE_NORMAL_API  STD_ON
#define MTR_SET_DUTY_CYCLE_FAST_API    STD_OFF


/** \b Description: Switches set output to idle feature on/off.
<br>\b Range:
<br>STD_ON:  enable function to set output to idle state
<br>STD_OFF: disable function to set output to idle state
<br> \b Example:*/
#define MTR_SET_OUTPUT_TO_IDLE_API     STD_OFF

#define MTR_ISR_API                    STD_ON

/**
* Description: Switches development error detection on/off.
* Range:       STD_ON:      enable Deveopment Error Detection
*              STD_OFF:     disable Deveopment Error Detection
* Example:
*/
#define MTR_DEV_ERROR_DETECT          PROJECT_SETTINGS_GLOBAL_DET_SWITCH

/**
* Description: Switches function Mtr_GetVersionInfo() on/off.
* Range:       STD_ON:      enable function Mtr_GetVersionInfo()
*              STD_OFF:     disable function Mtr_GetVersionInfo()
* Example:
*/
#define MTR_VERSION_INFO_API           PROJECT_SETTINGS_GLOBAL_VERSION_API


#define MTR_DEINIT_API                 PROJECT_SETTINGS_GLOBAL_DEINIT_API

/* ************************************************************************************************************** */
#define MTR_DISABLE_CH1() \
         { \
            * ( (uint8 * const ) MTR_CTRL_MCCC0_ADR_UI16) &= (uint8) (~MTR_CTRL_MCCC_MCAM_MASK ); \
         }

#define MTR_DISABLE_CH2() \
         { \
            * ( (uint8 * const ) MTR_CTRL_MCCC1_ADR_UI16) &= (uint8) (~MTR_CTRL_MCCC_MCAM_MASK ); \
         }

#define MTR_ENABLE_CH1() \
         { \
              *((uint8 * const ) MTR_CTRL_MCCC0_ADR_UI16) |= (( (uint8) 0x01 \
                     << MTR_CTRL_MCCC_MCAM_BITNUM ) & MTR_CTRL_MCCC_MCAM_MASK ); \
         }
#define MTR_ENABLE_CH2() \
         { \
               *((uint8 * const ) MTR_CTRL_MCCC1_ADR_UI16) |= (( (uint8) 0x01 \
                     << MTR_CTRL_MCCC_MCAM_BITNUM ) & MTR_CTRL_MCCC_MCAM_MASK ); \
         }

#define MTR_SET_DUTYCYCLE_MTR1_COIL0(dutyCycle_ui16) \
         { \
            * ( (uint16 * const ) MTR_CTRL_MCDC0_ADR_UI16) = (dutyCycle_ui16 & MTR_CTRL_MCDC_D0_D10_S_MASK_UI16 ); \
         }

#define MTR_SET_DUTYCYCLE_MTR1_COIL1(dutyCycle_ui16) \
         { \
            * ( (uint16 * const ) MTR_CTRL_MCDC1_ADR_UI16) = (dutyCycle_ui16 & MTR_CTRL_MCDC_D0_D10_S_MASK_UI16 ); \
         }
/* ************************************************************************************************************** */
#define MTR_DISABLE_CH3() \
         { \
            * ( (uint8 * const ) MTR_CTRL_MCCC2_ADR_UI16) &= (uint8) (~MTR_CTRL_MCCC_MCAM_MASK ); \
         }

#define MTR_DISABLE_CH4() \
         { \
            * ( (uint8 * const ) MTR_CTRL_MCCC3_ADR_UI16) &= (uint8) (~MTR_CTRL_MCCC_MCAM_MASK ); \
         }

#define MTR_ENABLE_CH3() \
         { \
              *((uint8 * const ) MTR_CTRL_MCCC2_ADR_UI16) |= (( (uint8) 0x01 \
                     << MTR_CTRL_MCCC_MCAM_BITNUM ) & MTR_CTRL_MCCC_MCAM_MASK ); \
         }
#define MTR_ENABLE_CH4() \
         { \
               *((uint8 * const ) MTR_CTRL_MCCC3_ADR_UI16) |= (( (uint8) 0x01 \
                     << MTR_CTRL_MCCC_MCAM_BITNUM ) & MTR_CTRL_MCCC_MCAM_MASK ); \
         }

#define MTR_SET_DUTYCYCLE_MTR2_COIL0(dutyCycle_ui16) \
         { \
            * ( (uint16 * const ) MTR_CTRL_MCDC2_ADR_UI16) = (dutyCycle_ui16 & MTR_CTRL_MCDC_D0_D10_S_MASK_UI16 ); \
         }

#define MTR_SET_DUTYCYCLE_MTR2_COIL1(dutyCycle_ui16) \
         { \
            * ( (uint16 * const ) MTR_CTRL_MCDC3_ADR_UI16) = (dutyCycle_ui16 & MTR_CTRL_MCDC_D0_D10_S_MASK_UI16 ); \
         }
/* ************************************************************************************************************** */

#endif /* MTR_CFG_H */
