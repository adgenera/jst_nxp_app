#include "Version.h"
#include "EcuM.h"

#include "Events.h"

#include "API.h"	
#include "Wdg.h"

#include "Cdd_IIC.h"
#include "Dio.h"
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
		/* Call ECUM MainFunction */
		Ecum_MainFunction();
  		if (ms) 
        {
  			Wdg_Clear();
  			ms = FALSE;	
        }
	}
}

