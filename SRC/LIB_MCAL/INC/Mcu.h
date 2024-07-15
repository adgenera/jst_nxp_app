#ifndef MCU_H
#define MCU_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include "Mcu_Cfg.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define MCU_INSTANCE_ID           (0)  /* Instance id */
#define MCU_SW_MAJOR_VERSION      (1)  /* Software major version */
#define MCU_SW_MINOR_VERSION      (0)  /* Software minor version */
#define MCU_SW_PATCH_VERSION      (0)  /* Software patch version */


#if (MCU_DEV_ERROR_DETECTION == STD_ON)
/* DET Module API ID's */
#define MCU_INIT_API_ID           (0x01)       /* API ID of Mcu_Init() */
#define MCU_DEINIT_API_ID         (0x02)       /* API ID of Mcu_DeInit() */

/* DET Module error ID's */
#define MCU_E_PARAM_CONFIG        (0x10)       /* Error ID: config not found */
#define MCU_E_ALREADY_INITIALIZED (0x11)       /* Error ID: multiple call of Mcu_Init() */
#define MCU_E_NOT_INITIALIZED     (0x12)       /* Error ID: multiple call of Mcu_DeInit() */
#endif /* MCU_DEV_ERROR_DETECTION == STD_ON */

/* value of inactive special mode in MODE Register */
#define MCU_MODE_SPECIALMODE_INACTIVE (uint8)0x80U
/* value of active special mode in MODE Register */
#define MCU_MODE_SPECIALMODE_ACTIVE (uint8)0x00U

/* Bit positions in S12CPMU_UHV_V5 Reset Flags Register */
#define MCU_CPMURFLG_PORF_POS (uint8)6U
/* Bit positions in S12CPMU_UHV_V5 Reset Flags Register */
#define MCU_CPMURFLG_LVRF_POS (uint8)5U
/* Bit positions in S12CPMU_UHV_V5 Reset Flags Register */
#define MCU_CPMURFLG_COPRF_POS (uint8)3U
/* Bit positions in S12CPMU_UHV_V5 Reset Flags Register */
#define MCU_CPMURFLG_OMRF_POS (uint8)1U
/* Bit positions in S12CPMU_UHV_V5 Reset Flags Register */
#define MCU_CPMURFLG_PMRF_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 Synthesizer Register */
#define MCU_CPMUSYNR_VCOFRQ_POS (uint8)6U
/* Bit positions in S12CPMU_UHV_V5 Synthesizer Register */
#define MCU_CPMUSYNR_SYNDIV_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 Reference Divider Register */
#define MCU_CPMUREFDIV_REFFRQ_POS (uint8)6U
/* Bit positions in S12CPMU_UHV_V5 Reference Divider Register */
#define MCU_CPMUREFDIV_REFDIV_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 Post Divider Register */
#define MCU_CPMUPOSTDIV_POSTDIV_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Flags Register */
#define MCU_CPMUIFLG_RTIF_POS (uint8)7U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Flags Register */
#define MCU_CPMUIFLG_LOCKIF_POS (uint8)4U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Flags Register */
#define MCU_CPMUIFLG_LOCK_POS (uint8)3U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Flags Register */
#define MCU_CPMUIFLG_OSCIF_POS (uint8)1U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Flags Register */
#define MCU_CPMUIFLG_UPOSC_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Enable Register */
#define MCU_CPMUINT_RTIE_POS (uint8)7U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Enable Register */
#define MCU_CPMUINT_LOCKIE_POS (uint8)4U
/* Bit positions in S12CPMU_UHV_V5 Interrupt Enable Register */
#define MCU_CPMUINT_OSCIE_POS (uint8)1U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_PLLSEL_POS (uint8)7U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_PSTP_POS (uint8)6U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_CSAD_POS (uint8)5U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_COPOSCSEL1_POS (uint8)4U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_PRE_POS (uint8)3U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_PCE_POS (uint8)2U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_RTIOSCSEL_POS (uint8)1U
/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define MCU_CPMUCLKS_COPOSCSEL0_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 PLL Control Register */
#define MCU_CPMUPLL_FM_POS (uint8)4U
/* Bit positions in S12CPMU_UHV_V5 RTI Control Register */
#define MCU_CPMURTI_RTDEC_POS (uint8)7U
/* Bit positions in S12CPMU_UHV_V5 RTI Control Register */
#define MCU_CPMURTI_RTRPRE_POS (uint8)4U
/* Bit positions in S12CPMU_UHV_V5 RTI Control Register */
#define MCU_CPMURTI_RTRMOD_POS (uint8)0U
/* Bit positions in High Temperature Control Register */
#define MCU_CPMUHTCTL_VSEL_POS (uint8)5U
/* Bit positions in High Temperature Control Register */
#define MCU_CPMUHTCTL_HTE_POS (uint8)3U
/* Bit positions in High Temperature Control Register */
#define MCU_CPMUHTCTL_HTDS_POS (uint8)2U
/* Bit positions in High Temperature Control Register */
#define MCU_CPMUHTCTL_HTIE_POS (uint8)1U
/* Bit positions in High Temperature Control Register */
#define MCU_CPMUHTCTL_HTIF_POS (uint8)0U
/* Bit positions in Low Voltage Control Register */
#define MCU_CPMULVCTL_LVDS_POS (uint8)2U
/* Bit positions in Low Voltage Control Register */
#define MCU_CPMULVCTL_LVIE_POS (uint8)2U
/* Bit positions in Low Voltage Control Register */
#define MCU_CPMULVCTL_LVIF_POS (uint8)0U
/* Bit positions in Autonomous Periodical Interrupt Control Register */
#define MCU_CPMUAPICTL_APICLK_POS (uint8)7U
/* Bit positions in Autonomous Periodical Interrupt Control Register */
#define MCU_CPMUAPICTL_APIES_POS (uint8)4U
/* Bit positions in Autonomous Periodical Interrupt Control Register */
#define MCU_CPMUAPICTL_APIEA_POS (uint8)3U
/* Bit positions in Autonomous Periodical Interrupt Control Register */
#define MCU_CPMUAPICTL_APIFE_POS (uint8)2U
/* Bit positions in Autonomous Periodical Interrupt Control Register */
#define MCU_CPMUAPICTL_APIE_POS (uint8)1U
/* Bit positions in Autonomous Periodical Interrupt Control Register */
#define MCU_CPMUAPICTL_APIF_POS (uint8)0U
/* Bit positions in Autonomous Clock Trimming Register */
#define MCU_CPMUACLKTR_ACLKTR_POS (uint8)2U
/* Bit positions in Autonomous Periodical Interrupt Rate Register */
#define MCU_CPMUAPIR_APIR_POS (uint8)0U
/* Bit positions in High Temperature Trimming Register */
#define MCU_CPMUHTTR_HTOE_POS (uint8)7U
/* Bit positions in High Temperature Trimming Register */
#define MCU_CPMUHTTR_HTTR_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 IRC1M Trim Registers */
#define MCU_CPMUIRCTRIM_TCTRIM_POS (uint8)11U
/* Bit positions in S12CPMU_UHV_V5 IRC1M Trim Registers */
#define MCU_CPMUIRCTRIM_IRCTRIM_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 Oscillator Register */
#define MCU_CPMUOSC_OSCE_POS (uint8)7U
/* Bit positions in S12CPMU_UHV_V5 Protection Register */
#define MCU_CPMUPROT_PROT_POS (uint8)0U
/* Bit positions in Voltage Regulator Control Register */
#define MCU_CPMUVREGCTL_EXTXON_POS (uint8)1U
/* Bit positions in Voltage Regulator Control Register */
#define MCU_CPMUVREGCTL_INTXON_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 Oscillator Register 2 */
#define MCU_CPMUOSC2_OMRE_POS (uint8)1U
/* Bit positions in S12CPMU_UHV_V5 Oscillator Register 2 */
#define MCU_CPMUOSC2_OSCMOD_POS (uint8)0U

