/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include "Version.h"
#include "Port.h"

/* ***************************** # defines ********************************** */

/* ***************************** modul global data ************************** */

/* ***************************** global data ******************************** */

const Port_ConfigType port_initialConfig_s =
{
   /* configuration of port s DDR register.
    * set PS6 DO POW_3V3_EN  as output */
   0x40U
};

/* ***************************** modul global functions ********************* */

/* ***************************** global functions *************************** */
/*
 * \brief Function to get the pointer to link-time configuration .
 *
 * Standardized function for reading out the link time configuration.
 * Is always called by the function Port_Init().
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      returnValue_pv = void pointer to module configuration
 */
const void * Port_GetLcfgData
(
   void
)
{
   /* ------ variables declaration ------ */

   /* --- init module global variables -- */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
   return ((const void*) &port_initialConfig_s);
}
