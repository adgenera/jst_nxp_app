/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- includes " " ------------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "Cdd_IIC.h"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module #defines ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #makros --------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* version check */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal #defines -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define SPEED_SIGN_MASK 	0b0000001000000000
#define SPEED_SIGN_POS		9U
#define SPEED_MODULE_MASK 	0b0000000111111111

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal typedefs  ------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal enums  ---------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- internal structs  -------------------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config internal data (const) --------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static uint16 Cdd_IIC_Pos_HHSS_ui16;
static uint16 Cdd_IIC_Pos_MM_ui16;
static sint16 Cdd_IIC_Speed_HHSS_si16;
static sint16 Cdd_IIC_Speed_MM_si16;
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global data (Userdata) (const) ------------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- config function (internal use only)--------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- module internal functions (static) --------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
static sint16 convert_speed_to_signed(uint16 val) {
	// Extract the sign bit (1st bit from the left, i.e., bit Speed-9)
	uint8 sign = (uint8) ((val & SPEED_SIGN_MASK) >> SPEED_SIGN_POS);
	// Extract the 9-bit module (bits Speed-8 to Speed-0)
	uint16 module = val & SPEED_MODULE_MASK;
	// Prepare the result signed variable
	int result = (sint16) module;

	// Apply the sign. If sign bit is 1, negate the module
	if (sign) {
		result = -result;
	}

	return result;
}

static uint16 convert_speed_to_unsigned(sint16 val) {
	// Extract the sign bit (1st bit from the left, i.e., bit Speed-9)
	uint8 sign = val < 0 ? 1 : 0;
	// Prepare the result unsigned variable
	uint16 result = 0;

	// Apply the sign. If sign bit is 1, set the sign bit
	if (sign) {
		// Extract the 9-bit module (bits Speed-8 to Speed-0)
		result = (uint16) (~val & SPEED_MODULE_MASK) + 1;
		result |= SPEED_SIGN_MASK;
	}
	else {
		// Extract the 9-bit module (bits Speed-8 to Speed-0)
		result = (uint16) (val & SPEED_MODULE_MASK);
	}

	return result;
}

static uint8 extract_sign_speed(sint16 val) {
	// Extract the sign bit (1st bit from the left, i.e., bit Speed-9)
	uint8 result = val < 0 ? 1 : 0;

	return result;
}