/* Default values of PORF in CPMURFLG */
#define MCU_CPMURFLG_PORF_DEFAULT STD_OFF
/* Default values of LVRF in CPMURFLG */
#define MCU_CPMURFLG_LVRF_DEFAULT STD_OFF
/* Default values of COPRF in CPMURFLG */
#define MCU_CPMURFLG_COPRF_DEFAULT STD_OFF
/* Default values of OMRF in CPMURFLG */
#define MCU_CPMURFLG_OMRF_DEFAULT STD_OFF
/* Default values of PMRF in CPMURFLG */
#define MCU_CPMURFLG_PMRF_DEFAULT STD_OFF
/* Default values of VCOFRQ in CPMUSYNR */
#define MCU_CPMUSYNR_VCOFRQ_DEFAULT MCU_48MHZ_FVCO_64MHZ
/* Default values of SYNDIV in CPMUSYNR */
#define MCU_CPMUSYNR_SYNDIV_DEFAULT 24
/* Default values of REFFRQ in CPMUREFDIV */
#define MCU_CPMUREFDIV_REFFRQ_DEFAULT MCU_1MHZ_FREF_2MHZ
/* Default values of REFDIV in CPMUREFDIV */
#define MCU_CPMUREFDIV_REFDIV_DEFAULT 15
/* Default values of POSTDIV in CPMUPOSTDIV */
#define MCU_CPMUPOSTDIV_POSTDIV_DEFAULT 3
/* Default values of RTIF in CPMUIFLG */
#define MCU_CPMUIFLG_RTIF_DEFAULT MCU_RTI_NOT_OCCURED
/* Default values of LOCKIF in CPMUIFLG */
#define MCU_CPMUIFLG_LOCKIF_DEFAULT MCU_LOCK_BIT_NOT_CHANGED
/* Default values of LOCK in CPMUIFLG */
#define MCU_CPMUIFLG_LOCK_DEFAULT MCU_PLL_NOT_LOCKED
/* Default values of OSCIF in CPMUIFLG */
#define MCU_CPMUIFLG_OSCIF_DEFAULT MCU_UPOSC_BIT_NOT_CHANGED
/* Default values of UPOSC in CPMUIFLG */
#define MCU_CPMUIFLG_UPOSC_DEFAULT MCU_OSC_NOT_QUALIFIED
/* Default values of RTIE in CPMUINT */
#define MCU_CPMUINT_RTIE_DEFAULT STD_OFF
/* Default values of LOCKIE in CPMUINT */
#define MCU_CPMUINT_LOCKIE_DEFAULT STD_OFF
/* Default values of OSCIE in CPMUINT */
#define MCU_CPMUINT_OSCIE_DEFAULT STD_OFF
/* Default values of PLLSEL in CPMUCLKS */
#define MCU_CPMUCLKS_PLLSEL_DEFAULT MCU_SYSCLK_FROM_PLLCLK
/* Default values of PSTP in CPMUCLKS */
#define MCU_CPMUCLKS_PSTP_DEFAULT MCU_FULL_STOP_MODE
/* Default values of CSAD in CPMUCLKS */
#define MCU_CPMUCLKS_CSAD_DEFAULT MCU_COP_RUN_IN_STOP_MODE
/* Default values of COPOSCSEL1 in CPMUCLKS */
#define MCU_CPMUCLKS_COPOSCSEL1_DEFAULT MCU_COP_CLK_COPOSCSEL0
/* Default values of PRE in CPMUCLKS */
#define MCU_CPMUCLKS_PRE_DEFAULT MCU_RTI_STOP_IN_PSEUDO_STOP_MODE
/* Default values of PCE in CPMUCLKS */
#define MCU_CPMUCLKS_PCE_DEFAULT MCU_COP_STOP_IN_PSEUDO_STOP_MODE
/* Default values of RTIOSCSEL in CPMUCLKS */
#define MCU_CPMUCLKS_RTIOSCSEL_DEFAULT MCU_RTI_CLK_IRCCLK
/* Default values of COPOSCSEL0 in CPMUCLKS */
#define MCU_CPMUCLKS_COPOSCSEL0_DEFAULT MCU_COP_CLK_IRCCLK
/* Default values of FM in CPMUPLL */
#define MCU_CPMUPLL_FM_DEFAULT MCU_FM_OFF
/* Default values of RTDEC in CPMURTI */
#define MCU_CPMURTI_RTDEC_DEFAULT MCU_BIN_DIV
/* Default values of RTRPRE in CPMURTI */
#define MCU_CPMURTI_RTRPRE_DEFAULT 0
/* Default values of RTRMOD in CPMURTI */
#define MCU_CPMURTI_RTRMOD_DEFAULT 0
/* Default values of VSEL in CPMUHTCTL */
#define MCU_CPMUHTCTL_VSEL_DEFAULT MCU_INTERNAL_TEMPERATURE
/* Default values of HTE in CPMUHTCTL */
#define MCU_CPMUHTCTL_HTE_DEFAULT STD_OFF
/* Default values of HTDS in CPMUHTCTL */
#define MCU_CPMUHTCTL_HTDS_DEFAULT MCU_JUNCTION_TEMP_LOW
/* Default values of HTIE in CPMUHTCTL */
#define MCU_CPMUHTCTL_HTIE_DEFAULT STD_OFF
/* Default values of HTIF in CPMUHTCTL */
#define MCU_CPMUHTCTL_HTIF_DEFAULT STD_OFF
/* Default values of LVDS in CPMULVCTL */
#define MCU_CPMULVCTL_LVDS_DEFAULT MCU_INPUT_VOLTAGE_LOW
/* Default values of LVIE in CPMULVCTL */
#define MCU_CPMULVCTL_LVIE_DEFAULT STD_OFF
/* Default values of LVIF in CPMULVCTL */
#define MCU_CPMULVCTL_LVIF_DEFAULT STD_OFF
/* Default values of APICLK in CPMUAPICTL */
#define MCU_CPMUAPICTL_APICLK_DEFAULT MCU_SRC_ACLK
/* Default values of APIES in CPMUAPICTL */
#define MCU_CPMUAPICTL_APIES_DEFAULT MCU_API_EXTCLK_HIGH_PULSE
/* Default values of APIEA in CPMUAPICTL */
#define MCU_CPMUAPICTL_APIEA_DEFAULT MCU_APIES_EXT_ACCESS
/* Default values of APIFE in CPMUAPICTL */
#define MCU_CPMUAPICTL_APIFE_DEFAULT STD_OFF
/* Default values of APIE in CPMUAPICTL */
#define MCU_CPMUAPICTL_APIE_DEFAULT STD_OFF
/* Default values of APIF in CPMUAPICTL */
#define MCU_CPMUAPICTL_APIF_DEFAULT STD_OFF
/* Default values of ACLKTR in CPMUACLKTR */
#define MCU_CPMUACLKTR_ACLKTR_DEFAULT 0
/* Default values of APIR in CPMUAPIR */
#define MCU_CPMUAPIR_APIR_DEFAULT 0
/* Default values of HTOE in CPMUHTTR */
#define MCU_CPMUHTTR_HTOE_DEFAULT STD_OFF
/* Default values of HTTR in CPMUHTTR */
#define MCU_CPMUHTTR_HTTR_DEFAULT 0
/* Default values of TCTRIM in CPMUIRCTRIM */
#define MCU_CPMUIRCTRIM_TCTRIM_DEFAULT 0
/* Default values of IRCTRIM in CPMUIRCTRIM */
#define MCU_CPMUIRCTRIM_IRCTRIM_DEFAULT 0
/* Default values of OSCE in CPMUOSC */
#define MCU_CPMUOSC_OSCE_DEFAULT STD_OFF
/* Default values of PROT in CPMUPROT */
#define MCU_CPMUPROT_PROT_DEFAULT MCU_PROT_DISABLE
/* Default values of EXTXON in CPMUVREGCTL */
#define MCU_CPMUVREGCTL_EXTXON_DEFAULT MCU_VDDX_USE_BJT
/* Default values of INTXON in CPMUVREGCTL */
#define MCU_CPMUVREGCTL_INTXON_DEFAULT MCU_VDDX_USE_INT_PWR
/* Default values of OMRE in CPMUOSC2 */
#define MCU_CPMUOSC2_OMRE_DEFAULT STD_OFF
/* Default values of OSCMOD in CPMUOSC2 */
#define MCU_CPMUOSC2_OSCMOD_DEFAULT MCU_EXTOSC_LOOP_CTL_MODE

