#ifndef WDG_CFG_H
#define WDG_CFG_H
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
#define WDG_DEV_ERROR_DETECTION                PROJECT_SETTINGS_GLOBAL_DET_SWITCH

/*
* Description: Switches function Wdg_GetVersionInfo() on/off.
* Range:       STD_ON:      enable function Wdg_GetVersionInfo()
*              STD_OFF:     disable function Wdg_GetVersionInfo()
* Example:
*/
#define WDG_VERSION_INFO_API                   PROJECT_SETTINGS_GLOBAL_VERSION_API


#define WDG_DEINIT_API                         PROJECT_SETTINGS_GLOBAL_DEINIT_API

/** Description: address of S12CPMU_UHV_V5 Clock Select Register */
#define WDG_CPMUCLKS_ADR_UI16 (uint16)0x06C9
/** Description: address of S12CPMU_UHV_V5 COP Control Register */
#define WDG_CPMUCOP_ADR_UI16 (uint16)0x06CC
/** Description: address of S12CPMU_UHV_V5 COP Timer Arm/Reset Register */
#define WDG_CPMUARMCOP_ADR_UI16 (uint16)0x06CF


#endif /* WDG_CFG_H */

