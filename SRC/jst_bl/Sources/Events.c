/* ###################################################################
 **     Filename    : Events.c
 **     Project     : jst_bl
 **     Processor   : MC9S12ZVHL32CLL
 **     Component   : Events
 **     Version     : Driver 01.04
 **     Compiler    : CodeWarrior HCS12Z C Compiler
 **     Date/Time   : 2024-02-09, 13:58
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file Events.c
 ** @version 01.04
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes */
#include "BL.h"
#include "MC9S12ZVHL32.h"

extern flags_t flags;
extern char *char_read;
extern byte cnt;
extern commands_ut commands;
extern word sent;
static byte command;
extern bl_flags_ut bl_flags;
byte data;

#pragma CODE_SEG DEFAULT

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnRxChar (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
 **     Description :
 **         Called when a correct character is received. This event is
 **         not available for the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void CI2C1_OnRxChar(void) {
	if (1 == flags.Bits.R_WRITE_REQ) {
		CI2C1_RecvChar(&command);
		switch (command) {
		case ERASE:
			commands.erase.command = command;
			break;
		case WRITE_HEADER:
			commands.program_header.command = command;
			break;
		case WRITE_PAYLOAD:
			commands.program_payload.command = command;
			break;
		case FUNCTION:
			commands.function.command = command;
			break;
		case STATUS:
			break;
		case RESET:
			commands.function.command = command;
			bl_fsm_status.command_recv = TRUE;
			bl_flags.detail.reset = TRUE;
		default:
			break;
		}
		cnt = 0;
		flags.Bits.R_WRITE_REQ = FALSE;
	} else {
		byte data;
		CI2C1_RecvChar(&data);
		switch (command) {
		case ERASE:
			if (cnt < sizeof(commands.erase.data) - 1) {
				commands.erase.data[cnt] = data;
			} else if (cnt == sizeof(commands.erase.data) - 1) {
				commands.erase.data[cnt] = data;
				bl_fsm_status.command_recv = TRUE;
				bl_flags.detail.erase = TRUE;
			}
			break;
		case WRITE_HEADER:
			if (cnt < sizeof(commands.program_header.data) - 1) {
				commands.program_header.data[cnt] = data;
			} else if (cnt == sizeof(commands.program_header.data) - 1) {
				commands.program_header.data[cnt] = data;
				bl_fsm_status.command_recv = TRUE;
				bl_flags.detail.header = TRUE;
			}
			break;
		case WRITE_PAYLOAD:
			if (cnt < sizeof(commands.program_payload.data) - 1) {
				commands.program_payload.data[cnt] = data;
			} else if (cnt == sizeof(commands.program_payload.data) - 1) {
				commands.program_payload.data[cnt] = data;
				bl_fsm_status.command_recv = TRUE;
				bl_flags.detail.payload = TRUE;
			}
			break;
		case FUNCTION:
			if (cnt < sizeof(commands.function.data)) {
				commands.function.data = data;
				bl_fsm_status.command_recv = TRUE;
				bl_flags.detail.function = TRUE;
			}
			break;
		case STATUS:
			break;
		default:
			break;
		}
		cnt++;
	}
}

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnTxChar (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
 **     Description :
 **         Called when a correct character is sent (placed to the
 **         transmitter). This event is not available for the MASTER
 **         mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void CI2C1_OnTxChar(void) {
	flags.Bits.R_TX_CHAR = TRUE; /* Set the "TX" flag */
}



/*
 ** ===================================================================
 **     Event       :  CI2C1_OnReadReq (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
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
void CI2C1_OnReadReq(void) {
	flags.Bits.R_READ_REQ = TRUE; /* Set the "READ REQ" flag */
	//while (command == 0)
	//	;
	bl_flags.detail.r = TRUE;
	bl_flags.detail.w = FALSE;
	switch (command) {
	case ERASE:
		CI2C1_SendBlock(commands.erase.data, sizeof(commands.erase.data),
				&sent);
		break;
	case WRITE_HEADER:
		CI2C1_SendBlock(commands.program_header.data,
				sizeof(commands.program_header.data), &sent);
		break;
	case WRITE_PAYLOAD:
		CI2C1_SendBlock(commands.program_payload.data,
				sizeof(commands.program_payload.data), &sent);
		break;
	case FUNCTION:
		CI2C1_SendBlock(&commands.function.data, sizeof(commands.function.data),
				&sent);
		break;
	case STATUS:
		CI2C1_SendBlock(&bl_flags.flags, sizeof(word), &sent);
		break;
	default:
		break;
	}
}

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnArbitLost (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
 **     Description :
 **         This event is called when the master lost the bus
 **         arbitration or the device detects an error on the bus. This
 **         event is enabled only if interrupts/events are enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void CI2C1_OnArbitLost(void) {
	flags.Bits.R_ARB_LOST = TRUE; /* Set the "ARB LOST" flag */
}

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnError (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
 **     Description :
 **         This event is called when input data buffer has overrun.
 **         This event is not available for the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void CI2C1_OnError(void) {
	flags.Bits.R_ERR = TRUE; /* Set the "ERR" flag */
}

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnWriteReq (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
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
void CI2C1_OnWriteReq(void) {
	/* Write your code here ... */
	byte temp;
	flags.Bits.R_WRITE_REQ = TRUE; /* Set the "R_WRITE_REQ" flag */
	temp = IIC0IBDR;
	bl_flags.detail.r = FALSE;
	bl_flags.detail.w = TRUE;
}

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnFreeTxBuf (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
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
void CI2C1_OnFreeTxBuf(void) {
	/* Write your code here ... */
	bl_flags.detail.r = FALSE;
	bl_flags.detail.w = FALSE;
}

/* END Events */

/*!
 ** @}
 */

