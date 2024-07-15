/* ###################################################################
**     Filename    : API.c
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
** @file API.c
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

/* MODULE API. */

#include "API.h"

/*
** ###################################################################
**
**  The interrupt service routine(s) must be implemented
**  by user in one of the following user modules.
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
**         this method in the user code to initialize the module.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void API_Init(void)
{
  /* CPMUAPICTL: APICLK=0,??=0,??=0,APIES=0,APIEA=0,APIFE=0,APIE=0,APIF=0 */
  setReg8(CPMUAPICTL, 0x00U);           
  /* CPMUAPIR: APIR15=0,APIR14=0,APIR13=0,APIR12=0,APIR11=0,APIR10=1,APIR9=1,APIR8=0,APIR7=0,APIR6=1,APIR5=0,APIR4=0,APIR3=0,APIR2=0,APIR1=0,APIR0=0 */
  setReg16(CPMUAPIR, 0x0640U);          
  /* CPMUACLKTR: ACLKTR5=0,ACLKTR4=0,ACLKTR3=0,ACLKTR2=0,ACLKTR1=0,ACLKTR0=0,??=0,??=0 */
  setReg8(CPMUACLKTR, 0x00U);           
  /* CPMUAPICTL: APICLK=1,APIE=1,APIF=1 */
  setReg8Bits(CPMUAPICTL, 0x83U);       
  /* CPMUAPICTL: APIFE=1 */
  setReg8Bits(CPMUAPICTL, 0x04U);       
}

/* END API. */
/*!
** @}
*/
