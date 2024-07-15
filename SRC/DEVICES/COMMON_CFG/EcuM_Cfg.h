#ifndef ECUM_CFG_H
#define ECUM_CFG_H

#include "Version.h"

/* ***************************** typedefs *********************************** */

/* ***************************** # defines ********************************** */
#define ECUM_DEV_ERROR_DETECTION    PROJECT_SETTINGS_GLOBAL_DET_SWITCH   /**<\brief Switch "Development Error Detection" on/off */
#define ECUM_VERSION_INFO_API       PROJECT_SETTINGS_GLOBAL_VERSION_API  /**<\brief Switch function "Ecum_GetVersionInfo()" on/off */
#define ECUM_DEINIT_API             PROJECT_SETTINGS_GLOBAL_DEINIT_API  /**<\brief Switch function "Ecum_DeInit()" on/off */

#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
#define ECUM_MAX_NUM_OF_MAIN_FUNC_DEFAULT   17u                  /**<\brief  default max number of MainFunctions that could be called*/
#elif (DEVICE_TYPE == DEVICE_COMPASS)
#define ECUM_MAX_NUM_OF_MAIN_FUNC_DEFAULT   15u                  /**<\brief  default max number of MainFunctions that could be called*/
#elif (DEVICE_TYPE == DEVICE_OAT)
#define ECUM_MAX_NUM_OF_MAIN_FUNC_DEFAULT   17u                  /**<\brief  default max number of MainFunctions that could be called*/
#elif (DEVICE_TYPE == DEVICE_STOPWATCH)
#define ECUM_MAX_NUM_OF_MAIN_FUNC_DEFAULT   19u                  /**<\brief  default max number of MainFunctions that could be called*/
#endif

#define ECUM_MAX_NUM_OF_MAIN_FUNC   ECUM_MAX_NUM_OF_MAIN_FUNC_DEFAULT                  /**<\brief  max number of MainFunctions that could be called*/

#define ECUM_TIMER_OVERFLOW_VALUE (0xFFFFu) /**<\brief max value of 16bit timer before an overflow occurs */

#define ECUM_C_DI_WAKE              C_DI_WAKE         /**<\brief  route to wake pin in DIO module */
#define ECUM_C_DO_SELFHOLD          C_DO_SELFHOLD     /**<\brief  route to self hold pin in DIO module */
#define ECUM_C_DI_CAL_REQUEST       C_DI_CAL_REQUEST  /**<\brief  route to calibration pin in DIO module */

#define ECUM_CFG_NORMAL_AL_ILLUM_MF_PERIOD_UI16      (uint16)140u /**<\brief  call Period of Al_Illum_Mainfunction */

#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
#define ECUM_CFG_NORMAL_AL_ILLUM_MF_CALL_TIME_UI16   (uint16)2u   /**<\brief  call trigger of Al_Illum_Mainfunction */
#elif (DEVICE_TYPE == DEVICE_COMPASS)
#define ECUM_CFG_NORMAL_AL_ILLUM_MF_CALL_TIME_UI16   (uint16)121u /**<\brief  call trigger of Al_Illum_Mainfunction */
#elif (DEVICE_TYPE == DEVICE_OAT)
#define ECUM_CFG_NORMAL_AL_ILLUM_MF_CALL_TIME_UI16   (uint16)139u /**<\brief  call trigger of Al_Illum_Mainfunction */
#elif (DEVICE_TYPE == DEVICE_STOPWATCH)
#define ECUM_CFG_NORMAL_AL_ILLUM_MF_CALL_TIME_UI16   (uint16)121u /**<\brief  call trigger of Al_Illum_Mainfunction */
#endif

#endif /* ECUM_CFG_H */
