/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include "Version.h"

#include "EcuM.h"

/* MCAL ************************ */
#include <IIC0.h>

#include <Dio.h>
#include <Mtr.h>
#include <Port.h>

#include <Mcu.h>

#include <Gpt.h>
#include <Mcu.h>
#include <Wdg.h>

/* HAL ************************* */
#include "IIc_Lcfg.h"

/* SL ************************* */
#include "Cdd_Motor.h"

/* RTE ************************ */

/* AL ************************* */
#include "Al_Motor.h"

/* ***************************** typedefs *********************************** */

/* ***************************** # defines ********************************** */

/* ***************************** modul global data ************************** */

#pragma CONST_SEG ROM
#pragma CODE_SEG __NEAR_SEG NON_BANKED

const Ecum_CallbackType ecum_initFunctionPtr_apf[] =
{
   /* WDG is initialized separately **************************************** */
   /* MCAL ***************************************************************** */
   (Ecum_CallbackType) &Dio_Init,
   (Ecum_CallbackType) &Gpt_Init,
   (Ecum_CallbackType) &Mtr_Init,
   
   (Ecum_CallbackType) &IIC0_Init,

   /* HAL ****************************************************************** */
   (Ecum_CallbackType) &Cdd_Motor_Init,

   /* SL ******************************************************************* */
   (Ecum_CallbackType) &Al_Motor_Init
};

const uint8 ecum_initFunctionPtrSIZE_ui8 = (uint8)STD_NUMBER_OF_ELEMENTS(ecum_initFunctionPtr_apf); /*lint !e866: Unusual use of '' in argument to sizeof */

#if (ECUM_DEINIT_API == STD_ON)
volatile Ecum_CallbackType const ecum_deinitFunctionPtr_apf[] =
{
   /* SL ******************************************************************* */
   (Ecum_CallbackType) &Al_Motor_DeInit,

   /* HAL ****************************************************************** */
   (Ecum_CallbackType) &Wdg_DeInit,
   (Ecum_CallbackType) &Cdd_Motor_DeInit,

   /* MCAL ***************************************************************** */   
   (Ecum_CallbackType) &Pwm_DeInit,
   (Ecum_CallbackType) &Mtr_DeInit,

   (Ecum_CallbackType) &Gpt_DeInit,

   (Ecum_CallbackType) &Dio_DeInit,
   (Ecum_CallbackType) &Port_DeInit,
   (Ecum_CallbackType) &Mcu_DeInit,

   /* WDG is initialized separately **************************************** */
/*    (Ecum_CallbackType) &Wdg_DeInit,*/
#if (ECUM_DEV_ERROR_DETECTION == STD_ON)

#endif /* (WDG_DEV_ERROR_DETECT == STD_ON) */
};
#endif /* #if (ECUM_DEINIT_API == STD_ON) */

/* --------- MainFunctions in Normal Mode -------- *
 * configuration of the 'Normal Mode'              *
 * Cycle 0 will trigger every time                 *
 * Trigger 0 is invalid                            *
 * e.g. cycle 10 allows trigger 1-10               */
/* DID YOU UPDATE *** ECUM_MAX_NUM_OF_MAIN_FUNC *** in EcuM_Cfg.h ??? */
static const Ecum_MainFuncConfigType ecum_mainFctCfgNormalMode_as[] =
{
//#if ! ((defined DEBUG_WATCHDOG_DISABLE) && (DEBUG_WATCHDOG_DISABLE == 1))
//   { &Wdg_Trigger, 2000, 2000 },
//#endif
   { &Al_Motor_MainFunction, 200, 20 },
   { &IIc_LcfgMainFunction, 20, 5}, //4
};
/* DID YOU UPDATE *** ECUM_MAX_NUM_OF_MAIN_FUNC *** in EcuM_Cfg.h */

/* DID YOU UPDATE *** ECUM_MAX_NUM_OF_MAIN_FUNC *** in EcuM.h ??? */
/* --------- MainFunctions in Sleep Mode --------- *
 * configuration of the 'Sleep Mode'               *
 * Cycle 0 will trigger every time                 *
 * Trigger 0 is invalid                            *
 * e.g. cycle 10 allows trigger 1-10               */
/* DID YOU UPDATE *** ECUM_MAX_NUM_OF_MAIN_FUNC *** in EcuM_cfg.h */
static const Ecum_MainFuncConfigType ecum_mainFctCfgSleepMode_as[] =
{
//#if ! ((defined DEBUG_WATCHDOG_DISABLE) && (DEBUG_WATCHDOG_DISABLE == 1))
//   { &Wdg_Trigger, 1, 1 },
//#endif
   { &Al_Motor_MainFunction, 1, 1 },
   { &IIc_LcfgMainFunction, 20, 5}

};
/* DID YOU UPDATE *** ECUM_MAX_NUM_OF_MAIN_FUNC *** in EcuM_Cfg.h */

const Ecum_ConfigType ecum_initialConfiguration_s =
{
   /* Used Timer channel */
   GPT_0_CHANNEL_1,
   /* Normal Mode configuration, also used for Production Mode */
   {
      /* Initial Timer Ticks */
      500,
      /* number of main functions used */
      (uint8)STD_NUMBER_OF_ELEMENTS(ecum_mainFctCfgNormalMode_as), /*lint !e866: Unusual use of '' in argument to sizeof */
      /* array of main functions and their timing information */
      &ecum_mainFctCfgNormalMode_as[0]
   },
   /* Sleep Mode configuration */
   {
      /* Initial Timer Ticks    */
      1000,
      /* number of main functions used */
      (uint8)STD_NUMBER_OF_ELEMENTS(ecum_mainFctCfgSleepMode_as), /*lint !e866: Unusual use of '' in argument to sizeof */
      /* array of main functions and their timing information */
      &ecum_mainFctCfgSleepMode_as[0]
   }
};

/* ***************************** modul global prototypes ******************** */

/* ***************************** global prototypes ************************** */

#pragma CONST_SEG DEFAULT
#pragma CODE_SEG DEFAULT

/* END */

