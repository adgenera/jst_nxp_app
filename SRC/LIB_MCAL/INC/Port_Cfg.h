#ifndef PORT_CFG_H
#define PORT_CFG_H
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
#define PORT_DEV_ERROR_DETECTION                PROJECT_SETTINGS_GLOBAL_DET_SWITCH

/*
* Description: Switches function Port_GetVersionInfo() on/off.
* Range:       STD_ON:      enable function Port_GetVersionInfo()
*              STD_OFF:     disable function Port_GetVersionInfo()
* Example:
*/
#define PORT_VERSION_INFO_API                   PROJECT_SETTINGS_GLOBAL_VERSION_API


#define PORT_DEINIT_API                         PROJECT_SETTINGS_GLOBAL_DEINIT_API

/* Use ROM optimized initialization */
#define PORT_ROM_OPTIMIZATION                   STD_ON


/** Description: address of Module Routing Register 0 */
#define PORT_MODRR0_ADR_UI16 (uint16)0x0200
/** Description: address of Module Routing Register 1 */
#define PORT_MODRR1_ADR_UI16 (uint16)0x0201
/** Description: address of Module Routing Register 2 */
#define PORT_MODRR2_ADR_UI16 (uint16)0x0202
/** Description: address of Module Routing Register 3 */
#define PORT_MODRR3_ADR_UI16 (uint16)0x0203
/** Description: address of ECLK Control Register */
#define PORT_ECLKCTL_ADR_UI16 (uint16)0x0208
/** Description: address of IRQ Control Register */
#define PORT_IRQCR_ADR_UI16 (uint16)0x0209
/** Description: address of PIM Miscellaneous Register */
#define PORT_PIMMISC_ADR_UI16 (uint16)0x020A
/** Description: address of Port A Input Register */
#define PORT_PTIA_ADR_UI16 (uint16)0x0222
/** Description: address of Port B Input Register */
#define PORT_PTIB_ADR_UI16 (uint16)0x0223
/** Description: address of Port C Input Register */
#define PORT_PTIC_ADR_UI16 (uint16)0x0242
/** Description: address of Port D Input Register */
#define PORT_PTID_ADR_UI16 (uint16)0x0243
/** Description: address of Port E Input Register */
#define PORT_PTIE_ADR_UI16 (uint16)0x0262
/** Description: address of Port F Input Register */
#define PORT_PTIF_ADR_UI16 (uint16)0x0263
/** Description: address of Port ADL Input Register */
#define PORT_PTIADL_ADR_UI16 (uint16)0x0283
/** Description: address of Port T Input Register */
#define PORT_PTIT_ADR_UI16 (uint16)0x02C1
/** Description: address of Port S Input Register */
#define PORT_PTIS_ADR_UI16 (uint16)0x02D1
/** Description: address of Port P Input Register */
#define PORT_PTIP_ADR_UI16 (uint16)0x02F1
/** Description: address of Port H Input Register */
#define PORT_PTIH_ADR_UI16 (uint16)0x0301
/** Description: address of Port J Input Register */
#define PORT_PTIJ_ADR_UI16 (uint16)0x0311
/** Description: address of Port G Input Register */
#define PORT_PTIG_ADR_UI16 (uint16)0x0321
/** Description: address of Port U Input Register */
#define PORT_PTIU_ADR_UI16 (uint16)0x0351
/** Description: address of Data Direction Register A */
#define PORT_DDRA_ADR_UI16 (uint16)0x0224
/** Description: address of Data Direction Register B */
#define PORT_DDRB_ADR_UI16 (uint16)0x0225
/** Description: address of Data Direction Register C */
#define PORT_DDRC_ADR_UI16 (uint16)0x0244
/** Description: address of Data Direction Register D */
#define PORT_DDRD_ADR_UI16 (uint16)0x0245
/** Description: address of Data Direction Register E */
#define PORT_DDRE_ADR_UI16 (uint16)0x0264
/** Description: address of Data Direction Register F */
#define PORT_DDRF_ADR_UI16 (uint16)0x0265
/** Description: address of Data Direction Register ADL */
#define PORT_DDRADL_ADR_UI16 (uint16)0x0285
/** Description: address of Data Direction Register T */
#define PORT_DDRT_ADR_UI16 (uint16)0x02C2
/** Description: address of Data Direction Register S */
#define PORT_DDRS_ADR_UI16 (uint16)0x02D2
/** Description: address of Data Direction Register P */
#define PORT_DDRP_ADR_UI16 (uint16)0x02F2
/** Description: address of Data Direction Register H */
#define PORT_DDRH_ADR_UI16 (uint16)0x0302
/** Description: address of Data Direction Register J */
#define PORT_DDRJ_ADR_UI16 (uint16)0x0312
/** Description: address of Data Direction Register G */
#define PORT_DDRG_ADR_UI16 (uint16)0x0322
/** Description: address of Data Direction Register U */
#define PORT_DDRU_ADR_UI16 (uint16)0x0352
/** Description: address of Digital Input Enable Register ADL */
#define PORT_DIENADL_ADR_UI16 (uint16)0x0299
/** Description: address of Pull Device Enable Register A */
#define PORT_PERA_ADR_UI16 (uint16)0x0226
/** Description: address of Pull Device Enable Register B */
#define PORT_PERB_ADR_UI16 (uint16)0x0227
/** Description: address of Pull Device Enable Register C */
#define PORT_PERC_ADR_UI16 (uint16)0x0246
/** Description: address of Pull Device Enable Register D */
#define PORT_PERD_ADR_UI16 (uint16)0x0247
/** Description: address of Pull Device Enable Register E */
#define PORT_PERE_ADR_UI16 (uint16)0x0266
/** Description: address of Pull Device Enable Register F */
#define PORT_PERF_ADR_UI16 (uint16)0x0267
/** Description: address of Pull Device Enable Register ADL */
#define PORT_PERADL_ADR_UI16 (uint16)0x0287
/** Description: address of Pull Device Enable Register T */
#define PORT_PERT_ADR_UI16 (uint16)0x02C3
/** Description: address of Pull Device Enable Register S */
#define PORT_PERS_ADR_UI16 (uint16)0x02D3
/** Description: address of Pull Device Enable Register P */
#define PORT_PERP_ADR_UI16 (uint16)0x02F3
/** Description: address of Pull Device Enable Register H */
#define PORT_PERH_ADR_UI16 (uint16)0x0303
/** Description: address of Pull Device Enable Register J */
#define PORT_PERJ_ADR_UI16 (uint16)0x0313
/** Description: address of Pull Device Enable Register G */
#define PORT_PERG_ADR_UI16 (uint16)0x0323
/** Description: address of Pull Device Enable Register U */
#define PORT_PERU_ADR_UI16 (uint16)0x0353
/** Description: address of Port Polarity Select Register A */
#define PORT_PPSA_ADR_UI16 (uint16)0x0228
/** Description: address of Port Polarity Select Register B */
#define PORT_PPSB_ADR_UI16 (uint16)0x0229
/** Description: address of Port Polarity Select Register C */
#define PORT_PPSC_ADR_UI16 (uint16)0x0248
/** Description: address of Port Polarity Select Register D */
#define PORT_PPSD_ADR_UI16 (uint16)0x0249
/** Description: address of Port Polarity Select Register E */
#define PORT_PPSE_ADR_UI16 (uint16)0x0268
/** Description: address of Port Polarity Select Register F */
#define PORT_PPSF_ADR_UI16 (uint16)0x0269
/** Description: address of Port Polarity Select Register ADL */
#define PORT_PPSADL_ADR_UI16 (uint16)0x0289
/** Description: address of Port Polarity Select Register T */
#define PORT_PPST_ADR_UI16 (uint16)0x02C4
/** Description: address of Port Polarity Select Register S */
#define PORT_PPSS_ADR_UI16 (uint16)0x02D4
/** Description: address of Port Polarity Select Register P */
#define PORT_PPSP_ADR_UI16 (uint16)0x02F4
/** Description: address of Port Polarity Select Register H */
#define PORT_PPSH_ADR_UI16 (uint16)0x0304
/** Description: address of Port Polarity Select Register J */
#define PORT_PPSJ_ADR_UI16 (uint16)0x0314
/** Description: address of Port Polarity Select Register G */
#define PORT_PPSG_ADR_UI16 (uint16)0x0324
/** Description: address of Port Polarity Select Register U */
#define PORT_PPSU_ADR_UI16 (uint16)0x0354
/** Description: address of Wired-Or Mode Register A */
#define PORT_WOMA_ADR_UI16 (uint16)0x023E
/** Description: address of Wired-Or Mode Register S */
#define PORT_WOMS_ADR_UI16 (uint16)0x02DF
/** Description: address of Port Interrupt Enable Register T */
#define PORT_PIET_ADR_UI16 (uint16)0x02C6
/** Description: address of Port Interrupt Enable Register S */
#define PORT_PIES_ADR_UI16 (uint16)0x02D6
/** Description: address of Port Interrupt Enable Register ADL */
#define PORT_PIEADL_ADR_UI16 (uint16)0x028D
/** Description: address of Port Interrupt Flag Register T */
#define PORT_PIFT_ADR_UI16 (uint16)0x02C7
/** Description: address of Port Interrupt Flag Register S */
#define PORT_PIFS_ADR_UI16 (uint16)0x02D7
/** Description: address of Port Interrupt Flag Register ADL */
#define PORT_PIFADL_ADR_UI16 (uint16)0x028F
/** Description: address of Port Slew Rate Register U */
#define PORT_SRRU_ADR_UI16 (uint16)0x035E

#endif /* PORT_CFG_H */

