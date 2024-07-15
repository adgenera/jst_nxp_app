/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Wdg_Cfg.h"

#include "Wdg.h"
#include "Mcu.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define WDG_SW_MAJOR_VERSION_C   (1)    /* Software major_c version */
#define WDG_SW_MINOR_VERSION_C   (0)    /* Software minor_c version */
#define WDG_SW_PATCH_VERSION_C   (0)    /* Software patch_c version */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #makros --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if((WDG_SW_MAJOR_VERSION_C != WDG_SW_MAJOR_VERSION) || \
    (WDG_SW_MINOR_VERSION_C != WDG_SW_MINOR_VERSION) || \
    (WDG_SW_PATCH_VERSION_C != WDG_SW_PATCH_VERSION))
   #error "Software Version Numbers of Wdg.c and Wdg.h are different."
#endif /* (WDG_SW_MAJOR_VERSION_C != WDG_SW_MAJOR_VERSION) || ... */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #defines -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal typedefs -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal enums  ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal structs --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal data (static) -------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/* internal Module Status */
static Std_ModuleStatusReturnType wdg_moduleStatus_e;
#endif


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global data (Userdata) --------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config function prototype (internal use only) ---------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal function prototypes (static) ----------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal functions (static) --------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global functions (Userfunctions) ----------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
* \brief Function to initialize the WDG module.
*
* Initializes the Module Short Name.
*
* \param [in]  ---
* \param [out] ---
* \return      ---
*/
void Wdg_Init(uint8 DeviceType)
{
   /* -- source code -------------------------- */
  /* set write once bit, can not be read back, shows always zero = 0x20
   * and COP and RTI stops in Active BDM Mode Bit = 0x40 */
  //*((uint8*)WDG_CPMUCOP_ADR_UI16)  = (uint8)(((uint8)0x1 << WDG_CPMUCOP_RSBCK_POS) | ((uint8)0x1 << WDG_CPMUCOP_WRTMASK_POS) );
  /* has no effect for changing the timeout period of the wdg, but counts for write once condition! */
  //*((uint8*)WDG_CPMUCOP_ADR_UI16)  = (uint8)0x00u;
  /* -> from now on no more changes of CR and WCOP are possible */

	  //setReg8(CPMUPROT, 0x26U);            /* Disable protection of clock-source register */ 
	*(uint8 *)MCU_CPMUPROT_ADR_UI16 = 0x26U;
	/* CPMUCLKS: CSAD=0,PCE=0,COPOSCSEL0=0 */
	  //clrReg8Bits(CPMUCLKS, 0x25U);         
    /* Initialise pllSel in S12CPMU_UHV_V5 Clock Select Register */
    *((uint8*)MCU_CPMUCLKS_ADR_UI16) = 0b00100001U;
	
	/* CPMUPROT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,PROT=0 */
	  //setReg8(CPMUPROT, 0x00U);            /* Re-Enable protection of clock-source register */ 
    *(uint8 *)MCU_CPMUPROT_ADR_UI16 = 0x00U;
	
	/* CPMURFLG: COPRF=0 */
	  //setReg8(CPMURFLG, 0x00U);            /* Clear COP reset flag */ 
    *((uint8*)MCU_CPMURFLG_ADR_UI16) = 0x00U;
		
	/* CPMUCOP: WCOP=0,CR2=1,CR1=1,CR0=0 */
	  //clrSetReg8Bits(CPMUCOP, 0x83U, 0x04U); 
    *((uint8*)WDG_CPMUCOP_ADR_UI16) = 0b00000110U;
}



/**
* \brief This service triggers the watchdog.
*
* \param [in]  ---
* \param [out] ---
* \return      ---
*/
void Wdg_Trigger
(
   void
)
{
   //#if !((defined TEST_ERRORHANDLER_5_WDGTRIGGER_FAIL) && (TEST_ERRORHANDLER_5_WDGTRIGGER_FAIL == 1))
   /* write trigger sequence */
   //Wdg_SetCpmuArmCopArmCop(0x55); /*lint !e9078 !e923 !e835 !e845 !e831 MISRA not necessary at MCAL */
   //Wdg_SetCpmuArmCopArmCop(0xAA); /*lint !e9078 !e923 !e835 !e845 !e831 MISRA not necessary at MCAL */
   //#endif

	*(uint8 *)WDG_CPMUARMCOP_ADR_UI16 = 0x01U;
	*(uint8 *)WDG_CPMUARMCOP_ADR_UI16 = 0x10U;
   return;
}

/*
** ===================================================================
**     Method      :  WDog1_Clear (component WatchDog)
**     Description :
**         Clears the watchdog timer (it makes the timer restart from
**         zero).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - The component is disabled
** ===================================================================
*/
uint8 Wdg_Clear(void)
{
	//Wdg_SetCpmuArmCopArmCop(0x55); /*lint !e9078 !e923 !e835 !e845 !e831 MISRA not necessary at MCAL */
	//Wdg_SetCpmuArmCopArmCop(0xAA); /*lint !e9078 !e923 !e835 !e845 !e831 MISRA not necessary at MCAL */
	
	*(uint8 *)WDG_CPMUARMCOP_ADR_UI16 = 0x55U;
	*(uint8 *)WDG_CPMUARMCOP_ADR_UI16 = 0xAAU;
	
	return 0;
}