/* Macro to disable special mode in MODE Register */
#define MCU_DISABLE_SPECIALMODE() (\
   *((uint8*)MCU_MODE_ADR_UI16) = \
   MCU_MODE_SPECIALMODE_INACTIVE)
/* Macro to set PORF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_SetCpmuRFlgPoRf(value) ( \
   *((uint8*)MCU_CPMURFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMURFLG_PORF_POS ) | \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMURFLG_PORF_POS) ) ) ) )
/* Macro to set LVRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_SetCpmuRFlgLvRf(value) ( \
   *((uint8*)MCU_CPMURFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMURFLG_LVRF_POS ) | \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMURFLG_LVRF_POS) ) ) ) )
/* Macro to set COPRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_SetCpmuRFlgCopRf(value) ( \
   *((uint8*)MCU_CPMURFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMURFLG_COPRF_POS ) | \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMURFLG_COPRF_POS) ) ) ) )
/* Macro to set OMRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_SetCpmuRFlgOmRf(value) ( \
   *((uint8*)MCU_CPMURFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMURFLG_OMRF_POS ) | \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMURFLG_OMRF_POS) ) ) ) )
/* Macro to set PMRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_SetCpmuRFlgPmRf(value) ( \
   *((uint8*)MCU_CPMURFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )
/* Macro to set VCOFRQ of S12CPMU_UHV_V5 Synthesizer Register */
#define Mcu_SetCpmuSynRVcoFrq(value) ( \
   *((uint8*)MCU_CPMUSYNR_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x3 ) << MCU_CPMUSYNR_VCOFRQ_POS ) | \
      ( (*((uint8*)MCU_CPMUSYNR_ADR_UI16)) & (uint8)(~((uint8)0x3 << MCU_CPMUSYNR_VCOFRQ_POS) ) ) ) )
/* Macro to set SYNDIV of S12CPMU_UHV_V5 Synthesizer Register */
#define Mcu_SetCpmuSynRSynDiv(value) ( \
   *((uint8*)MCU_CPMUSYNR_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x3f ) ) | \
      ( (*((uint8*)MCU_CPMUSYNR_ADR_UI16)) & (uint8)(~((uint8)0x3f) ) ) ) )
/* Macro to set REFFRQ of S12CPMU_UHV_V5 Reference Divider Register */
#define Mcu_SetCpmuRefDivRefFrq(value) ( \
   *((uint8*)MCU_CPMUREFDIV_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x3 ) << MCU_CPMUREFDIV_REFFRQ_POS ) | \
      ( (*((uint8*)MCU_CPMUREFDIV_ADR_UI16)) & (uint8)(~((uint8)0x3 << MCU_CPMUREFDIV_REFFRQ_POS) ) ) ) )
/* Macro to set REFDIV of S12CPMU_UHV_V5 Reference Divider Register */
#define Mcu_SetCpmuRefDivRefDiv(value) ( \
   *((uint8*)MCU_CPMUREFDIV_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0xf ) ) | \
      ( (*((uint8*)MCU_CPMUREFDIV_ADR_UI16)) & (uint8)(~((uint8)0xf) ) ) ) )
/* Macro to set POSTDIV of S12CPMU_UHV_V5 Post Divider Register */
#define Mcu_SetCpmuPostDivPostDiv(value) ( \
   *((uint8*)MCU_CPMUPOSTDIV_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1f ) ) | \
      ( (*((uint8*)MCU_CPMUPOSTDIV_ADR_UI16)) & (uint8)(~((uint8)0x1f) ) ) ) )
/* Macro to set RTIF of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_SetCpmuIFlgRtIf(value) ( \
   *((uint8*)MCU_CPMUIFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUIFLG_RTIF_POS ) | \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUIFLG_RTIF_POS) ) ) ) )
/* Macro to set LOCKIF of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_SetCpmuIFlgLockIf(value) ( \
   *((uint8*)MCU_CPMUIFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUIFLG_LOCKIF_POS ) | \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUIFLG_LOCKIF_POS) ) ) ) )
/* Macro to set OSCIF of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_SetCpmuIFlgOscIf(value) ( \
   *((uint8*)MCU_CPMUIFLG_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUIFLG_OSCIF_POS ) | \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUIFLG_OSCIF_POS) ) ) ) )
/* Macro to set RTIE of S12CPMU_UHV_V5 Interrupt Enable Register */
#define Mcu_SetCpmuIntRtIE(value) ( \
   *((uint8*)MCU_CPMUINT_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUINT_RTIE_POS ) | \
      ( (*((uint8*)MCU_CPMUINT_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUINT_RTIE_POS) ) ) ) )
/* Macro to set LOCKIE of S12CPMU_UHV_V5 Interrupt Enable Register */
#define Mcu_SetCpmuIntLockIE(value) ( \
   *((uint8*)MCU_CPMUINT_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUINT_LOCKIE_POS ) | \
      ( (*((uint8*)MCU_CPMUINT_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUINT_LOCKIE_POS) ) ) ) )
/* Macro to set OSCIE of S12CPMU_UHV_V5 Interrupt Enable Register */
#define Mcu_SetCpmuIntOscIE(value) ( \
   *((uint8*)MCU_CPMUINT_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUINT_OSCIE_POS ) | \
      ( (*((uint8*)MCU_CPMUINT_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUINT_OSCIE_POS) ) ) ) )
