/* ###################################################################
 **     Filename    : Events.c
 **     Project     : iic bl test
 **     Processor   : MC9S12ZVHL32CLL
 **     Component   : Events
 **     Version     : Driver 01.04
 **     Compiler    : CodeWarrior HCS12Z C Compiler
 **     Date/Time   : 2024-02-09, 13:58, # CodeGen: 0
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

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "PE_Types.h"

#define M1_TARGET_ALL 0x1A
#define M2_TARGET_ALL 0x2A
#define M1_CTRL_REG 0x1F
#define M2_CTRL_REG 0x2F
#define M1_CUR_ALL 0x4A
#define M2_CUR_ALL 0x5A

extern flags_t flags;
extern char *char_read;
extern byte cnt;
extern word sent;
static byte command;
byte data;
byte i2c_buf[8];
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
		cnt = 0;
		flags.Bits.R_WRITE_REQ = FALSE;
		// if command == 0x7A, reset by watchdog
		if (0x7A == command) {
			CPMUARMCOP = 0x01U;
			CPMUARMCOP = 0x10U;
		}
	} else {
		byte data;
		CI2C1_RecvChar(&data);
		i2c_buf[cnt] = data + 0x10;
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
	CI2C1_SendBlock(i2c_buf, sizeof(i2c_buf), &sent);
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
}

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnFullRxBuf (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
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
void CI2C1_OnFullRxBuf(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  CI2C1_OnTxEmptyChar (module Events)
 **
 **     Component   :  CI2C1 [InternalI2C]
 **     Description :
 **         The event is called when an Empty character is sent (see
 **         "Empty character" property for details about empty character).
 **         This event is not available for the MASTER mode.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void CI2C1_OnTxEmptyChar(void) {
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  Cpu_OnIllegalOpcode (module Events)
 **
 **     Component   :  Cpu [MC9S12ZVHL64_100]
 **     Description :
 **         This event is called after unimplemented instruction
 **         execution.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void Cpu_OnIllegalOpcode(void) {
	/* Write your code here ... */
}

/* END Events */

/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale HCS12Z series of microcontrollers.
 **
 ** ###################################################################
 */
