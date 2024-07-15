/*******************************************************************************
* NXP Semiconductors
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by NXP in this matter are performed AS IS and without 
any warranty. CUSTOMER retains the final decision relative to the total design 
and functionality of the end product. NXP neither guarantees nor will be 
held liable by CUSTOMER for the success of this project.
NXP DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING, 
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR 
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE OR ADVISE SUPPLIED TO THE PROJECT
BY NXP, AND OR NAY PRODUCT RESULTING FROM NXP SERVICES. IN NO EVENT
SHALL NXP BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF
THIS AGREEMENT.

CUSTOMER agrees to hold NXP harmless against any and all claims demands or
actions by anyone on account of any damage, or injury, whether commercial, 
contractual, or tortuous, rising directly or indirectly as a result of an advise
or assistance supplied CUSTOMER in connection with product, services or goods 
supplied under this Agreement.
********************************************************************************
* File      main.c
* Owner     NXA19261
* Version   1.0
* Date      Aug-17-2017
* Classification   General Business Information
* Brief     Bootloader Dispatcher header file
********************************************************************************
* Detailed Description:
* Bootloader Dispatcher header file.
* 
********************************************************************************
Revision History:
Version  Date         Author    Description of Changes
1.0      Aug-17-2017  NXA19261  Initial version
*******************************************************************************/

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Cpu.h"

//==============================================================================
// Definitions
//==============================================================================
extern int __SEG_END_SSTACK[];

//==============================================================================
// Function Prototypes
//============================================================================== 
extern void _Startup(void);		/* bootloader startup function */
#pragma CODE_SEG _PRESTART
void Dispatcher(void);		/* prototype of main function */
#pragma CODE_SEG DEFAULT
#endif /* DISPATCHER_H_ */
