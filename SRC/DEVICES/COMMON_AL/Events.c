#include "Events.h"
#include "IIC0.h"

#include "Cdd_Motor.h"
#include "Al_Motor_PBcfg.h"

#include "Wdg.h"
#include "Cdd_IIC.h"

flags_t flags;
extern char *char_read;
static uint8 cnt = 0;
static uint16 sent = 0;

extern uint8 InpBufferS[9];
extern uint8 OutBufferS[9];
extern nxp_info_s mcu_info;
uint8 pos_speed_acc[9];
uint8 error[9] = "666777888";

uint32 curPos_ui32;
uint16 curSpeed_ui16;
uint8 data;
uint8 i2c_buf[8];

static uint8 command = 0;

// TODO TEMP
extern uint8 MCU;

/*
 ** ===================================================================
 **     Event       :  IIC0_OnRxChar (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         Called when a correct character is received. This event is
 **         not available for the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnRxChar(void) {
	uint16 pos;
	uint16 speed;

	if (1 == flags.Bits.R_WRITE_REQ) {
		IIC0_RecvChar(&command);
		cnt = 0;
		flags.Bits.R_WRITE_REQ = FALSE;
		// if command == 0x7A, reset by watchdog
		if (RESET == command) {
			Wdg_Trigger();
		}
	} else {
		uint8 data;
		IIC0_RecvChar(&data);
		InpBufferS[cnt] = data;
		cnt++;
	}

	if (8 == cnt) {
		switch (command) {
		case M1_TARGET_ALL:
			// Set Pos
			pos = InpBufferS[0];
			pos = pos << 8;
			pos |= InpBufferS[1];
			Cdd_IIC_Set_Pos_HHSS(pos);

			// Set Speed
			speed = InpBufferS[2];
			speed = speed << 8;
			speed |= InpBufferS[3];
			Cdd_IIC_Set_Speed_HHSS(speed);
			break;

		case M2_TARGET_ALL:
			// Set Pos
			pos = InpBufferS[0];
			pos = pos << 8;
			pos |= InpBufferS[1];
			Cdd_IIC_Set_Pos_MM(pos);

			// Set Speed
			speed = InpBufferS[2];
			speed = speed << 8;
			speed |= InpBufferS[3];
			Cdd_IIC_Set_Speed_MM(speed);
			break;

		case MCU_INFO:
			mcu_info.mcu = InpBufferS[0];
			mcu_info.status = InpBufferS[1];
			break;
		default:
			break;
		}
	}

}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnTxChar (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         Called when a correct character is sent (placed to the
 **         transmitter). This event is not available for the MASTER
 **         mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnTxChar(void) {
	flags.Bits.R_TX_CHAR = 1; /* Set the "TX" flag */
}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnReadReq (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         This event is invoked when its own specific address is
 **         matched with the calling address and the value of the R/W
 **         command bit of the calling address equal to 1, ie., the
 **         Master requests reading from slave (the slave will be
 **         sending). After the return from the event call the first
 **         data byte sending will start. This event is not available
 **         for the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnReadReq(void) {
	flags.Bits.R_READ_REQ = 1; /* Set the "READ REQ" flag */
	command = InpBufferS[0];

	switch (command) {
	case M1_TARGET_ALL:
		//IIC0_SendBlock(InpBufferS, 9, &sent);
		break;
	case M2_TARGET_ALL:
		//IIC0_SendBlock(InpBufferS, 9, &sent);
		break;
	case M1_CTRL_REG:
		//IIC0_SendBlock(InpBufferS, 9, &sent);
		break;
	case M2_CTRL_REG:
		//IIC0_SendBlock(InpBufferS, 9, &sent);
		break;
	case M1_CUR_ALL:
		curPos_ui32 = Cdd_Motor_GetPositionCurrentAbsolute(CDD_MOTOR_MTR_HHSS);
		curPos_ui32 *= AL_MOTORPOS_GEAR_DIVISOR;
		curPos_ui32 /= (CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE
				* AL_MOTORPOS_GEAR_FACTOR);

		curSpeed_ui16 = Cdd_IIC_Get_Speed_ui16(CDD_MOTOR_MTR_HHSS);

		pos_speed_acc[0] = (uint8) ((curPos_ui32 >> 8) & 0xFF);
		pos_speed_acc[1] = (uint8) (curPos_ui32 & 0xFF);
		pos_speed_acc[2] = (uint8) ((curSpeed_ui16 >> 8) & 0xFF);
		pos_speed_acc[3] = (uint8) (curSpeed_ui16 & 0xFF);
		pos_speed_acc[4] = 0xBB;
		pos_speed_acc[5] = 0xBB;
		pos_speed_acc[6] = 0xFF;
		pos_speed_acc[7] = 0xFF;

		IIC0_SendBlock(pos_speed_acc, 8, &sent);
		break;
	case M2_CUR_ALL:
		if (2 == MCU) {
			curPos_ui32 = Cdd_Motor_GetPositionCurrentAbsolute(
					CDD_MOTOR_MTR_MM);
			curPos_ui32 *= AL_MOTORPOS_GEAR_DIVISOR;
			curPos_ui32 /= (CDD_MOTOR_MICRO_STEPS_ARRAY_SIZE
					* AL_MOTORPOS_GEAR_FACTOR);

			curSpeed_ui16 = Cdd_IIC_Get_Speed_ui16(CDD_MOTOR_MTR_MM);
		} else {
			curPos_ui32 = 0xFFFFFFFF;
			curSpeed_ui16 = 0xFFFF;
		}
		pos_speed_acc[0] = (uint8) ((curPos_ui32 >> 8) & 0xFF);
		pos_speed_acc[1] = (uint8) (curPos_ui32 & 0xFF);
		pos_speed_acc[2] = (uint8) ((curSpeed_ui16 >> 8) & 0xFF);
		pos_speed_acc[3] = (uint8) (curSpeed_ui16 & 0xFF);
		pos_speed_acc[4] = 0xDD;
		pos_speed_acc[5] = 0xDD;
		pos_speed_acc[6] = 0xFF;
		pos_speed_acc[7] = 0xFF;

		IIC0_SendBlock(pos_speed_acc, 8, &sent);
		break;

	case RESET:
		InpBufferS[0] += 0x10;
		InpBufferS[1] += 0x10;
		InpBufferS[2] += 0x10;
		InpBufferS[3] += 0x10;
		InpBufferS[4] += 0x10;
		InpBufferS[5] += 0x10;
		InpBufferS[6] += 0x10;
		InpBufferS[7] += 0x10;

		IIC0_SendBlock(InpBufferS, 8, &sent);
		break;

	case MCU_INFO:
		InpBufferS[0] = mcu_info.mcu;
		InpBufferS[1] = mcu_info.status;
		InpBufferS[2] += 0xFF;
		InpBufferS[3] += 0xFF;
		InpBufferS[4] += 0xFF;
		InpBufferS[5] += 0xFF;
		InpBufferS[6] += 0xFF;
		InpBufferS[7] += 0xFF;

		IIC0_SendBlock(InpBufferS, 8, &sent);
		break;
	default:
		IIC0_SendBlock(error, 8, &sent);
		break;
	}

	IIC0_ClearRxBuf();

	command = 0;
}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnWriteReq (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         This event is invoked when its own specific address is
 **         matched with the calling address and the value of the R/W
 **         command bit of the calling address is set to 0, ie., the
 **         Master requests writing to the slave (the slave will be
 **         receiving). After the return from the event call the first
 **         data byte receiving starts. This event is not available for
 **         the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnWriteReq(void) {
	uint8 temp;
	flags.Bits.R_WRITE_REQ = 1; /* Set the "R_WRITE_REQ" flag */
	temp = IIC0IBDR;
}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnFreeTxBuf (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         The event is called when the last byte from the output
 **         buffer is sent. This event is not available for the MASTER
 **         mode.
 **         If OnTxChar event is also generated, this event is called
 **         after OnTxChar.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnFreeTxBuf(void) {
}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnFullRxBuf (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         Called when the input buffer is full, i.e. after reception
 **         of the last character that was successfully placed into
 **         input buffer. This event is not available for the MASTER
 **         mode. 
 **         If OnRxChar event also generated, this event is called after
 **         OnRxChar.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnFullRxBuf(void) {
}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnArbitLost (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         This event is called when the master lost the bus
 **         arbitration or the device detects an error on the bus. This
 **         event is enabled only if interrupts/events are enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnArbitLost(void) {
	flags.Bits.R_ARB_LOST = 1; /* Set the "ARB LOST" flag */
}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnError (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         This event is called when input data buffer has overrun.
 **         This event is not available for the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnError(void) {
	flags.Bits.R_ERR = 1; /* Set the "ERR" flag */
}

/*
 ** ===================================================================
 **     Event       :  IIC0_OnTxEmptyChar (module Events)
 **
 **     Component   :  IIC0 [InternalI2C]
 **     Description :
 **         The event is called when an Empty character is sent (see
 **         "Empty character" property for details about empty character).
 **         This event is not available for the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void IIC0_OnTxEmptyChar(void) {
}

/* END Events */

/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 0.00.00 [05.06]
 **     for the Freescale HCS12Z series of microcontrollers.
 **
 ** ###################################################################
 */
