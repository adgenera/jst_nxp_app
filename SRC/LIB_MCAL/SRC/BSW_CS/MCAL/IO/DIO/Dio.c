/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Dio_Cfg.h"

#if(DIO_DEV_ERROR_DETECTION == STD_ON)
   //#include "Det.h"
#endif /* DIO_DEV_ERROR_DETECT == STD_ON */

#include "Dio.h"


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define DIO_SW_MAJOR_VERSION_C   (1)    /* Software major_c version */
#define DIO_SW_MINOR_VERSION_C   (0)    /* Software minor_c version */
#define DIO_SW_PATCH_VERSION_C   (0)    /* Software patch_c version */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #makros --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if((DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION) || \
    (DIO_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION) || \
    (DIO_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION))
   #error "Software Version Numbers of Dio.c and Dio.h are different."
#endif /* (DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION) || ... */



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
static Std_ModuleStatusReturnType dio_moduleStatus_e;
#endif

/** Description: address to data */
static const uint8 * const dio_baseAddrData_pui8[] = {
   (uint8* const) DIO_PTA_ADR_UI16,
   (uint8* const) DIO_PTB_ADR_UI16,
   (uint8* const) DIO_DDRC_ADR_UI16,
   (uint8* const) DIO_DDRD_ADR_UI16,
   (uint8* const) DIO_DDRE_ADR_UI16,
   (uint8* const) DIO_DDRF_ADR_UI16,
   (uint8* const) DIO_DDRADL_ADR_UI16,
   (uint8* const) DIO_DDRT_ADR_UI16,
   (uint8* const) DIO_DDRS_ADR_UI16,
   (uint8* const) DIO_DDRP_ADR_UI16,
   (uint8* const) DIO_DDRH_ADR_UI16,
   (uint8* const) DIO_DDRJ_ADR_UI16,
   (uint8* const) DIO_DDRG_ADR_UI16,
   (uint8* const) DIO_DDRU_ADR_UI16
};


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global data (Userdata) --------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (DIO_ROM_OPTIMIZATION == STD_OFF)
extern const Dio_ChannelConfigType dio_channelConfiguration[];
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
* \brief Function to initialize the DIO module.
*
* Initializes the Module Short Name.
*
* \param [in]  ---
* \param [out] ---
* \return      E_OK: Initialization done correctly
*              E_NOT_OK: Something went wrong during initialization
*/
void Dio_Init (void)
{
   /* -- variables declaration ---------------- */
   uint8 i_ui8;

   /* -- init module internal variables ------- */
   i_ui8 = 0U;

   /* -- init function internal variables ----- */

   /* -- source code -------------------------- */
#if(DIO_DEV_ERROR_DETECTION == STD_ON)
   if(dio_moduleStatus_e == MODULE_INITIALIZED)
   {
      /* Send error to DET */
      //Det_ReportError((uint16)DIO_MODULE_ID, (uint8)DIO_INSTANCE_ID, (uint8)DIO_INIT_API_ID, (uint8)DIO_E_ALREADY_INITIALIZED);
   }
   else
#endif /* DIO_DEV_ERROR_DETECT == STD_ON */
   {
#if (DIO_ROM_OPTIMIZATION == STD_OFF)
      for ( i_ui8=0; i_ui8<DIO_CHANNEL_COUNT; i_ui8++ ) {
         /* Initialise DATA */
         Dio_SetData(
            dio_baseAddrData_pui8[(uint8)dio_channelConfiguration[i_ui8].dio_ChannelId >> 3],
            (uint8)dio_channelConfiguration[i_ui8].dio_ChannelId & 0x7,
            DIO_DATA_DEFAULT
         );
      }

      /*for ( i_ui8=0; i_ui8<DIO_CHANNEL_COUNT; i_ui8++ ) {*/
         /* Template to configure DATA */
         /*Dio_SetData(
            dio_baseAddrData_pui8[(uint8)dio_channelConfiguration[i_ui8].dio_ChannelId >> 3],
            (uint8)dio_channelConfiguration[i_ui8].dio_ChannelId & 0x7,
            dio_channelConfiguration[i_ui8].dio_Data
         ); */
      /*}*/

      for ( i_ui8=0; i_ui8<DIO_CHANNEL_COUNT; i_ui8++ ) {
         /* Template to configure DATA */
         Dio_SetData(
            dio_baseAddrData_pui8[(uint8)dio_channelConfiguration[i_ui8].dio_ChannelId >> 3],
            (uint8)dio_channelConfiguration[i_ui8].dio_ChannelId & 0x7,
            dio_channelConfiguration[i_ui8].dio_Data
         );
      }
#else
      /* Port initialization already done by module Port */
#endif

#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
      /* Module is initialized */
      dio_moduleStatus_e = MODULE_INITIALIZED;
#endif
   }
}


