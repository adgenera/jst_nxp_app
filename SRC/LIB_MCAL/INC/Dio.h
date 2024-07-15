#ifndef DIO_H
#define DIO_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>
#include "Dio_Cfg.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define DIO_INSTANCE_ID           (0)  /* Instance id */
#define DIO_SW_MAJOR_VERSION      (1)  /* Software major version */
#define DIO_SW_MINOR_VERSION      (0)  /* Software minor version */
#define DIO_SW_PATCH_VERSION      (0)  /* Software patch version */


#if (DIO_DEV_ERROR_DETECTION == STD_ON)
/* DET Module API ID's */
#define DIO_INIT_API_ID           (0x01)       /* API ID of Dio_Init() */
#define DIO_DEINIT_API_ID         (0x02)       /* API ID of Dio_DeInit() */

/* DET Module error ID's */
#define DIO_E_PARAM_CONFIG        (0x10)       /* Error ID: config not found */
#define DIO_E_ALREADY_INITIALIZED (0x11)       /* Error ID: multiple call of Dio_Init() */
#define DIO_E_NOT_INITIALIZED     (0x12)       /* Error ID: multiple call of Dio_DeInit() */
#endif /* DIOWDG_DEV_ERROR_DETECTION == STD_ON */


/* Default values of DATA */
#define DIO_DATA_DEFAULT STD_OFF

/* Set macro for DATA */
#define Dio_SetData(reg, pos, value) ( \
   *((uint8*)(reg)) = \
      ( (uint8)( ( ((uint8)(value)) & (uint8)0x1 ) << (pos) ) | \
      ( (*((uint8*)(reg))) & (uint8)(~((uint8)0x1 << (pos)) ) ) ) )


/* Get macro for DATA */
#define Dio_GetData(reg, pos) ( \
      ( ((*((uint8*)(reg))) >> (pos)) & 0x1) )


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config typedefs ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \b Description: Type for channel naming
*/
typedef enum
{
   DIO_CHANNEL_PA0   = (uint8)0,
   DIO_CHANNEL_PA1   = (uint8)1,
   DIO_CHANNEL_PA2   = (uint8)2,
   DIO_CHANNEL_PA3   = (uint8)3,
   DIO_CHANNEL_PA4   = (uint8)4,
   DIO_CHANNEL_PA5   = (uint8)5,
   DIO_CHANNEL_PA6   = (uint8)6,
   DIO_CHANNEL_PA7   = (uint8)7,
   DIO_CHANNEL_PB0   = (uint8)8,
   DIO_CHANNEL_PB1   = (uint8)9,
   DIO_CHANNEL_PB2   = (uint8)10,
   DIO_CHANNEL_PB3   = (uint8)11,
   DIO_CHANNEL_PC0   = (uint8)16,
   DIO_CHANNEL_PC1   = (uint8)17,
   DIO_CHANNEL_PC2   = (uint8)18,
   DIO_CHANNEL_PC3   = (uint8)19,
   DIO_CHANNEL_PC4   = (uint8)20,
   DIO_CHANNEL_PC5   = (uint8)21,
   DIO_CHANNEL_PC6   = (uint8)22,
   DIO_CHANNEL_PC7   = (uint8)23,
   DIO_CHANNEL_PD0   = (uint8)24,
   DIO_CHANNEL_PD1   = (uint8)25,
   DIO_CHANNEL_PD2   = (uint8)26,
   DIO_CHANNEL_PD3   = (uint8)27,
   DIO_CHANNEL_PD4   = (uint8)28,
   DIO_CHANNEL_PD5   = (uint8)29,
   DIO_CHANNEL_PD6   = (uint8)30,
   DIO_CHANNEL_PD7   = (uint8)31,
   DIO_CHANNEL_PE0   = (uint8)32,
   DIO_CHANNEL_PE1   = (uint8)33,
   DIO_CHANNEL_PE2   = (uint8)34,
   DIO_CHANNEL_PE3   = (uint8)35,
   DIO_CHANNEL_PF0   = (uint8)40,
   DIO_CHANNEL_PF1   = (uint8)41,
   DIO_CHANNEL_PF2   = (uint8)42,
   DIO_CHANNEL_PF3   = (uint8)43,
   DIO_CHANNEL_PF4   = (uint8)44,
   DIO_CHANNEL_PF5   = (uint8)45,
   DIO_CHANNEL_PF6   = (uint8)46,
   DIO_CHANNEL_PF7   = (uint8)47,
   DIO_CHANNEL_PADL0 = (uint8)48,
   DIO_CHANNEL_PADL1 = (uint8)49,
   DIO_CHANNEL_PADL2 = (uint8)50,
   DIO_CHANNEL_PADL3 = (uint8)51,
   DIO_CHANNEL_PADL4 = (uint8)52,
   DIO_CHANNEL_PADL5 = (uint8)53,
   DIO_CHANNEL_PADL6 = (uint8)54,
   DIO_CHANNEL_PADL7 = (uint8)55,
   DIO_CHANNEL_PT0   = (uint8)56,
   DIO_CHANNEL_PT1   = (uint8)57,
   DIO_CHANNEL_PT2   = (uint8)58,
   DIO_CHANNEL_PT3   = (uint8)59,
   DIO_CHANNEL_PT4   = (uint8)60,
   DIO_CHANNEL_PT5   = (uint8)61,
   DIO_CHANNEL_PT6   = (uint8)62,
   DIO_CHANNEL_PT7   = (uint8)63,
   DIO_CHANNEL_PS0   = (uint8)64,
   DIO_CHANNEL_PS1   = (uint8)65,
   DIO_CHANNEL_PS2   = (uint8)66,
   DIO_CHANNEL_PS3   = (uint8)67,
   DIO_CHANNEL_PS4   = (uint8)68,
   DIO_CHANNEL_PS5   = (uint8)69,
   DIO_CHANNEL_PS6   = (uint8)70,
   DIO_CHANNEL_PS7   = (uint8)71,
   DIO_CHANNEL_PP0   = (uint8)72,
   DIO_CHANNEL_PP1   = (uint8)73,
   DIO_CHANNEL_PP2   = (uint8)74,
   DIO_CHANNEL_PP3   = (uint8)75,
   DIO_CHANNEL_PP4   = (uint8)76,
   DIO_CHANNEL_PP5   = (uint8)77,
   DIO_CHANNEL_PP6   = (uint8)78,
   DIO_CHANNEL_PP7   = (uint8)79,
   DIO_CHANNEL_PH0   = (uint8)80,
   DIO_CHANNEL_PH1   = (uint8)81,
   DIO_CHANNEL_PH2   = (uint8)82,
   DIO_CHANNEL_PH3   = (uint8)83,
   DIO_CHANNEL_PH4   = (uint8)84,
   DIO_CHANNEL_PH5   = (uint8)85,
   DIO_CHANNEL_PH6   = (uint8)86,
   DIO_CHANNEL_PH7   = (uint8)87,
   DIO_CHANNEL_PJ0   = (uint8)88,
   DIO_CHANNEL_PJ1   = (uint8)89,
   DIO_CHANNEL_PJ2   = (uint8)90,
   DIO_CHANNEL_PJ3   = (uint8)91,
   DIO_CHANNEL_PJ4   = (uint8)92,
   DIO_CHANNEL_PJ5   = (uint8)93,
   DIO_CHANNEL_PJ6   = (uint8)94,
   DIO_CHANNEL_PJ7   = (uint8)95,
   DIO_CHANNEL_PG0   = (uint8)96,
   DIO_CHANNEL_PG1   = (uint8)97,
   DIO_CHANNEL_PG2   = (uint8)98,
   DIO_CHANNEL_PG3   = (uint8)99,
   DIO_CHANNEL_PG4   = (uint8)100,
   DIO_CHANNEL_PG5   = (uint8)101,
   DIO_CHANNEL_PG6   = (uint8)102,
   DIO_CHANNEL_PG7   = (uint8)103,
   DIO_CHANNEL_PU0   = (uint8)104,
   DIO_CHANNEL_PU1   = (uint8)105,
   DIO_CHANNEL_PU2   = (uint8)106,
   DIO_CHANNEL_PU3   = (uint8)107,
   DIO_CHANNEL_PU4   = (uint8)108,
   DIO_CHANNEL_PU5   = (uint8)109,
   DIO_CHANNEL_PU6   = (uint8)110,
   DIO_CHANNEL_PU7   = (uint8)111
} Dio_ChannelType;

