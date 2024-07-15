/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Port_Cfg.h"

#include "Port.h"


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define PORT_SW_MAJOR_VERSION_C   (1)    /* Software major_c version */
#define PORT_SW_MINOR_VERSION_C   (0)    /* Software minor_c version */
#define PORT_SW_PATCH_VERSION_C   (0)    /* Software patch_c version */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #makros --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if((PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION) || \
    (PORT_SW_MINOR_VERSION_C != PORT_SW_MINOR_VERSION) || \
    (PORT_SW_PATCH_VERSION_C != PORT_SW_PATCH_VERSION))
   #error "Software Version Numbers of Port.c and Port.h are different."
#endif /* (PORT_SW_MAJOR_VERSION_C != PORT_SW_MAJOR_VERSION) || ... */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #defines -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if (PORT_ROM_OPTIMIZATION == STD_ON)
#define   PORT_ECLKCTL *((uint8*)((uint16)0x000208))   /* ECLKCTLRegister */
#define   PORT_MODRR0 *((uint8*)((uint16)0x000200))   /* Module RoutingRegister */
#define   PORT_MODRR1 *((uint8*)((uint16)0x000201))   /* Module RoutingRegister */
#define   PORT_MODRR2 *((uint8*)((uint16)0x000202))   /* Module RoutingRegister */
#define   PORT_MODRR3 *((uint8*)((uint16)0x000203))   /* Module RoutingRegister */
#define   PORT_PIMMISC *((uint8*)((uint16)0x00020a))   /* Module RoutingRegister */
#define   PORT_DDRA *((uint8*)((uint16)0x000224))   /* Port ARegister */
#define   PORT_PERA *((uint8*)((uint16)0x000226))   /* Port ARegister */
#define   PORT_PPSA *((uint8*)((uint16)0x000228))   /* Port ARegister */
#define   PORT_PTA *((uint8*)((uint16)0x000220))   /* Port ARegister */
#define   PORT_PTIA *((uint8*)((uint16)0x000222))   /* Port ARegister */
#define   PORT_WOMA *((uint8*)((uint16)0x00023e))   /* Port ARegister */
#define   PORT_DDRADL *((uint8*)((uint16)0x000285))   /* Port ADLRegister */
#define   PORT_DIENADL *((uint8*)((uint16)0x000299))   /* Port ADLRegister */
#define   PORT_PERADL *((uint8*)((uint16)0x000287))   /* Port ADLRegister */
#define   PORT_PIEADL *((uint8*)((uint16)0x00028d))   /* Port ADLRegister */
#define   PORT_PIFADL *((uint8*)((uint16)0x00028f))   /* Port ADLRegister */
#define   PORT_PPSADL *((uint8*)((uint16)0x000289))   /* Port ADLRegister */
#define   PORT_PTADL *((uint8*)((uint16)0x000281))   /* Port ADLRegister */
#define   PORT_PTIADL *((uint8*)((uint16)0x000283))   /* Port ADLRegister */
#define   PORT_DDRB *((uint8*)((uint16)0x000225))   /* Port BRegister */
#define   PORT_PERB *((uint8*)((uint16)0x000227))   /* Port BRegister */
#define   PORT_PPSB *((uint8*)((uint16)0x000229))   /* Port BRegister */
#define   PORT_PTB *((uint8*)((uint16)0x000221))   /* Port BRegister */
#define   PORT_PTIB *((uint8*)((uint16)0x000223))   /* Port BRegister */
#define   PORT_DDRC *((uint8*)((uint16)0x000244))   /* Port CRegister */
#define   PORT_PERC *((uint8*)((uint16)0x000246))   /* Port CRegister */
#define   PORT_PPSC *((uint8*)((uint16)0x000248))   /* Port CRegister */
#define   PORT_PTC *((uint8*)((uint16)0x000240))   /* Port CRegister */
#define   PORT_PTIC *((uint8*)((uint16)0x000242))   /* Port CRegister */
#define   PORT_DDRD *((uint8*)((uint16)0x000245))   /* Port DRegister */
#define   PORT_PERD *((uint8*)((uint16)0x000247))   /* Port DRegister */
#define   PORT_PPSD *((uint8*)((uint16)0x000249))   /* Port DRegister */
#define   PORT_PTD *((uint8*)((uint16)0x000241))   /* Port DRegister */
#define   PORT_PTID *((uint8*)((uint16)0x000243))   /* Port DRegister */
#define   PORT_DDRE *((uint8*)((uint16)0x000264))   /* Port ERegister */
#define   PORT_PERE *((uint8*)((uint16)0x000266))   /* Port ERegister */
#define   PORT_PPSE *((uint8*)((uint16)0x000268))   /* Port ERegister */
#define   PORT_PTE *((uint8*)((uint16)0x000260))   /* Port ERegister */
#define   PORT_PTIE *((uint8*)((uint16)0x000262))   /* Port ERegister */
#define   PORT_DDRF *((uint8*)((uint16)0x000265))   /* Port FRegister */
#define   PORT_PERF *((uint8*)((uint16)0x000267))   /* Port FRegister */
#define   PORT_PPSF *((uint8*)((uint16)0x000269))   /* Port FRegister */
#define   PORT_PTF *((uint8*)((uint16)0x000261))   /* Port FRegister */
#define   PORT_PTIF *((uint8*)((uint16)0x000263))   /* Port FRegister */
#define   PORT_DDRG *((uint8*)((uint16)0x000322))   /* Port GRegister */
#define   PORT_PERG *((uint8*)((uint16)0x000323))   /* Port GRegister */
#define   PORT_PPSG *((uint8*)((uint16)0x000324))   /* Port GRegister */
#define   PORT_PTG *((uint8*)((uint16)0x000320))   /* Port GRegister */
#define   PORT_PTIG *((uint8*)((uint16)0x000321))   /* Port GRegister */
#define   PORT_DDRH *((uint8*)((uint16)0x000302))   /* Port HRegister */
#define   PORT_PERH *((uint8*)((uint16)0x000303))   /* Port HRegister */
#define   PORT_PPSH *((uint8*)((uint16)0x000304))   /* Port HRegister */
#define   PORT_PTH *((uint8*)((uint16)0x000300))   /* Port HRegister */
#define   PORT_PTIH *((uint8*)((uint16)0x000301))   /* Port HRegister */
#define   PORT_DDRJ *((uint8*)((uint16)0x000312))   /* Port JRegister */
#define   PORT_PERJ *((uint8*)((uint16)0x000313))   /* Port JRegister */
#define   PORT_PPSJ *((uint8*)((uint16)0x000314))   /* Port JRegister */
#define   PORT_PTIJ *((uint8*)((uint16)0x000311))   /* Port JRegister */
#define   PORT_PTJ *((uint8*)((uint16)0x000310))   /* Port JRegister */
#define   PORT_DDRP *((uint8*)((uint16)0x0002f2))   /* Port PRegister */
#define   PORT_PERP *((uint8*)((uint16)0x0002f3))   /* Port PRegister */
#define   PORT_PPSP *((uint8*)((uint16)0x0002f4))   /* Port PRegister */
#define   PORT_PTIP *((uint8*)((uint16)0x0002f1))   /* Port PRegister */
#define   PORT_PTP *((uint8*)((uint16)0x0002f0))   /* Port PRegister */
#define   PORT_DDRS *((uint8*)((uint16)0x0002d2))   /* Port SRegister */
#define   PORT_PERS *((uint8*)((uint16)0x0002d3))   /* Port SRegister */
#define   PORT_PIES *((uint8*)((uint16)0x0002d6))   /* Port SRegister */
#define   PORT_PIFS *((uint8*)((uint16)0x0002d7))   /* Port SRegister */
#define   PORT_PPSS *((uint8*)((uint16)0x0002d4))   /* Port SRegister */
#define   PORT_PTIS *((uint8*)((uint16)0x0002d1))   /* Port SRegister */
#define   PORT_PTS *((uint8*)((uint16)0x0002d0))   /* Port SRegister */
#define   PORT_WOMS *((uint8*)((uint16)0x0002df))   /* Port SRegister */
#define   PORT_DDRT *((uint8*)((uint16)0x0002c2))   /* Port TRegister */
#define   PORT_PERT *((uint8*)((uint16)0x0002c3))   /* Port TRegister */
#define   PORT_PIET *((uint8*)((uint16)0x0002c6))   /* Port TRegister */
#define   PORT_PIFT *((uint8*)((uint16)0x0002c7))   /* Port TRegister */
#define   PORT_PPST *((uint8*)((uint16)0x0002c4))   /* Port TRegister */
#define   PORT_PTIT *((uint8*)((uint16)0x0002c1))   /* Port TRegister */
#define   PORT_PTT *((uint8*)((uint16)0x0002c0))   /* Port TRegister */
#define   PORT_DDRU *((uint8*)((uint16)0x000352))   /* Port URegister */
#define   PORT_PERU *((uint8*)((uint16)0x000353))   /* Port URegister */
#define   PORT_PPSU *((uint8*)((uint16)0x000354))   /* Port URegister */
#define   PORT_PTIU *((uint8*)((uint16)0x000351))   /* Port URegister */
#define   PORT_PTU *((uint8*)((uint16)0x000350))   /* Port URegister */
#define   PORT_SRRU *((uint8*)((uint16)0x00035e))   /* Port URegister */
#endif


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
static volatile Std_ModuleStatusReturnType port_moduleStatus_e;
#endif