#if (DIO_DEINIT_API == STD_ON)
/*
* \brief Function to deinitialize the DIO module.
*
* Deinitializes the DIO module.
*
* \param [in]  ---
* \param [out] ---
* \return      E_OK: Deinitialization done
*              E_NOT_OK: Something went wrong during deinitialization
*/
Std_ReturnType Dio_DeInit (void)
{
   /* -- variables declaration ---------------- */
   Std_ReturnType dio_deInitFunctionStatus_e;

   /* -- init function internal variables ----- */
   dio_deInitFunctionStatus_e = E_NOT_OK;

   /* -- source code -------------------------- */
   #if(DIO_DEV_ERROR_DETECTION == STD_ON)
      if(dio_moduleStatus_e != MODULE_INITIALIZED)
      {
         /* Send error to DET */
         Det_ReportError((uint16)DIO_MODULE_ID, (uint8)DIO_INSTANCE_ID, (uint8)DIO_DEINIT_API_ID, (uint8)DIO_E_NOT_INITIALIZED);
      }
      else
   #endif /* DIO_DEV_ERROR_DETECT == STD_ON */
      {
         /* Module is de-initialized */
         dio_moduleStatus_e = DIO_DEINITIALIZED;

         /* If something went wrong you have to return E_NOT_OK */
         dio_deInitFunctionStatus_e = E_OK;
      }

      return dio_deInitFunctionStatus_e;
}
#endif /* #if (DIO_DEINIT_API == STD_ON) */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/*
* \brief This service returns the status of this module (DO NOT CHANGE).
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: DIO_UNINIT, DIO_DEINITIALIZED, MODULE_INITIALIZED
*/
Std_ModuleStatusReturnType Dio_GetModuleStatus (void)
{
   /* -- source code -------------------------- */
   return(dio_moduleStatus_e);
}
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */


#if(DIO_VERSION_INFO_API == STD_ON)
   /*
   * \brief This service returns the version information of this module. (DO NOT CHANGE)
   *
   * \param [in]  ---
   * \param [out] versioninfo = Pointer to where to store the version
   *                            information of this module .
   * \return      ---
   */
   void Dio_GetVersionInfo
   (
      Std_VersionInfoType *versioninfo
   )
   {
      /* -- source code -------------------------- */
      versioninfo->moduleID = (uint16)DIO_MODULE_ID;
      versioninfo->instanceID = (uint8)DIO_INSTANCE_ID;
      versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
      versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
      versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
   }
#endif /* DIO_VERSION_INFO_API == STD_ON */


void Dio_WriteChannel
(
   Dio_ChannelType ChannelId,
   Dio_LevelType Level
)
{
   /* ------ variables declaration ------ */

   /* --- init modul global variables --- */

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
   Dio_SetData( dio_baseAddrData_pui8[ChannelId >> 3], ChannelId & 0x7, Level );
}



Dio_LevelType Dio_ReadChannel
(
   Dio_ChannelType ChannelId
)
{
   /* ------ variables declaration ------ */
   Dio_LevelType level;

   /* --- init modul global variables --- */
   level = DIO_LEVEL_LOW;

   /* ----- init internal variables ----- */

   /* ----------- source code ----------- */
   level = (Dio_LevelType)Dio_GetData( dio_baseAddrData_pui8[ChannelId >> 3], ChannelId & 0x7);

   return level;
}

