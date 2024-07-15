/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include <ProjectSettings.h>
#include "Mcu_Cfg.h"
#include "CoSyst.h"

#if(MCU_DEV_ERROR_DETECTION == STD_ON)
   //#include "Det.h"
#endif /* MCU_DEV_ERROR_DETECT == STD_ON */

#include "Mcu.h"
#include "Wdg.h"


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define MCU_SW_MAJOR_VERSION_C   (1)    /* Software major_c version */
#define MCU_SW_MINOR_VERSION_C   (0)    /* Software minor_c version */
#define MCU_SW_PATCH_VERSION_C   (0)    /* Software patch_c version */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #makros --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if((MCU_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || \
    (MCU_SW_MINOR_VERSION_C != MCU_SW_MINOR_VERSION) || \
    (MCU_SW_PATCH_VERSION_C != MCU_SW_PATCH_VERSION))
   #error "Software Version Numbers of Mcu.c and Mcu.h are different."
#endif /* (MCU_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || ... */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #defines -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if (MCU_ROM_OPTIMIZATION == STD_ON)
#define   MCU_CPMUAPICTL *((uint8*)((uint16)0x0006d2))   /* Autonomous Periodic Interrupt (API) Register */
#define   MCU_CPMUACLKTR *((uint8*)((uint16)0x0006d3))   /* Autonomous Periodic Interrupt (API) Register */
#define   MCU_CPMUAPIR *((uint8*)((uint16)0x0006d4))   /* Autonomous Periodic Interrupt (API) Register */
#define   MCU_CPMURFLG *((uint8*)((uint16)0x0006c3))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUSYNR *((uint8*)((uint16)0x0006c4))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUREFDIV *((uint8*)((uint16)0x0006c5))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUPOSTDIV *((uint8*)((uint16)0x0006c6))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUIFLG *((uint8*)((uint16)0x0006c7))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUINT *((uint8*)((uint16)0x0006c8))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUCLKS *((uint8*)((uint16)0x0006c9))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUPLL *((uint8*)((uint16)0x0006ca))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUHTCTL *((uint8*)((uint16)0x0006d0))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMULVCTL *((uint8*)((uint16)0x0006d1))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUHTTR *((uint8*)((uint16)0x0006d7))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUIRCTRIM *((uint8*)((uint16)0x0006d8))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUOSC *((uint8*)((uint16)0x0006da))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUPROT *((uint8*)((uint16)0x0006db))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUVREGCTL *((uint8*)((uint16)0x0006dd))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUOSC2 *((uint8*)((uint16)0x0006de))   /* Clock, Reset and Power Management Unit (CPMU) Register */
#define   MCU_CPMUCOP *((uint8*)((uint16)0x0006cc))   /* Computer Operating Properly Watchdog (COP) Register */
#define   MCU_CPMURTI *((uint8*)((uint16)0x0006cb))   /* Real Time Interrupt (RTI) Register */
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal typedefs -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal enums  ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal structs --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal data (static) -------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/* internal Module Status */
static Std_ModuleStatusReturnType mcu_moduleStatus_e;
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global data (Userdata) --------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern const Mcu_ConfigType mcu_initialConfiguration_s;


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config function prototype (internal use only) ---------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal function prototypes (static) ----------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal functions (static) --------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global functions (Userfunctions) ----------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* \brief Function to initialize the MCU module.
*
* Initializes the Module Short Name.
*
* \param [in]  ---
* \param [out] ---
* \return      MCU_E_OK: Initialization done correctly
*              MCU_E_NOT_OK: Something went wrong during initialization
*/
void Mcu_Init
(
   void
)
{
   /* -- variables declaration ---------------- */
   /* -- init function internal variables ----- */
   /* -- source code -------------------------- */
#if(MCU_DEV_ERROR_DETECTION == STD_ON)
if(mcu_moduleStatus_e == MODULE_INITIALIZED)
   {
      /* Send error to DET */
      //Det_ReportError((uint16)MCU_MODULE_ID, (uint8)MCU_INSTANCE_ID, (uint8)MCU_INIT_API_ID, (uint8)MCU_E_ALREADY_INITIALIZED);
   }
   else
#endif /* MCU_DEV_ERROR_DETECT == STD_ON */
   {
      /* turn off special mode if special mode is activated */
      if(*((uint8*)MCU_MODE_ADR_UI16) == MCU_MODE_SPECIALMODE_ACTIVE)
      {
         MCU_DISABLE_SPECIALMODE();
      }

      //mcu_initialConfiguration_s.mcu_CheckResetReason();

#if (MCU_ROM_OPTIMIZATION == STD_ON)
      MCU_CPMURFLG = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUSYNR = 0x58U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUREFDIV = 0x0FU;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUPOSTDIV = 0x03U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUIFLG = 0x18U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUINT = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUCLKS = 0x80U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUPLL = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMURTI = 0x00U;     /* Register Real Time Interrupt (RTI) */
      MCU_CPMUHTCTL = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMULVCTL = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUAPICTL = 0x00U;     /* Register Autonomous Periodic Interrupt (API) */
      MCU_CPMUACLKTR = 0x00U;     /* Register Autonomous Periodic Interrupt (API) */
      MCU_CPMUAPIR = 0x0000U;     /* Register Autonomous Periodic Interrupt (API) */
      MCU_CPMUHTTR = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUOSC = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUPROT = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUVREGCTL = 0x03U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
      MCU_CPMUOSC2 = 0x00U;     /* Register Clock, Reset and Power Management Unit (CPMU) */
#else
      /* Initialise poRf in S12CPMU_UHV_V5 Reset Flags Register */
      Mcu_SetCpmuRFlgPoRf(MCU_CPMURFLG_PORF_DEFAULT);
      /* Initialise lvRf in S12CPMU_UHV_V5 Reset Flags Register */
      Mcu_SetCpmuRFlgLvRf(MCU_CPMURFLG_LVRF_DEFAULT);
      /* Initialise copRf in S12CPMU_UHV_V5 Reset Flags Register */
      Mcu_SetCpmuRFlgCopRf(MCU_CPMURFLG_COPRF_DEFAULT);
      /* Initialise omRf in S12CPMU_UHV_V5 Reset Flags Register */
      Mcu_SetCpmuRFlgOmRf(MCU_CPMURFLG_OMRF_DEFAULT);
      /* Initialise pmRf in S12CPMU_UHV_V5 Reset Flags Register */
      Mcu_SetCpmuRFlgPmRf(MCU_CPMURFLG_PMRF_DEFAULT);
      /* Initialise vcoFrq in S12CPMU_UHV_V5 Synthesizer Register */
      Mcu_SetCpmuSynRVcoFrq(MCU_CPMUSYNR_VCOFRQ_DEFAULT);
      /* Initialise synDiv in S12CPMU_UHV_V5 Synthesizer Register */
      Mcu_SetCpmuSynRSynDiv(MCU_CPMUSYNR_SYNDIV_DEFAULT);
      /* Initialise refFrq in S12CPMU_UHV_V5 Reference Divider Register */
      Mcu_SetCpmuRefDivRefFrq(MCU_CPMUREFDIV_REFFRQ_DEFAULT);
      /* Initialise refDiv in S12CPMU_UHV_V5 Reference Divider Register */
      Mcu_SetCpmuRefDivRefDiv(MCU_CPMUREFDIV_REFDIV_DEFAULT);
      /* Initialise postDiv in S12CPMU_UHV_V5 Post Divider Register */
      Mcu_SetCpmuPostDivPostDiv(MCU_CPMUPOSTDIV_POSTDIV_DEFAULT);
      /* Initialise rtIf in S12CPMU_UHV_V5 Interrupt Flags Register */
      Mcu_SetCpmuIFlgRtIf(MCU_CPMUIFLG_RTIF_DEFAULT);
      /* Initialise lockIf in S12CPMU_UHV_V5 Interrupt Flags Register */
      Mcu_SetCpmuIFlgLockIf(MCU_CPMUIFLG_LOCKIF_DEFAULT);
      /* Initialise oscIf in S12CPMU_UHV_V5 Interrupt Flags Register */
      Mcu_SetCpmuIFlgOscIf(MCU_CPMUIFLG_OSCIF_DEFAULT);
      /* Initialise rtIE in S12CPMU_UHV_V5 Interrupt Enable Register */
      Mcu_SetCpmuIntRtIE(MCU_CPMUINT_RTIE_DEFAULT);
      /* Initialise lockIE in S12CPMU_UHV_V5 Interrupt Enable Register */
      Mcu_SetCpmuIntLockIE(MCU_CPMUINT_LOCKIE_DEFAULT);
      /* Initialise oscIE in S12CPMU_UHV_V5 Interrupt Enable Register */
      Mcu_SetCpmuIntOscIE(MCU_CPMUINT_OSCIE_DEFAULT);
      /* Initialise pllSel in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSPllSel(MCU_CPMUCLKS_PLLSEL_DEFAULT);
      /* Initialise pStp in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSPStp(MCU_CPMUCLKS_PSTP_DEFAULT);
      /* Initialise cSAD in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSCSAD(MCU_CPMUCLKS_CSAD_DEFAULT);
      /* Initialise copOscSel1 in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSCopOscSel1(MCU_CPMUCLKS_COPOSCSEL1_DEFAULT);
      /* Initialise pre in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSPre(MCU_CPMUCLKS_PRE_DEFAULT);
      /* Initialise pce in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSPce(MCU_CPMUCLKS_PCE_DEFAULT);
      /* Initialise rtiOscSel in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSRtiOscSel(MCU_CPMUCLKS_RTIOSCSEL_DEFAULT);
      /* Initialise copOscSel0 in S12CPMU_UHV_V5 Clock Select Register */
      Mcu_SetCpmuClkSCopOscSel0(MCU_CPMUCLKS_COPOSCSEL0_DEFAULT);
      /* Initialise fm in S12CPMU_UHV_V5 PLL Control Register */
      Mcu_SetCpmuPllFm(MCU_CPMUPLL_FM_DEFAULT);
      /* Initialise rtDec in S12CPMU_UHV_V5 RTI Control Register */
      Mcu_SetCpmuRtiRtDec(MCU_CPMURTI_RTDEC_DEFAULT);
      /* Initialise rtRPre in S12CPMU_UHV_V5 RTI Control Register */
      Mcu_SetCpmuRtiRtRPre(MCU_CPMURTI_RTRPRE_DEFAULT);
      /* Initialise rtRMod in S12CPMU_UHV_V5 RTI Control Register */
      Mcu_SetCpmuRtiRtRMod(MCU_CPMURTI_RTRMOD_DEFAULT);
      /* Initialise vSel in High Temperature Control Register */
      Mcu_SetCpmuHtCtlVSel(MCU_CPMUHTCTL_VSEL_DEFAULT);
      /* Initialise htE in High Temperature Control Register */
      Mcu_SetCpmuHtCtlHtE(MCU_CPMUHTCTL_HTE_DEFAULT);
      /* Initialise htIf in High Temperature Control Register */
      Mcu_SetCpmuHtCtlHtIf(MCU_CPMUHTCTL_HTIF_DEFAULT);
      /* Initialise lvIE in Low Voltage Control Register */
      Mcu_SetCpmuLvCtlLvIE(MCU_CPMULVCTL_LVIE_DEFAULT);
      /* Initialise lvIF in Low Voltage Control Register */
      Mcu_SetCpmuLvCtlLvIF(MCU_CPMULVCTL_LVIF_DEFAULT);
      /* Initialise apiClk in Autonomous Periodical Interrupt Control Register */
      Mcu_SetCpmuAPICtlApiClk(MCU_CPMUAPICTL_APICLK_DEFAULT);
      /* Initialise apiEs in Autonomous Periodical Interrupt Control Register */
      Mcu_SetCpmuAPICtlApiEs(MCU_CPMUAPICTL_APIES_DEFAULT);
      /* Initialise apiEa in Autonomous Periodical Interrupt Control Register */
      Mcu_SetCpmuAPICtlApiEa(MCU_CPMUAPICTL_APIEA_DEFAULT);
      /* Initialise apiFe in Autonomous Periodical Interrupt Control Register */
      Mcu_SetCpmuAPICtlApiFe(MCU_CPMUAPICTL_APIFE_DEFAULT);
      /* Initialise apiE in Autonomous Periodical Interrupt Control Register */
      Mcu_SetCpmuAPICtlApiE(MCU_CPMUAPICTL_APIE_DEFAULT);
      /* Initialise apiF in Autonomous Periodical Interrupt Control Register */
      Mcu_SetCpmuAPICtlApiF(MCU_CPMUAPICTL_APIF_DEFAULT);
      /* Initialise aClkTr in Autonomous Clock Trimming Register */
      Mcu_SetCpmuAClkTrAClkTr(MCU_CPMUACLKTR_ACLKTR_DEFAULT);
      /* Initialise APIR in Autonomous Periodical Interrupt Rate Register */
      Mcu_SetCpmuAPIRAPIR(MCU_CPMUAPIR_APIR_DEFAULT);
      /* Initialise htOe in High Temperature Trimming Register */
      Mcu_SetCpmuHtTrHtOe(MCU_CPMUHTTR_HTOE_DEFAULT);
      /* Initialise htTr in High Temperature Trimming Register */
      Mcu_SetCpmuHtTrHtTr(MCU_CPMUHTTR_HTTR_DEFAULT);
      /* Initialise oscE in S12CPMU_UHV_V5 Oscillator Register */
      Mcu_SetCpmuOscOscE(MCU_CPMUOSC_OSCE_DEFAULT);
      /* Initialise prot in S12CPMU_UHV_V5 Protection Register */
      Mcu_SetCpmuProtProt(MCU_CPMUPROT_PROT_DEFAULT);
      /* Initialise omRe in S12CPMU_UHV_V5 Oscillator Register 2 */
      Mcu_SetCpmuOsc2OmRe(MCU_CPMUOSC2_OMRE_DEFAULT);
      /* Initialise oscMod in S12CPMU_UHV_V5 Oscillator Register 2 */
      Mcu_SetCpmuOsc2OscMod(MCU_CPMUOSC2_OSCMOD_DEFAULT);

      /* ---------- CAUTION  ---------- */
      /* Voltage Regulator Control Register (CPMUVREGCTL) is not written due the customer request */


      /* Template to configure synDiv in S12CPMU_UHV_V5 Synthesizer Register */
      /* Mcu_SetCpmuSynRSynDiv(mcu_initialConfiguration_s.mcu_CpmuSynRSynDiv); */
      /* Template to configure postDiv in S12CPMU_UHV_V5 Post Divider Register */
      /* Mcu_SetCpmuPostDivPostDiv(mcu_initialConfiguration_s.mcu_CpmuPostDivPostDiv); */
      /* Template to configure copOscSel1 in S12CPMU_UHV_V5 Clock Select Register */
      /* Mcu_SetCpmuClkSCopOscSel1(mcu_initialConfiguration_s.mcu_CpmuClkSCopOscSel1); */
#endif

      /* disable protection of clock configuration registers */
      Mcu_SetCpmuProtProt(MCU_PROT_DISABLE);

      /* set post divider */
      Mcu_SetCpmuPostDivPostDiv(mcu_initialConfiguration_s.mcu_CpmuPostDivPostDiv);

      /* set VCOFRQ and SYNDIV to 0 before changing pll frequency */
      Mcu_SetCpmuSynRVcoFrq(0);
      Mcu_SetCpmuSynRSynDiv(0);

      /* set vco range */
      Mcu_SetCpmuSynRVcoFrq(mcu_initialConfiguration_s.mcu_SyncfvcoRange_e);
      /* set pll multiplier */
      Mcu_SetCpmuSynRSynDiv(mcu_initialConfiguration_s.mcu_CpmuSynRSynDiv);

      /* Wait until the PLL is within the desired tolerance of the target frequency */
      while(Mcu_GetCpmuIFlgLockIf() == 0U) {
         ;
      }

      /* configure watchdog clock */
      Mcu_SetCpmuClkSCopOscSel1(mcu_initialConfiguration_s.mcu_CpmuClkSCopOscSel1);

      /* enable protection of clock configuration registers */
      //Mcu_SetCpmuProtProt(MCU_PROT_ENABLE);

      /* ---------- CAUTION  ---------- */
      /* Voltage Regulator Control Register (CPMUVREGCTL) is not written due the customer request */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
      /* Module is initialized */
      mcu_moduleStatus_e = MODULE_INITIALIZED;
#endif
   }
}


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
)
{
   /* -- variables declaration ---------------- */
   Std_ReturnType mcu_deInitFunctionStatus_e;

   /* -- init function internal variables ----- */
   mcu_deInitFunctionStatus_e = MCU_E_NOT_OK;

   /* -- source code -------------------------- */
   #if(MCU_DEV_ERROR_DETECTION == STD_ON)
      if(mcu_moduleStatus_e != MODULE_INITIALIZED)
      {
         /* Send error to DET */
         Det_ReportError((uint16)MCU_MODULE_ID, (uint8)MCU_INSTANCE_ID, (uint8)MCU_DEINIT_API_ID, (uint8)MCU_E_NOT_INITIALIZED);
      }
      else
   #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
      {
         /* Module is de-initialized */
         mcu_moduleStatus_e = MCU_DEINITIALIZED;

         /* If something went wrong you have to return MCU_E_NOT_OK */
         mcu_deInitFunctionStatus_e = MCU_E_OK;
      }

      return mcu_deInitFunctionStatus_e;
}
#endif /* #if (MCU_DEINIT_API == STD_ON) */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/*
* \brief This service returns the status of this module (DO NOT CHANGE).
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: MCU_UNINIT, MCU_DEINITIALIZED, MODULE_INITIALIZED
*/
Std_ModuleStatusReturnType Mcu_GetModuleStatus
(
   void
)
{
   /* -- source code -------------------------- */
   return(mcu_moduleStatus_e);
}
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */



