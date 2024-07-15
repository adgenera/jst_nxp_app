#include "Version.h"
#include "EcuM.h"

#include "Events.h"

#include "API.h"	
#include "Wdg.h"

#include "Dio.h"
#include "Mtr.h"
#include "Cdd_Motor.h"
#include "Al_Motor.h"
#include "ISR_VectorTable.h"
#include "Mcu.h"
#include "Port.h"
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
	//Ecum_Init ();
	
	Dio_Init();
	Gpt_Init();
	Mtr_Init();
		   
	IIC0_Init();
	Cdd_Motor_Init();
	Al_Motor_Init();

	/* ******************************************************* *
	 *                                                         *
	 *  !!!!!!!!!!!!!!!!!!!!!!ATTENTION!!!!!!!!!!!!!!!!!!!!!!  *
	 *                                                         *
	 *  The frequencies for oscillator and bus clock must be   *
	 *        configured in the Ecum_Start() function          *
	 *  False configuration can result in hardware malfunction *
	 *                                                         *
	 * ******************************************************* */
	//Ecum_Start ();
	
	ISR_Set_PriorityLevel(); /*lint !e522: Highest operation, function 'ISR_Set_PriorityLevel', lacks side-effects -> direct writing to registers */

	/* initialize the MCU with 8 MHz oscillator */
	Mcu_Init ();
	/* initializing of the PORT module */
	Port_Init ();
	
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
  		if (ms) {
  			//WDog1_Clear();
  			Wdg_Clear();
  			//APP_FSM();
  			/* Call ECUM MainFunction */
  			//Ecum_MainFunction();
  			Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_HHSS);
  			Cdd_Motor_RunToNextFullStep (CDD_MOTOR_MTR_MM);
  			ms = FALSE;		
  		}
	}
}

