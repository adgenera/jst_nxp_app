#ifndef ISR_VECTOR_TABLE_H
#define ISR_VECTOR_TABLE_H

#include "Version.h"
#include "Gpt_Cfg.h"

/* ***************************** includes < > ******************************* */


/* ***************************** includes " " ******************************* */

/* ***************************** typedefs *********************************** */


/* ***************************** # defines ********************************** */
#define ISR_VECTAB_VENDOR_ID        99 /**<\brief CoSyst VendorID */
#define ISR_VECTAB_AR_MAJOR_VERSION 3  /**<\brief AUTOSAR major version */
#define ISR_VECTAB_AR_MINOR_VERSION 1  /**<\brief AUTOSAR minor version */
#define ISR_VECTAB_AR_PATCH_VERSION 0  /**<\brief AUTOSAR patch version */
#define ISR_VECTAB_SW_MAJOR_VERSION 1  /**<\brief Software major version */
#define ISR_VECTAB_SW_MINOR_VERSION 1  /**<\brief Software minor version */
#define ISR_VECTAB_SW_PATCH_VERSION 1  /**<\brief Software patch version */

/** \b Description: Total number of hardware timers used for counters and alarms
<br>\b Range: 0 - 4
<br> \b Example:*/
#define Isr_NUMBER_OF_HW_TIMER          4


#define ROUTE_INTERRUPT(vec_adr, cfdata) INT_CFADDR= (vec_adr) & 0xF0; INT_CFDATA_ARR[((vec_adr) & 0x0F) >> 1]= (cfdata)
/* ***************************** enums ************************************** */
/* ***************************** structs ************************************ */
/* ***************************** global data ******************************** */
/* ***************************** modul global prototypes ******************** */
/* ***************************** global prototypes ************************** */
/**
*  \brief Link to system startup routine..
*
*  \param [in]  ---
*  \param [out] ---
*  \return      ---
*/

/**
*  \brief Interrupt service routine for unimplemented Vectors.
*
*  \param [in]  ---
*  \param [out] ---
*  \return      ---
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ErrH_UnimplementedIsr(void);
#pragma CODE_SEG DEFAULT

/**
*  \brief Functions sets the interrupt priority
*
*  \param [in]  ---
*  \param [out] ---
*  \return      ---
*/
extern void ISR_Set_PriorityLevel
(
   void
);


#pragma CODE_SEG DEFAULT

#endif /* ISR_VECTOR_TABLE_H */

