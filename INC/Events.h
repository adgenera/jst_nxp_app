#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "IIC0.h"
#include "IIC0_Cfg.h"

typedef union {
   uint8 byte_flags;
   struct {
      uint8 R_ARB_LOST :1;
      uint8 R_ERR :1;
      uint8 R_READ_REQ :1;
      uint8 R_WRITE_REQ :1;
      uint8 R_RX_CHAR :1;
      uint8 R_TX_CHAR :1;
      uint8 :1;
      uint8 :1;
   } Bits;
} flags_t;

#pragma CODE_SEG DEFAULT

void IIC0_OnRxChar(void);
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

void IIC0_OnTxChar(void);
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

void IIC0_OnReadReq(void);
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

void IIC0_OnWriteReq(void);
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

void IIC0_OnFreeTxBuf(void);
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

void IIC0_OnFullRxBuf(void);
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

void IIC0_OnArbitLost(void);
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

void IIC0_OnError(void);
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

void IIC0_OnTxEmptyChar(void);
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

/* END Events */
#endif /* __Events_H*/

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
