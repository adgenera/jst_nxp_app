/* ***************************** includes " " ******************************* */
#include "Gpt.h"
//#pragma CONST_SEG ROM_CONST

/* ***************************** typedefs *********************************** */

/* ***************************** #defines *********************************** */

/* ***************************** #macros ************************************ */

/* ***************************** module global data ************************* */
/** GPT driver configuration 
 * 
 * If precision timer is disabled:
 * fTimer = (Fbus / GPT_PRESCALER)
 * 
 * If precision timer is enabled:
 * fTimer = (ft1 / (GPT_PRECISION_TIMER_PRESCALER + 1))
 * 
 * */
const Gpt_DriverConfigType gpt_driverConfig_s =
{
    GPT_STOP_IN_WAIT_DISABLED,      /* stop in wait mode */
    GPT_COUNTER_FREEZE_DISABLED,    /* counter freeze while in freeze Mode */
    GPT_PRESCALER_1,                /* Prescaler  */
    GPT_PRECISION_TIMER_ENABLED,    /* Precision Timer */
    (uint8)31U                    /* Precision Timer Prescaler */
};

/* ***************************** global data ******************************** */

/* ***************************** module global functions ********************* */

/* ***************************** global functions *************************** */