/* Macro to set PLLSEL of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSPllSel(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUCLKS_PLLSEL_POS ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUCLKS_PLLSEL_POS) ) ) ) )
/* Macro to set PSTP of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSPStp(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUCLKS_PSTP_POS ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUCLKS_PSTP_POS) ) ) ) )
/* Macro to set CSAD of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSCSAD(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUCLKS_CSAD_POS ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUCLKS_CSAD_POS) ) ) ) )
/* Macro to set COPOSCSEL1 of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSCopOscSel1(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUCLKS_COPOSCSEL1_POS ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUCLKS_COPOSCSEL1_POS) ) ) ) )
/* Macro to set PRE of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSPre(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUCLKS_PRE_POS ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUCLKS_PRE_POS) ) ) ) )
/* Macro to set PCE of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSPce(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUCLKS_PCE_POS ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUCLKS_PCE_POS) ) ) ) )
/* Macro to set RTIOSCSEL of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSRtiOscSel(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUCLKS_RTIOSCSEL_POS ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUCLKS_RTIOSCSEL_POS) ) ) ) )
/* Macro to set COPOSCSEL0 of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_SetCpmuClkSCopOscSel0(value) ( \
   *((uint8*)MCU_CPMUCLKS_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )
/* Macro to set FM of S12CPMU_UHV_V5 PLL Control Register */
#define Mcu_SetCpmuPllFm(value) ( \
   *((uint8*)MCU_CPMUPLL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x3 ) << MCU_CPMUPLL_FM_POS ) | \
      ( (*((uint8*)MCU_CPMUPLL_ADR_UI16)) & (uint8)(~((uint8)0x3 << MCU_CPMUPLL_FM_POS) ) ) ) )
/* Macro to set RTDEC of S12CPMU_UHV_V5 RTI Control Register */
#define Mcu_SetCpmuRtiRtDec(value) ( \
   *((uint8*)MCU_CPMURTI_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMURTI_RTDEC_POS ) | \
      ( (*((uint8*)MCU_CPMURTI_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMURTI_RTDEC_POS) ) ) ) )
/* Macro to set RTRPRE of S12CPMU_UHV_V5 RTI Control Register */
#define Mcu_SetCpmuRtiRtRPre(value) ( \
   *((uint8*)MCU_CPMURTI_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x7 ) << MCU_CPMURTI_RTRPRE_POS ) | \
      ( (*((uint8*)MCU_CPMURTI_ADR_UI16)) & (uint8)(~((uint8)0x7 << MCU_CPMURTI_RTRPRE_POS) ) ) ) )
/* Macro to set RTRMOD of S12CPMU_UHV_V5 RTI Control Register */
#define Mcu_SetCpmuRtiRtRMod(value) ( \
   *((uint8*)MCU_CPMURTI_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0xf ) ) | \
      ( (*((uint8*)MCU_CPMURTI_ADR_UI16)) & (uint8)(~((uint8)0xf) ) ) ) )
/* Macro to set VSEL of High Temperature Control Register */
#define Mcu_SetCpmuHtCtlVSel(value) ( \
   *((uint8*)MCU_CPMUHTCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUHTCTL_VSEL_POS ) | \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUHTCTL_VSEL_POS) ) ) ) )
/* Macro to set HTE of High Temperature Control Register */
#define Mcu_SetCpmuHtCtlHtE(value) ( \
   *((uint8*)MCU_CPMUHTCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUHTCTL_HTE_POS ) | \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUHTCTL_HTE_POS) ) ) ) )
/* Macro to set HTIF of High Temperature Control Register */
#define Mcu_SetCpmuHtCtlHtIf(value) ( \
   *((uint8*)MCU_CPMUHTCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )
/* Macro to set LVIE of Low Voltage Control Register */
#define Mcu_SetCpmuLvCtlLvIE(value) ( \
   *((uint8*)MCU_CPMULVCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMULVCTL_LVIE_POS ) | \
      ( (*((uint8*)MCU_CPMULVCTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMULVCTL_LVIE_POS) ) ) ) )
/* Macro to set LVIF of Low Voltage Control Register */
#define Mcu_SetCpmuLvCtlLvIF(value) ( \
   *((uint8*)MCU_CPMULVCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)MCU_CPMULVCTL_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )
/* Macro to set APICLK of Autonomous Periodical Interrupt Control Register */
#define Mcu_SetCpmuAPICtlApiClk(value) ( \
   *((uint8*)MCU_CPMUAPICTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUAPICTL_APICLK_POS ) | \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUAPICTL_APICLK_POS) ) ) ) )
/* Macro to set APIES of Autonomous Periodical Interrupt Control Register */
#define Mcu_SetCpmuAPICtlApiEs(value) ( \
   *((uint8*)MCU_CPMUAPICTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUAPICTL_APIES_POS ) | \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUAPICTL_APIES_POS) ) ) ) )
/* Macro to set APIEA of Autonomous Periodical Interrupt Control Register */
#define Mcu_SetCpmuAPICtlApiEa(value) ( \
   *((uint8*)MCU_CPMUAPICTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUAPICTL_APIEA_POS ) | \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUAPICTL_APIEA_POS) ) ) ) )
/* Macro to set APIFE of Autonomous Periodical Interrupt Control Register */
#define Mcu_SetCpmuAPICtlApiFe(value) ( \
   *((uint8*)MCU_CPMUAPICTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUAPICTL_APIFE_POS ) | \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUAPICTL_APIFE_POS) ) ) ) )
/* Macro to set APIE of Autonomous Periodical Interrupt Control Register */
#define Mcu_SetCpmuAPICtlApiE(value) ( \
   *((uint8*)MCU_CPMUAPICTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUAPICTL_APIE_POS ) | \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUAPICTL_APIE_POS) ) ) ) )
/* Macro to set APIF of Autonomous Periodical Interrupt Control Register */
#define Mcu_SetCpmuAPICtlApiF(value) ( \
   *((uint8*)MCU_CPMUAPICTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )
/* Macro to set ACLKTR of Autonomous Clock Trimming Register */
#define Mcu_SetCpmuAClkTrAClkTr(value) ( \
   *((uint8*)MCU_CPMUACLKTR_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x3f ) << MCU_CPMUACLKTR_ACLKTR_POS ) | \
      ( (*((uint8*)MCU_CPMUACLKTR_ADR_UI16)) & (uint8)(~((uint8)0x3f << MCU_CPMUACLKTR_ACLKTR_POS) ) ) ) )
/* Macro to set APIR of Autonomous Periodical Interrupt Rate Register */
#define Mcu_SetCpmuAPIRAPIR(value) ( \
   *((uint16*)MCU_CPMUAPIR_ADR_UI16) = \
      ( (uint16)( ( ((uint16)value) & (uint16)0xffff ) ) | \
      ( (*((uint16*)MCU_CPMUAPIR_ADR_UI16)) & (uint16)(~((uint16)0xffff) ) ) ) )
/* Macro to set HTOE of High Temperature Trimming Register */
#define Mcu_SetCpmuHtTrHtOe(value) ( \
   *((uint8*)MCU_CPMUHTTR_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUHTTR_HTOE_POS ) | \
      ( (*((uint8*)MCU_CPMUHTTR_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUHTTR_HTOE_POS) ) ) ) )
