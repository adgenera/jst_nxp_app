/*
 * timer.c
 *
 *  Created on: Mar 21, 2024
 *      Author: Andrea Cencio
 */

 #include "timer.h"

#pragma CODE_SEG DEFAULT
/*******************************************************************************
 * Definitions & Macros
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile dword ms_clock = 0;
extern bool us100;

/*******************************************************************************
 * Declaration
 ******************************************************************************/

/*******************************************************************************
 * Code (API function)
 ******************************************************************************/

dword wait_s(dword wait_time)
{
	return ms_clock + wait_time * 1000;
}

dword wait_ms(dword wait_time)
{
	return ms_clock + wait_time;
}

dword get_time(void)
{
	return ms_clock;
}

void init_time(void)
{
	ms_clock = 0;
}

void busy_waiting_ms(dword wait_time)
{
	dword end_time;

	end_time = wait_ms(wait_time);
	while (ms_clock < end_time)
	{
		;
	}
}

/*******************************************************************************
 * Code
 ******************************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(API_interrupt)
{
  // NOTE: The routine should include the following actions to obtain
  //       correct functionality of the hardware.
  //
  //       API interrupt request flag (APIF bit) must be set to 1 to
  //       clear the interrupt request.
  //       HCS12,HCS12Z Example: CPMUAPICTL_APIF = 1;
  //       HCS12X Example: VREGAPICL_APIF = 1;
    
    /* clear flag */
	CPMUAPICTL_APIF = 1;

    /* 100us flag updated */
	us100 = TRUE;

    /* time increment */
	ms_clock++;
}
