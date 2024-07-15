/* ###################################################################
**     Filename    : Events.c
**     Project     : motor_test
**     Processor   : MC9S12ZVHL32CLL
**     Component   : Events
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-07-15, 13:01, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#pragma CODE_SEG DEFAULT

/*
** ===================================================================
**     Event       :  Cpu_OnIllegalOpcode (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is called after unimplemented instruction
**         execution.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Cpu_OnIllegalOpcode(void)
{
  /* Write your code here ... */
}

/* END Events */

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
