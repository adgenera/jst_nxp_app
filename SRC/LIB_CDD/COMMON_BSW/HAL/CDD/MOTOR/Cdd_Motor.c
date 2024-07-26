#include <Mtr.h>

#include <Dio.h>
#include <Gpt.h>

#include "Version.h"

#include "Cdd_Motor.h"
#include "Cdd_Motor_Cfg.h"

/* ***************************** # defines ********************************** */
#define CDD_MOTOR_VENDOR_ID_C 99	   /**<\brief CoSyst VendorID */
#define CDD_MOTOR_AR_MAJOR_VERSION_C 3 /**<\brief AUTOSAR major version */
#define CDD_MOTOR_AR_MINOR_VERSION_C 1 /**<\brief AUTOSAR minor version */
#define CDD_MOTOR_AR_PATCH_VERSION_C 0 /**<\brief AUTOSAR patch version */
#define CDD_MOTOR_SW_MAJOR_VERSION_C 1 /**<\brief SW major version */
#define CDD_MOTOR_SW_MINOR_VERSION_C 1 /**<\brief SW minor version */
#define CDD_MOTOR_SW_PATCH_VERSION_C 0 /**<\brief SW patch version */

/* version check */
#if (CDD_MOTOR_VENDOR_ID_C != CDD_MOTOR_VENDOR_ID)
#error "Cdd_Motor.c and Cdd_Motor.h have different vendor ids."
#endif /* CDD_MOTOR_VENDOR_ID_C != CDD_MOTOR_VENDOR_ID */

#if ((CDD_MOTOR_AR_MAJOR_VERSION_C != CDD_MOTOR_AR_MAJOR_VERSION) || \
	 (CDD_MOTOR_AR_MINOR_VERSION_C != CDD_MOTOR_AR_MINOR_VERSION) || \
	 (CDD_MOTOR_AR_PATCH_VERSION_C != CDD_MOTOR_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Cdd_Motor.c and Cdd_Motor.h are different."
#endif /* (CDD_MOTOR_AR_MAJOR_VERSION_C != CDD_MOTOR_AR_MAJOR_VERSION) || ... */

#if ((CDD_MOTOR_SW_MAJOR_VERSION_C != CDD_MOTOR_SW_MAJOR_VERSION) || \
	 (CDD_MOTOR_SW_MINOR_VERSION_C != CDD_MOTOR_SW_MINOR_VERSION) || \
	 (CDD_MOTOR_SW_PATCH_VERSION_C != CDD_MOTOR_SW_PATCH_VERSION))
#error "Software Version Numbers of Cdd_Motor.c and Cdd_Motor.h are different."
#endif /* (CDD_MOTOR_SW_MAJOR_VERSION_C != CDD_MOTOR_SW_MAJOR_VERSION) || ... */

/* ***************************** module global data ************************** */
#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
/* \brief Cdd Motor module state */
static Std_ModuleStatusReturnType cdd_motor_moduleState_e = MODULE_UNINIT;
#endif

/* \brief Motor runtime data*/
// static Cdd_Motor_RunTimeDataType cdd_motor_Data_t;
static Cdd_Motor_RunTimeDataType cdd_motor_Data_as[CDD_MOTOR_MTR_NR_SIZE];

/* \brief Motor zero detection information*/
// static Cdd_Motor_ZeroDetectionType cdd_motor_zeroDetectionWindow_t;
static Cdd_Motor_ZeroDetectionType cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_NR_SIZE];
/* \brief Motor zero detection information for debouncing raising edge */
// static volatile Cdd_Motor_DebounceType cdd_motor_debounceRise_t;
static volatile Cdd_Motor_DebounceType cdd_motor_debounceRise_as[CDD_MOTOR_MTR_NR_SIZE];
/* \brief Motor zero detection information for debouncing falling edge */
// static volatile Cdd_Motor_DebounceType cdd_motor_debounceFall_t;
static volatile Cdd_Motor_DebounceType cdd_motor_debounceFall_as[CDD_MOTOR_MTR_NR_SIZE];

/** \brief Minimum zero detection window size (loaded from EEPROM) */
static uint8 cdd_motor_zeroWinWidthMin_ui8;
/** \brief Zero detection window debouncing threshold (loaded from EEPROM) */
static uint8 cdd_motor_debouncingThresh_ui8;

/* ***************************** module global function definitions ********** */
// static void Cdd_Motor_ChangeStepModeConfig (void);
static void Cdd_Motor_ChangeStepModeConfig(
		const Cdd_Motor_MotorNumberEnum motor_e);
// static void Cdd_Motor_TriggerMotorStart (void);
static void Cdd_Motor_TriggerMotorStart(const Cdd_Motor_MotorNumberEnum motor_e);
// static void Cdd_Motor_ApplyDirChangeAndGearPlayComp (void);
static void Cdd_Motor_ApplyDirChangeAndGearPlayComp(
		const Cdd_Motor_MotorNumberEnum motor_e);

#if (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON)
// static void Cdd_Motor_ApplyGearPlayInc (uint32 incSteps_ui32);
static void Cdd_Motor_ApplyGearPlayInc(const Cdd_Motor_MotorNumberEnum motor_e, uint32 incSteps_ui32);
// static void Cdd_Motor_ApplyGearPlayDec (uint32 decSteps_ui32);
static void Cdd_Motor_ApplyGearPlayDec(const Cdd_Motor_MotorNumberEnum motor_e, uint32 decSteps_ui32);
#endif /* CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON */

/* ***************************** external global data ************************* */
/** \brief Motor linktime configuration */
// extern const Cdd_Motor_MotorConfigType Cdd_Motor_Cfg_t;
extern const Cdd_Motor_MotorConfigType Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_NR_SIZE];

/* ***************************** global data ******************************** */

/* ***************************** module global functions ********************* */
/**
 *  \brief Function to configure the motor's step mode
 *
 */

static void Cdd_Motor_ChangeStepModeConfig(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	cdd_motor_Data_as[motor_e].stepMode_e =
			cdd_motor_Data_as[motor_e].stepModeChangeReq_e;
	cdd_motor_Data_as[motor_e].stepModeChangeReq_e = CDD_MOTOR_STEPMODE_UNDEF;

	if (cdd_motor_Data_as[motor_e].stepMode_e <= CDD_MOTOR_STEPMODE_STOP) {
		Cdd_Motor_StopPWM(motor_e);
	} else {
		if (cdd_motor_Data_as[motor_e].stepMode_e
				== CDD_MOTOR_STEPMODE_MICRO_FAST) {
			cdd_motor_Data_as[motor_e].usedPatternCoil_0_ui16 =
					Cdd_Motor_Cfg_as[motor_e].coil_0_Fast_ui16;
			cdd_motor_Data_as[motor_e].usedPatternCoil_1_ui16 =
					Cdd_Motor_Cfg_as[motor_e].coil_1_Fast_ui16;
		} else if (cdd_motor_Data_as[motor_e].stepMode_e
				== CDD_MOTOR_STEPMODE_MICRO_SLOW) {
			cdd_motor_Data_as[motor_e].usedPatternCoil_0_ui16 =
					Cdd_Motor_Cfg_as[motor_e].coil_0_Slow_ui16;
			cdd_motor_Data_as[motor_e].usedPatternCoil_1_ui16 =
					Cdd_Motor_Cfg_as[motor_e].coil_1_Slow_ui16;
		} else {
			; /* do nothing */
		}

		/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
		/*lint !e960 */
		/* Set duty cycle ********************************************************************* */

		if (motor_e == CDD_MOTOR_MTR_HHSS) {
			CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR1(
					cdd_motor_Data_as[motor_e].usedPatternCoil_0_ui16[cdd_motor_Data_as[motor_e].currPosLevel0_ui8]);
			/* c:8 */
			CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR1(
					cdd_motor_Data_as[motor_e].usedPatternCoil_1_ui16[cdd_motor_Data_as[motor_e].currPosLevel0_ui8]);
			/* c:8 */
		} else {
			CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR2(
					cdd_motor_Data_as[motor_e].usedPatternCoil_0_ui16[cdd_motor_Data_as[motor_e].currPosLevel0_ui8]);
			/* c:8 */
			CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR2(
					cdd_motor_Data_as[motor_e].usedPatternCoil_1_ui16[cdd_motor_Data_as[motor_e].currPosLevel0_ui8]);
			/* c:8 */
		}

		ENABLE_ALL_INTERRUPTS();
		/*lint !e960 */
		/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */
	}
}

/**
 *  \brief Cdd_Motor_TriggerMotorStart
 *
 *  Triggers the motor ISR to start
 *
 *  \req #CS_REQ_000021  - If operational state is "active" AND temperature <= HIGH_SM_TEMP OR clock pointers are not at a full minute, the software shall update the position of all clock pointers (hh, mm, ss) every second
 *  \req #CS_REQ_000003 - The software shall control one stepper motor leading hours and minutes
 *  \req #CS_REQ_000004 - The software shall control one stepper motor leading seconds
 */