#define DIO_CHANNEL_COUNT (uint8)104


/** \b Description: Pin level */
typedef enum
{
   DIO_LEVEL_LOW  = (uint8)0,
   DIO_LEVEL_HIGH = (uint8)1
} Dio_LevelType;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config struct ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/** \b Description:
*/
typedef struct
{
   Dio_ChannelType dio_ChannelId;
   uint8 dio_Data;
} Dio_ChannelConfigType;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
* \brief Function to initialize the DIO module.
*
* Initializes the DIO module.
*
* \param [in]  ---
* \param [out] ---
* \return      DIO_E_OK: Initialization done correctly
*              DIO_E_NOT_OK: Something went wrong during initialization
*/
void Dio_Init
(
   void
);


#if (DIO_DEINIT_API == STD_ON)
/*
* \brief Function to deinitialize the DIO module.
*
* Deinitializes the DIO module.
*
* \param [in]  ---
* \param [out] ---
* \return      DIO_E_OK: Deinitialization done
*              DIO_E_NOT_OK: Something went wrong during deinitialization
*/
Std_ReturnType Dio_DeInit
(
   void
);
#endif /* #if (DIO_DEINIT_API == STD_ON) */


#if (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON)
/**
* \brief This service returns the status of this module .
*
* \param [in]  ---
* \param [out] ---
* \return      Module Status: DIO_UNINIT, DIO_DEINITIALIZED, DIO_INITIALIZED
*/
Std_ModuleStatusReturnType Dio_GetModuleStatus
(
   void
);
#endif /* (PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API == STD_ON) */


#if(DIO_VERSION_INFO_API == STD_ON)
/*
* \brief This service returns the version information of this module .
*
* \param [in]  ---
* \param [out] versioninfo = Pointer to where to store the version
*                            information of this module .
* \return      ---
*/
void Dio_GetVersionInfo
(
   Std_VersionInfoType *versioninfo
);
#endif /* DIO_VERSION_INFO_API == STD_ON */

#endif /* DIO_H */


/*
*  \brief Function to set Channel
*
*  \param [in]  ChannelId =  Dio Channel ID. For example: DIO_CHANNEL_PE0_UI8
*  \param [in]  Level  =  \li DIO_LEVEL_LOW
*                         \li DIO_LEVEL_HIGH
*  \param [out] ---
*  \return      ---
*/
void Dio_WriteChannel
(
   Dio_ChannelType ChannelId,
   Dio_LevelType Level
);


/*
*  \brief Function to get Channel
*
*  \param [in]  ChannelId =  Dio Channel ID. For example: DIO_CHANNEL_PE0_UI8
*  \return      Level  =  \li DIO_LEVEL_LOW
*                         \li DIO_LEVEL_HIGH
*/
Dio_LevelType Dio_ReadChannel
(
   Dio_ChannelType ChannelId
);