/* Macro to set HTTR of High Temperature Trimming Register */
#define Mcu_SetCpmuHtTrHtTr(value) ( \
   *((uint8*)MCU_CPMUHTTR_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0xf ) ) | \
      ( (*((uint8*)MCU_CPMUHTTR_ADR_UI16)) & (uint8)(~((uint8)0xf) ) ) ) )
/* Macro to set OSCE of S12CPMU_UHV_V5 Oscillator Register */
#define Mcu_SetCpmuOscOscE(value) ( \
   *((uint8*)MCU_CPMUOSC_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUOSC_OSCE_POS ) | \
      ( (*((uint8*)MCU_CPMUOSC_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUOSC_OSCE_POS) ) ) ) )
/* Macro to set PROT of S12CPMU_UHV_V5 Protection Register */
#define Mcu_SetCpmuProtProt(value) ( \
   *((uint8*)MCU_CPMUPROT_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0xff ) ) | \
      ( (*((uint8*)MCU_CPMUPROT_ADR_UI16)) & (uint8)(~((uint8)0xff) ) ) ) )
/* Macro to set EXTXON of Voltage Regulator Control Register */
#define Mcu_SetCpmuVRegCtlExtXOn(value) ( \
   *((uint8*)MCU_CPMUVREGCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUVREGCTL_EXTXON_POS ) | \
      ( (*((uint8*)MCU_CPMUVREGCTL_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUVREGCTL_EXTXON_POS) ) ) ) )
/* Macro to set INTXON of Voltage Regulator Control Register */
#define Mcu_SetCpmuVRegCtlIntXOn(value) ( \
   *((uint8*)MCU_CPMUVREGCTL_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)MCU_CPMUVREGCTL_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )
/* Macro to set OMRE of S12CPMU_UHV_V5 Oscillator Register 2 */
#define Mcu_SetCpmuOsc2OmRe(value) ( \
   *((uint8*)MCU_CPMUOSC2_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << MCU_CPMUOSC2_OMRE_POS ) | \
      ( (*((uint8*)MCU_CPMUOSC2_ADR_UI16)) & (uint8)(~((uint8)0x1 << MCU_CPMUOSC2_OMRE_POS) ) ) ) )
/* Macro to set OSCMOD of S12CPMU_UHV_V5 Oscillator Register 2 */
#define Mcu_SetCpmuOsc2OscMod(value) ( \
   *((uint8*)MCU_CPMUOSC2_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) ) | \
      ( (*((uint8*)MCU_CPMUOSC2_ADR_UI16)) & (uint8)(~((uint8)0x1) ) ) ) )

/* Macro to get PORF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_GetCpmuRFlgPoRf() ( \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) >> MCU_CPMURFLG_PORF_POS) & (uint8)0x1)
/* Macro to get LVRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_GetCpmuRFlgLvRf() ( \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) >> MCU_CPMURFLG_LVRF_POS) & (uint8)0x1)
/* Macro to get COPRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_GetCpmuRFlgCopRf() ( \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) >> MCU_CPMURFLG_COPRF_POS) & (uint8)0x1)
/* Macro to get OMRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_GetCpmuRFlgOmRf() ( \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16)) >> MCU_CPMURFLG_OMRF_POS) & (uint8)0x1)
/* Macro to get PMRF of S12CPMU_UHV_V5 Reset Flags Register */
#define Mcu_GetCpmuRFlgPmRf() ( \
      ( (*((uint8*)MCU_CPMURFLG_ADR_UI16))) & (uint8)0x1)
/* Macro to get VCOFRQ of S12CPMU_UHV_V5 Synthesizer Register */
#define Mcu_GetCpmuSynRVcoFrq() ( \
      ( (*((uint8*)MCU_CPMUSYNR_ADR_UI16)) >> MCU_CPMUSYNR_VCOFRQ_POS) & (uint8)0x3)
/* Macro to get SYNDIV of S12CPMU_UHV_V5 Synthesizer Register */
#define Mcu_GetCpmuSynRSynDiv() ( \
      ( (*((uint8*)MCU_CPMUSYNR_ADR_UI16))) & (uint8)0x3f)
/* Macro to get REFFRQ of S12CPMU_UHV_V5 Reference Divider Register */
#define Mcu_GetCpmuRefDivRefFrq() ( \
      ( (*((uint8*)MCU_CPMUREFDIV_ADR_UI16)) >> MCU_CPMUREFDIV_REFFRQ_POS) & (uint8)0x3)
/* Macro to get REFDIV of S12CPMU_UHV_V5 Reference Divider Register */
#define Mcu_GetCpmuRefDivRefDiv() ( \
      ( (*((uint8*)MCU_CPMUREFDIV_ADR_UI16))) & (uint8)0xf)
/* Macro to get POSTDIV of S12CPMU_UHV_V5 Post Divider Register */
#define Mcu_GetCpmuPostDivPostDiv() ( \
      ( (*((uint8*)MCU_CPMUPOSTDIV_ADR_UI16))) & (uint8)0x1f)
/* Macro to get RTIF of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_GetCpmuIFlgRtIf() ( \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16)) >> MCU_CPMUIFLG_RTIF_POS) & (uint8)0x1)
/* Macro to get LOCKIF of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_GetCpmuIFlgLockIf() ( \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16)) >> MCU_CPMUIFLG_LOCKIF_POS) & (uint8)0x1)
/* Macro to get LOCK of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_GetCpmuIFlgLock() ( \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16)) >> MCU_CPMUIFLG_LOCK_POS) & (uint8)0x1)
/* Macro to get OSCIF of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_GetCpmuIFlgOscIf() ( \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16)) >> MCU_CPMUIFLG_OSCIF_POS) & (uint8)0x1)
/* Macro to get UPOSC of S12CPMU_UHV_V5 Interrupt Flags Register */
#define Mcu_GetCpmuIFlgUpOsc() ( \
      ( (*((uint8*)MCU_CPMUIFLG_ADR_UI16))) & (uint8)0x1)
/* Macro to get RTIE of S12CPMU_UHV_V5 Interrupt Enable Register */
#define Mcu_GetCpmuIntRtIE() ( \
      ( (*((uint8*)MCU_CPMUINT_ADR_UI16)) >> MCU_CPMUINT_RTIE_POS) & (uint8)0x1)
/* Macro to get LOCKIE of S12CPMU_UHV_V5 Interrupt Enable Register */
#define Mcu_GetCpmuIntLockIE() ( \
      ( (*((uint8*)MCU_CPMUINT_ADR_UI16)) >> MCU_CPMUINT_LOCKIE_POS) & (uint8)0x1)
/* Macro to get OSCIE of S12CPMU_UHV_V5 Interrupt Enable Register */
#define Mcu_GetCpmuIntOscIE() ( \
      ( (*((uint8*)MCU_CPMUINT_ADR_UI16)) >> MCU_CPMUINT_OSCIE_POS) & (uint8)0x1)
