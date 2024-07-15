/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Version.h"
#include "IIc_Lcfg.h"

#include "IIC0.h"
#include "IIC0_Cfg.h"

static uint8 IICBuffer[9];             /* Input buffer I2C commmunication */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #makros --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* version check */


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #defines -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal typedefs  ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal enums  ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal structs  -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config internal data (const) --------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

static volatile uint16 IIc_KBI_Kompass_Peilung_HHSS_ui16;
static volatile uint16 IIc_KBI_Kompass_Peilung_MM_ui16;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global data (Userdata) (const) ------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config function (internal use only)--------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal functions (static) --------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global functions (Userfunctions) ----------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
* \brief Function Initialise internal variables of the Lin Interface.
*        Variables are Initialized with their Init Values.
*/
void IIc_LcfgInit(void)
{

   return;
}

/**
* \brief MainFunction of Lin Interface. It is called cyclic by the EcuM to extract Signals from Messages.
* There is also a timeout handling to serve default values in case of a timeout of that message
*
*/
void IIc_LcfgMainFunction(void)
{
   //"IIC_GetBuffer()" as in Lin mode
   boolean ret = IIC0_GetBuffer(IICBuffer);
   
   uint8 command = IICBuffer[0];
   
   switch(command){
   case M1_TARGET_ALL:
	   IIc_KBI_Kompass_Peilung_HHSS_ui16 = (uint16)(IICBuffer[1]<< 8);
	   IIc_KBI_Kompass_Peilung_HHSS_ui16 |= (uint16)IICBuffer[2];
	   IIc_KBI_Kompass_Peilung_HHSS_ui16 /= 10;	// TODO - ANGLE ON 16 Bit
	   break;
	   
   case M2_TARGET_ALL:
	   IIc_KBI_Kompass_Peilung_MM_ui16 = (uint16)(IICBuffer[1]<< 8);
	   IIc_KBI_Kompass_Peilung_MM_ui16 |= (uint16)IICBuffer[2];
	   IIc_KBI_Kompass_Peilung_MM_ui16 /= 10; // TODO - ANGLE ON 16 Bit
	   break;
	   
   default :
	   break;
   }
   
}

/**
* \brief Getter Function for Signal _KBI_Kompass_Peilung
*
* \return Value of Signal _KBI_Kompass_Peilung
*/
uint16 IIc_Get_KBI_Kompass_Peilung_HHSS(void)
{
   return (IIc_KBI_Kompass_Peilung_HHSS_ui16);
}

/**
* \brief Getter Function for Signal _KBI_Kompass_Peilung
*
* \return Value of Signal _KBI_Kompass_Peilung
*/
uint16 IIc_Get_KBI_Kompass_Peilung_MM(void)
{
   return (IIc_KBI_Kompass_Peilung_MM_ui16);
}
