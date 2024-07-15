/* ###################################################################
**     Filename    : Events.h
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

#include "MC9S12ZVHL32.h"
#include "Error.h"
#include "Const.h"
#include "CI2C1.h"
#include "IFsh1.h"
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

#pragma CODE_SEG DEFAULT


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

void IFsh1_OnWriteEnd(void);
/*
** ===================================================================
**     Event       :  IFsh1_OnWriteEnd (module Events)
**
**     Component   :  IFsh1 [IntFLASH]
*/
/*!
**     @brief
**         Event is called after a write operation to FLASH memory is
**         finished (except [SetPage]). This event is available only if
**         an [Interrupt service/event] is selected.
*/
/* ===================================================================*/

void CI2C1_OnReadReq(void);
/*
** ===================================================================
**     Event       :  CI2C1_OnReadReq (module Events)
**
**     Component   :  CI2C1 [InternalI2C]
**     Description :
**         This event is invoked when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address equal to 1, i.e., the
**         Master requests reading from slave (the slave will be
**         sending). After the return from the event call the first
**         data byte sending will start. This event is not available
**         for the MASTER mode.
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

void CI2C1_OnWriteReq(void);
/*
** ===================================================================
**     Event       :  CI2C1_OnWriteReq (module Events)
**
**     Component   :  CI2C1 [InternalI2C]
**     Description :
**         This event is invoked when its own specific address is
**         matched with the calling address and the value of the R/W
**         command bit of the calling address is set to 0, i.e., the
**         Master requests writing to the slave (the slave will be
**         receiving). After the return from the event call the first
**         data byte receiving starts. This event is not available for
**         the MASTER mode.
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

void CI2C1_OnNACKReq(void);
/*
** ===================================================================
**     Event       :  CI2C1_OnNACKReq (module Events)
**
**     Component   :  CI2C1 [InternalI2C]
**     Description :
**         This event is invoked when its own specific address is
**         matched with the calling address and a NACK is received.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnMachineException(void);
/*
** ===================================================================
**     Event       :  Cpu_OnMachineException (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This software event is called when machine exception
**         interrupt occurs.This event allocates Machine Exception
**         interrupt vector.
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

void Cpu_OnSpareOpcode(void);
/*
** ===================================================================
**     Event       :  Cpu_OnSpareOpcode (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is called after unimplemented page 1 instruction interrupt
**         execution.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnSwINT(void);
/*
** ===================================================================
**     Event       :  Cpu_OnSwINT (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This software event is called after software reset.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnSysCall(void);
/*
** ===================================================================
**     Event       :  Cpu_OnSysCall (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This software event is called after system call interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnLvdStatusChanged(void);
/*
** ===================================================================
**     Event       :  Cpu_OnLvdStatusChanged (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is triggered by any change of the LVD status
**         bit. Enabling this event also allocate LVI interrupt
**         vector (see CPU interrupts on Properties tab of the Cpu
**         component).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnHighTemperatureStatusChanged(void);
/*
** ===================================================================
**     Event       :  Cpu_OnHighTemperatureStatusChanged (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is triggered by any change of the High
**         temperature status bit. This event allocates <High
**         temperature interrupt> vector.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnPllLockStatusChanged(void);
/*
** ===================================================================
**     Event       :  Cpu_OnPllLockStatusChanged (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is triggered by any change of the LOCK status
**         bit. Enabling this event also allocate PLL interrupt
**         vector (see CPU interrupts on Properties tab of the Cpu
**         component). PLL must be enabled to enable this event.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnOscStatusChanged(void);
/*
** ===================================================================
**     Event       :  Cpu_OnOscStatusChanged (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is triggered when oscillator corruption is
**         detected. This event allocates <Oscillator Status Changed interrupt
**         vector>.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnSpuriousInterrupt(void);
/*
** ===================================================================
**     Event       :  Cpu_OnSpuriousInterrupt (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is called after spurious interrupt has been
**         detected. Enabling this event also allocate  Spurious
**         interrupt vector (see CPU interrupts on Properties tab of
**         the Cpu component).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Cpu_OnSRAM_ECCerror(void);
/*
** ===================================================================
**     Event       :  Cpu_OnSRAM_ECCerror (module Events)
**
**     Component   :  Cpu [MC9S12ZVHL64_100]
**     Description :
**         This event is called after SRAM single bit ECC error
**         interrupt has been detected. This event allocates
**         Single bit SRAM ECC interrupt vector.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*!
** @}
*/
