/* ***************************** includes " " ******************************* */
#include "Version.h"

#include <Mtr.h>
#include "Cdd_Motor.h"
#include "Cdd_Motor_Cfg.h"

/* ***************************** # defines ********************************** */
/* Module configuration ***************************************************** */
#define CDD_MOTOR_SIGN_NEGATIVE_UI16            (uint16)0x8000U

/* ***************************** modul global data ************************** */
static const Mtr_ChannelDutyCycleType cdd_motor_MtrCoil_0_Pattern_Fast_t [CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE] =
{
   CDD_MOTOR_MTRPWM__70_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__80_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__85_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__90_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__95_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM_100_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__95_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__90_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__85_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__80_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__70_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__60_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__50_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__40_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__30_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__20_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__10_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM___0_PERC_UI16,
   CDD_MOTOR_MTRPWM__10_PERC_UI16,
   CDD_MOTOR_MTRPWM__20_PERC_UI16,
   CDD_MOTOR_MTRPWM__30_PERC_UI16,
   CDD_MOTOR_MTRPWM__40_PERC_UI16,
   CDD_MOTOR_MTRPWM__50_PERC_UI16,
   CDD_MOTOR_MTRPWM__60_PERC_UI16,
   CDD_MOTOR_MTRPWM__70_PERC_UI16,
   CDD_MOTOR_MTRPWM__80_PERC_UI16,
   CDD_MOTOR_MTRPWM__85_PERC_UI16,
   CDD_MOTOR_MTRPWM__90_PERC_UI16,
   CDD_MOTOR_MTRPWM__95_PERC_UI16,
   CDD_MOTOR_MTRPWM_100_PERC_UI16,
   CDD_MOTOR_MTRPWM__95_PERC_UI16,
   CDD_MOTOR_MTRPWM__90_PERC_UI16,
   CDD_MOTOR_MTRPWM__85_PERC_UI16,
   CDD_MOTOR_MTRPWM__80_PERC_UI16,
   CDD_MOTOR_MTRPWM__70_PERC_UI16,
   CDD_MOTOR_MTRPWM__60_PERC_UI16,
   CDD_MOTOR_MTRPWM__50_PERC_UI16,
   CDD_MOTOR_MTRPWM__40_PERC_UI16,
   CDD_MOTOR_MTRPWM__30_PERC_UI16,
   CDD_MOTOR_MTRPWM__20_PERC_UI16,
   CDD_MOTOR_MTRPWM__10_PERC_UI16,
   CDD_MOTOR_MTRPWM___0_PERC_UI16,
   CDD_MOTOR_MTRPWM__10_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__20_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__30_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__40_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__50_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__60_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
};

static const Mtr_ChannelDutyCycleType cdd_motor_MtrCoil_1_Pattern_Fast_t [CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE] =
{
   CDD_MOTOR_MTRPWM__70_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__60_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__50_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__40_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__30_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__20_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__10_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM___0_PERC_UI16,
   CDD_MOTOR_MTRPWM__10_PERC_UI16,
   CDD_MOTOR_MTRPWM__20_PERC_UI16,
   CDD_MOTOR_MTRPWM__30_PERC_UI16,
   CDD_MOTOR_MTRPWM__40_PERC_UI16,
   CDD_MOTOR_MTRPWM__50_PERC_UI16,
   CDD_MOTOR_MTRPWM__60_PERC_UI16,
   CDD_MOTOR_MTRPWM__70_PERC_UI16,
   CDD_MOTOR_MTRPWM__80_PERC_UI16,
   CDD_MOTOR_MTRPWM__85_PERC_UI16,
   CDD_MOTOR_MTRPWM__90_PERC_UI16,
   CDD_MOTOR_MTRPWM__95_PERC_UI16,
   CDD_MOTOR_MTRPWM_100_PERC_UI16,
   CDD_MOTOR_MTRPWM__95_PERC_UI16,
   CDD_MOTOR_MTRPWM__90_PERC_UI16,
   CDD_MOTOR_MTRPWM__85_PERC_UI16,
   CDD_MOTOR_MTRPWM__80_PERC_UI16,
   CDD_MOTOR_MTRPWM__70_PERC_UI16,
   CDD_MOTOR_MTRPWM__60_PERC_UI16,
   CDD_MOTOR_MTRPWM__50_PERC_UI16,
   CDD_MOTOR_MTRPWM__40_PERC_UI16,
   CDD_MOTOR_MTRPWM__30_PERC_UI16,
   CDD_MOTOR_MTRPWM__20_PERC_UI16,
   CDD_MOTOR_MTRPWM__10_PERC_UI16,
   CDD_MOTOR_MTRPWM___0_PERC_UI16,
   CDD_MOTOR_MTRPWM__10_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__20_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__30_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__40_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__50_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__60_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__70_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__80_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__85_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__90_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__95_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM_100_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__95_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__90_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__85_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
   CDD_MOTOR_MTRPWM__80_PERC_UI16 | CDD_MOTOR_SIGN_NEGATIVE_UI16, /* negative sign */
};

const Cdd_Motor_MotorConfigType Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_NR_SIZE] =
{
   {
	MTR_MTR1_COIL0_CHANNEL_0,                    /* channelCoil_0_ui8 */
	MTR_MTR1_COIL1_CHANNEL_1,                    /* channelCoil_1_ui8 */

	(uint32)CDD_MOTOR_RNDS_THRSH * (uint32)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE,                   /* miniFullRoundsThreshold_ui16 */
	(uint32)CDD_MOTOR_RNDS_THRSH * (uint32)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE,                   /* fullRoundsThreshold_ui16 */
	
	cdd_motor_MtrCoil_0_Pattern_Fast_t,    /* coil PWM lookup table */
	cdd_motor_MtrCoil_1_Pattern_Fast_t,    /* coil PWM lookup table */
	
	cdd_motor_MtrCoil_0_Pattern_Fast_t,    /* coil PWM lookup table */
	cdd_motor_MtrCoil_1_Pattern_Fast_t,    /* coil PWM lookup table */
   },
   {
	MTR_MTR2_COIL0_CHANNEL_2,                    /* channelCoil_0_ui8 */
	MTR_MTR2_COIL1_CHANNEL_3,                    /* channelCoil_1_ui8 */

	(uint32)CDD_MOTOR_RNDS_THRSH * (uint32)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE,                   /* miniFullRoundsThreshold_ui16 */
	(uint32)CDD_MOTOR_RNDS_THRSH * (uint32)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE,                   /* fullRoundsThreshold_ui16 */
	
	cdd_motor_MtrCoil_0_Pattern_Fast_t,    /* coil PWM lookup table */
	cdd_motor_MtrCoil_1_Pattern_Fast_t,    /* coil PWM lookup table */
	
	cdd_motor_MtrCoil_0_Pattern_Fast_t,    /* coil PWM lookup table */
	cdd_motor_MtrCoil_1_Pattern_Fast_t,    /* coil PWM lookup table */
   }
};


/* ***************************** global data ******************************** */

/* ***************************** modul global functions ********************* */

/* ***************************** global functions *************************** */
