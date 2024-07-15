#ifndef DIO_CFG_H
#define DIO_CFG_H
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
#define DIO_DEV_ERROR_DETECTION                PROJECT_SETTINGS_GLOBAL_DET_SWITCH

/*
* Description: Switches function Dio_GetVersionInfo() on/off.
* Range:       STD_ON:      enable function Dio_GetVersionInfo()
*              STD_OFF:     disable function Dio_GetVersionInfo()
* Example:
*/
#define DIO_VERSION_INFO_API                   PROJECT_SETTINGS_GLOBAL_VERSION_API

#define DIO_DEINIT_API                         PROJECT_SETTINGS_GLOBAL_DEINIT_API


/* Use ROM optimized initialization */
#define DIO_ROM_OPTIMIZATION                   STD_ON


/** Description: address of Data Register A */
#define DIO_PTA_ADR_UI16 (uint16)0x0220
/** Description: address of Data Register B */
#define DIO_PTB_ADR_UI16 (uint16)0x0221
/** Description: address of Data Register C */
#define DIO_DDRC_ADR_UI16 (uint16)0x0240
/** Description: address of Data Register D */
#define DIO_DDRD_ADR_UI16 (uint16)0x0241
/** Description: address of Data Register E */
#define DIO_DDRE_ADR_UI16 (uint16)0x0260
/** Description: address of Data Register F */
#define DIO_DDRF_ADR_UI16 (uint16)0x0261
/** Description: address of Data Register ADL */
#define DIO_DDRADL_ADR_UI16 (uint16)0x0281
/** Description: address of Data Register T */
#define DIO_DDRT_ADR_UI16 (uint16)0x02C0
/** Description: address of Data Register S */
#define DIO_DDRS_ADR_UI16 (uint16)0x02D0
/** Description: address of Data Register P */
#define DIO_DDRP_ADR_UI16 (uint16)0x02F0
/** Description: address of Data Register H */
#define DIO_DDRH_ADR_UI16 (uint16)0x0300
/** Description: address of Data Register J */
#define DIO_DDRJ_ADR_UI16 (uint16)0x0310
/** Description: address of Data Register G */
#define DIO_DDRG_ADR_UI16 (uint16)0x0320
/** Description: address of Data Register U */
#define DIO_DDRU_ADR_UI16 (uint16)0x0350

#endif /* DIO_CFG_H */

