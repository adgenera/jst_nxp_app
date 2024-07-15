#include "API.h"
#include "Mcu.h"

/*
** ###################################################################
**
**  The interrupt service routine(s) must be implemented
**  by user in one of the following user modules.
**
**  If the "Generate ISR" option is enabled, Processor Expert generates
**  ISR templates in the CPU event module.
**
**  User modules:
**      main.c
**      Events.c
**
** ###################################################################
ISR(API_interrupt)
{
  // NOTE: The routine should include the following actions to obtain
  //       correct functionality of the hardware.
  //
  //       API interrupt request flag (APIF bit) must be set to 1 to
  //       clear the interrupt request.
  //       HCS12,HCS12Z Example: CPMUAPICTL_APIF = 1;
  //       HCS12X Example: VREGAPICL_APIF = 1;
}
*/
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
void API_Init(void)
{
	/* CPMUAPICTL: APICLK=0,??=0,??=0,APIES=0,APIEA=0,APIFE=0,APIE=0,APIF=0 */
	*((uint8*)MCU_CPMUAPICTL_ADR_UI16) = 0x00U;
	/* CPMUAPIR: APIR15=0,APIR14=0,APIR13=0,APIR12=0,APIR11=0,APIR10=0,APIR9=0,APIR8=0,APIR7=0,APIR6=0,APIR5=0,APIR4=0,APIR3=0,APIR2=1,APIR1=0,APIR0=0 */
    /* Initialise APIR in Autonomous Periodical Interrupt Rate Register */
	*((uint16*)MCU_CPMUAPIR_ADR_UI16) = 0x0004U;	
	
    /* CPMUACLKTR: ACLKTR5=0,ACLKTR4=0,ACLKTR3=0,ACLKTR2=0,ACLKTR1=0,ACLKTR0=0,??=0,??=0 */
    /* Initialise aClkTr in Autonomous Clock Trimming Register */
	*((uint8*)MCU_CPMUACLKTR_ADR_UI16) = 0x00U;
	
    /* CPMUAPICTL: APIFE=1,APIE=1,APIF=1 */
	*((uint8*)MCU_CPMUAPICTL_ADR_UI16) |= 0b00000011U;
	/* CPMUAPICTL: APIFE=1 to enable timer and interrupt */
	*((uint8*)MCU_CPMUAPICTL_ADR_UI16) |= 0b00000100U;
}

/* END API. */

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
