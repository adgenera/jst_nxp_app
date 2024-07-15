#ifndef AL_MOTORPOS_H
#define AL_MOTORPOS_H

/* ***************************** includes < > ******************************* */

/* ***************************** includes " " ******************************* */
#include "Version.h"

#include "Cdd_Motor.h"

/* ***************************** typedefs *********************************** */

/* ***************************** # defines ********************************** */

#define AL_MOTORPOS_GEAR_FACTOR                       1u //CENTRAL DISPLAY
#define AL_MOTORPOS_GEAR_DIVISOR                      2u //CENTRAL DISPLAY

#define AL_MOTORPOS_MICROSTEPS_PER_ROUND_UI16         ((uint16)(CDD_MOTOR_RNDS_THRSH_UI16 * CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE))
#define AL_MOTORPOS_HALF_FULLROUND_MICROSTEPS_UI16    (AL_MOTORPOS_MICROSTEPS_PER_ROUND_UI16 >> (uint16)1u) /*AL_MOTORPOS_MICROSTEPS_PER_ROUND_UI16 / 2 */

#define AL_MOTORPOS_EPSILON                           9u

/* ***************************** enums ************************************** */

/* ***************************** structs ************************************ */


/* ***************************** global data ******************************** */

/* ***************************** modul global prototypes ******************** */

/* ***************************** global prototypes ************************** */
boolean Al_MotorPos_Calculate (const Cdd_Motor_MotorNumberEnum motor_e, Cdd_Motor_DirectionEnum * destDir_e, uint32 * destUSteps_ui32);

#endif /* AL_MOTORPOS_H */

