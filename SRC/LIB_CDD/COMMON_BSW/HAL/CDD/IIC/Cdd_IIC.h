/*
 * Cdd_IIC.h
 *
 *  Created on: Jul 22, 2024
 *      Author: Andrea Cencio
 */

#ifndef CDD_IIC_H_
#define CDD_IIC_H_

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Version.h"
#include "IIC0.h"
#include "IIC0_Cfg.h"
#include "Cdd_Motor.h"
#include "Platform_Types.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config #defines ----------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user/config enums -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- user function prototypes ------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void Cdd_IIC_Init(void);

void Cdd_IIC_MainFunction(void);

uint16 Cdd_IIC_Get_Pos_HHSS(void); // STEPPER MOTOR M1C POSITION ON MCU2, STEPPER MOTOR M1A POSITION ON MCU3
uint16 Cdd_IIC_Get_Pos_MM(void); // STEPPER MOTOR M1B POSITION ON MCU2

void Cdd_IIC_Set_Pos_HHSS(uint16 value); // STEPPER MOTOR M1C POSITION ON MCU2, STEPPER MOTOR M1A POSITION ON MCU3
void Cdd_IIC_Set_Pos_MM(uint16 value); // STEPPER MOTOR M1B POSITION ON MCU2

sint16 Cdd_IIC_Get_Speed_HHSS_si16(void); // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
sint16 Cdd_IIC_Get_Speed_MM_si16(void); // STEPPER MOTOR M1B SPEED ON MCU2
sint16 Cdd_IIC_Get_Speed_si16(const Cdd_Motor_MotorNumberEnum motor_e); // STEPPER MOTOR SPEED, BASED on MOTOR

uint16 Cdd_IIC_Get_Speed_HHSS_ui16(void); // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
uint16 Cdd_IIC_Get_Speed_MM_ui16(void); // STEPPER MOTOR M1B SPEED ON MCU2
uint16 Cdd_IIC_Get_Speed_ui16(const Cdd_Motor_MotorNumberEnum motor_e); // STEPPER MOTOR SPEED, BASED on MOTOR

uint8 Cdd_IIC_Get_Sign_Speed_HHSS_ui8(void); // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
uint8 Cdd_IIC_Get_Sign_Speed_MM_ui8(void); // STEPPER MOTOR M1B SPEED ON MCU2
uint8 Cdd_IIC_Get_Sign_Speed_ui8(const Cdd_Motor_MotorNumberEnum motor_e); // STEPPER MOTOR SIGN SPEED, BASED on MOTOR 

uint16 Cdd_IIC_Get_Module_Speed_HHSS_ui16(void); // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
uint16 Cdd_IIC_Get_Module_Speed_MM_ui16(void); // STEPPER MOTOR M1B SPEED ON MCU2
uint16 Cdd_IIC_Get_Module_Speed_ui16(const Cdd_Motor_MotorNumberEnum motor_e); // STEPPER MOTOR MODULE SPEED, BASED on MOTOR 

void Cdd_IIC_Set_Speed_HHSS(uint16 value); // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
void Cdd_IIC_Set_Speed_MM(uint16 value); // STEPPER MOTOR M1B SPEED ON MCU2

#endif /* CDD_IIC_H_ */
