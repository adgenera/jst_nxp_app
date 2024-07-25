#ifndef PROJECT_SETTINGS_DEVEL_H
#define PROJECT_SETTINGS_DEVEL_H

#if ((defined DEBUG_DEVELOPMENT) && (DEBUG_DEVELOPMENT == 1))
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <Std_Types.h>

#ifndef PROJECT_SETTINGS_DEVEL_INFO_MSG
#define PROJECT_SETTINGS_DEVEL_INFO_MSG
#pragma message("Using project settings DEVELOPMENT")
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define PROJECT_SETTINGS_INSTANCE_ID           (1)  /* Instance id */
#define PROJECT_SETTINGS_SW_MAJOR_VERSION      (0)  /* Software major version */
#define PROJECT_SETTINGS_SW_MINOR_VERSION      (0)  /* Software minor version */
#define PROJECT_SETTINGS_SW_PATCH_VERSION      (1)  /* Software patch version */

/*
* Description: Switch for enable/disable development error detection in project.
* Range:       STD_ON:      global enable of DET
*              STD_OFF:     global disable of DET
* Example:
*/
#define PROJECT_SETTINGS_GLOBAL_VERSION_API                   (STD_OFF)
#define PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API              (STD_OFF)

#define PROJECT_SETTINGS_GLOBAL_DEINIT_API                    (STD_OFF)
#define PROJECT_SETTINGS_GLOBAL_DET_SWITCH                    (STD_ON)

#if (PROJECT_SETTINGS_GLOBAL_DET_SWITCH == STD_ON)
#undef PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API
#define PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API              (STD_ON)
#endif

#define SYSTEM_BUILD_TYPE                       SYSTEM_BUILD_TYPE_DEBUG

#define DEBUG_LIN_SLEEP_MODE_DISABLE            0
#define DEBUG_MCU_STOP_MODE_DISABLE             0
#define DEBUG_WATCHDOG_DISABLE                  0
#define TEST_ERRORHANDLER_ENABLED               0
#define TEST_ERRORHANDLER_1_ZERODETECTION       0
#define TEST_ERRORHANDLER_3_ALUFAIL             0
#define TEST_ERRORHANDLER_5_WDGTRIGGER_FAIL     0
#define TEST_ERRORHANDLER_6_ECUM                0
#define TEST_ERRORHANDLER_7_APP_CTRL            0
#define TEST_ERRORHANDLER_9_RAMERROR            0
#define TEST_ERRORHANDLER_10_ILLEGALADDR        0
#define TEST_UNITTEST_ACTIVE                    0
#define DEVICE_SECURED_DISABLED                 1
#define TEST_MEASURE_STACKUSAGE_ENABLED         0

#define USE_TESTHANDLE (((defined TEST_UNITTEST_ACTIVE) && (TEST_UNITTEST_ACTIVE == 1)) || ((defined TEST_MEASURE_STACKUSAGE_ENABLED) && (TEST_MEASURE_STACKUSAGE_ENABLED == 1)))

/*
* Description: Switch for enable/disable time measurement in project.
*/
#define PROJECT_TIME_MEASUREMENT_SWITCH                        (STD_OFF)

/*
* Description: Switch for enable/disable load measurement in project.
*/
#define PROJECT_SETTINGS_LOAD_MEASUREMENT_SWITCH              (STD_OFF)

/*
* Description: Some Modules are used in application and bootloader. But some functions need to be custumized by compiler switch for use in bootloader.
* Range:       STD_ON:      for use of modules in bootloader
*              STD_OFF:     for use of modules in application
* Example:
*/
#define PROJECT_SETTINGS_BOOTLOADER_BEHAVIOR                  (STD_OFF)

/*
 * UDS Read Memory by Address service allows for arbitrary memory read access. It should
 * only be enabled in development builds.
 */
#define PROJECT_SETTINGS_RMBA_SWITCH                          (STD_ON)

/*
* Description: Defines System Clock in HZ
*/
#define SYSTEM_CLOCK_HZ_UI32                                  ((uint32)80000000U)

/*
 * Description: Defines the System Bus Clock
 */
#define BUSCLOCK_HZ_UI32									  ((uint32) 32000000u)

#endif /* ((!defined DEBUG_DEVELOPMENT) && (DEBUG_DEVELOPMENT != 1)) */
#endif /* PROJECT_SETTINGS_DEVEL_H */
