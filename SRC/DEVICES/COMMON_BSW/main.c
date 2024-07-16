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
  		if (ms) {
  			//if((ms_counter % 17) == 0) {
  			if((ms_counter % 1000) == 0) {
  				IIc_Set_KBI_Kompass_Peilung_HHSS();
  				//IIc_Set_KBI_Kompass_Peilung_MM();
  			}
  			//if((ms_counter % 34) == 0) {
  			if((ms_counter % 2000) == 0) {
  			  //IIc_Set_KBI_Kompass_Peilung_HHSS();
  			  IIc_Set_KBI_Kompass_Peilung_MM();
  			  ms_counter = 0;
  			}
  			//WDog1_Clear();
  			Wdg_Clear();
  			//APP_FSM();
  			/* Call ECUM MainFunction */
  			ms = FALSE;	
  			ms_counter++;
  		}
	}
}

