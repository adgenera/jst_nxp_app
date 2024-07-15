#ifndef WDG_H
#define WDG_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include "Wdg_Cfg.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define WDG_INSTANCE_ID           (0)  /* Instance id */
#define WDG_SW_MAJOR_VERSION      (1)  /* Software major version */
#define WDG_SW_MINOR_VERSION      (0)  /* Software minor version */
#define WDG_SW_PATCH_VERSION      (0)  /* Software patch version */


#if (WDG_DEV_ERROR_DETECTION == STD_ON)
/* DET Module API ID's */
#define WDG_INIT_API_ID           (0x01)       /* API ID of Wdg_Init() */
#define WDG_DEINIT_API_ID         (0x02)       /* API ID of Wdg_DeInit() */

/* DET Module error ID's */
#define WDG_E_PARAM_CONFIG        (0x10)       /* Error ID: config not found */
#define WDG_E_ALREADY_INITIALIZED (0x11)       /* Error ID: multiple call of Wdg_Init() */
#define WDG_E_NOT_INITIALIZED     (0x12)       /* Error ID: multiple call of Wdg_DeInit() */
#endif /* WDG_DEV_ERROR_DETECTION == STD_ON */

/* Bit positions in S12CPMU_UHV_V5 Clock Select Register */
#define WDG_CPMUCLKS_CSAD_POS (uint8)5U
/* Bit positions in S12CPMU_UHV_V5 COP Control Register */
#define WDG_CPMUCOP_WCOP_POS (uint8)7U
/* Bit positions in S12CPMU_UHV_V5 COP Control Register */
#define WDG_CPMUCOP_RSBCK_POS (uint8)6U
/* Bit positions in S12CPMU_UHV_V5 COP Control Register */
#define WDG_CPMUCOP_WRTMASK_POS (uint8)5U
/* Bit positions in S12CPMU_UHV_V5 COP Control Register */
#define WDG_CPMUCOP_CR_POS (uint8)0U
/* Bit positions in S12CPMU_UHV_V5 COP Timer Arm/Reset Register */
#define WDG_CPMUARMCOP_ARMCOP_POS (uint8)0U

/* Default values of WCOP in CPMUCOP */
#define WDG_CPMUCOP_WCOP_DEFAULT WDG_NORMAL_COP
/* Default values of RSBCK in CPMUCOP */
#define WDG_CPMUCOP_RSBCK_DEFAULT WDG_COP_RTI_RUN_IN_BDM
/* Default values of WRTMASK in CPMUCOP */
#define WDG_CPMUCOP_WRTMASK_DEFAULT WDG_MASK_WCOP_CR
/* Default values of CR in CPMUCOP */
#define WDG_CPMUCOP_CR_DEFAULT 0
/* Default values of ARMCOP in CPMUARMCOP */
#define WDG_CPMUARMCOP_ARMCOP_DEFAULT 0


/* Macro to set WCOP of S12CPMU_UHV_V5 COP Control Register */
#define Wdg_SetCpmuCopWCop(value) ( \
   *((uint8*)WDG_CPMUCOP_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << WDG_CPMUCOP_WCOP_POS ) | \
      ( (*((uint8*)WDG_CPMUCOP_ADR_UI16)) & (uint8)(~((uint8)0x1 << WDG_CPMUCOP_WCOP_POS) ) ) ) )
/* Macro to set RSBCK of S12CPMU_UHV_V5 COP Control Register */
#define Wdg_SetCpmuCopRsbck(value) ( \
   *((uint8*)WDG_CPMUCOP_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << WDG_CPMUCOP_RSBCK_POS ) | \
      ( (*((uint8*)WDG_CPMUCOP_ADR_UI16)) & (uint8)(~((uint8)0x1 << WDG_CPMUCOP_RSBCK_POS) ) ) ) )
/* Macro to set WRTMASK of S12CPMU_UHV_V5 COP Control Register */
#define Wdg_SetCpmuCopWrtMask(value) ( \
   *((uint8*)WDG_CPMUCOP_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x1 ) << WDG_CPMUCOP_WRTMASK_POS ) | \
      ( (*((uint8*)WDG_CPMUCOP_ADR_UI16)) & (uint8)(~((uint8)0x1 << WDG_CPMUCOP_WRTMASK_POS) ) ) ) )
