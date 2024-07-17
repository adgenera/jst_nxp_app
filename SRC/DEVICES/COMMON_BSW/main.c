#include "Version.h"
#include "EcuM.h"

#include "Events.h"

#include "API.h"	
#include "Wdg.h"

#include "IIc_Lcfg.h"
/**********************************************************************************************
 * External objects
// **********************************************************************************************/

/**********************************************************************************************
 * Constants and macros
 **********************************************************************************************/


/**********************************************************************************************
 * Global variables
 **********************************************************************************************/
flags_t flags;
boolean ms = FALSE;
uint8 cnt = 0;
uint16 sent = 0;

uint16 rcv = 0;
uint8 address = 0;

const uint16 jst_code @0x00FFE600 = 0x2540;

/**********************************************************************************************
 * Local types
 **********************************************************************************************/

/**********************************************************************************************
 * Local function prototypes
 *********************************************************************************************/

/**********************************************************************************************
 * Local variables
 **********************************************************************************************/
uint32 ms_counter = 0;
/**********************************************************************************************
 * Local functions
 **********************************************************************************************/

/**********************************************************************************************
 * Global functions
 **********************************************************************************************/

/***********************************************************************************************
 *
 * @brief    none
 * @param    none
 * @return   none
 *
 ************************************************************************************************/
uint16 MOVING_PATTERN[8] = {
    0,
    900,
    1800,
    2700,
    3600,
    2700,
    1800,
    900};

uint8 motor_index[2] = {0, 0};

static void bump_index(uint8 *index) {
    *index = (*index + 1) % 8;
}

void main (void)
{
	/* Disable all interrupts for initialization */
	DISABLE_ALL_INTERRUPTS(); /*lint !e960 */
    
	/* initialize the ECUM module */
	Ecum_Init ();

	/* ******************************************************* *
	 *                                                         *
	 *  !!!!!!!!!!!!!!!!!!!!!!ATTENTION!!!!!!!!!!!!!!!!!!!!!!  *
	 *                                                         *
	 *  The frequencies for oscillator and bus clock must be   *
	 *        configured in the Ecum_Start() function          *
	 *  False configuration can result in hardware malfunction *
	 *                                                         *
	 * ******************************************************* */
	Ecum_Start ();
	
	/* Initialize external Peripherals */
	    /* WDG is initialized separately **************************************** */
	//#if ! ((defined DEBUG_WATCHDOG_DISABLE) && (DEBUG_WATCHDOG_DISABLE == 1))
		Wdg_Init((uint8)DEVICE_TYPE);
	//#endif
	API_Init();
	/* Enable all interrupts */
	ENABLE_ALL_INTERRUPTS(); /*lint !e960 */	
		
	/* infinite loop */
	for (;;)
	{			
		Ecum_MainFunction();
  		if (ms) 
        {/*
                if((ms_counter % 1000) == 0) 
                {
                    IIc_Set_KBI_Kompass_Peilung_HHSS(MOVING_PATTERN[motor_index[0]]);                
                    bump_index(&motor_index[0]);
                }
                if (((ms_counter + 500) % 1000) == 0)
                {
                    IIc_Set_KBI_Kompass_Peilung_MM(MOVING_PATTERN[motor_index[1]]);
                    bump_index(&motor_index[1]);
                }

  			  //ms_counter = 0;
        */
  			Wdg_Clear();
   			//APP_FSM();
  			/* Call ECUM MainFunction */
  			ms = FALSE;	
  			ms_counter++;
        }
	}
}

