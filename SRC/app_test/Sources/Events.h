/* ###################################################################
**     Filename    : Events.h
**     Project     : iic bl test
**     Processor   : MC9S12ZVHL32CLL
**     Component   : Events
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-03-26, 15:26, # CodeGen: 100
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         IFsh1_OnWriteEnd    - void IFsh1_OnWriteEnd(void);
**         CI2C1_OnReadReq     - void CI2C1_OnReadReq(void);
**         CI2C1_OnWriteReq    - void CI2C1_OnWriteReq(void);
**         CI2C1_OnRxChar      - void CI2C1_OnRxChar(void);
**         CI2C1_OnTxChar      - void CI2C1_OnTxChar(void);
**         CI2C1_OnFreeTxBuf   - void CI2C1_OnFreeTxBuf(void);
**         CI2C1_OnFullRxBuf   - void CI2C1_OnFullRxBuf(void);
**         CI2C1_OnError       - void CI2C1_OnError(void);
**         CI2C1_OnTxEmptyChar - void CI2C1_OnTxEmptyChar(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "CI2C1.h"
#include "WDog1.h"
#include "API.h"

typedef union {
	byte byte_flags;
	struct {
		byte R_ARB_LOST :1;
		byte R_ERR :1;
		byte R_READ_REQ :1;
		byte R_WRITE_REQ :1;
		byte R_RX_CHAR :1;
		byte R_TX_CHAR :1;
		byte :1;
		byte :1;
	} Bits;
} flags_t;

extern byte i2c_buf[8];
extern flags_t flags;

#pragma CODE_SEG DEFAULT

void CI2C1_OnReadReq(void);
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

void CI2C1_OnWriteReq(void);
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

void CI2C1_OnRxChar(void);
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

void CI2C1_OnTxChar(void);
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

void CI2C1_OnFreeTxBuf(void);
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

void CI2C1_OnFullRxBuf(void);
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

void CI2C1_OnError(void);
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

void CI2C1_OnTxEmptyChar(void);
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


void CI2C1_OnArbitLost(void);
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

void Cpu_OnIllegalOpcode(void);
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

/* END Events */
#endif /* __Events_H*/

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