/* Macro to set CR of S12CPMU_UHV_V5 COP Control Register */
#define Wdg_SetCpmuCopCr(value) ( \
   *((uint8*)WDG_CPMUCOP_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0x7 ) ) | \
      ( (*((uint8*)WDG_CPMUCOP_ADR_UI16)) & (uint8)(~((uint8)0x7) ) ) ) )
/* Macro to set ARMCOP of S12CPMU_UHV_V5 COP Timer Arm/Reset Register */
#define Wdg_SetCpmuArmCopArmCop(value) ( \
   *((uint8*)WDG_CPMUARMCOP_ADR_UI16) = \
      ( (uint8)( ( ((uint8)value) & (uint8)0xff ) ) | \
      ( (*((uint8*)WDG_CPMUARMCOP_ADR_UI16)) & (uint8)(~((uint8)0xff) ) ) ) )



/* Macro to get WCOP of S12CPMU_UHV_V5 COP Control Register */
#define Wdg_GetCpmuCopWCop() ( \
      ( (*((uint8*)WDG_CPMUCOP_ADR_UI16)) >> WDG_CPMUCOP_WCOP_POS) & (uint8)0x1)
/* Macro to get RSBCK of S12CPMU_UHV_V5 COP Control Register */
#define Wdg_GetCpmuCopRsbck() ( \
      ( (*((uint8*)WDG_CPMUCOP_ADR_UI16)) >> WDG_CPMUCOP_RSBCK_POS) & (uint8)0x1)
/* Macro to get CR of S12CPMU_UHV_V5 COP Control Register */
#define Wdg_GetCpmuCopCr() ( \
      ( (*((uint8*)WDG_CPMUCOP_ADR_UI16))) & (uint8)0x7)

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config typedefs ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
* \brief Configuration options of wdg bits in S12CPMU_UHV_V5 COP Control Register
*/
typedef enum
{
   WDG_NORMAL_COP = (uint8)0, /* Normal COP operation */
   WDG_WINDOW_COP = (uint8)1  /* Window COP operation */
} Wdg_CpmuCopWCopType;

/*
* \brief Configuration options of wdg bits in S12CPMU_UHV_V5 COP Control Register
*/
typedef enum
{
   WDG_COP_RTI_RUN_IN_BDM  = (uint8)0, /* Allows the COP and RTI to keep running in Active BDM mode */
   WDG_COP_RTI_STOP_IN_BDM = (uint8)1  /* Stops the COP and RTI counters whenever the part is in Active BDM mode */
} Wdg_CpmuCopRsbckType;

/*
* \brief Configuration options of wdg bits in S12CPMU_UHV_V5 COP Control Register
*/
typedef enum
{
   WDG_MASK_WCOP_CR   = (uint8)0, /* Write of WCOP and CR[2:0] has an effect with this write of CPMUCOP */
   WDG_UNMASK_WCOP_CR = (uint8)1  /* Write of WCOP and CR[2:0] has no effect with this write of CPMUCOP */
} Wdg_CpmuCopWrtMaskType;


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config struct ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* \brief Function to initialize the WDG module.
*
* Initializes the WDG module.
*
* \param [in]  ---
* \param [out] ---
*/
void Wdg_Init
(
   uint8 DeviceType
);


#if (WDG_DEINIT_API == STD_ON)
/*
* \brief Function to deinitialize the WDG module.
*
* Deinitializes the WDG module.
*
* \param [in]  ---
* \param [out] ---
* \return      WDG_E_OK: Deinitialization done
*              WDG_E_NOT_OK: Something went wrong during deinitialization
*/
Std_ReturnType Wdg_DeInit
(
   void
);
#endif /* #if (WDG_DEINIT_API == STD_ON) */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/*
* \brief This service returns the status of this module .
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: WDG_UNINIT, WDG_DEINITIALIZED, WDG_INITIALIZED
*/
Std_ModuleStatusReturnType Wdg_GetModuleStatus
(
   void
);
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */


#if (WDG_VERSION_INFO_API == STD_ON)
/*
* \brief This service returns the version information of this module .
*
* \param [in]  ---
* \param [out] versioninfo = Pointer to where to store the version
*                            information of this module .
* \return      ---
*/
void Wdg_GetVersionInfo
(
   Std_VersionInfoType *versioninfo
);
#endif /* WDG_VERSION_INFO_API == STD_ON */



void Wdg_Trigger
(
   void
);


uint8 Wdg_Clear
(
   void
);


#endif /* WDG_H */