/* Macro to get PLLSEL of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSPllSel() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) >> MCU_CPMUCLKS_PLLSEL_POS) & (uint8)0x1)
/* Macro to get PSTP of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSPStp() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) >> MCU_CPMUCLKS_PSTP_POS) & (uint8)0x1)
/* Macro to get CSAD of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSCSAD() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) >> MCU_CPMUCLKS_CSAD_POS) & (uint8)0x1)
/* Macro to get COPOSCSEL1 of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSCopOscSel1() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) >> MCU_CPMUCLKS_COPOSCSEL1_POS) & (uint8)0x1)
/* Macro to get PRE of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSPre() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) >> MCU_CPMUCLKS_PRE_POS) & (uint8)0x1)
/* Macro to get PCE of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSPce() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) >> MCU_CPMUCLKS_PCE_POS) & (uint8)0x1)
/* Macro to get RTIOSCSEL of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSRtiOscSel() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16)) >> MCU_CPMUCLKS_RTIOSCSEL_POS) & (uint8)0x1)
/* Macro to get COPOSCSEL0 of S12CPMU_UHV_V5 Clock Select Register */
#define Mcu_GetCpmuClkSCopOscSel0() ( \
      ( (*((uint8*)MCU_CPMUCLKS_ADR_UI16))) & (uint8)0x1)
/* Macro to get FM of S12CPMU_UHV_V5 PLL Control Register */
#define Mcu_GetCpmuPllFm() ( \
      ( (*((uint8*)MCU_CPMUPLL_ADR_UI16)) >> MCU_CPMUPLL_FM_POS) & (uint8)0x3)
/* Macro to get RTDEC of S12CPMU_UHV_V5 RTI Control Register */
#define Mcu_GetCpmuRtiRtDec() ( \
      ( (*((uint8*)MCU_CPMURTI_ADR_UI16)) >> MCU_CPMURTI_RTDEC_POS) & (uint8)0x1)
/* Macro to get RTRPRE of S12CPMU_UHV_V5 RTI Control Register */
#define Mcu_GetCpmuRtiRtRPre() ( \
      ( (*((uint8*)MCU_CPMURTI_ADR_UI16)) >> MCU_CPMURTI_RTRPRE_POS) & (uint8)0x7)
/* Macro to get RTRMOD of S12CPMU_UHV_V5 RTI Control Register */
#define Mcu_GetCpmuRtiRtRMod() ( \
      ( (*((uint8*)MCU_CPMURTI_ADR_UI16))) & (uint8)0xf)
/* Macro to get VSEL of High Temperature Control Register */
#define Mcu_GetCpmuHtCtlVSel() ( \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16)) >> MCU_CPMUHTCTL_VSEL_POS) & (uint8)0x1)
/* Macro to get HTE of High Temperature Control Register */
#define Mcu_GetCpmuHtCtlHtE() ( \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16)) >> MCU_CPMUHTCTL_HTE_POS) & (uint8)0x1)
/* Macro to get HTDS of High Temperature Control Register */
#define Mcu_GetCpmuHtCtlHtDs() ( \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16)) >> MCU_CPMUHTCTL_HTDS_POS) & (uint8)0x1)
/* Macro to get HTIE of High Temperature Control Register */
#define Mcu_GetCpmuHtCtlHtIe() ( \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16)) >> MCU_CPMUHTCTL_HTIE_POS) & (uint8)0x1)
/* Macro to get HTIF of High Temperature Control Register */
#define Mcu_GetCpmuHtCtlHtIf() ( \
      ( (*((uint8*)MCU_CPMUHTCTL_ADR_UI16))) & (uint8)0x1)
/* Macro to get LVDS of Low Voltage Control Register */
#define Mcu_GetCpmuLvCtlLvDs() ( \
      ( (*((uint8*)MCU_CPMULVCTL_ADR_UI16)) >> MCU_CPMULVCTL_LVDS_POS) & (uint8)0x1)
/* Macro to get LVIE of Low Voltage Control Register */
#define Mcu_GetCpmuLvCtlLvIE() ( \
      ( (*((uint8*)MCU_CPMULVCTL_ADR_UI16)) >> MCU_CPMULVCTL_LVIE_POS) & (uint8)0x1)
/* Macro to get LVIF of Low Voltage Control Register */
#define Mcu_GetCpmuLvCtlLvIF() ( \
      ( (*((uint8*)MCU_CPMULVCTL_ADR_UI16))) & (uint8)0x1)
/* Macro to get APICLK of Autonomous Periodical Interrupt Control Register */
#define Mcu_GetCpmuAPICtlApiClk() ( \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) >> MCU_CPMUAPICTL_APICLK_POS) & (uint8)0x1)
/* Macro to get APIES of Autonomous Periodical Interrupt Control Register */
#define Mcu_GetCpmuAPICtlApiEs() ( \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) >> MCU_CPMUAPICTL_APIES_POS) & (uint8)0x1)
/* Macro to get APIEA of Autonomous Periodical Interrupt Control Register */
#define Mcu_GetCpmuAPICtlApiEa() ( \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) >> MCU_CPMUAPICTL_APIEA_POS) & (uint8)0x1)
/* Macro to get APIFE of Autonomous Periodical Interrupt Control Register */
#define Mcu_GetCpmuAPICtlApiFe() ( \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) >> MCU_CPMUAPICTL_APIFE_POS) & (uint8)0x1)
/* Macro to get APIE of Autonomous Periodical Interrupt Control Register */
#define Mcu_GetCpmuAPICtlApiE() ( \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16)) >> MCU_CPMUAPICTL_APIE_POS) & (uint8)0x1)
/* Macro to get APIF of Autonomous Periodical Interrupt Control Register */
#define Mcu_GetCpmuAPICtlApiF() ( \
      ( (*((uint8*)MCU_CPMUAPICTL_ADR_UI16))) & (uint8)0x1)
/* Macro to get ACLKTR of Autonomous Clock Trimming Register */
#define Mcu_GetCpmuAClkTrAClkTr() ( \
      ( (*((uint8*)MCU_CPMUACLKTR_ADR_UI16)) >> MCU_CPMUACLKTR_ACLKTR_POS) & (uint8)0x3f)
/* Macro to get APIR of Autonomous Periodical Interrupt Rate Register */
#define Mcu_GetCpmuAPIRAPIR() ( \
      ( (*((uint16*)MCU_CPMUAPIR_ADR_UI16))) & (uint16)0xffff)
/* Macro to get HTOE of High Temperature Trimming Register */
#define Mcu_GetCpmuHtTrHtOe() ( \
      ( (*((uint8*)MCU_CPMUHTTR_ADR_UI16)) >> MCU_CPMUHTTR_HTOE_POS) & (uint8)0x1)
/* Macro to get HTTR of High Temperature Trimming Register */
#define Mcu_GetCpmuHtTrHtTr() ( \
      ( (*((uint8*)MCU_CPMUHTTR_ADR_UI16))) & (uint8)0xf)
/* Macro to get TCTRIM of S12CPMU_UHV_V5 IRC1M Trim Registers */
#define Mcu_GetCpmuIrcTrimTcTrim() ( \
      ( (*((uint8*)MCU_CPMUIRCTRIM_ADR_UI16)) >> MCU_CPMUIRCTRIM_TCTRIM_POS) & (uint16)0x1f)
/* Macro to get IRCTRIM of S12CPMU_UHV_V5 IRC1M Trim Registers */
#define Mcu_GetCpmuIrcTrimIrcTrim() ( \
      ( (*((uint16*)MCU_CPMUIRCTRIM_ADR_UI16))) & (uint16)0x3ff)
