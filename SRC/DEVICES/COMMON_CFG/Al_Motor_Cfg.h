#ifndef AL_MOTOR_CFG_H
#define AL_MOTOR_CFG_H

/* ***************************** includes " " ******************************* */
#include "Version.h"

/* ***************************** typedefs *********************************** */
/* ***************************** # defines ********************************** */

/* Module API configuration ************************************************* */
#define AL_MOTOR_VERSION_INFO_API         PROJECT_SETTINGS_GLOBAL_VERSION_API
#define AL_MOTOR_DEINIT_API               PROJECT_SETTINGS_GLOBAL_DEINIT_API
#define AL_MOTOR_MODULE_STATE_API         PROJECT_SETTINGS_GLOBAL_MODULE_STATE_API


/*
* Description: Switches development error detection on/off.
* Range:       STD_ON:      enable Deveopment Error Detection
*              STD_OFF:     disable Deveopment Error Detection
* Example:
*/
#define AL_MOTOR_DEV_ERROR_DETECT          PROJECT_SETTINGS_GLOBAL_DET_SWITCH

#define AL_MOTOR_STATECALIB_FIRSTBACK_UI16         (uint16)60
#define AL_MOTOR_STATECALIB_FIRSTFWD_UI16          (uint16)240
#define AL_MOTOR_STATECALIB_FIRSTCP_UI16           (uint16)180
#define AL_MOTOR_STATECALIB_ENDPOS                 (uint16)120

#define AL_MOTOR_SLOWDOWN_FAC_CALIBRATION      CDD_MOTOR_SPEED_1000US
#define AL_MOTOR_SLOWDOWN_FAC_RUN              CDD_MOTOR_SPEED_1000US
#define AL_MOTOR_SLOWDOWN_FAC_SLEEP            CDD_MOTOR_SPEED_1000US
#define AL_MOTOR_SLOWDOWN_FAC_PRODUCTION       CDD_MOTOR_SPEED_1000US
#define AL_MOTOR_SLOWDOWN_FAC_STELLTEST        CDD_MOTOR_SPEED_1000US
#define AL_MOTOR_SLOWDOWN_FAC_EXCEPTION        CDD_MOTOR_SPEED_1000US
#define AL_MOTOR_SLOWDOWN_FAC_SHUTDOWN         CDD_MOTOR_SPEED_1000US

/* ############################################################################################## */
#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
#define AL_MOTOR_DEF_FULL_STEP_COUNTER_CALIBRATION              CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE
#define AL_MOTOR_DEF_FULL_STEP_COUNTER_RUN                      CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE
#define AL_MOTOR_DEF_FULL_STEP_COUNTER_SLEEP                    CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE
#define AL_MOTOR_DEF_FULL_STEP_COUNTER_PRODUCTION               CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE
#define AL_MOTOR_DEF_FULL_STEP_COUNTER_STELLTEST                CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE
#define AL_MOTOR_DEF_FULL_STEP_COUNTER_EXCEPTION                CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE
#define AL_MOTOR_DEF_FULL_STEP_COUNTER_SHUTDOWN                 CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE
/* ############################################################################################## */
#else
#error "Unconfigured device"
#endif
/* ############################################################################################## */


/* ############################################################################################## */
#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
#define AL_MOTOR_STEPMODE_CALIBRATION                          CDD_MOTOR_STEPMODE_MICRO_FAST
#define AL_MOTOR_STEPMODE_RUN                                  CDD_MOTOR_STEPMODE_MICRO_FAST
#define AL_MOTOR_STEPMODE_SLEEP                                CDD_MOTOR_STEPMODE_MICRO_FAST
#define AL_MOTOR_STEPMODE_PRODUCTION_REQUEST                   CDD_MOTOR_STEPMODE_MICRO_FAST
#define AL_MOTOR_STEPMODE_PRODUCTION                           CDD_MOTOR_STEPMODE_STOP
#define AL_MOTOR_STEPMODE_STELLTEST                            CDD_MOTOR_STEPMODE_MICRO_FAST
#define AL_MOTOR_STEPMODE_EXCEPTION                            CDD_MOTOR_STEPMODE_STOP
#define AL_MOTOR_STEPMODE_SHUTDOWN                             CDD_MOTOR_STEPMODE_STOP
/* ############################################################################################## */
#else
#error "Unconfigured device"
#endif
/* ############################################################################################## */


/* ############################################################################################## */
#if (DEVICE_TYPE == DEVICE_CENTRAL_DISPLAY)
#define AL_MOTOR_STELLTEST_POSITION_TOP                     0
#define AL_MOTOR_STELLTEST_POSITION_TOP_LEFT_DELTA          0
#define AL_MOTOR_STELLTEST_POSITION_TOP_RIGHT_DELTA         360
/* ############################################################################################## */
#else
#error "Unconfigured device"
#endif
/* ############################################################################################## */

/* Module configuration ***************************************************** */


/* PWM duty cycle lookup tables ********************************************* */


/* ***************************** enums ************************************** */


/* ***************************** structs ************************************ */


/* ***************************** global data ******************************** */


/* ***************************** modul global prototypes ******************** */


/* ***************************** global prototypes ************************** */
#endif /* AL_MOTOR_CFG_H */