static void Cdd_Motor_TriggerMotorStart(const Cdd_Motor_MotorNumberEnum motor_e) {
	/* ****************************************************************************************** */
	/* Perform mode change request */
	/* ****************************************************************************************** */
	if ((cdd_motor_Data_as[motor_e].stepModeChangeReq_e
			!= CDD_MOTOR_STEPMODE_UNDEF)
			&& (cdd_motor_Data_as[motor_e].isrIsRunning_ui8 == (uint8) FALSE)
			&& (cdd_motor_Data_as[motor_e].currPosLevel0_ui8 == (uint8) 0u)) {
		Cdd_Motor_ChangeStepModeConfig(motor_e);
	} else {
		; /* do nothing */
	}

	if (cdd_motor_Data_as[motor_e].stepMode_e <= CDD_MOTOR_STEPMODE_STOP) {
		return;
	}

	/* ****************************************************************************************** *
	 * ****************************************************************************************** */
	/* Trigger Motor once to initiate Isr Controlling */
	// TODO allora capisco che questo serve ad inizializzare i motori e deve essere chiamata all'avvio o dopo uno stop PWM.
	// Ma non deve essere fatta due volte vista che setta una callback comune. 
	if ((Cdd_Motor_ReachedFinalPosition(motor_e) != (uint8) TRUE)
			&& (cdd_motor_Data_as[motor_e].isrIsRunning_ui8 != (uint8) TRUE)) {
		if (motor_e == CDD_MOTOR_MTR_HHSS) {
			CDD_MOTOR_ENABLE_COIL0_MTR1()
			;
			CDD_MOTOR_ENABLE_COIL1_MTR1()
			;
		} else {
			CDD_MOTOR_ENABLE_COIL0_MTR2()
			;
			CDD_MOTOR_ENABLE_COIL1_MTR2()
			;
		}
		// TODO questo potrebbe essere scritto una volta sola inizialmente e poi abilitato o disabilitato
		update_Mtr_TimerCounterOverflowInterruptFp(&Cdd_Motor_RunMotorISR);

		cdd_motor_Data_as[motor_e].isrIsRunning_ui8 = (uint8) TRUE;
		(void) Mtr_SetMotorInterrupt(MTR_CTRL_MCTOIE_ENABLE);
	} else {
		; /* do nothing */
	}

	/* END OF NEEDLE HANDLING ***************************************************************************** */
}

/**
 *  \brief Function to apply gear play compensation to motor
 *
 */

static void Cdd_Motor_ApplyDirChangeAndGearPlayComp(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	if (cdd_motor_Data_as[motor_e].dirChangeReq_e != CDD_MOTOR_DIR_UNDEF) {
#if (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON)
		/* GEAR PLAY COMPENSATION */
		/* Correction during change: REWARD -> FORWARD */
		if (cdd_motor_Data_as[motor_e].dirChangeReq_e == CDD_MOTOR_DIR_FORWARD)
		{
			/* decrement motor position */
			Cdd_Motor_ApplyGearPlayDec(motor_e, cdd_motor_Data_as[motor_e].gearPlayCompensation_ui8);
		}
		/* Correction during change: FORWARD -> REWARD */
		else
		{
			/* increment motor position */
			Cdd_Motor_ApplyGearPlayInc(motor_e, cdd_motor_Data_as[motor_e].gearPlayCompensation_ui8);
		}
#endif /* CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON */

		/* Change direction and delete request */
		cdd_motor_Data_as[motor_e].dir_e =
				cdd_motor_Data_as[motor_e].dirChangeReq_e;
		cdd_motor_Data_as[motor_e].dirChangeReq_e = CDD_MOTOR_DIR_UNDEF;
	} else {
		; /* do nothing */
	}
}

#if (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON)
/**
 *  \brief Function to increment the motor's position by one micro step
 *
 */
// static void Cdd_Motor_ApplyGearPlayInc (uint32 incSteps_ui32)
//{
//    /* increment absolute motor position */
//    cdd_motor_Data_t.currPosLevel1_ui32 += incSteps_ui32;
//
//    /* Check for overflow */
//    if (cdd_motor_Data_t.currPosLevel1_ui32 >= Cdd_Motor_Cfg_t.uStepMaximumAbsolute_ui32)
//    {
//       cdd_motor_Data_t.currPosLevel1_ui32 -= Cdd_Motor_Cfg_t.uStepMaximumAbsolute_ui32;
//    }
//    else
//    {
//       ; /* do nothing */
//    }
// }
static void Cdd_Motor_ApplyGearPlayInc(const Cdd_Motor_MotorNumberEnum motor_e, uint32 incSteps_ui32)
{
	/* increment absolute motor position */
	cdd_motor_Data_as[motor_e].currPosLevel1_ui32 += incSteps_ui32;

	/* Check for overflow */
	if (cdd_motor_Data_as[motor_e].currPosLevel1_ui32 >= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32)
	{
		cdd_motor_Data_as[motor_e].currPosLevel1_ui32 -= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
	}
	else
	{
		; /* do nothing */
	}
}

/**
 *  \brief Function to decrement the motor's position by one micro step
 *
 */
// static void Cdd_Motor_ApplyGearPlayDec (uint32 decSteps_ui32)
//{
//    /* Check for underflow */
//    if (cdd_motor_Data_t.currPosLevel1_ui32 < decSteps_ui32)
//    {
//       cdd_motor_Data_t.currPosLevel1_ui32 += Cdd_Motor_Cfg_t.uStepMaximumAbsolute_ui32;
//    }
//    else
//    {
//       ; /* do nothing */
//    }
//    /* decrement absolute motor position */
//    cdd_motor_Data_t.currPosLevel1_ui32 -= decSteps_ui32;
// }
static void Cdd_Motor_ApplyGearPlayDec(const Cdd_Motor_MotorNumberEnum motor_e, uint32 decSteps_ui32)
{
	/* Check for underflow */
	if (cdd_motor_Data_as[motor_e].currPosLevel1_ui32 < decSteps_ui32)
	{
		cdd_motor_Data_as[motor_e].currPosLevel1_ui32 += Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
	}
	else
	{
		; /* do nothing */
	}
	/* decrement absolute motor position */
	cdd_motor_Data_as[motor_e].currPosLevel1_ui32 -= decSteps_ui32;
}

#endif /* CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON */

/* ***************************** global functions *************************** */
/**
 *  \brief Function to initialize the motor
 *
 */