/* Macro to get OSCE of S12CPMU_UHV_V5 Oscillator Register */
#define Mcu_GetCpmuOscOscE() ( \
      ( (*((uint8*)MCU_CPMUOSC_ADR_UI16)) >> MCU_CPMUOSC_OSCE_POS) & (uint8)0x1)
/* Macro to get PROT of S12CPMU_UHV_V5 Protection Register */
#define Mcu_GetCpmuProtProt() ( \
      ( (*((uint8*)MCU_CPMUPROT_ADR_UI16))) & (uint8)0xff)
/* Macro to get EXTXON of Voltage Regulator Control Register */
#define Mcu_GetCpmuVRegCtlExtXOn() ( \
      ( (*((uint8*)MCU_CPMUVREGCTL_ADR_UI16)) >> MCU_CPMUVREGCTL_EXTXON_POS) & (uint8)0x1)
/* Macro to get INTXON of Voltage Regulator Control Register */
#define Mcu_GetCpmuVRegCtlIntXOn() ( \
      ( (*((uint8*)MCU_CPMUVREGCTL_ADR_UI16))) & (uint8)0x1)
/* Macro to get OMRE of S12CPMU_UHV_V5 Oscillator Register 2 */
#define Mcu_GetCpmuOsc2OmRe() ( \
      ( (*((uint8*)MCU_CPMUOSC2_ADR_UI16)) >> MCU_CPMUOSC2_OMRE_POS) & (uint8)0x1)
/* Macro to get OSCMOD of S12CPMU_UHV_V5 Oscillator Register 2 */
#define Mcu_GetCpmuOsc2OscMod() ( \
      ( (*((uint8*)MCU_CPMUOSC2_ADR_UI16))) & (uint8)0x1)


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config typedefs ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

typedef  void (* Mcu_CheckResetReasonType) (void);

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Synthesizer Register
*/
typedef enum
{
   MCU_32MHZ_FVCO_48MHZ = (uint8)0, /* 32MHz <= fVCO <= 48MHz */
   MCU_48MHZ_FVCO_64MHZ = (uint8)1  /* 48MHz <= fVCO <= 64MHz */
} Mcu_CpmuSynRVcoFrqType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Reference Divider Register
*/
typedef enum
{
   MCU_1MHZ_FREF_2MHZ  = (uint8)0, /* 1MHz <= fREF <= 2MHz */
   MCU_2MHZ_FREF_6MHZ  = (uint8)1, /* 2MHz <= fREF <= 6MHz */
   MCU_6MHZ_FREF_12MHZ = (uint8)2, /* 6MHz <= fREF <= 12MHz */
   MCU_FREF_GT_12MHZ   = (uint8)3  /* fREF > 12MHz */
} Mcu_CpmuRefDivRefFrqType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Interrupt Flags Register
*/
typedef enum
{
   MCU_RTI_NOT_OCCURED = (uint8)0, /* RTI time-out has not yet occurred */
   MCU_RTI_OCCURED     = (uint8)1  /* Power on reset has occurred */
} Mcu_CpmuIFlgRtIfType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Interrupt Flags Register
*/
typedef enum
{
   MCU_LOCK_BIT_NOT_CHANGED = (uint8)0, /* No change in LOCK bit */
   MCU_LOCK_BIT_CHANGED     = (uint8)1  /* LOCK bit has changed */
} Mcu_CpmuIFlgLockIfType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Interrupt Flags Register
*/
typedef enum
{
   MCU_PLL_NOT_LOCKED = (uint8)0, /* VCOCLK is not within the desired tolerance of the target frequency */
   MCU_PLL_LOCKED     = (uint8)1  /* VCOCLK is within the desired tolerance of the target frequency */
} Mcu_CpmuIFlgLockType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Interrupt Flags Register
*/
typedef enum
{
   MCU_UPOSC_BIT_NOT_CHANGED = (uint8)0, /* No change in UPOSC bit */
   MCU_UPOSC_BIT_CHANGED     = (uint8)1  /* UPOSC bit has changed */
} Mcu_CpmuIFlgOscIfType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Interrupt Flags Register
*/
typedef enum
{
   MCU_OSC_NOT_QUALIFIED = (uint8)0, /* The oscillator is off or oscillation is not qualified by the PLL */
   MCU_OSC_QUALIFIED     = (uint8)1  /* The oscillator is qualified by the PLL */
} Mcu_CpmuIFlgUpOscType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_SYSCLK_FROM_OSCCLK = (uint8)0, /* System clocks are derived from OSCCLK if oscillator is up */
   MCU_SYSCLK_FROM_PLLCLK = (uint8)1  /* System clocks are derived from PLLCLK */
} Mcu_CpmuClkSPllSelType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_FULL_STOP_MODE   = (uint8)0, /* Oscillator is disabled in Stop Mode */
   MCU_PSEUDO_STOP_MODE = (uint8)1  /* Oscillator continues to run in Stop Mode */
} Mcu_CpmuClkSPStpType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_COP_RUN_IN_STOP_MODE  = (uint8)0, /* COP running in Stop Mode */
   MCU_COP_STOP_IN_STOP_MODE = (uint8)1  /* COP stopped in Stop Mode */
} Mcu_CpmuClkSCSADType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_COP_CLK_COPOSCSEL0 = (uint8)0, /* COP clock source defined by COPOSCSEL0 */
   MCU_COP_CLK_ACLK       = (uint8)1  /* COP clock source is ACLK derived from a trimmable internal RC-Oscillator */
} Mcu_CpmuClkSCopOscSel1Type;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_RTI_STOP_IN_PSEUDO_STOP_MODE = (uint8)0, /* RTI stops running during Pseudo Stop Mode */
   MCU_RTI_RUN_IN_PSEUDO_STOP_MODE  = (uint8)1  /* RTI continues running during Pseudo Stop Mode if RTIOSCSEL=1 */
} Mcu_CpmuClkSPreType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_COP_STOP_IN_PSEUDO_STOP_MODE = (uint8)0, /* COP stops running during Pseudo Stop Mode */
   MCU_COP_RUN_IN_PSEUDO_STOP_MODE  = (uint8)1  /* COP continues running during Pseudo Stop Mode if COPOSCSEL=1 */
} Mcu_CpmuClkSPceType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_RTI_CLK_IRCCLK = (uint8)0, /* RTI clock source is IRCCLK */
   MCU_RTI_CLK_OSCCLK = (uint8)1  /* RTI clock source is OSCCLK */
} Mcu_CpmuClkSRtiOscSelType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Clock Select Register
*/
typedef enum
{
   MCU_COP_CLK_IRCCLK = (uint8)0, /* COP clock source is IRCCLK */
   MCU_COP_CLK_OSCCLK = (uint8)1  /* COP clock source is OSCCLK */
} Mcu_CpmuClkSCopOscSel0Type;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 PLL Control Register
*/
typedef enum
{
   MCU_FM_OFF       = (uint8)0, /* FM Amplitude fVCO Variation off */
   MCU_FM_1_PERCENT = (uint8)1, /* FM Amplitude fVCO Variation +-1 percent */
   MCU_FM_2_PERCENT = (uint8)2, /* FM Amplitude fVCO Variation +-2 percent */
   MCU_FM_4_PERCENT = (uint8)3  /* FM Amplitude fVCO Variation +-4 percent */
} Mcu_CpmuPllFmType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 RTI Control Register
*/
typedef enum
{
   MCU_BIN_DIV = (uint8)0, /* Binary based divider value */
   MCU_DEC_DIV = (uint8)1  /* Decimal based divider value */
} Mcu_CpmuRtiRtDecType;

