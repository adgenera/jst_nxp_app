#include "Timer.h"
#include "Mcu.h"

#pragma CODE_SEG DEFAULT
/*******************************************************************************
 * Definitions & Macros
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile uint32 ms_clock = 0;
extern boolean ms;

/*******************************************************************************
 * Declaration
 ******************************************************************************/

/*******************************************************************************
 * Code (API function)
 ******************************************************************************/

uint32 wait_s(uint32 wait_time)
{
	return ms_clock + wait_time * 1000;
}

uint32 wait_ms(uint32 wait_time)
{
	return ms_clock + wait_time;
}

uint32 get_time(void)
{
	return ms_clock;
}

void init_time(void)
{
	ms_clock = 0;
}

void busy_waiting_ms(uint32 wait_time)
{
	uint32 end_time;

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
__interrupt void API_interrupt
(
   void
)
{
  // NOTE: The routine should include the following actions to obtain
  //       correct functionality of the hardware.
  //
  //       API interrupt request flag (APIF bit) must be set to 1 to
  //       clear the interrupt request.
  //       HCS12,HCS12Z Example: CPMUAPICTL_APIF = 1;
  //       HCS12X Example: VREGAPICL_APIF = 1;
    
    /* clear flag */
	//CPMUAPICTL_APIF = 1;
	*((uint8*)MCU_CPMUAPICTL_ADR_UI16) |= 0x01U;
    /* ms flag updated */
	ms = TRUE;

    /* time increment */
	ms_clock++;
}
#pragma CODE_SEG DEFAULT

