/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "MC.h"

#pragma CODE_SEG DEFAULT


void Cpu_OnIllegalOpcode(void);
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

/* END Events */
#endif /* __Events_H*/

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