#if (PORT_ROM_OPTIMIZATION == STD_OFF)
/* Register dummy variable */
static volatile uint8 port_DummyRegister;

/** Description: address to input */
static uint8 * const port_baseAddrInput_pui8[] = {
   (uint8* const) PORT_PTIA_ADR_UI16,
   (uint8* const) PORT_PTIB_ADR_UI16,
   (uint8* const) PORT_PTIC_ADR_UI16,
   (uint8* const) PORT_PTID_ADR_UI16,
   (uint8* const) PORT_PTIE_ADR_UI16,
   (uint8* const) PORT_PTIF_ADR_UI16,
   (uint8* const) PORT_PTIADL_ADR_UI16,
   (uint8* const) PORT_PTIT_ADR_UI16,
   (uint8* const) PORT_PTIS_ADR_UI16,
   (uint8* const) PORT_PTIP_ADR_UI16,
   (uint8* const) PORT_PTIH_ADR_UI16,
   (uint8* const) PORT_PTIJ_ADR_UI16,
   (uint8* const) PORT_PTIG_ADR_UI16,
   (uint8* const) PORT_PTIU_ADR_UI16
};


/** Description: address to dataDirection */
static volatile uint8 * const port_baseAddrDataDirection_pui8[] = {
   (uint8* const) PORT_DDRA_ADR_UI16,
   (uint8* const) PORT_DDRB_ADR_UI16,
   (uint8* const) PORT_DDRC_ADR_UI16,
   (uint8* const) PORT_DDRD_ADR_UI16,
   (uint8* const) PORT_DDRE_ADR_UI16,
   (uint8* const) PORT_DDRF_ADR_UI16,
   (uint8* const) PORT_DDRADL_ADR_UI16,
   (uint8* const) PORT_DDRT_ADR_UI16,
   (uint8* const) PORT_DDRS_ADR_UI16,
   (uint8* const) PORT_DDRP_ADR_UI16,
   (uint8* const) PORT_DDRH_ADR_UI16,
   (uint8* const) PORT_DDRJ_ADR_UI16,
   (uint8* const) PORT_DDRG_ADR_UI16,
   (uint8* const) PORT_DDRU_ADR_UI16
};