#if(MCU_VERSION_INFO_API == STD_ON)
   /*
   * \brief This service returns the version information of this module. (DO NOT CHANGE)
   *
   * \param [in]  ---
   * \param [out] versioninfo = Pointer to where to store the version
   *                            information of this module .
   * \return      ---
   */
   void Mcu_GetVersionInfo
   (
      Std_VersionInfoType *versioninfo
   )
   {
      /* -- source code -------------------------- */
      versioninfo->moduleID = (uint16)MCU_MODULE_ID;
      versioninfo->instanceID = (uint8)MCU_INSTANCE_ID;
      versioninfo->sw_major_version = (uint8)MCU_SW_MAJOR_VERSION;
      versioninfo->sw_minor_version = (uint8)MCU_SW_MINOR_VERSION;
      versioninfo->sw_patch_version = (uint8)MCU_SW_PATCH_VERSION;
   }
#endif /* MCU_VERSION_INFO_API == STD_ON */

void Mcu_SetStopMode (void)
{
#if ! ((defined DEBUG_MCU_STOP_MODE_DISABLE) && (DEBUG_MCU_STOP_MODE_DISABLE == 1))
   __asm(ANDCC #0x7F);
   __asm(STOP);

   /* Wait until the PLL is within the desired tolerance of the target frequency */
   while(Mcu_GetCpmuIFlgLockIf() == 0U) {
      ;
   }
#endif

   return;
}


void Mcu_SetWaitMode (void)
{
   __asm(WAI);

   return;
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED
void Mcu_PerformReset (void)
{
	*(uint8 *)WDG_CPMUARMCOP_ADR_UI16 = 0x01U;
	*(uint8 *)WDG_CPMUARMCOP_ADR_UI16 = 0x10U;
}

#pragma CODE_SEG DEFAULT


