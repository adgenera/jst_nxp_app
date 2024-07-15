/* ###################################################################
**     Filename    : InpB1.c
**     Project     : iic bl test
**     Processor   : MC9S12ZVHL32CLL
**     Component   : InputPin
**     Version     : Component 01.006, Driver 03.00, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-03-26, 15:26
**     Abstract    :
**         This component implements a one-bit input. Use of the component 
**         is convenient if selected pin is used by some on-chip 
**         peripheral device (asychronous serial channel, 
**         synchronous serial channel,...) and there is some reason 
**         to read state on this pin. This is why component neither 
**         allocates nor inicializes this pin. This component can be used 
**         for autodiagnostics, where on-chip peripheral device is 
**         verified on functionality, for example sending and 
**         receiving of data by asychronous serial channel or 
**         synchronous serial channel or generating periodic signal 
**         by Timer.
**     Settings    :
**          Component name                                 : InpB1
**          Pin for Input                                  : PF4_FP20
**          Pin signal                                     : 
**     Contents    :
**         GetVal - bool InpB1_GetVal(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file InpB1.c
** @version 03.00
** @brief
**         This component implements a one-bit input. Use of the component 
**         is convenient if selected pin is used by some on-chip 
**         peripheral device (asychronous serial channel, 
**         synchronous serial channel,...) and there is some reason 
**         to read state on this pin. This is why component neither 
**         allocates nor initializes this pin. This component can be used 
**         for autodiagnostics, where on-chip peripheral device is 
**         verified on functionality, for example sending and 
**         receiving of data by asychronous serial channel or 
**         synchronous serial channel or generating periodic signal 
**         by Timer.
*/         
/*!
**  @addtogroup InpB1_module InpB1 module documentation
**  @{
*/         

/* MODULE InpB1. */

#include "InpB1.h"
  /* Including shared modules, which are used in the whole project */

#pragma DATA_SEG InpB1_DATA            /* Select data segment "InpB1_DATA" */
#pragma CODE_SEG InpB1_CODE
#pragma CONST_SEG InpB1_CONST          /* Constant section for this module */
/*
** ===================================================================
**     Method      :  InpB1_GetVal (component InputPin)
**     Description :
**         Return the value on the pin.
**     Parameters  : None
**     Returns     :
**         ---             - Input value
** ===================================================================
*/
/*
bool InpB1_GetVal(void)

**  This method is implemented as a macro. See InpB1.h file.  **
*/


/* END InpB1. */
/*!
** @}
*/