void Cdd_Motor_Init(void) {
	uint8 i_ui8;
	// Ea_ReturnType rtn_e;

#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
	if (cdd_motor_moduleState_e == MODULE_INITIALIZED) {
		//(void) Det_ReportError (CDD_MOTOR_MODULE_ID, (uint8) CDD_MOTOR_INSTANCE_ID, (uint8) CDD_MOTOR_INIT_API_ID,
		//         (uint8) CDD_MOTOR_E_ALREADY_INITIALIZED);  /*lint !e792 */
	} else
#endif /* CDD_MOTOR_DEV_ERROR_DETECT == STD_ON */
	{
#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		cdd_motor_moduleState_e = MODULE_UNINIT;
#endif

		for (i_ui8 = (uint8) 0U; i_ui8 < (uint8) CDD_MOTOR_MTR_NR_SIZE;
				i_ui8++) {
			cdd_motor_debounceRise_as[i_ui8].ctr_ui8 = (uint8) 0U;
			cdd_motor_debounceRise_as[i_ui8].dir_e = CDD_MOTOR_DIR_UNDEF;
			cdd_motor_debounceRise_as[i_ui8].posAbsolute_ui32 =
					CDD_MOTOR_INVALID_POS_UI32;
			cdd_motor_debounceFall_as[i_ui8].ctr_ui8 = (uint8) 0U;
			cdd_motor_debounceFall_as[i_ui8].dir_e = CDD_MOTOR_DIR_UNDEF;
			cdd_motor_debounceFall_as[i_ui8].posAbsolute_ui32 =
					CDD_MOTOR_INVALID_POS_UI32;

			cdd_motor_zeroDetectionWindow_as[i_ui8].rising_s.pos_ui32 =
					CDD_MOTOR_INVALID_POS_UI32;
			cdd_motor_zeroDetectionWindow_as[i_ui8].rising_s.dir_e =
					CDD_MOTOR_DIR_UNDEF;
			cdd_motor_zeroDetectionWindow_as[i_ui8].rising_s.valid_ui8 =
					(uint8) FALSE;
			cdd_motor_zeroDetectionWindow_as[i_ui8].falling_s.pos_ui32 =
					CDD_MOTOR_INVALID_POS_UI32;
			cdd_motor_zeroDetectionWindow_as[i_ui8].falling_s.dir_e =
					CDD_MOTOR_DIR_UNDEF;
			cdd_motor_zeroDetectionWindow_as[i_ui8].falling_s.valid_ui8 =
					(uint8) FALSE;
			cdd_motor_zeroDetectionWindow_as[i_ui8].lastResult_s.windowStart_ui32 =
					CDD_MOTOR_ZERO_POSITION_INVALID_UI32;
			cdd_motor_zeroDetectionWindow_as[i_ui8].lastResult_s.windowEnd_ui32 =
					CDD_MOTOR_ZERO_POSITION_INVALID_UI32;
			cdd_motor_zeroDetectionWindow_as[i_ui8].lastResult_s.windowSize_ui8 =
					CDD_MOTOR_ZERO_WIDTH_INVALID_UI8;
			cdd_motor_zeroDetectionWindow_as[i_ui8].lastResult_s.windowSizeLeftMiddle_ui8 =
					CDD_MOTOR_ZERO_WIDTH_INVALID_UI8;
			cdd_motor_zeroDetectionWindow_as[i_ui8].enabled_ui8 = (uint8) FALSE;
			cdd_motor_zeroDetectionWindow_as[i_ui8].state_e =
					CDD_MOTOR_ZERO_DET_STATE_INITIAL;

			cdd_motor_Data_as[i_ui8].currPosLevel0_ui8 = (uint8) 0u;
			cdd_motor_Data_as[i_ui8].currPosLevel1_ui32 = (uint32) 0uL;
			cdd_motor_Data_as[i_ui8].trgtPosLevel1_ui32 = (uint32) 0uL;
			cdd_motor_Data_as[i_ui8].usedFullStep_e =
					CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE;

			cdd_motor_Data_as[i_ui8].dir_e = CDD_MOTOR_DIR_FORWARD;
			cdd_motor_Data_as[i_ui8].stepModeChangeReq_e =
					CDD_MOTOR_STEPMODE_UNDEF;
		}

		// HHSS
		/* Load gear play compensation for MTR HHSS from EEPROM */

#if (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON)
		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].gearPlayCompensation_ui8 = (uint8)0u;
#endif /* CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON */

		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].usedUStepMaximum_pui32 =
				&Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_HHSS].uStepMaximumAbsolute_ui32;

		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].stepMode_e =
				CDD_MOTOR_STEPMODE_MICRO_FAST;
		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].usedPatternCoil_0_ui16 =
				Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_HHSS].coil_0_Fast_ui16;
		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].usedPatternCoil_1_ui16 =
				Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_HHSS].coil_1_Fast_ui16;

		//	#if (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON)
		//		  /* EEPROM: load gear play compensation for MTR */
		//		  rtn_e = Ea_Read(EA_GEAR_PLAY_COMP_MTR, &cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].gearPlayCompensation_ui8);
		//	#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		//		  if (rtn_e != EA_OK)
		//		  {
		//			 Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID, CDD_MOTOR_INIT_API_ID, CDD_MOTOR_EEPROM_READ_ERROR);
		//		  }
		//	#endif
		//	#endif /* CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON */
		//
		//		  /* EEPROM: load debouncing threshold */
		//		  rtn_e = Ea_Read(EA_ZERO_DETECT_WINDOW_DEBOUNCING_THRESHOLD, &cdd_motor_debouncingThresh_ui8);
		//	#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		//		  if (rtn_e != EA_OK)
		//		  {
		//			 Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID, CDD_MOTOR_INIT_API_ID, CDD_MOTOR_EEPROM_READ_ERROR);
		//		  }
		//	#endif
		//
		//		  /* EEPROM: load minimum window width */
		//		  rtn_e = Ea_Read(EA_ZERO_DETECT_WINDOW_MINIMUM_WIDTH, &cdd_motor_zeroWinWidthMin_ui8);
		//	#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		//		  if (rtn_e != EA_OK)
		//		  {
		//			 Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID, CDD_MOTOR_INIT_API_ID, CDD_MOTOR_EEPROM_READ_ERROR);
		//		  }
		//	#endif

		// TODO COMPASS: -> PORT CFG
		/* Configure Port F 7 as output */
		(*((uint8 * const ) CDD_MOTOR_PTF_DATA_DIR_REG_ADR_UI16 )) |=
				(uint8) (0x1U << CDD_MOTOR_NO2_BITPOS_UI8 ); /*lint !e923 */
		/* Configure Port T 7 as input */
		(*((uint8 * const ) CDD_MOTOR_PTT_DATA_DIR_REG_ADR_UI16)) &=
				(uint8) (~((uint8) (0x1U << CDD_MOTOR_NO2_BITPOS_UI8 ))); /*lint !e923 */
		/* Set pull and polarity */
		(*((uint8 * const ) CDD_MOTOR_PTT_PULL_EN_REG_ADR_UI16)) |=
				(uint8) (0x1U << CDD_MOTOR_NO2_BITPOS_UI8 ); /*lint !e923 */
		(*((uint8 * const ) CDD_MOTOR_PTT_POL_SEL_REG_ADR_UI16)) |=
				(uint8) (0x1U << CDD_MOTOR_NO2_BITPOS_UI8 ); /*lint !e923 */

		// MM
		/* Load gear play compensation for MTR MM from EEPROM */

#if (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON)
		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].gearPlayCompensation_ui8 = (uint8)0u;
#endif /* CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON */

		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].usedUStepMaximum_pui32 =
				&Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_MM].uStepMaximumAbsolute_ui32;

		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].stepMode_e =
				CDD_MOTOR_STEPMODE_MICRO_FAST;
		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].usedPatternCoil_0_ui16 =
				Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_MM].coil_0_Fast_ui16;
		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].usedPatternCoil_1_ui16 =
				Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_MM].coil_1_Fast_ui16;

		//	#if (CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON)
		//		  /* EEPROM: load gear play compensation for MTR */
		//		  rtn_e = Ea_Read(EA_GEAR_PLAY_COMP_MTR, &cdd_motor_Data_as[CDD_MOTOR_MTR_MM].gearPlayCompensation_ui8);
		//	#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		//		  if (rtn_e != EA_OK)
		//		  {
		//			 Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID, CDD_MOTOR_INIT_API_ID, CDD_MOTOR_EEPROM_READ_ERROR);
		//		  }
		//	#endif
		//	#endif /* CDD_MOTOR_GEAR_PLAY_COMPENSATION_API == STD_ON */
		//
		//		  /* EEPROM: load debouncing threshold */
		//		  rtn_e = Ea_Read(EA_ZERO_DETECT_WINDOW_DEBOUNCING_THRESHOLD, &cdd_motor_debouncingThresh_ui8);
		//	#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		//		  if (rtn_e != EA_OK)
		//		  {
		//			 Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID, CDD_MOTOR_INIT_API_ID, CDD_MOTOR_EEPROM_READ_ERROR);
		//		  }
		//	#endif
		//
		//		  /* EEPROM: load minimum window width */
		//		  rtn_e = Ea_Read(EA_ZERO_DETECT_WINDOW_MINIMUM_WIDTH, &cdd_motor_zeroWinWidthMin_ui8);
		//	#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		//		  if (rtn_e != EA_OK)
		//		  {
		//			 Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID, CDD_MOTOR_INIT_API_ID, CDD_MOTOR_EEPROM_READ_ERROR);
		//		  }
		//	#endif

		// TODO COMPASS: -> PORT CFG
		/* Configure Port F 6 as output */
		(*((uint8 * const ) CDD_MOTOR_PTF_DATA_DIR_REG_ADR_UI16 )) |=
				(uint8) (0x1U << CDD_MOTOR_NO1_BITPOS_UI8 ); /*lint !e923 */
		/* Configure Port T 6 as input */
		(*((uint8 * const ) CDD_MOTOR_PTT_DATA_DIR_REG_ADR_UI16)) &=
				(uint8) (~((uint8) (0x1U << CDD_MOTOR_NO1_BITPOS_UI8 ))); /*lint !e923 */
		/* Set pull and polarity */
		(*((uint8 * const ) CDD_MOTOR_PTT_PULL_EN_REG_ADR_UI16)) |=
				(uint8) (0x1U << CDD_MOTOR_NO1_BITPOS_UI8 ); /*lint !e923 */
		(*((uint8 * const ) CDD_MOTOR_PTT_POL_SEL_REG_ADR_UI16)) |=
				(uint8) (0x1U << CDD_MOTOR_NO1_BITPOS_UI8 ); /*lint !e923 */

#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
		cdd_motor_moduleState_e = MODULE_INITIALIZED;
#endif
	}
}

#if (CDD_MOTOR_DEINIT_API == STD_ON)
/**
 *  \brief Service for module deinitialization
 *
 */
// void Cdd_Motor_DeInit (void)
//{
//    /* --- local variable declaration --- */
//    uint8 i_ui8;
//
//    /* ----- init internal variables ----- */
//    i_ui8 = (uint8) 0U;
//
//    /* ----------- source code ----------- */
// #if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
//    if (cdd_motor_moduleState_e != CDD_MOTOR_MODSTATE_INIT) /* Safety request */
//    {
//       Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID,
//                CDD_MOTOR_DEINIT_API_ID, CDD_MOTOR_E_UNINIT);
//    }
//    else /* CDD_MOTOR_DEV_ERROR_DETECT == STD_ON */
// #endif
//    {
//       cdd_motor_moduleState_e = CDD_MOTOR_MODSTATE_UNINIT;
//    }
// }
void Cdd_Motor_DeInit(void)
{
	/* --- local variable declaration --- */
	uint8 i_ui8;

	/* ----- init internal variables ----- */
	i_ui8 = (uint8)0U;

	/* ----------- source code ----------- */
#if (CDD_MOTOR_DEV_ERROR_DETECT == STD_ON)
	if (cdd_motor_moduleState_e != CDD_MOTOR_MODSTATE_INIT) /* Safety request */
	{
		Det_ReportError(CDD_MOTOR_MODULE_ID, CDD_MOTOR_INSTANCE_ID,
				CDD_MOTOR_DEINIT_API_ID, CDD_MOTOR_E_UNINIT);
	}
	else /* CDD_MOTOR_DEV_ERROR_DETECT == STD_ON */
#endif
	{
		cdd_motor_moduleState_e = CDD_MOTOR_MODSTATE_UNINIT;
	}
}