/*
* \brief Configuration options of mcu bits in High Temperature Control Register
*/
typedef enum
{
   MCU_INTERNAL_TEMPERATURE = (uint8)0, /* An internal temperature proportional voltage VHT can be accessed internally */
   MCU_BANDGAP_REF_VOLTAGE  = (uint8)1  /* Bandgap reference voltage VBG can be accessed internally */
} Mcu_CpmuHtCtlVSelType;

/*
* \brief Configuration options of mcu bits in High Temperature Control Register
*/
typedef enum
{
   MCU_JUNCTION_TEMP_LOW  = (uint8)0, /* Junction Temperature is below level THTID or RPM */
   MCU_JUNCTION_TEMP_HIGH = (uint8)1  /* Junction Temperature is above level THTIA and FPM */
} Mcu_CpmuHtCtlHtDsType;

/*
* \brief Configuration options of mcu bits in Low Voltage Control Register
*/
typedef enum
{
   MCU_INPUT_VOLTAGE_LOW  = (uint8)0, /* Input voltage VDDA is above level VLVID or RPM */
   MCU_INPUT_VOLTAGE_HIGH = (uint8)1  /* Input voltage VDDA is below level VLVIA and FPM */
} Mcu_CpmuLvCtlLvDsType;

/*
* \brief Configuration options of mcu bits in Autonomous Periodical Interrupt Control Register
*/
typedef enum
{
   MCU_SRC_ACLK   = (uint8)0, /* Autonomous Clock (ACLK) used as source */
   MCU_SRC_BUSCLK = (uint8)1  /* Bus Clock used as source */
} Mcu_CpmuAPICtlApiClkType;

/*
* \brief Configuration options of mcu bits in Autonomous Periodical Interrupt Control Register
*/
typedef enum
{
   MCU_API_EXTCLK_HIGH_PULSE = (uint8)0, /* If APIEA and APIFE are set, at the external pin API_EXTCLK periodic high pulses are visible at the end of
every selected period with the size of half of the minimum period */
   MCU_API_EXTCLK_CLOCK      = (uint8)1  /* If APIEA and APIFE are set, at the external pin API_EXTCLK a clock is visible with 2 times the selected API
Period */
} Mcu_CpmuAPICtlApiEsType;

/*
* \brief Configuration options of mcu bits in Autonomous Periodical Interrupt Control Register
*/
typedef enum
{
   MCU_APIES_EXT_ACCESS    = (uint8)0, /* Waveform selected by APIES can not be accessed externally */
   MCU_APIES_NO_EXT_ACCESS = (uint8)1  /* Waveform selected by APIES can be accessed externally, if APIFE is set */
} Mcu_CpmuAPICtlApiEaType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Protection Register
*/
typedef enum
{
   MCU_PROT_DISABLED = (uint8)0x00, /* Protection of clock configuration registers is disabled */
   MCU_PROT_ENABLED  = (uint8)0x01, /* Protection of clock configuration registers is enabled */
   MCU_PROT_ENABLE   = (uint8)0xFF, /* Enable Protection of clock configuration registers */
   MCU_PROT_DISABLE  = (uint8)0x26  /* Disable Protection of clock configuration registers */
} Mcu_CpmuProtProtType;

/*
* \brief Configuration options of mcu bits in Voltage Regulator Control Register
*/
typedef enum
{
   MCU_VDDX_NOT_USE_BJT = (uint8)0, /* VDDX control loop does not use external BJT */
   MCU_VDDX_USE_BJT     = (uint8)1  /* VDDX control loop uses external BJT */
} Mcu_CpmuVRegCtlExtXOnType;

/*
* \brief Configuration options of mcu bits in Voltage Regulator Control Register
*/
typedef enum
{
   MCU_VDDX_NOT_USE_INT_PWR = (uint8)0, /* VDDX control loop does not use internal power transistor */
   MCU_VDDX_USE_INT_PWR     = (uint8)1  /* VDDX control loop uses internal power transistor */
} Mcu_CpmuVRegCtlIntXOnType;

/*
* \brief Configuration options of mcu bits in S12CPMU_UHV_V5 Oscillator Register 2
*/
typedef enum
{
   MCU_EXTOSC_LOOP_CTL_MODE   = (uint8)0, /* External oscillator configured for loop controlled mode */
   MCU_EXTOSC_FULL_SWING_MODE = (uint8)1  /* External oscillator configured for full swing mode */
} Mcu_CpmuOsc2OscModType;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config struct ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
*	\brief contains information for initialisation
*
*	This type contains information for the initialisation process
*/
typedef struct
{
   uint8                      mcu_CpmuSynRSynDiv;
   Mcu_CpmuSynRVcoFrqType     mcu_SyncfvcoRange_e;
   uint8                      mcu_CpmuPostDivPostDiv;
   Mcu_CpmuClkSCopOscSel1Type mcu_CpmuClkSCopOscSel1;
   //Mcu_CheckResetReasonType   mcu_CheckResetReason;
} Mcu_ConfigType;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* \brief Function to initialize the MCU module.
*
* Initializes the MCU module.
*
* \param [in]  ---
* \param [out] ---
* \return      MCU_E_OK: Initialization done correctly
*              MCU_E_NOT_OK: Something went wrong during initialization
*/
void Mcu_Init
(
   void
);


#if (MCU_DEINIT_API == STD_ON)
/*
* \brief Function to deinitialize the MCU module.
*
* Deinitializes the MCU module.
*
* \param [in]  ---
* \param [out] ---
* \return      MCU_E_OK: Deinitialization done
*              MCU_E_NOT_OK: Something went wrong during deinitialization
*/
Std_ReturnType Mcu_DeInit
(
   void
);
#endif /* MCU_DEINIT_API */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/*
* \brief This service returns the status of this module .
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: MCU_UNINIT, MCU_DEINITIALIZED, MCU_INITIALIZED
*/
Std_ModuleStatusReturnType Mcu_GetModuleStatus
(
   void
);
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */


#if(MCU_VERSION_INFO_API == STD_ON)
/*
* \brief This service returns the version information of this module .
*
* \param [in]  ---
* \param [out] versioninfo = Pointer to where to store the version
*                            information of this module .
* \return      ---
*/
void Mcu_GetVersionInfo
(
   Std_VersionInfoType *versioninfo
);
#endif /* MCU_VERSION_INFO_API == STD_ON */

/**
 * \brief Set stop mode
 */
void Mcu_SetStopMode(
   void
);



/**
 * \brief Set wait mode
 */
void Mcu_SetWaitMode(
   void
);



#pragma CODE_SEG __NEAR_SEG NON_BANKED
/**
 * \brief Performs a reset by writing an invalid value into COP register
 */
void Mcu_PerformReset(
   void
);
#pragma CODE_SEG DEFAULT

#endif /* MCU_H */