static uint16 extract_module_speed(sint16 val) {
	// Extract the sign bit (1st bit from the left, i.e., bit Speed-9)
	uint8 sign = val < 0 ? 1 : 0;
	// Prepare the result unsigned variable
	uint16 result = 0;

	// Apply the sign. If sign bit is 1, set the sign bit
	if (sign) {
		// Extract the 9-bit module with sign negative (bits Speed-8 to Speed-0)
		result = (uint16) (~val & SPEED_MODULE_MASK) + 1;
	}
	else {
		// Extract the 9-bit module with sign positive (bits Speed-8 to Speed-0)
		result = (uint16) (val & SPEED_MODULE_MASK);
	}

	return result;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* ------------------------------------------------------------------- global functions (Userfunctions) ----------------------------------------------------- */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/**
 * \brief Function Initialise internal variables of the IIC Interface.
 *        Variables are Initialized with their Init Values.
 */
void Cdd_IIC_Init(void) {
	Cdd_IIC_Pos_HHSS_ui16 = 0;
	Cdd_IIC_Pos_MM_ui16 = 0;
	Cdd_IIC_Speed_HHSS_si16 = 0;
	Cdd_IIC_Speed_MM_si16 = 0;
	return;
}

/**
 * \brief MainFunction of IIC Interface. It is called cyclic by the EcuM to extract Signals from Messages.
 * There is also a timeout handling to serve default values in case of a timeout of that message
 *
 */
void Cdd_IIC_MainFunction(void) {

}

/**
 * \brief Getter Function for Signal Cdd_IIC_Pos_HHSS
 *
 * \return Value of Signal Cdd_IIC_Pos_HHSS
 */
uint16 Cdd_IIC_Get_Pos_HHSS(void) {
	return (Cdd_IIC_Pos_HHSS_ui16);
}

/**
 * \brief Getter Function for Signal Cdd_IIC_Pos_MM
 *
 * \return Value of Signal Cdd_IIC_Pos_MM
 */
uint16 Cdd_IIC_Get_Pos_MM(void) {
	return (Cdd_IIC_Pos_MM_ui16);
}

/**
 * \brief Setter Function for Signal Cdd_IIC_Pos_HHSS
 *
 * \return void
 */
void Cdd_IIC_Set_Pos_HHSS(uint16 value) {
	Cdd_IIC_Pos_HHSS_ui16 = value;
}

/**
 * \brief Setter Function for Signal Cdd_IIC_Pos_MM
 *
 * \return void
 */
void Cdd_IIC_Set_Pos_MM(uint16 value) {
	Cdd_IIC_Pos_MM_ui16 = value;
}

/**
 * \brief Getter Function for Signal Cdd_IIC_Speed_HHSS
 *
 * \return Value of Signal Cdd_IIC_Speed_HHSS in signed version
 */
sint16 Cdd_IIC_Get_Speed_HHSS_si16(void) // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
{
	return Cdd_IIC_Speed_HHSS_si16;
}

/**
 * \brief Getter Function for Signal Cdd_IIC_Speed_MM
 *
 * \return Value of Signal Cdd_IIC_Speed_MM in signed version
 */
sint16 Cdd_IIC_Get_Speed_MM_si16(void) // STEPPER MOTOR M1B SPEED ON MCU2
{
	return Cdd_IIC_Speed_MM_si16;
}

/**
 * \brief Getter Function for Signal Cdd_IIC_Speed, based on motor number
 *
 * \return Value of Signal Cdd_IIC_Speed in signed version
 */
sint16 Cdd_IIC_Get_Speed_si16(const Cdd_Motor_MotorNumberEnum motor_e) {
	if (CDD_MOTOR_MTR_HHSS == motor_e) {
		return Cdd_IIC_Get_Speed_HHSS_si16();
	} else if (CDD_MOTOR_MTR_MM == motor_e) {
		return Cdd_IIC_Get_Speed_MM_si16();
	} else {
		return 0;
	}
}

/**
 * \brief Getter Function for Signal Cdd_IIC_Speed_HHSS, unsigned value;
 *
 * \return Value of Signal Cdd_IIC_Speed_HHSS in unsigned version
 */
uint16 Cdd_IIC_Get_Speed_HHSS_ui16(void) // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
{
	return convert_speed_to_unsigned(Cdd_IIC_Speed_HHSS_si16);
}

/**
 * \brief Getter Function for Signal Cdd_IIC_Speed_MM
 *
 * \return Value of Signal Cdd_IIC_Speed_MM in unsigned version
 */
uint16 Cdd_IIC_Get_Speed_MM_ui16(void) // STEPPER MOTOR M1B SPEED ON MCU2
{
	return convert_speed_to_unsigned(Cdd_IIC_Speed_MM_si16);
}

/**
 * \brief Getter Function for Signal Cdd_IIC_Speed, based on motor number
 *
 * \return Value of Signal Cdd_IIC_Speed in unsigned version
 */
uint16 Cdd_IIC_Get_Speed_ui16(const Cdd_Motor_MotorNumberEnum motor_e) {
	if (CDD_MOTOR_MTR_HHSS == motor_e) {
		return Cdd_IIC_Get_Speed_HHSS_ui16();
	} else if (CDD_MOTOR_MTR_MM == motor_e) {
		return Cdd_IIC_Get_Speed_MM_ui16();
	} else {
		return 0;
	}
}

/**
 * \brief Getter Function for Sign Signal Cdd_IIC_Speed_HHSS, unsigned value;
 *
 * \return Value of Sign Signal Cdd_IIC_Speed_HHSS in unsigned version
 */
uint8 Cdd_IIC_Get_Sign_Speed_HHSS_ui8(void) // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
{
	return extract_sign_speed(Cdd_IIC_Speed_HHSS_si16);
}

/**
 * \brief Getter Function for Sign Signal Cdd_IIC_Speed_MM
 *
 * \return Value of Sign Signal Cdd_IIC_Speed_MM in unsigned version
 */
uint8 Cdd_IIC_Get_Sign_Speed_MM_ui8(void) // STEPPER MOTOR M1B SPEED ON MCU2
{
	return extract_sign_speed(Cdd_IIC_Speed_MM_si16);
}

/**
 * \brief Getter Function for Sign Signal Cdd_IIC_Speed, based on motor number
 *
 * \return Value of Sign Signal Cdd_IIC_Speed in unsigned version
 */
uint8 Cdd_IIC_Get_Sign_Speed_ui8(const Cdd_Motor_MotorNumberEnum motor_e) {
	if (CDD_MOTOR_MTR_HHSS == motor_e) {
		return Cdd_IIC_Get_Sign_Speed_HHSS_ui8();
	} else if (CDD_MOTOR_MTR_MM == motor_e) {
		return Cdd_IIC_Get_Sign_Speed_MM_ui8();
	} else {
		return 0;
	}
}

/**
 * \brief Getter Function for Module Signal Cdd_IIC_Speed_HHSS, unsigned value;
 *
 * \return Value of Module Signal Cdd_IIC_Speed_HHSS in unsigned version
 */
uint16 Cdd_IIC_Get_Module_Speed_HHSS_ui16(void) // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
{
	return extract_module_speed(Cdd_IIC_Speed_HHSS_si16);
}

/**
 * \brief Getter Function for Module Signal Cdd_IIC_Speed_MM
 *
 * \return Value of Module Signal Cdd_IIC_Speed_MM in unsigned version
 */
uint16 Cdd_IIC_Get_Module_Speed_MM_ui16(void) // STEPPER MOTOR M1B SPEED ON MCU2
{
	return extract_module_speed(Cdd_IIC_Speed_MM_si16);
}

/**
 * \brief Getter Function for Module Signal Cdd_IIC_Speed, based on motor number
 *
 * \return Value of Module Signal Cdd_IIC_Speed in unsigned version
 */
uint16 Cdd_IIC_Get_Module_Speed_ui16(const Cdd_Motor_MotorNumberEnum motor_e) {
	if (CDD_MOTOR_MTR_HHSS == motor_e) {
		return Cdd_IIC_Get_Module_Speed_HHSS_ui16();
	} else if (CDD_MOTOR_MTR_MM == motor_e) {
		return Cdd_IIC_Get_Module_Speed_MM_ui16();
	} else {
		return 0;
	}
}

/**
 * \brief Setter Function for Signal Cdd_IIC_Speed_HHSS
 *
 * \return void
 */
void Cdd_IIC_Set_Speed_HHSS(uint16 value) // STEPPER MOTOR M1C SPEED ON MCU2, STEPPER MOTOR M1A SPEED ON MCU3
{
	Cdd_IIC_Speed_HHSS_si16 = convert_speed_to_signed(value);
}

/**
 * \brief Setter Function for Signal Cdd_IIC_Speed_MM
 *
 * \return void
 */
void Cdd_IIC_Set_Speed_MM(uint16 value) // STEPPER MOTOR M1B SPEED ON MCU2
{
	Cdd_IIC_Speed_MM_si16 = convert_speed_to_signed(value);
}