#endif /* CDD_MOTOR_DEINIT_API == STD_ON */

/**
 *  \brief Function to change the motor's speed
 *
 */

Std_ReturnType Cdd_Motor_SetSpeedFac(const Cdd_Motor_MotorNumberEnum motor_e,
		const Cdd_Motor_SpeedEnum targetSpeed_e) {
	Std_ReturnType rtn_e = (uint8) E_NOT_OK;

	if (targetSpeed_e < CDD_MOTOR_NBR_OF_SPEEDS) {
		cdd_motor_Data_as[motor_e].isrTargetNbrOfPeriodes_ui16 = targetSpeed_e;
		rtn_e = (uint8) E_OK;
	}
	return rtn_e;
}

/**
 *  \brief Function to change the motor's default step counter
 *
 */

void Cdd_Motor_ChangeDefaultFullStepCounter(
		const Cdd_Motor_MotorNumberEnum motor_e,
		const Cdd_Motor_UsedFullStepModeEnum counterTyp_e) {
	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */
	DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	if (counterTyp_e == CDD_MOTOR_USED_FSTEP_CTR_RELATIVE) {
		cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32 =
				&Cdd_Motor_Cfg_as[motor_e].uStepMaximumRelative_ui32;
		cdd_motor_Data_as[motor_e].usedFullStep_e = counterTyp_e;
	} else {
		cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32 =
				&Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
		cdd_motor_Data_as[motor_e].usedFullStep_e =
				CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE;
	}
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */
}

void Cdd_Motor_StopPWM(const Cdd_Motor_MotorNumberEnum motor_e) {
	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */
	DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* Set duty cycle ********************************************************************* */

	if (motor_e == CDD_MOTOR_MTR_HHSS) {
		CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR1((Mtr_ChannelDutyCycleType)0U);
		CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR1((Mtr_ChannelDutyCycleType)0U);
		CDD_MOTOR_DISABLE_COIL0_MTR1()
		;
		CDD_MOTOR_DISABLE_COIL1_MTR1()
		;
	} else {
		CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR2((Mtr_ChannelDutyCycleType)0U);
		CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR2((Mtr_ChannelDutyCycleType)0U);
		CDD_MOTOR_DISABLE_COIL0_MTR2()
		;
		CDD_MOTOR_DISABLE_COIL1_MTR2()
		;
	}

	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	cdd_motor_Data_as[motor_e].isrIsRunning_ui8 = (uint8) FALSE;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

Cdd_Motor_StepModeEnum Cdd_Motor_GetStepMode(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	return cdd_motor_Data_as[motor_e].stepMode_e;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_SetStepMode(const Cdd_Motor_MotorNumberEnum motor_e,
		const Cdd_Motor_StepModeEnum stepMode_e) {
	if ((stepMode_e > CDD_MOTOR_STEPMODE_UNDEF)
			&& (stepMode_e < CDD_MOTOR_STEPMODE_SIZE)) {
		cdd_motor_Data_as[motor_e].stepModeChangeReq_e = stepMode_e;

		/* change step mode if necessary */
		if (((cdd_motor_Data_as[motor_e].isrIsRunning_ui8 == (uint8) FALSE)
				&& (cdd_motor_Data_as[motor_e].currPosLevel0_ui8 == (uint8) 0u))
				|| (cdd_motor_Data_as[motor_e].stepMode_e
						<= CDD_MOTOR_STEPMODE_STOP)) {
			Cdd_Motor_ChangeStepModeConfig(motor_e);
		} else {
			; /* do nothing */
		}
	} else {
		; /* do nothing */
	}
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_SetDirectionReq(const Cdd_Motor_MotorNumberEnum motor_e,
		const Cdd_Motor_DirectionEnum dir_e) {
	if ((CDD_MOTOR_DIR_UNDEF < dir_e) && (CDD_MOTOR_DIR_SIZE > dir_e)) {
		if (cdd_motor_Data_as[motor_e].dir_e != dir_e) {
			cdd_motor_Data_as[motor_e].dirChangeReq_e = dir_e;
		} else {
			cdd_motor_Data_as[motor_e].dirChangeReq_e = CDD_MOTOR_DIR_UNDEF;
		}
	} else {
		; /* do nothing */
	}
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

Cdd_Motor_DirectionEnum Cdd_Motor_GetDirection(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	return cdd_motor_Data_as[motor_e].dir_e;
}

/**
 *  \brief Return pointer real position
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint8 Cdd_Motor_GetUStepPosition(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint8 partpos_ui8;

	partpos_ui8 = cdd_motor_Data_as[motor_e].currPosLevel0_ui8;

	return partpos_ui8;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_RunToFullStepPosition(const Cdd_Motor_MotorNumberEnum motor_e,
		const uint16 pos_ui16) {
	uint32 destPos_ui32 = (uint32) 0UL;

	destPos_ui32 = (uint32) ((uint32) pos_ui16
			* (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);

	Cdd_Motor_RunToPosition(motor_e, destPos_ui32);
}

#if (CDD_MOTOR_RUN_TO_POSITION_API == STD_ON)
/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_RunToPosition(const Cdd_Motor_MotorNumberEnum motor_e,
		const uint32 newTarget_ui32) {
	uint32 destPos_ui32 = (uint32) 0uL;
	uint32 normalizedTarget_ui32;
	Cdd_Motor_DirectionEnum calcDir_e;

	/* normalise input vector */
	if (newTarget_ui32
			>= *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32)) {
		normalizedTarget_ui32 = newTarget_ui32
				% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32);
	} else {
		normalizedTarget_ui32 = newTarget_ui32;
	}

	if (cdd_motor_Data_as[motor_e].dirChangeReq_e != CDD_MOTOR_DIR_UNDEF) {
		calcDir_e = cdd_motor_Data_as[motor_e].dirChangeReq_e;
	} else {
		calcDir_e = cdd_motor_Data_as[motor_e].dir_e;
	}

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */

	if (cdd_motor_Data_as[motor_e].usedFullStep_e
			== CDD_MOTOR_USED_FSTEP_CTR_RELATIVE) {
		uint32 relPos_ui32;
		uint32 fullRoundPos_ui32;

		/* normalise current position */
		relPos_ui32 = cdd_motor_Data_as[motor_e].currPosLevel1_ui32
				% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32);
		fullRoundPos_ui32 = cdd_motor_Data_as[motor_e].currPosLevel1_ui32
				- relPos_ui32;

		if (calcDir_e == CDD_MOTOR_DIR_FORWARD) {
			if (relPos_ui32 <= normalizedTarget_ui32) {
				destPos_ui32 = fullRoundPos_ui32 + normalizedTarget_ui32;
			} else {
				destPos_ui32 = fullRoundPos_ui32
						+ *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32)
						+ normalizedTarget_ui32;
			}
		} else if (calcDir_e == CDD_MOTOR_DIR_BACKWARD) {
			if (relPos_ui32 >= normalizedTarget_ui32) {
				destPos_ui32 = fullRoundPos_ui32 + normalizedTarget_ui32;
			} else {
				if (fullRoundPos_ui32 == (uint32) 0uL) {
					fullRoundPos_ui32 =
							Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
				} else {
					; /* do nothing */
				}

				destPos_ui32 = (fullRoundPos_ui32
						- *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32))
						+ normalizedTarget_ui32;
			}
		} else {
			; /* do nothing */
		}

		/* normalise target position */
		destPos_ui32 %= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
	} else {
		destPos_ui32 = normalizedTarget_ui32;
	}

#if 0
	if (destPos_ui32 != cdd_motor_Data_as[motor_e].currPosLevel1_ui32)
	{
#endif
	/* Apply direction change request if required */
	/* TODO COMPASS: AUFPASSEN */
	Cdd_Motor_ApplyDirChangeAndGearPlayComp(motor_e);
#if 0
}
#endif

	/* set new target position */
	cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 = destPos_ui32;

	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	/* Start motor if not already happened */
	Cdd_Motor_TriggerMotorStart(motor_e);
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_RunToPositionAbsolute(const Cdd_Motor_MotorNumberEnum motor_e,
		const uint32 absolutposition_ui32) {
	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */
	DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */

#if 0
	if (absolutposition_ui32 != cdd_motor_Data_as[motor_e].currPosLevel1_ui32)
	{
#endif
	/* Apply direction change request if required */
	/* TODO COMPASS: AUFPASSEN */
	Cdd_Motor_ApplyDirChangeAndGearPlayComp(motor_e);
#if 0
}
#endif

	if (absolutposition_ui32
			>= *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32)) {
		cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 = absolutposition_ui32
				% (*(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32));
	} else {
		cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 = absolutposition_ui32;
	}

	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	/* Start motor if not already happened */
	Cdd_Motor_TriggerMotorStart(motor_e);
}
#endif /* (CDD_MOTOR_RUN_TO_POSITION_API == STD_ON) */

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_RunDistanceFullSteps(const Cdd_Motor_MotorNumberEnum motor_e,
		const uint16 position_ui16) {
	Cdd_Motor_RunDistance(motor_e, CDD_MOTOR_DIR_UNDEF, position_ui16,
			(uint8) 0u);
}

