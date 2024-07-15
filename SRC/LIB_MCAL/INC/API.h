#ifndef __API
#define __API

/* MODULE API. */

void API_Init(void);
/*
** ===================================================================
**     Method      :  API_Init (component Init_API)
**     Description :
**         This method initializes registers of the API module
**         according to this Peripheral Initialization settings. Call
**         this method in the user code to initialize the module. By
**         default, the method is called by PE automatically; see "Call
**         Init method" property of the component for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
** The interrupt service routine must be implemented by user in one
** of the user modules (see API.c file for more information).
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void API_interrupt(void);
#pragma CODE_SEG DEFAULT

#endif
/* ifndef __API */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS12Z series of microcontrollers.
**
** ###################################################################
*/
