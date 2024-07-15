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
 * Brief     Bootloader Dispatcher code
 ********************************************************************************
 * Detailed Description:
 * Please write your code here for detection whether Bootloader or Application will be executed.
 * 
 ********************************************************************************
 Revision History:
 Version  Date         Author    Description of Changes
 1.0      Aug-17-2017  NXA19261  Initial version
 *******************************************************************************/
#include "Dispatcher.h"
#include "Config.h"

#pragma CODE_SEG _PRESTART
void Dispatcher(void) {
	unsigned long int app_vector;
	asm LD S, #__SEG_END_SSTACK-1; /* Temporary initialise SP, Bootloader or Application will do it again */

	/*Write your code here*/
	/*Be Aware!!!: The global variables are not initialised yet. This code is executed prior Startup*/
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//Example of pin value testing 
	//if (PUSH_BOTTON==PB_ACTIVE_LEVEL)   //PB button test
	//{
	//_Startup();                         //bootloader Startup if button pressed
	//}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (((*(word *) JST_MAGIC_WORD) == 0x2540) && (PUSH_BUTTON!=PB_ACTIVE_LEVEL))
	{
		//Jump to main application
		app_vector = *(unsigned long int *) (APPLICATION_RESET_VEC_ADD + 1);
		asm LD X,app_vector;
		asm JMP (0,X);
	} else {
		_EntryPoint();	// bootloader Startup if Application is not loaded yet (empty application reset vector)
	}
}
#pragma CODE_SEG DEFAULT