#if (CDD_MOTOR_RUN_RELATIVE_API == STD_ON)
/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_RunDistance(const Cdd_Motor_MotorNumberEnum motor_e,
		const Cdd_Motor_DirectionEnum dir_e, const uint16 fStep_ui16,
		const uint8 uStep_ui8) {
	uint32 distance_ui32 = (uint32) 0UL;

	distance_ui32 = (((uint32) fStep_ui16)
			* ((uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE)) + (uint32) uStep_ui8;

	Cdd_Motor_SetDirectionReq(motor_e, dir_e);

	//   if (distance_ui32 >= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32)
	//   {
	//      distance_ui32 %= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
	//   }
	//
	//   if (distance_ui32 == (uint32) 0uL)
	//   {
	//      return;
	//   }

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */

	/* Direction change may be taken over immediately because this is a relative movement */
	/* Apply direction change request if required */
	/* TODO COMPASS: AUFPASSEN */
	Cdd_Motor_ApplyDirChangeAndGearPlayComp(motor_e);
	if (CDD_MOTOR_DIR_FORWARD == cdd_motor_Data_as[motor_e].dir_e) {
		cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 += distance_ui32;
	} else if (CDD_MOTOR_DIR_BACKWARD == cdd_motor_Data_as[motor_e].dir_e) {
		if (cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 >= distance_ui32) {
			cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 -= distance_ui32;
		} else {
			cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 +=
					(Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32
							- distance_ui32);
		}
	} else {
		; /* do nothing */
	}

	if (cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32
			>= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32) {
		cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 %=
				Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
	}

	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	/* Start motor if not already happened */
	Cdd_Motor_TriggerMotorStart(motor_e);
}
#endif /* CDD_MOTOR_RUN_RELATIVE_API == STD_ON */

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_RunToNextFullStep(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint32 destPos_ui32 = (uint32) 0uL;
	uint32 curPos_ui32 = 0uL;
	uint16 currPartStep_ui16 = (uint16) 0u;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */

	/* Apply direction change request if required */
	/* TODO COMPASS: AUFPASSEN */
	Cdd_Motor_ApplyDirChangeAndGearPlayComp(motor_e);

	curPos_ui32 = cdd_motor_Data_as[motor_e].currPosLevel1_ui32;
	currPartStep_ui16 = (uint16) (curPos_ui32
			% (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);

	if (cdd_motor_Data_as[motor_e].dir_e == CDD_MOTOR_DIR_FORWARD) {
		uint16 diffPartStep_ui16 = (uint16) 0u;
		diffPartStep_ui16 = (((uint16) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE)
				- currPartStep_ui16);

		destPos_ui32 = curPos_ui32 + (uint32) diffPartStep_ui16;

		if (destPos_ui32
				>= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32) {
			destPos_ui32 %= Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
		}
		cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 = destPos_ui32;
	} else if (cdd_motor_Data_as[motor_e].dir_e == CDD_MOTOR_DIR_BACKWARD) {
		/* Cannot become negative */
		cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32 = curPos_ui32
				- (uint32) currPartStep_ui16;
	} else {
		; /* do nothing */
	}

	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	/* Start motor if not already happened */
	Cdd_Motor_TriggerMotorStart(motor_e);
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint8 Cdd_Motor_GetPartStepPosition(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint8 partpos_ui8;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	partpos_ui8 = (uint8) (cdd_motor_Data_as[motor_e].currPosLevel1_ui32
			% (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return partpos_ui8;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint16 Cdd_Motor_GetFullStepPositionUsed(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	uint16 currPos_ui16;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	currPos_ui16 = (uint16) (cdd_motor_Data_as[motor_e].currPosLevel1_ui32
			/ (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	if (cdd_motor_Data_as[motor_e].usedFullStep_e
			== CDD_MOTOR_USED_FSTEP_CTR_RELATIVE) {
		currPos_ui16 = (uint16) ((uint32) currPos_ui16
				% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32));
	} else {
		; /* nothing to do */
	}

	return currPos_ui16;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint16 Cdd_Motor_GetFullStepPositionAbsolute(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	uint16 currPos_ui16;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	currPos_ui16 = (uint16) (cdd_motor_Data_as[motor_e].currPosLevel1_ui32
			/ (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return currPos_ui16;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint32 Cdd_Motor_GetPositionCurrentUsed(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint32 currPos_ui32;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	currPos_ui32 = (uint32) (cdd_motor_Data_as[motor_e].currPosLevel1_ui32
			% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32));
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return currPos_ui32;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint32 Cdd_Motor_GetPositionCurrentAbsolute(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	uint32 currPos_ui32;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	currPos_ui32 = (uint32) cdd_motor_Data_as[motor_e].currPosLevel1_ui32;
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return currPos_ui32;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint32 Cdd_Motor_GetPositionTargetUsed(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint32 target_ui32;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	target_ui32 = cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32
			% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32);
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return target_ui32;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint32 Cdd_Motor_GetPositionTargetAbsolute(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	uint32 target_ui32;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	target_ui32 = cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32;
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return target_ui32;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint8 Cdd_Motor_GetPartStepTarget(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint8 partpos_ui8;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	partpos_ui8 = (uint8) (cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32
			% (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return partpos_ui8;
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint16 Cdd_Motor_GetFullStepTargetUsed(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint16 currPos_ui16;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	currPos_ui16 = (uint16) (cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32
			/ (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	if (cdd_motor_Data_as[motor_e].usedFullStep_e
			== CDD_MOTOR_USED_FSTEP_CTR_RELATIVE) {
		currPos_ui16 = (uint16) ((uint32) currPos_ui16
				% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32));
	} else {
		; /* nothing to do */
	}

	return currPos_ui16;
}

uint16 Cdd_Motor_GetFullStepTargetFullPartAbsolute(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	uint16 currPos_ui16;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	currPos_ui16 = (uint16) (cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32
			/ (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return currPos_ui16;
}

uint32 Cdd_Motor_GetMaximumFullStepUsed(const Cdd_Motor_MotorNumberEnum motor_e) {
	return *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32);
}

/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint8 Cdd_Motor_ReachedFinalPosition(const Cdd_Motor_MotorNumberEnum motor_e) {
	uint8 ret_t;

	ret_t = (uint8) FALSE;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	if (cdd_motor_Data_as[motor_e].usedFullStep_e
			== CDD_MOTOR_USED_FSTEP_CTR_ABSOLUTE) {
		if (cdd_motor_Data_as[motor_e].currPosLevel1_ui32
				== cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32) {
			ret_t = (uint8) TRUE;
		} else {
			/* do nothing */
		}
	} else {
		uint32 current_ui32 = cdd_motor_Data_as[motor_e].currPosLevel1_ui32
				% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32);
		uint32 target_ui32 = cdd_motor_Data_as[motor_e].trgtPosLevel1_ui32
				% *(cdd_motor_Data_as[motor_e].usedUStepMaximum_pui32);

		if (current_ui32 == target_ui32) {
			ret_t = (uint8) TRUE;
		} else {
			/* do nothing */
		}
	}
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */

	return ret_t;
}

#if (CDD_MOTOR_VERSION_INFO_API == STD_ON)
/*
 *  \brief This service returns the version information of this module.
 *
 *  \param [in]  ---
 *  \param [out] versioninfo = Pointer to where to store the version
 *                             information of this module.
 *  \return      ---
 */
void Cdd_Motor_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	/* ----------- source code ----------- */
	versioninfo->vendorID = CDD_MOTOR_VENDOR_ID;
	versioninfo->moduleID = CDD_MOTOR_MODULE_ID;
	versioninfo->instanceID = CDD_MOTOR_INSTANCE_ID;
	versioninfo->sw_major_version = CDD_MOTOR_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = CDD_MOTOR_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = CDD_MOTOR_SW_PATCH_VERSION;
}
#endif /* CDD_MOTOR_VERSION_INFO_API == STD_ON */

/**
 *  \brief Zero detection: Function to delete the last zero window result
 *
 */

void Cdd_Motor_ZD_DeleteResult(const Cdd_Motor_MotorNumberEnum motor_e) {
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowStart_ui32 =
			CDD_MOTOR_ZERO_POSITION_INVALID_UI32;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowEnd_ui32 =
			CDD_MOTOR_ZERO_POSITION_INVALID_UI32;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSize_ui8 =
			CDD_MOTOR_ZERO_WIDTH_INVALID_UI8;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSizeLeftMiddle_ui8 =
			CDD_MOTOR_ZERO_WIDTH_INVALID_UI8;
}

/**
 *  \brief Zero detection: function to perform the zero window check / validation
 *
 */

void Cdd_Motor_ZD_PerformWindowCheck(const Cdd_Motor_MotorNumberEnum motor_e) {
	DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */

	if (CDD_MOTOR_ZERO_DET_STATE_DETECTION_VALIDATE
			== cdd_motor_zeroDetectionWindow_as[motor_e].state_e) {
		/* Runtime calibration */
		(void) Cdd_Motor_ZD_CalibrateZeroToWindow(motor_e);
	} else {
		; /* do nothing */
	}

	if (CDD_MOTOR_ZERO_DET_STATE_DETECTION_VALIDATE
			<= cdd_motor_zeroDetectionWindow_as[motor_e].state_e) {
		/* Restart zero detection */
		cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.pos_ui32 =
				CDD_MOTOR_INVALID_POS_UI32;
		cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.dir_e =
				CDD_MOTOR_DIR_UNDEF;
		cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.valid_ui8 =
				(uint8) FALSE;
		cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.pos_ui32 =
				CDD_MOTOR_INVALID_POS_UI32;
		cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.dir_e =
				CDD_MOTOR_DIR_UNDEF;
		cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.valid_ui8 =
				(uint8) FALSE;

		cdd_motor_debounceRise_as[motor_e].ctr_ui8 = (uint8) 0U;
		cdd_motor_debounceRise_as[motor_e].dir_e = CDD_MOTOR_DIR_UNDEF;
		cdd_motor_debounceRise_as[motor_e].posAbsolute_ui32 =
				CDD_MOTOR_INVALID_POS_UI32;
		cdd_motor_debounceFall_as[motor_e].ctr_ui8 = (uint8) 0U;
		cdd_motor_debounceFall_as[motor_e].dir_e = CDD_MOTOR_DIR_UNDEF;
		cdd_motor_debounceFall_as[motor_e].posAbsolute_ui32 =
				CDD_MOTOR_INVALID_POS_UI32;

		cdd_motor_zeroDetectionWindow_as[motor_e].state_e =
				CDD_MOTOR_ZERO_DET_STATE_INITIAL;
	} else {
		/* Following states are handled in RunMotorISR:
		 * CDD_MOTOR_ZERO_DET_STATE_INITIAL
		 * CDD_MOTOR_ZERO_DET_STATE_DETECTING_FIRST
		 * CDD_MOTOR_ZERO_DET_STATE_DETECTING_SECOND
		 */
		; /* do nothing */
	}

	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* *************************************************************************************** */
}

/**
 * \brief Zero detection: Calibrates zero position to active position
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_ZD_CalibrateZeroToActivePosition(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	uint32 usteps_ui32;

	/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */
	DISABLE_ALL_INTERRUPTS();
	/*lint !e960 */

	/* Save actual microstep position */
	usteps_ui32 = cdd_motor_Data_as[motor_e].currPosLevel1_ui32
			% ((uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE);

	/* Only full steps may be removed, never micro steps */
	cdd_motor_Data_as[motor_e].currPosLevel1_ui32 = usteps_ui32;
	ENABLE_ALL_INTERRUPTS();
	/*lint !e960 */
	/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */
}

/**
 * \brief Zero detection: Zero position is determined according to detected window.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

Std_ReturnType Cdd_Motor_ZD_CalibrateZeroToWindow(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	Std_ReturnType ret_t;
	uint32 firstpos_ui32;
	uint32 secondpos_ui32;
	uint32 partStep1st_ui32;
	uint32 zeroPositionAbsolute_ui32;
	uint8 windowSize_ui8;
	uint8 windowSizeLeftMiddle_ui8;

	ret_t = E_OK;

	if ((cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.valid_ui8
			!= (uint8) TRUE)
			|| (cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.valid_ui8
					!= (uint8) TRUE)
			|| (cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.dir_e
					!= CDD_MOTOR_DIR_FORWARD)
			|| (cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.dir_e
					!= CDD_MOTOR_DIR_FORWARD)) {
		cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.valid_ui8 =
				(uint8) FALSE;
		cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.valid_ui8 =
				(uint8) FALSE;

		ret_t = E_NOT_OK;

		return ret_t; /*lint !e904 */
	}

	/* exchange coordinates if motor drive direction was reward */
	if (cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.dir_e
			== CDD_MOTOR_DIR_BACKWARD) {
		uint32 exchangePos_ui32;

		exchangePos_ui32 =
				cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.pos_ui32;
		cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.pos_ui32 =
				cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.pos_ui32;
		cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.pos_ui32 =
				exchangePos_ui32;
	} else {
		/* do nothing */
	}

	/* window start position coordinates */
	firstpos_ui32 = cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.pos_ui32;
	/* window end position coordinates */
	secondpos_ui32 =
			cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.pos_ui32;

	/* Determine whether window is between zero, e.g. first = 719 FullSteps * 48 uSteps, second = 1 FullSteps * 48 uSteps
	 * Operation required for window size calculation
	 * */
	if (firstpos_ui32 > secondpos_ui32) {
		secondpos_ui32 += Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
	} else {
		/* do nothing */
	}

	/* Store window width */
	partStep1st_ui32 =
			cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.pos_ui32
					% (uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE;

	windowSize_ui8 = (uint8) (secondpos_ui32 - firstpos_ui32);
	windowSizeLeftMiddle_ui8 =
			(uint8) ((uint32) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE
					- partStep1st_ui32);

	/* If window is bigger than 2 full steps the detection was faulty */
	/* TODO: CHECK CDD_MOTOR_ZERO_DETECTION_MAXIMUM_SIZE for COMPASS */
	if ((windowSize_ui8 > (uint8) CDD_MOTOR_ZERO_DETECTION_MAXIMUM_SIZE)|| (windowSize_ui8 < cdd_motor_zeroWinWidthMin_ui8)){
	cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.valid_ui8 = (uint8)FALSE;
	cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.valid_ui8 = (uint8)FALSE;

	ret_t = E_NOT_OK;
}
else
{
	/* Save last window detection parameters */
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowStart_ui32 = cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.pos_ui32;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowEnd_ui32 = cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.pos_ui32;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSize_ui8 = windowSize_ui8;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSizeLeftMiddle_ui8 = windowSizeLeftMiddle_ui8;

	/* Determine new zero position */
	/* Zero position is part step zero if there exists one within the window */
	/* otherwise the window's edge part step which is closer to zero */
	/* Different strategy: zero is defined to be at last full step position */
	/* correct pointer position */
	/* TODO: COMPASS: Koordinatensystem darf nicht einfach verschoben werden!!! */
	zeroPositionAbsolute_ui32 = cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowStart_ui32 + ((uint32)CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE - partStep1st_ui32);
	cdd_motor_Data_as[motor_e].currPosLevel1_ui32 =
	((Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32 + cdd_motor_Data_as[motor_e].currPosLevel1_ui32) - zeroPositionAbsolute_ui32) % Cdd_Motor_Cfg_as[motor_e].uStepMaximumAbsolute_ui32;
}

	return ret_t;
}

/**
 *  \brief Zero detection: enable zero detection
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_ZD_EnableDetection(const Cdd_Motor_MotorNumberEnum motor_e) {
	if (CDD_MOTOR_MTR_HHSS == motor_e) {
		Dio_WriteChannel(DIO_CHANNEL_PF7, DIO_LEVEL_HIGH);
	} else {
		Dio_WriteChannel(DIO_CHANNEL_PF6, DIO_LEVEL_HIGH);
	}

	/* Do not enable zero detection if it was already enabled */
	if (cdd_motor_zeroDetectionWindow_as[motor_e].enabled_ui8 != (uint8) TRUE) {
		cdd_motor_zeroDetectionWindow_as[motor_e].enabled_ui8 = (uint8) TRUE;
		cdd_motor_zeroDetectionWindow_as[motor_e].state_e =
				CDD_MOTOR_ZERO_DET_STATE_INITIAL;
	} else {
		; /* Keep running detection */
	}
}

/**
 * \brief Zero detection: disable zero detection
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_ZD_DisableDetection(const Cdd_Motor_MotorNumberEnum motor_e) {
	/* Set Port F 6 output to low */
	*((uint8 * const ) CDD_MOTOR_PTF_DATA_REG_ADR_UI16 ) &=
			(uint8) (~((uint8) (0x1U << CDD_MOTOR_NO1_BITPOS_UI8 ))); /*lint !e923 */
	/* Reset zero detection debounce structure because zero detection was switched off */
	cdd_motor_debounceRise_as[motor_e].ctr_ui8 = (uint8) 0U;
	cdd_motor_debounceRise_as[motor_e].dir_e = CDD_MOTOR_DIR_UNDEF;
	cdd_motor_debounceRise_as[motor_e].posAbsolute_ui32 =
			CDD_MOTOR_INVALID_POS_UI32;
	cdd_motor_debounceFall_as[motor_e].ctr_ui8 = (uint8) 0U;
	cdd_motor_debounceFall_as[motor_e].dir_e = CDD_MOTOR_DIR_UNDEF;
	cdd_motor_debounceFall_as[motor_e].posAbsolute_ui32 =
			CDD_MOTOR_INVALID_POS_UI32;

	/* Reset detection structure */
	cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.pos_ui32 =
			CDD_MOTOR_INVALID_POS_UI32;
	cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.dir_e =
			CDD_MOTOR_DIR_UNDEF;
	cdd_motor_zeroDetectionWindow_as[motor_e].rising_s.valid_ui8 =
			(uint8) FALSE;
	cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.pos_ui32 =
			CDD_MOTOR_INVALID_POS_UI32;
	cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.dir_e =
			CDD_MOTOR_DIR_UNDEF;
	cdd_motor_zeroDetectionWindow_as[motor_e].falling_s.valid_ui8 =
			(uint8) FALSE;

	/* Do not invalidate valid results */
#if 0
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowStart_ui32 = CDD_MOTOR_ZERO_POSITION_INVALID_UI32;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowEnd_ui32 = CDD_MOTOR_ZERO_POSITION_INVALID_UI32;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSize_ui8 = CDD_MOTOR_ZERO_WIDTH_INVALID_UI8;
	cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSizeLeftMiddle_ui8 = CDD_MOTOR_ZERO_WIDTH_INVALID_UI8;
#endif

	/* Disable zero detection */
	cdd_motor_zeroDetectionWindow_as[motor_e].enabled_ui8 = (uint8) FALSE;
	cdd_motor_zeroDetectionWindow_as[motor_e].state_e =
			CDD_MOTOR_ZERO_DET_STATE_INITIAL;
}

/**
 * \brief Zero detection: return current state of zero detection
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

boolean Cdd_Motor_ZD_IsDetectionEnabled(const Cdd_Motor_MotorNumberEnum motor_e) {
	return (boolean) cdd_motor_zeroDetectionWindow_as[motor_e].enabled_ui8;
}

/**
 * \brief Zero detection: return whether active zero window is currently detected
 * Remark: This routine returns the current real PIN state without any debouncing etc.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint8 Cdd_Motor_ZD_IsCurrentPositionInZeroWindow(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	uint8 ret_ui8;

	ret_ui8 = (uint8) FALSE;

	if (motor_e == CDD_MOTOR_MTR_HHSS) {
		if ((uint8) CDD_MOTOR_PTT_GET(CDD_MOTOR_NO2_BITPOS_UI8) == (uint8) TRUE) /*lint !e923 */
		{
			ret_ui8 = (uint8) TRUE;
		}
	} else {
		if ((uint8) CDD_MOTOR_PTT_GET(CDD_MOTOR_NO1_BITPOS_UI8) == (uint8) TRUE) /*lint !e923 */
		{
			ret_ui8 = (uint8) TRUE;
		}
	}

	return ret_ui8;
}

/**
 *  \brief Zero detection: checks whether zero detection is complete and valid
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

uint8 Cdd_Motor_ZD_IsDetectionCompleteAndValid(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	return (uint8) ((cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSize_ui8
			!= CDD_MOTOR_ZERO_WIDTH_INVALID_UI8 )
			&& (cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSizeLeftMiddle_ui8
					!= CDD_MOTOR_ZERO_WIDTH_INVALID_UI8 ));
}

/*
 * \brief Zero detection: return size of zero window in micro steps
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      0x0 - 0xFE: Distance in microsteps
 0xFF:       Invalid
 */

uint8 Cdd_Motor_ZD_GetWindowSize(const Cdd_Motor_MotorNumberEnum motor_e) {
	return cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSize_ui8;
}

/*
 * \brief Zero detection: return distance in microsteps from zero position to zero window's left edge.
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      0x0 - 0xFE: Distance in microsteps
 0xFF:       Invalid
 */

uint8 Cdd_Motor_ZD_GetDistanceZeroPositionAndLeftWindowEdge(
		const Cdd_Motor_MotorNumberEnum motor_e) {
	return cdd_motor_zeroDetectionWindow_as[motor_e].lastResult_s.windowSizeLeftMiddle_ui8;
}

/* ************************************************************************** *
 * ISR ********************************************************************** *
 * ************************************************************************** */

#pragma optimize_for_size off
#pragma opt_lifetimes on
/**
 *  \brief
 *
 * \param [in]  ---
 * \param [out] ---
 * \return      ---
 */

void Cdd_Motor_RunMotorISR(void) {
	boolean disable_HHSS_b = FALSE;
	boolean disable_MM_b = FALSE;

	if (TRUE == cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrIsRunning_ui8) {
		disable_HHSS_b = Cdd_Motor_RunMotorISR_HHSS();
	}
	if (TRUE == cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrIsRunning_ui8) {
		disable_MM_b = Cdd_Motor_RunMotorISR_MM();
	}
	if (disable_MM_b && disable_HHSS_b) {
		(void) Mtr_SetMotorInterrupt(MTR_CTRL_MCTOIE_DISABLE);
	}
}

boolean Cdd_Motor_RunMotorISR_HHSS(void) {
	static uint16 isrUsedNbrOfPeriodes_ui16_HHSS; // TODO viene sempre scritta perchè è statica
	boolean disableMotorInterrupt_b = FALSE;
	uint8 index = 0;
	/* ISR MTR HHSS */
	if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrPeriodeCounter_ui16
			> (uint16) 1u) /* c:7,5 */
			{
		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrPeriodeCounter_ui16--; /* c:5,5 */
	} else if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrPeriodeCounter_ui16
			== (uint16) 1u) /* c:7,5 */
			{
		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrPeriodeCounter_ui16--; /* c:5,5 */

		/* change step mode if necessary */
		// TODO: Be aware of speed ramp
		if ((cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].stepModeChangeReq_e
				!= CDD_MOTOR_STEPMODE_UNDEF)
				&& (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8
						== (uint8) 0u)) {
			Cdd_Motor_ChangeStepModeConfig(CDD_MOTOR_MTR_HHSS);
		} else {
			; /* do nothing */
		}

		if (cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].enabled_ui8
				== (uint8) TRUE) {
			uint8 bitpos_ui8;

			/* Set POS_CHECK_M1 pin as output */
			bitpos_ui8 = CDD_MOTOR_PTT_GET(CDD_MOTOR_NO2_BITPOS_UI8); /*lint !e923 */

			/* DEBOUNCING FOR ZERO DETECTION */
			/* Detect rising edge / active zero window */
			if (bitpos_ui8 != (uint8) 0U) {
				if (cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].ctr_ui8
						<= cdd_motor_debouncingThresh_ui8) {
					if (cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].ctr_ui8
							== (uint8) 0U) {
						/* store second detection point */
						cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].posAbsolute_ui32 =
								cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32;
						/* store direction */
						cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].dir_e =
								cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].dir_e;
					}

					cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].ctr_ui8++;
				} else {
					/* Reset falling counter if threshold reached */
					cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].ctr_ui8 =
							(uint8) 0U;

					if (CDD_MOTOR_ZERO_DET_STATE_DETECTING_FIRST
							== cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].state_e) {
						/* store first detection information */
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].rising_s.pos_ui32 =
								cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].posAbsolute_ui32;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].rising_s.dir_e =
								cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].dir_e;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].rising_s.valid_ui8 =
								(uint8) TRUE;

						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].state_e =
								CDD_MOTOR_ZERO_DET_STATE_DETECTING_SECOND;
					} else {
						; /* do nothing */
					}
				}
			}
			/* Detect failing edge / NO zero window */
			else {
				if (cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].ctr_ui8
						<= cdd_motor_debouncingThresh_ui8) {
					if (cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].ctr_ui8
							== (uint8) 0U) {
						/* store second detection point */
						cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].posAbsolute_ui32 =
								cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32;
						/* store direction */
						cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].dir_e =
								cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].dir_e;
					}

					cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].ctr_ui8++;
				} else {
					/* Reset rising counter if threshold reached */
					cdd_motor_debounceRise_as[CDD_MOTOR_MTR_HHSS].ctr_ui8 =
							(uint8) 0U;

					if (CDD_MOTOR_ZERO_DET_STATE_DETECTING_SECOND
							== cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].state_e) {
						/* store second detection information */
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].falling_s.pos_ui32 =
								cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].posAbsolute_ui32;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].falling_s.dir_e =
								cdd_motor_debounceFall_as[CDD_MOTOR_MTR_HHSS].dir_e;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].falling_s.valid_ui8 =
								(uint8) TRUE;

						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].state_e =
								CDD_MOTOR_ZERO_DET_STATE_DETECTION_VALIDATE;
					} else if (CDD_MOTOR_ZERO_DET_STATE_INITIAL
							== cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].state_e) {
						/* Leave initial state ONLY if zero window is INactive */
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_HHSS].state_e =
								CDD_MOTOR_ZERO_DET_STATE_DETECTING_FIRST;
					} else {
						; /* do nothing */
					}
				}
			}
		}
	} else /* c:7,5 */
	{

		/* Nbr of periods is reached. Reset counter and apply new speed/period threshold */
		isrUsedNbrOfPeriodes_ui16_HHSS =
				cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrTargetNbrOfPeriodes_ui16; /* c:5,5 */

		cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrPeriodeCounter_ui16 =
				(uint16) isrUsedNbrOfPeriodes_ui16_HHSS; /* c:4 */

		if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32
				== cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].trgtPosLevel1_ui32) /* c:8,5 */
				{
			cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].isrIsRunning_ui8 =
					(uint8) FALSE;
			/* Disable Motor Interrupt, function will not be called again */
			disableMotorInterrupt_b = TRUE;

			/* change step mode if necessary */
			if ((cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].stepModeChangeReq_e
					!= CDD_MOTOR_STEPMODE_UNDEF)
					&& (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8
							== (uint8) 0u)) {
				Cdd_Motor_ChangeStepModeConfig(CDD_MOTOR_MTR_HHSS);
			} else {
				; /* do nothing */
			}
		} else {
			if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].dir_e
					== CDD_MOTOR_DIR_FORWARD) /* c:5,5 */
					{
				if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32
						>= (Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_HHSS].uStepMaximumAbsolute_ui32
								- (uint32) 1uL)) /* c:6 */
						{
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32 =
							0; /* c:4 */
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32++; /* c:5,5 */
				}

				if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8
						>= (CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE - (uint8) 1u)) {
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8 =
							(uint8) 0u;
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8++;
				}
			} else {
				if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32
						== (uint32) 0uL) {
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32 =
							(Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_HHSS].uStepMaximumAbsolute_ui32
									- (uint32) 1uL);
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel1_ui32--;
				}

				if (cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8
						== (uint8) 0u) {
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8 =
							(uint8) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE
									- (uint8) 1u;
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8--;
				}
			}
			/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
			/*lint !e960 */
			/* Set duty cycle ********************************************************************* */
			index = cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].currPosLevel0_ui8;
			CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR1(
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].usedPatternCoil_0_ui16[index]);
			/* c:8 */
			CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR1(
					cdd_motor_Data_as[CDD_MOTOR_MTR_HHSS].usedPatternCoil_1_ui16[index]);
			/* c:8 */
			ENABLE_ALL_INTERRUPTS();
			/*lint !e960 */
			/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */
		} /* 4 */
	}
	return disableMotorInterrupt_b;
}

