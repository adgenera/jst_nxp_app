#ifndef CDD_MOTOR_CFG_H
#define CDD_MOTOR_CFG_H

/* ***************************** includes < > ******************************* */


/* ***************************** includes " " ******************************* */
#include "Version.h"

#include <Gpt.h>

/* ***************************** typedefs *********************************** */


/* ***************************** # defines ********************************** */
#define CDD_MOTOR_VENDOR_ID        99  /**<\brief CoSyst VendorID */
#define CDD_MOTOR_CFG_AR_MAJOR_VERSION 3   /**<\brief AUTOSAR major version */
#define CDD_MOTOR_CFG_AR_MINOR_VERSION 1   /**<\brief AUTOSAR minor version */
#define CDD_MOTOR_CFG_AR_PATCH_VERSION 0   /**<\brief AUTOSAR patch version */
#define CDD_MOTOR_CFG_SW_MAJOR_VERSION 1   /**<\brief Software major version */
#define CDD_MOTOR_CFG_SW_MINOR_VERSION 0   /**<\brief Software minor version */
#define CDD_MOTOR_CFG_SW_PATCH_VERSION 0   /**<\brief Software patch version */


/* Module API configuration ************************************************* */
#define CDD_MOTOR_DEINIT_API              PROJECT_SETTINGS_GLOBAL_DEINIT_API
#define CDD_MOTOR_VERSION_INFO_API        PROJECT_SETTINGS_GLOBAL_VERSION_API

#define CDD_MOTOR_RUN_TO_POSITION_API           STD_ON
#define CDD_MOTOR_RUN_RELATIVE_API              STD_ON
#define CDD_MOTOR_GEAR_PLAY_COMPENSATION_API    STD_OFF

/*
* Description: Switches development error detection on/off.
* Range:       STD_ON:      enable Deveopment Error Detection
*              STD_OFF:     disable Deveopment Error Detection
* Example:
*/
#define CDD_MOTOR_DEV_ERROR_DETECT          PROJECT_SETTINGS_GLOBAL_DET_SWITCH

/* \brief */
#define CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE          48U
#define CDD_MOTOR_ZERO_DETECTION_MAXIMUM_SIZE     (CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE << 1)

#define CDD_MOTOR_NUMBER_OF_FULL_ROUNDS 36                                  /* Rounds for the fast pointer till zero detection reached */ // X10 : 72° = 36 rounds
#define CDD_MOTOR_RNDS_THRSH           180                                 /* Rounds for the fast pointer till zero detection reached */ // X10 : 12 * 60
#define CDD_MOTOR_RNDS_THRSH_HALF      90                                  /* Rounds for the fast pointer till zero detection reached */
#define CDD_MOTOR_MINIRNDS_THRSH       45

#define CDD_MOTOR_RNDS_THRSH_UI16      (uint16)CDD_MOTOR_RNDS_THRSH        /* Rounds for the fast pointer till zero detection reached */
#define CDD_MOTOR_RNDS_THRSH_HALF_UI16 (uint16)CDD_MOTOR_RNDS_THRSH_HALF   /* Rounds for the fast pointer till zero detection reached */
#define CDD_MOTOR_MINIRNDS_THRSH_UI16  (uint16)CDD_MOTOR_MINIRNDS_THRSH

#define CDD_MOTOR_RNDS_THRSH_SI16      (sint16)CDD_MOTOR_RNDS_THRSH        /* Rounds for the fast pointer till zero detection reached */
#define CDD_MOTOR_RNDS_THRSH_HALF_SI16 (sint16)CDD_MOTOR_RNDS_THRSH_HALF   /* Rounds for the fast pointer till zero detection reached */
#define CDD_MOTOR_MINIRNDS_THRSH_SI16  (sint16)CDD_MOTOR_MINIRNDS_THRSH

/* PWM duty cycle lookup tables ********************************************* */
#define CDD_MOTOR_MTRPWM___0_PERC_UI16        (uint16)0U
#define CDD_MOTOR_MTRPWM__10_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  1u) / 10u))   /*   10% = 1 / 10  */
#define CDD_MOTOR_MTRPWM__20_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  1u) /  5u))   /*   20% = 1 / 5   */
#define CDD_MOTOR_MTRPWM__30_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  3u) / 10u))   /*   30% = 3 / 10  */
#define CDD_MOTOR_MTRPWM__40_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  2u) /  5u))   /*   40% = 2 / 5   */
#define CDD_MOTOR_MTRPWM__50_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  1u) /  2u))   /*   50% = 1 / 2   */
#define CDD_MOTOR_MTRPWM__60_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  3u) /  5u))   /*   60% = 3 / 5   */
#define CDD_MOTOR_MTRPWM__70_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  7u) / 10u))   /*   70% = 7 / 10  */
#define CDD_MOTOR_MTRPWM__80_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  4u) /  5u))   /*   80% = 4 / 5   */
#define CDD_MOTOR_MTRPWM__85_PERC_UI16        ((uint16)((MTR_CTRL_MCPER * 17u) / 20u))   /*   85% = 17 / 20 */
#define CDD_MOTOR_MTRPWM__90_PERC_UI16        ((uint16)((MTR_CTRL_MCPER *  9u) / 10u))   /*   90% = 9 / 10  */
#define CDD_MOTOR_MTRPWM__95_PERC_UI16        ((uint16)((MTR_CTRL_MCPER * 19u) / 20u))   /*   95% = 19 / 20  */
#define CDD_MOTOR_MTRPWM_100_PERC_UI16        (uint16)MTR_CTRL_MCPER