/** Description: address to digitalInputEnable */
static volatile uint8 * const port_baseAddrDigitalInputEnable_pui8[] = {
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) PORT_DIENADL_ADR_UI16,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister
};

/** Description: address to pullDeviceEnable */
static volatile uint8 * const port_baseAddrPullDeviceEnable_pui8[] = {
   (uint8* const) PORT_PERA_ADR_UI16,
   (uint8* const) PORT_PERB_ADR_UI16,
   (uint8* const) PORT_PERC_ADR_UI16,
   (uint8* const) PORT_PERD_ADR_UI16,
   (uint8* const) PORT_PERE_ADR_UI16,
   (uint8* const) PORT_PERF_ADR_UI16,
   (uint8* const) PORT_PERADL_ADR_UI16,
   (uint8* const) PORT_PERT_ADR_UI16,
   (uint8* const) PORT_PERS_ADR_UI16,
   (uint8* const) PORT_PERP_ADR_UI16,
   (uint8* const) PORT_PERH_ADR_UI16,
   (uint8* const) PORT_PERJ_ADR_UI16,
   (uint8* const) PORT_PERG_ADR_UI16,
   (uint8* const) PORT_PERU_ADR_UI16
};

/** Description: address to polaritySelect */
static volatile uint8 * const port_baseAddrPolaritySelect_pui8[] = {
   (uint8* const) PORT_PPSA_ADR_UI16,
   (uint8* const) PORT_PPSB_ADR_UI16,
   (uint8* const) PORT_PPSC_ADR_UI16,
   (uint8* const) PORT_PPSD_ADR_UI16,
   (uint8* const) PORT_PPSE_ADR_UI16,
   (uint8* const) PORT_PPSF_ADR_UI16,
   (uint8* const) PORT_PPSADL_ADR_UI16,
   (uint8* const) PORT_PPST_ADR_UI16,
   (uint8* const) PORT_PPSS_ADR_UI16,
   (uint8* const) PORT_PPSP_ADR_UI16,
   (uint8* const) PORT_PPSH_ADR_UI16,
   (uint8* const) PORT_PPSJ_ADR_UI16,
   (uint8* const) PORT_PPSG_ADR_UI16,
   (uint8* const) PORT_PPSU_ADR_UI16
};

