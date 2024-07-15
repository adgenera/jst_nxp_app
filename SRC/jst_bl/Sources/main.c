/* ###################################################################
 **     Filename    : main.c
 **     Project     : jst_bl
 **     Processor   : MC9S12ZVHL32CLL
 **     Version     : Driver 01.14
 **     Compiler    : CodeWarrior HCS12Z C Compiler
 **     Date/Time   : 2024-02-09, 13:58
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.14
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CI2C1.h"
#include "IFsh1.h"
#include "API.h"
#include "InpB1.h"
/* Include shared modules, which are used for whole project */
#include "MC9S12ZVHL32.h"
#include "Error.h"
#include "Const.h"
#include "BL.h"

flags_t flags;
bool us100 = FALSE;
byte cnt = 0;
word sent = 0;

/* User includes */
void main(void) {
	/* Write your local variable definition here */

	Low_level_init();

	/* Write your code here */

	for (;;) {
		if (us100) {
			BL_FSM();
			us100 = FALSE;		
		}
	}
} /*** End of main routine ***/

/* END main */
/*!
 ** @}
 */