#define CDD_MOTOR_PTT_BASE_REGISTER_UI16          (uint16)0x2C0

/** \b Description: Motor Controller Control Register 0
 * <br>\b  Range:
 * <br> \b Example:*/
#define CDD_MOTOR_PTT_DATA_REG_ADR_UI16      (CDD_MOTOR_PTT_BASE_REGISTER_UI16 + (uint16)0x0)
#define CDD_MOTOR_PTT_INPUT_REG_ADR_UI16     (CDD_MOTOR_PTT_BASE_REGISTER_UI16 + (uint16)0x1)
#define CDD_MOTOR_PTT_DATA_DIR_REG_ADR_UI16  (CDD_MOTOR_PTT_BASE_REGISTER_UI16 + (uint16)0x2)
#define CDD_MOTOR_PTT_PULL_EN_REG_ADR_UI16   (CDD_MOTOR_PTT_BASE_REGISTER_UI16 + (uint16)0x3)
#define CDD_MOTOR_PTT_POL_SEL_REG_ADR_UI16   (CDD_MOTOR_PTT_BASE_REGISTER_UI16 + (uint16)0x4)
#define CDD_MOTOR_PTT_IRQ_EN_REG_ADR_UI16    (CDD_MOTOR_PTT_BASE_REGISTER_UI16 + (uint16)0x6)
#define CDD_MOTOR_PTT_IRQ_FLAG_REG_ADR_UI16  (CDD_MOTOR_PTT_BASE_REGISTER_UI16 + (uint16)0x7)

#define CDD_MOTOR_PTF_DATA_REG_ADR_UI16      ((uint16)0x261U)
#define CDD_MOTOR_PTF_DATA_DIR_REG_ADR_UI16  ((uint16)0x265U)

#define CDD_MOTOR_PTT_GET(pos)     (((*((uint8 *)CDD_MOTOR_PTT_DATA_REG_ADR_UI16)) >> (pos)) & ((uint8)0x1u))
#define CDD_MOTOR_NO1_BITPOS_UI8        (uint8) 6u
#define CDD_MOTOR_NO2_BITPOS_UI8        (uint8) 7u

#define CDD_MOTOR_DISABLE_COIL0_MTR1()      MTR_DISABLE_CH1()
#define CDD_MOTOR_DISABLE_COIL1_MTR1()      MTR_DISABLE_CH2()
#define CDD_MOTOR_ENABLE_COIL0_MTR1()       MTR_ENABLE_CH1()
#define CDD_MOTOR_ENABLE_COIL1_MTR1()       MTR_ENABLE_CH2()
#define CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR1(dutyCycle_ui16)    MTR_SET_DUTYCYCLE_MTR1_COIL0(dutyCycle_ui16)
#define CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR1(dutyCycle_ui16)    MTR_SET_DUTYCYCLE_MTR1_COIL1(dutyCycle_ui16)

#define CDD_MOTOR_DISABLE_COIL0_MTR2()      MTR_DISABLE_CH3()
#define CDD_MOTOR_DISABLE_COIL1_MTR2()      MTR_DISABLE_CH4()
#define CDD_MOTOR_ENABLE_COIL0_MTR2()       MTR_ENABLE_CH3()
#define CDD_MOTOR_ENABLE_COIL1_MTR2()       MTR_ENABLE_CH4()
#define CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR2(dutyCycle_ui16)    MTR_SET_DUTYCYCLE_MTR2_COIL0(dutyCycle_ui16)
#define CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR2(dutyCycle_ui16)    MTR_SET_DUTYCYCLE_MTR2_COIL1(dutyCycle_ui16)

/* ***************************** enums ************************************** */

/* ***************************** structs ************************************ */

/* ***************************** global data ******************************** */

/* ***************************** modul global prototypes ******************** */

/* ***************************** global prototypes ************************** */
#endif /* CDD_MOTOR_CFG_H */