/** Description: address to wiredOrMode */
static volatile uint8 * const port_baseAddrWiredOrMode_pui8[] = {
   (uint8* const) PORT_WOMA_ADR_UI16,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) PORT_WOMS_ADR_UI16,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister
};

/** Description: address to interruptEnable */
static volatile uint8 * const port_baseAddrInterruptEnable_pui8[] = {
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) PORT_PIEADL_ADR_UI16,
   (uint8* const) PORT_PIET_ADR_UI16,
   (uint8* const) PORT_PIES_ADR_UI16,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister
};

/** Description: address to interruptFlag */
static volatile uint8 * const port_baseAddrInterruptFlag_pui8[] = {
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) PORT_PIFADL_ADR_UI16,
   (uint8* const) PORT_PIFT_ADR_UI16,
   (uint8* const) PORT_PIFS_ADR_UI16,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister
};

/** Description: address to slewRate */
static volatile uint8 * const port_baseAddrSlewRate_pui8[] = {
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) &port_DummyRegister,
   (uint8* const) PORT_SRRU_ADR_UI16
};

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global data (Userdata) --------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
extern volatile const Port_ConfigType port_initialConfiguration_s;
#endif

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
/*
* \brief Function to initialize the PORT module.
*
* Initializes the Module Short Name.
*
* \param [in]  ---
* \param [out] ---
* \return      E_OK: Initialization done correctly
*              E_NOT_OK: Something went wrong during initialization
*/
void Port_Init
(
   void
)
{
   /* -- variables declaration ---------------- */
   uint8 i_ui8;

   /* -- init module internal variables ------- */
   /* -- init function internal variables ----- */
   i_ui8 = 0;

   /* -- source code -------------------------- */
   #if(PORT_DEV_ERROR_DETECTION == STD_ON)
   if(port_moduleStatus_e == MODULE_INITIALIZED)
   {
      /* Send error to DET */
      //Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_INIT_API_ID, (uint8)PORT_E_ALREADY_INITIALIZED);
   }
   else
   #endif /* PORT_DEV_ERROR_DETECT == STD_ON */
   {
#if (PORT_ROM_OPTIMIZATION == STD_OFF)
      /* Initialise c0Rr in Module Routing Register 0 */
      Port_SetModRr0C0Rr(PORT_MODRR0_C0RR_DEFAULT);
      /* Initialise pwm6Rr in Module Routing Register 1 */
      Port_SetModRr1Pwm6Rr(PORT_MODRR1_PWM6RR_DEFAULT);
      /* Initialise pwm4Rr in Module Routing Register 1 */
      Port_SetModRr1Pwm4Rr(PORT_MODRR1_PWM4RR_DEFAULT);
      /* Initialise pwm2Rr in Module Routing Register 1 */
      Port_SetModRr1Pwm2Rr(PORT_MODRR1_PWM2RR_DEFAULT);
      /* Initialise pwm0Rr in Module Routing Register 1 */
      Port_SetModRr1Pwm0Rr(PORT_MODRR1_PWM0RR_DEFAULT);
      /* Initialise sci1Rr in Module Routing Register 2 */
      Port_SetModRr2Sci1Rr(PORT_MODRR2_SCI1RR_DEFAULT);
      /* Initialise iic0Rr in Module Routing Register 2 */
      Port_SetModRr2Iic0Rr(PORT_MODRR2_IIC0RR_DEFAULT);
      /* Initialise t1ic0Rr in Module Routing Register 2 */
      Port_SetModRr2T1ic0Rr(PORT_MODRR2_T1IC0RR_DEFAULT);
      /* Initialise s0L0Rr in Module Routing Register 3 */
      Port_SetModRr3S0L0Rr(PORT_MODRR3_S0L0RR_DEFAULT);
      /* Initialise nEClk in ECLK Control Register */
      Port_SetEClkCtlNEClk(PORT_ECLKCTL_NECLK_DEFAULT);
      /* Initialise irqE in IRQ Control Register */
      Port_SetIrqCrIrqE(PORT_IRQCR_IRQE_DEFAULT);
      /* Initialise irqEn in IRQ Control Register */
      Port_SetIrqCrIrqEn(PORT_IRQCR_IRQEN_DEFAULT);
      /* Initialise calClkEn in PIM Miscellaneous Register */
      Port_SetPimMiscCalClkEn(PORT_PIMMISC_CALCLKEN_DEFAULT);
      for ( i_ui8=0; i_ui8<PORT_PIN_COUNT; i_ui8++ ) {
         /* Initialise DATADIRECTION */
         Port_SetDataDirection(
            port_baseAddrDataDirection_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_DATADIRECTION_DEFAULT
         );
         /* Initialise DIGITALINPUTENABLE */
         Port_SetDigitalInputEnable(
            port_baseAddrDigitalInputEnable_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_DIGITALINPUTENABLE_DEFAULT
         );
         /* Initialise PULLDEVICEENABLE */
         Port_SetPullDeviceEnable(
            port_baseAddrPullDeviceEnable_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_PULLDEVICEENABLE_DEFAULT
         );
         /* Initialise POLARITYSELECT */
         Port_SetPolaritySelect(
            port_baseAddrPolaritySelect_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_POLARITYSELECT_DEFAULT
         );
         /* Initialise WIREDORMODE */
         Port_SetWiredOrMode(
            port_baseAddrWiredOrMode_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_WIREDORMODE_DEFAULT
         );
         /* Initialise INTERRUPTENABLE */
         Port_SetInterruptEnable(
            port_baseAddrInterruptEnable_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_INTERRUPTENABLE_DEFAULT
         );
         /* Initialise INTERRUPTFLAG */
         Port_SetInterruptFlag(
            port_baseAddrInterruptFlag_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_INTERRUPTFLAG_DEFAULT
         );
         /* Initialise SLEWRATE */
         Port_SetSlewRate(
            port_baseAddrSlewRate_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            PORT_SLEWRATE_DEFAULT
         );
      }

      /* Template to configure nEClk in ECLK Control Register */
      /* Port_SetEClkCtlNEClk(port_initialConfiguration_s.port_EClkCtlNEClk); */
      /* Template to configure calClkEn in PIM Miscellaneous Register */
      /* Port_SetPimMiscCalClkEn(port_initialConfiguration_s.port_PimMiscCalClkEn); */
      /*for ( i_ui8=0; i_ui8<PORT_PIN_COUNT; i_ui8++ ) {*/
         /* Template to configure DATADIRECTION */
         /*Port_SetDataDirection(
            port_baseAddrDataDirection_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_DataDirection
         ); */
      /*}*/

      for ( i_ui8=0; i_ui8<PORT_PIN_COUNT; i_ui8++ ) {
         /* Template to configure DATADIRECTION */
         Port_SetDataDirection(
            port_baseAddrDataDirection_pui8[(uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId >> 3],
            (uint8)port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_PinId & 0x7,
            port_initialConfiguration_s.port_PinConfig_ps[i_ui8].port_DataDirection
         );
      }

      Port_SetEClkCtlNEClk(port_initialConfiguration_s.port_EClkCtlNEClk);
      Port_SetPimMiscCalClkEn(port_initialConfiguration_s.port_PimMiscCalClkEn);
#else
      PORT_ECLKCTL = 0x80U;     /* Register ECLKCTL */
      PORT_MODRR0 = 0x00U;     /* Register Module Routing */
      PORT_MODRR1 = 0x00U;     /* Register Module Routing */
      PORT_MODRR2 = 0x02U;     /* Register Module Routing */
      PORT_MODRR3 = 0x00U;     /* Register Module Routing */
      PORT_PIMMISC = 0x00U;     /* Register Module Routing */
      PORT_DDRA = 0x00U;     /* Register Port A */
      PORT_PERA = 0xFFU;     /* Register Port A */
      PORT_PPSA = 0xFFU;     /* Register Port A */
      PORT_PTA = 0x00U;     /* Register Port A */
      PORT_PTIA = 0x00U;     /* Register Port A */
      PORT_WOMA = 0x00U;     /* Register Port A */
      PORT_DDRADL = 0x00U;     /* Register Port ADL */
      PORT_DIENADL = 0x00U;     /* Register Port ADL */
      PORT_PERADL = 0xFFU;     /* Register Port ADL */
      PORT_PIEADL = 0x00U;     /* Register Port ADL */
      PORT_PIFADL = 0x00U;     /* Register Port ADL */
      PORT_PPSADL = 0xFFU;     /* Register Port ADL */
      PORT_PTADL = 0xFFU;     /* Register Port ADL */
      PORT_PTIADL = 0xFFU;     /* Register Port ADL */
      PORT_DDRB = 0x00U;     /* Register Port B */
      PORT_PERB = 0x0FU;     /* Register Port B */
      PORT_PPSB = 0x0FU;     /* Register Port B */
      PORT_PTB = 0x00U;     /* Register Port B */
      PORT_PTIB = 0x00U;     /* Register Port B */
      PORT_DDRC = 0x00U;     /* Register Port C */
      PORT_PERC = 0xFFU;     /* Register Port C */
      PORT_PPSC = 0xFFU;     /* Register Port C */
      PORT_PTC = 0x00U;     /* Register Port C */
      PORT_PTIC = 0x00U;     /* Register Port C */
      PORT_DDRD = 0x00U;     /* Register Port D */
      PORT_PERD = 0xFFU;     /* Register Port D */
      PORT_PPSD = 0xFFU;     /* Register Port D */
      PORT_PTD = 0x00U;     /* Register Port D */
      PORT_PTID = 0x00U;     /* Register Port D */
      PORT_DDRE = 0x00U;     /* Register Port E */
      PORT_PERE = 0x0FU;     /* Register Port E */
      PORT_PPSE = 0x0FU;     /* Register Port E */
      PORT_PTE = 0x0CU;     /* Register Port E */
      PORT_PTIE = 0x0CU;     /* Register Port E */
      PORT_DDRF = 0x00U;     /* Register Port F */
      PORT_PERF = 0xFFU;     /* Register Port F */
      PORT_PPSF = 0xFFU;     /* Register Port F */
      PORT_PTF = 0x00U;     /* Register Port F */
      PORT_PTIF = 0x00U;     /* Register Port F */
      PORT_DDRG = 0x00U;     /* Register Port G */
      PORT_PERG = 0xFFU;     /* Register Port G */
      PORT_PPSG = 0xFFU;     /* Register Port G */
      PORT_PTG = 0x00U;     /* Register Port G */
      PORT_PTIG = 0x00U;     /* Register Port G */
      PORT_DDRH = 0x00U;     /* Register Port H */
      PORT_PERH = 0xFFU;     /* Register Port H */
      PORT_PPSH = 0xFFU;     /* Register Port H */
      PORT_PTH = 0x00U;     /* Register Port H */
      PORT_PTIH = 0x00U;     /* Register Port H */
      PORT_DDRJ = 0x00U;     /* Register Port J */
      PORT_PERJ = 0x0FU;     /* Register Port J */
      PORT_PPSJ = 0x0FU;     /* Register Port J */
      PORT_PTIJ = 0x00U;     /* Register Port J */
      PORT_PTJ = 0x00U;     /* Register Port J */
      PORT_DDRP = 0x0AU;     /* Register Port P */
      PORT_PERP = 0xFFU;     /* Register Port P */
      PORT_PPSP = 0xFFU;     /* Register Port P */
      PORT_PTIP = 0x00U;     /* Register Port P */
      PORT_PTP = 0x00U;     /* Register Port P */
      PORT_DDRS = 0x40U;     /* Register Port S */
      PORT_PERS = 0xFFU;     /* Register Port S */
      PORT_PIES = 0x00U;     /* Register Port S */
      PORT_PIFS = 0x00U;     /* Register Port S */
      PORT_PPSS = 0xFFU;     /* Register Port S */
      PORT_PTIS = 0x00U;     /* Register Port S */
      PORT_PTS = 0x00U;     /* Register Port S */
      PORT_WOMS = 0x00U;     /* Register Port S */
      PORT_DDRT = 0x50U;     /* Register Port T */
      PORT_PERT = 0xFFU;     /* Register Port T */
      PORT_PIET = 0x00U;     /* Register Port T */
      PORT_PIFT = 0x00U;     /* Register Port T */
      PORT_PPST = 0xFFU;     /* Register Port T */
      PORT_PTIT = 0x00U;     /* Register Port T */
      PORT_PTT = 0x00U;     /* Register Port T */
      PORT_DDRU = 0xC0u;     /* Register Port U */
      PORT_PERU = 0xFFU;     /* Register Port U */
      PORT_PPSU = 0xFFU;     /* Register Port U */
      PORT_PTIU = 0x00U;     /* Register Port U */
      PORT_PTU = 0x00U;     /* Register Port U */
      PORT_SRRU = 0x00U;     /* Register Port U */
#endif

#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
      /* Module is initialized */
      port_moduleStatus_e = MODULE_INITIALIZED;
#endif
   }

}


#if (PORT_DEINIT_API == STD_ON)
/*
* \brief Function to deinitialize the PORT module.
*
* Deinitializes the PORT module.
*
* \param [in]  ---
* \param [out] ---
* \return      E_OK: Deinitialization done
*              E_NOT_OK: Something went wrong during deinitialization
*/
Std_ReturnType Port_DeInit
(
   void
)
{
   /* -- variables declaration ---------------- */
   Std_ReturnType port_deInitFunctionStatus_e;

   /* -- init function internal variables ----- */
   port_deInitFunctionStatus_e = E_NOT_OK;

   /* -- source code -------------------------- */
   #if(PORT_DEV_ERROR_DETECTION == STD_ON)
      if(port_moduleStatus_e != MODULE_INITIALIZED)
      {
         /* Send error to DET */
         Det_ReportError((uint16)PORT_MODULE_ID, (uint8)PORT_INSTANCE_ID, (uint8)PORT_DEINIT_API_ID, (uint8)PORT_E_NOT_INITIALIZED);
      }
      else
   #endif /* PORT_DEV_ERROR_DETECT == STD_ON */
      {
         /* Module is de-initialized */
         port_moduleStatus_e = PORT_DEINITIALIZED;

         /* If something went wrong you have to return E_NOT_OK */
         port_deInitFunctionStatus_e = E_OK;
      }

      return port_deInitFunctionStatus_e;
}
#endif /* #if (PORT_DEINIT_API == STD_ON) */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/*
* \brief This service returns the status of this module (DO NOT CHANGE).
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: PORT_UNINIT, PORT_DEINITIALIZED, MODULE_INITIALIZED
*/
Std_ModuleStatusReturnType Port_GetModuleStatus
(
   void
)
{
   /* -- source code -------------------------- */
   return(port_moduleStatus_e);
}
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */


#if(PORT_VERSION_INFO_API == STD_ON)
   /*
   * \brief This service returns the version information of this module. (DO NOT CHANGE)
   *
   * \param [in]  ---
   * \param [out] versioninfo = Pointer to where to store the version
   *                            information of this module .
   * \return      ---
   */
   void Port_GetVersionInfo
   (
      Std_VersionInfoType *versioninfo
   )
   {
      /* -- source code -------------------------- */
      versioninfo->moduleID = (uint16)PORT_MODULE_ID;
      versioninfo->instanceID = (uint8)PORT_INSTANCE_ID;
      versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
      versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
      versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
   }
#endif /* PORT_VERSION_INFO_API == STD_ON */