#pragma opt_lifetimes off
#pragma optimize_for_size on

boolean Cdd_Motor_RunMotorISR_MM(void) {
	boolean disableMotorInterrupt_b = FALSE;
	uint8 index = 0;
	/* isrPeriodeCounter_ui16 is used to count each expired period.
	 * If the nbr of needed periods is reached a new pwm duty cycle/pwm pattern is set
	 */
	/* ISR MTR MM */
	static uint16 isrUsedNbrOfPeriodes_ui16_MM;

	if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrPeriodeCounter_ui16
			> (uint16) 1u) /* c:7,5 */
			{
		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrPeriodeCounter_ui16--; /* c:5,5 */
	} else if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrPeriodeCounter_ui16
			== (uint16) 1u) /* c:7,5 */
			{
		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrPeriodeCounter_ui16--; /* c:5,5 */

		/* change step mode if necessary */
		// TODO: Be aware of speed ramp
		if ((cdd_motor_Data_as[CDD_MOTOR_MTR_MM].stepModeChangeReq_e
				!= CDD_MOTOR_STEPMODE_UNDEF)
				&& (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8
						== (uint8) 0u)) {
			Cdd_Motor_ChangeStepModeConfig(CDD_MOTOR_MTR_MM);
		} else {
			; /* do nothing */
		}

		if (cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].enabled_ui8
				== (uint8) TRUE) {
			uint8 bitpos_ui8;

			/* Set POS_CHECK_M1 pin as output */
			bitpos_ui8 = CDD_MOTOR_PTT_GET(CDD_MOTOR_NO2_BITPOS_UI8); /*lint !e923 */

			/* DEBOUNCING FOR ZERO DETECTION */
			/* Detect rising edge / active zero window */
			if (bitpos_ui8 != (uint8) 0U) {
				if (cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].ctr_ui8
						<= cdd_motor_debouncingThresh_ui8) {
					if (cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].ctr_ui8
							== (uint8) 0U) {
						/* store second detection point */
						cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].posAbsolute_ui32 =
								cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32;
						/* store direction */
						cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].dir_e =
								cdd_motor_Data_as[CDD_MOTOR_MTR_MM].dir_e;
					}

					cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].ctr_ui8++;
				} else {
					/* Reset falling counter if threshold reached */
					cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].ctr_ui8 =
							(uint8) 0U;

					if (CDD_MOTOR_ZERO_DET_STATE_DETECTING_FIRST
							== cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].state_e) {
						/* store first detection information */
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].rising_s.pos_ui32 =
								cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].posAbsolute_ui32;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].rising_s.dir_e =
								cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].dir_e;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].rising_s.valid_ui8 =
								(uint8) TRUE;

						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].state_e =
								CDD_MOTOR_ZERO_DET_STATE_DETECTING_SECOND;
					} else {
						; /* do nothing */
					}
				}
			}
			/* Detect failing edge / NO zero window */
			else {
				if (cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].ctr_ui8
						<= cdd_motor_debouncingThresh_ui8) {
					if (cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].ctr_ui8
							== (uint8) 0U) {
						/* store second detection point */
						cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].posAbsolute_ui32 =
								cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32;
						/* store direction */
						cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].dir_e =
								cdd_motor_Data_as[CDD_MOTOR_MTR_MM].dir_e;
					}

					cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].ctr_ui8++;
				} else {
					/* Reset rising counter if threshold reached */
					cdd_motor_debounceRise_as[CDD_MOTOR_MTR_MM].ctr_ui8 =
							(uint8) 0U;

					if (CDD_MOTOR_ZERO_DET_STATE_DETECTING_SECOND
							== cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].state_e) {
						/* store second detection information */
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].falling_s.pos_ui32 =
								cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].posAbsolute_ui32;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].falling_s.dir_e =
								cdd_motor_debounceFall_as[CDD_MOTOR_MTR_MM].dir_e;
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].falling_s.valid_ui8 =
								(uint8) TRUE;

						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].state_e =
								CDD_MOTOR_ZERO_DET_STATE_DETECTION_VALIDATE;
					} else if (CDD_MOTOR_ZERO_DET_STATE_INITIAL
							== cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].state_e) {
						/* Leave initial state ONLY if zero window is INactive */
						cdd_motor_zeroDetectionWindow_as[CDD_MOTOR_MTR_MM].state_e =
								CDD_MOTOR_ZERO_DET_STATE_DETECTING_FIRST;
					} else {
						; /* do nothing */
					}
				}
			}
		}
	} else /* c:7,5 */
	{

		/* Nbr of periods is reached. Reset counter and apply new speed/period threshold */
		isrUsedNbrOfPeriodes_ui16_MM =
				cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrTargetNbrOfPeriodes_ui16; /* c:5,5 */

		cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrPeriodeCounter_ui16 =
				(uint16) isrUsedNbrOfPeriodes_ui16_MM; /* c:4 */

		if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32
				== cdd_motor_Data_as[CDD_MOTOR_MTR_MM].trgtPosLevel1_ui32) /* c:8,5 */
				{
			cdd_motor_Data_as[CDD_MOTOR_MTR_MM].isrIsRunning_ui8 =
					(uint8) FALSE;
			/* Disable Motor Interrupt, function will not be called again */
			// TODO non può essere diabilitata da un motore altrimenti non funziona più per l'altro !!!
			disableMotorInterrupt_b = TRUE;

			/* change step mode if necessary */
			if ((cdd_motor_Data_as[CDD_MOTOR_MTR_MM].stepModeChangeReq_e
					!= CDD_MOTOR_STEPMODE_UNDEF)
					&& (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8
							== (uint8) 0u)) {
				Cdd_Motor_ChangeStepModeConfig(CDD_MOTOR_MTR_MM);
			} else {
				; /* do nothing */
			}
		} else {
			if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].dir_e
					== CDD_MOTOR_DIR_FORWARD) /* c:5,5 */
					{
				if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32
						>= (Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_MM].uStepMaximumAbsolute_ui32
								- (uint32) 1uL)) /* c:6 */
						{
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32 = 0; /* c:4 */
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32++; /* c:5,5 */
				}

				if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8
						>= (CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE - (uint8) 1u)) {
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8 =
							(uint8) 0u;
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8++;
				}
			} else {
				if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32
						== (uint32) 0uL) {
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32 =
							(Cdd_Motor_Cfg_as[CDD_MOTOR_MTR_MM].uStepMaximumAbsolute_ui32
									- (uint32) 1uL);
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel1_ui32--;
				}

				if (cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8
						== (uint8) 0u) {
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8 =
							(uint8) CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE
									- (uint8) 1u;
				} else {
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8--;
				}
			}
			/* THIS SEQUENCE MAY NOT BE INTERRUPTED ********************************** */DISABLE_ALL_INTERRUPTS();
			/*lint !e960 */
			/* Set duty cycle ********************************************************************* */
			index = cdd_motor_Data_as[CDD_MOTOR_MTR_MM].currPosLevel0_ui8;
			CDD_MOTOR_SET_DUTYCYCLE_COIL0_MTR2(
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].usedPatternCoil_0_ui16[index]);
			/* c:8 */
			CDD_MOTOR_SET_DUTYCYCLE_COIL1_MTR2(
					cdd_motor_Data_as[CDD_MOTOR_MTR_MM].usedPatternCoil_1_ui16[index]);
			/* c:8 */
			ENABLE_ALL_INTERRUPTS();
			/*lint !e960 */
			/* END OF UNINTERRUPTABLE SEQUENCE *************************************** */
		} /* 4 */
	}
	return disableMotorInterrupt_b;
}

#pragma opt_lifetimes off
#pragma optimize_for_size on
