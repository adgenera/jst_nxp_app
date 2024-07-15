#ifndef MCU_CFG_H
#define MCU_CFG_H
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include "ProjectSettings.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- Compiler switches/Register defines/Pre-compile-Config  (#defines) -------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* Description: Switches development error detection on/off.
* Range:       STD_ON:      enable Deveopment Error Detection
*              STD_OFF:     disable Deveopment Error Detection
* Example:
*/
#define MCU_DEV_ERROR_DETECTION                PROJECT_SETTINGS_GLOBAL_DET_SWITCH

/*
* Description: Switches function Mcu_GetVersionInfo() on/off.
* Range:       STD_ON:      enable function Mcu_GetVersionInfo()
*              STD_OFF:     disable function Mcu_GetVersionInfo()
* Example:
*/
#define MCU_VERSION_INFO_API                   PROJECT_SETTINGS_GLOBAL_VERSION_API


#define MCU_DEINIT_API                         PROJECT_SETTINGS_GLOBAL_DEINIT_API

/* Use ROM optimized initialization */
#define MCU_ROM_OPTIMIZATION                   STD_OFF

/** Description: address of Mode Register */
#define MCU_MODE_ADR_UI16 (uint16)0x0070
/** Description: address of S12CPMU_UHV_V5 Reset Flags Register */
#define MCU_CPMURFLG_ADR_UI16 (uint16)0x06C3
/** Description: address of S12CPMU_UHV_V5 Synthesizer Register */
#define MCU_CPMUSYNR_ADR_UI16 (uint16)0x06C4
/** Description: address of S12CPMU_UHV_V5 Reference Divider Register */
#define MCU_CPMUREFDIV_ADR_UI16 (uint16)0x06C5
/** Description: address of S12CPMU_UHV_V5 Post Divider Register */
#define MCU_CPMUPOSTDIV_ADR_UI16 (uint16)0x06C6
/** Description: address of S12CPMU_UHV_V5 Interrupt Flags Register */
#define MCU_CPMUIFLG_ADR_UI16 (uint16)0x06C7
/** Description: address of S12CPMU_UHV_V5 Interrupt Enable Register */
#define MCU_CPMUINT_ADR_UI16 (uint16)0x06C8
/** Description: address of S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_ADR_UI16 (uint16)0x06C9
/** Description: address of S12CPMU_UHV_V5 PLL Control Register */
#define MCU_CPMUPLL_ADR_UI16 (uint16)0x06CA
/** Description: address of S12CPMU_UHV_V5 RTI Control Register */
#define MCU_CPMURTI_ADR_UI16 (uint16)0x06CB
/** Description: address of S12CPMU_UHV_V5 COP Control Register */
#define MCU_CPMUCOP_ADR_UI16 (uint16)0x06CC
/** Description: address of S12CPMU_UHV_V5 COP Timer Arm/Reset Register */
#define MCU_CPMUARMCOP_ADR_UI16 (uint16)0x06CF
/** Description: address of High Temperature Control Register */
#define MCU_CPMUHTCTL_ADR_UI16 (uint16)0x06D0
/** Description: address of Low Voltage Control Register */
#define MCU_CPMULVCTL_ADR_UI16 (uint16)0x06D1
/** Description: address of Autonomous Periodical Interrupt Control Register */
#define MCU_CPMUAPICTL_ADR_UI16 (uint16)0x06D2
/** Description: address of Autonomous Clock Trimming Register */
#define MCU_CPMUACLKTR_ADR_UI16 (uint16)0x06D3
/** Description: address of Autonomous Periodical Interrupt Rate Register */
#define MCU_CPMUAPIR_ADR_UI16 (uint16)0x06D4
/** Description: address of High Temperature Trimming Register */
#define MCU_CPMUHTTR_ADR_UI16 (uint16)0x06D7
/** Description: address of S12CPMU_UHV_V5 IRC1M Trim Registers */
#define MCU_CPMUIRCTRIM_ADR_UI16 (uint16)0x06D8
/** Description: address of S12CPMU_UHV_V5 Oscillator Register */
#define MCU_CPMUOSC_ADR_UI16 (uint16)0x06DA
/** Description: address of S12CPMU_UHV_V5 Protection Register */
#define MCU_CPMUPROT_ADR_UI16 (uint16)0x06DB
/** Description: address of Voltage Regulator Control Register */
#define MCU_CPMUVREGCTL_ADR_UI16 (uint16)0x06DD
/** Description: address of S12CPMU_UHV_V5 Oscillator Register 2 */
#define MCU_CPMUOSC2_ADR_UI16 (uint16)0x06DE


/** Description: interrupt vector base address */
#define MCU_IVBR_ADR_UI16              (uint16)0x0010U
/** Description: Interrupt Request Configuration Address Register */
#define MCU_INT_CFADDR_ADR_UI16        (uint16)0x0017U
/** Description: Interrupt Request Configuration Data Register 0 */
#define MCU_INT_CFDATA0_ADR_UI16       (uint16)0x0018U
/** Description: Interrupt Request Configuration Data Register 1 */
#define MCU_INT_CFDATA1_ADR_UI16       (uint16)0x0019U
/** Description: Interrupt Request Configuration Data Register 2 */
#define MCU_INT_CFDATA2_ADR_UI16       (uint16)0x001AU
/** Description: Interrupt Request Configuration Data Register 3 */
#define MCU_INT_CFDATA3_ADR_UI16       (uint16)0x001BU
/** Description: Interrupt Request Configuration Data Register 4 */
#define MCU_INT_CFDATA4_ADR_UI16       (uint16)0x001CU
/** Description: Interrupt Request Configuration Data Register 5 */
#define MCU_INT_CFDATA5_ADR_UI16       (uint16)0x001DU
/** Description: Interrupt Request Configuration Data Register 6 */
#define MCU_INT_CFDATA6_ADR_UI16       (uint16)0x001EU
/** Description: Interrupt Request Configuration Data Register 7 */
#define MCU_INT_CFDATA7_ADR_UI16       (uint16)0x001FU


#endif /* MCU_CFG_H */

