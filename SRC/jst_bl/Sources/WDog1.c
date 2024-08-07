/* ###################################################################
**     Filename    : WDog1.c
**     Project     : jst_bl
**     Processor   : MC9S12ZVHL32CLL
**     Component   : WatchDog
**     Version     : Component 02.142, Driver 01.16, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-04-24, 23:31,
**     Abstract    :
**         This device "WatchDog" implements a watchdog.
**         When enabled, the watchdog timer counts until it reaches
**         a critical value corresponding to the period specified
**         in 'Properties'. Then, the watchdog causes a CPU reset.
**         Applications may clear the timer before it reaches the critical
**         value. The timer then restarts the watchdog counter.
**         Watchdog is used for increasing the safety of the system
**         (unforeseeable situations can cause system crash or an
**         infinite loop - watchdog can restart the system or handle
**         the situation).
**
**         Note: Watchdog can be enabled or disabled in the initialization
**               code only. If the watchdog is once enabled user have
**               to call Clear method in defined time intervals.
**     Settings    :
**         Watchdog causes             : Reset CPU
**
**         Clock Source                : Bus clock
**
**         Initial Watchdog state      : Enabled
**
**         Mode of operation           : Normal
**
**         High speed mode
**           Watchdog period/frequency
**             microseconds            : 12800
**             milliseconds            : 13
**             Hz                      : 78
**
**         Run register                : CPMUCOP   [0x06CC]
**         Mode register               : CPMUCOP   [0x06CC]
**         Prescaler register          : CPMUCOP   [0x06CC]
**     Contents    :
**         Clear - byte WDog1_Clear(void);
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
** @file WDog1.c
** @version 01.16
** @brief
**         This device "WatchDog" implements a watchdog.
**         When enabled, the watchdog timer counts until it reaches
**         a critical value corresponding to the period specified
**         in 'Properties'. Then, the watchdog causes a CPU reset.
**         Applications may clear the timer before it reaches the critical
**         value. The timer then restarts the watchdog counter.
**         Watchdog is used for increasing the safety of the system
**         (unforeseeable situations can cause system crash or an
**         infinite loop - watchdog can restart the system or handle
**         the situation).
**
**         Note: Watchdog can be enabled or disabled in the initialization
**               code only. If the watchdog is once enabled user have
**               to call Clear method in defined time intervals.
*/         
/*!
**  @addtogroup WDog1_module WDog1 module documentation
**  @{
*/         


/* MODULE WDog1. */

#include "Error.h"
#include "WDog1.h"

#pragma DATA_SEG WDog1_DATA            /* Select data segment "WDog1_DATA" */
#pragma CODE_SEG WDog1_CODE

/*
** ===================================================================
**     Method      :  WDog1_Clear (component WatchDog)
**     Description :
**         Clears the watchdog timer (it makes the timer restart from
**         zero).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - The component is disabled
** ===================================================================
*/
byte WDog1_Clear(void)
{
  CPMUARMCOP = 0x55U;
  CPMUARMCOP = 0xAAU;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  WDog1_Trigger (component WatchDog)
**     Description :
**         Triggers the watchdog timer (it fill the timer with wrong 
**         values).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - The component is disabled
** ===================================================================
*/
byte WDog1_Trigger(void)
{
  CPMUARMCOP = 0x01U;
  CPMUARMCOP = 0x10U;
  return ERR_OK;
}

/* END WDog1. */

/*!
** @}
*/
