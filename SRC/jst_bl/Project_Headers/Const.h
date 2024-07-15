/* ###################################################################
**     Filename    : Const.h
**     Project     : jst_bl
**     Processor   : MC9S12ZVHL32CLL
**     Component   : Const
**     Version     : Driver 01.01
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-02-09, 14:40
**     Abstract    :
**         This component "Const" contains internal definitions
**         of the constants.
**     Settings    :
**     Contents    :
**         No public methods
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
** @file Const.h
** @version 01.01
** @brief
**         This component "Const" contains internal definitions
**         of the constants.
*/         
/*!
**  @addtogroup Const_module Const module documentation
**  @{
*/         

#ifndef _Const_H
#define _Const_H

/* Constants for detecting running mode */
#define HIGH_SPEED        0x00U        /* High speed */
#define LOW_SPEED         0x01U        /* Low speed */
#define SLOW_SPEED        0x02U        /* Slow speed */

/* Reset cause constants */
#define RSTSRC_POR        0x01U        /* Power-on reset        */
#define RSTSRC_PIN        0x08U        /* External reset bit    */
#define RSTSRC_COP        0x04U        /* COP reset             */
#define RSTSRC_ILOP       0x02U        /* Illegal opcode reset  */
#define RSTSRC_ILAD       0x10U        /* Illegal address reset */
#define RSTSRC_LVI        0x20U        /* Low voltage inhibit reset */

#endif /* _Const_H */
/*!
** @}
*/
