/* ###################################################################
**     Filename    : API.h
**     Project     : jst_bl
**     Processor   : MC9S12ZVHL32CLL
**     Component   : Init_API
**     Version     : Component 01.103, Driver 01.08, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-04-22, 14:14
**     Abstract    :
**          This file implements the API (API) module 
**          initialization according to the Peripheral Initialization 
**          Component settings, and defines interrupt service routines prototypes.
**          The Autonomous periodical Interrupt module can generate
**          periodical interrupts independent of the clock source of 
**          the MCU. To enable the timer, the bit APIFE needs to be 
**          set. The API timer is either clocked by a trimmable 
**          internal RC oscillator or the bus clock. Timer operation
**          will freeze when MCU clock source is selected and bus clock 
**          is turned off. The clock source can be selected with bit
**          APICLK. As soon as the configured timeout period of the API 
**          has elapsed, the APIF bit is set. An interrupt, indicated by 
**          flag APIF = 1, is triggered if interrupt enable bit APIE = 1.
**     Settings    :
**          Component name                                 : API
**          Device                                         : API
**          Settings                                       : 
**            Clock settings                               : 
**              Clock select                               : Bus clock
**              Period rate                                : 1600
**              Prescaler                                  : 3202
**              Period                                     : 100.062 us
**            Trim settings                                : 
**              Period increase                            : no
**              Period decrease value                      : 0
**          Pins                                           : 
**            External Access                              : Disabled
**          Interrupts                                     : 
**            Interrupt                                    : Vapi
**            API Interrupt                                : Enabled
**            Priority                                     : 1
**            ISR name                                     : API_interrupt
**          Initialization                                 : 
**            Call Init method                             : yes
**            Enable module                                : yes
**     Contents    :
**         Init - void API_Init(void);
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
** @file API.h
** @version 01.08
** @brief
**          This file implements the API (API) module 
**          initialization according to the Peripheral Initialization 
**          Component settings, and defines interrupt service routines prototypes.
**          The Autonomous periodical Interrupt module can generate
**          periodical interrupts independent of the clock source of 
**          the MCU. To enable the timer, the bit APIFE needs to be 
**          set. The API timer is either clocked by a trimmable 
**          internal RC oscillator or the bus clock. Timer operation
**          will freeze when MCU clock source is selected and bus clock 
**          is turned off. The clock source can be selected with bit
**          APICLK. As soon as the configured timeout period of the API 
**          has elapsed, the APIF bit is set. An interrupt, indicated by 
**          flag APIF = 1, is triggered if interrupt enable bit APIE = 1.
*/         
/*!
**  @addtogroup API_module API module documentation
**  @{
*/         

#ifndef __API
#define __API

/* MODULE API. */

/* Include shared modules, which are used for whole project */
#include "Error.h"
#include "Const.h"
#include "MC9S12ZVHL32.h"
/* Include inherited components */
#include "Cpu.h"

void API_Init(void);
/*
** ===================================================================
**     Method      :  API_Init (component Init_API)
**     Description :
**         This method initializes registers of the API module
**         according to this Peripheral Initialization settings. Call
**         this method in the user code to initialize the module. 
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
/* END API. */

#endif
/*!
** @}
*/
