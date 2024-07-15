/* ###################################################################
**     Filename    : CI2C1.c
**     Project     : jst_bl
**     Processor   : MC9S12ZVHL32CLL
**     Component   : InternalI2C
**     Version     : Component 01.287, Driver 01.22, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-04-23, 16:17
**     Abstract    :
**          This component encapsulates the internal I2C communication 
**          interface. The implementation of the interface is based 
**          on the Philips I2C-bus specification version 2.0. 
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible 
**              (see "Automatic stop condition" property)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
**     Settings    :
**         Serial channel              : IIC0
**
**         Protocol
**             Mode                    : SLAVE
**             Slave address           : 122
**             Empty character         : 220
**
**         Initialization
**
**             Component init          : Enabled
**             Events                  : Enabled
**
**         Registers
**             Input buffer            : IIC0IBDR  [0x07C4]
**             Output buffer           : IIC0IBDR  [0x07C4]
**             Control register        : IIC0IBCR  [0x07C2]
**             Status register         : IIC0IBSR  [0x07C3]
**             Baud setting reg.       : IIC0IBFD  [0x07C1]
**             Address register        : IIC0IBAD  [0x07C0]
**
**         Interrupt
**             Vector name             : Viic0
**             Priority                : 1
**
**         Used pins                   :
**       ----------------------------------------------------------
**            Function    | On package |    Name
**       ----------------------------------------------------------
**              SDA       |     63     |  PS5_TXCAN0_SDA0_KWS5
**              SCL       |     62     |  PS4_RXCAN0_SCL0_KWS4
**       ----------------------------------------------------------
**     Contents    :
**         Enable          - byte CI2C1_Enable(void);
**         Disable         - byte CI2C1_Disable(void);
**         SendChar        - byte CI2C1_SendChar(byte Chr);
**         RecvChar        - byte CI2C1_RecvChar(byte *Chr);
**         SendBlock       - byte CI2C1_SendBlock(void* Ptr, word Siz, word *Snt);
**         RecvBlock       - byte CI2C1_RecvBlock(void* Ptr, word Siz, word *Rcv);
**         ClearTxBuf      - byte CI2C1_ClearTxBuf(void);
**         ClearRxBuf      - byte CI2C1_ClearRxBuf(void);
**         GetCharsInTxBuf - word CI2C1_GetCharsInTxBuf(void);
**         GetCharsInRxBuf - word CI2C1_GetCharsInRxBuf(void);
**         GetMode         - bool CI2C1_GetMode(void);
**         CheckBus        - byte CI2C1_CheckBus(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file CI2C1.c
** @version 01.22
** @brief
**          This component encapsulates the internal I2C communication 
**          interface. The implementation of the interface is based 
**          on the Philips I2C-bus specification version 2.0. 
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible 
**              (see "Automatic stop condition" property)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
*/         
/*!
**  @addtogroup CI2C1_module CI2C1 module documentation
**  @{
*/         

/* MODULE CI2C1. */

#include "Events.h"
#include "CI2C1.h"

#pragma DATA_SEG CI2C1_DATA            /* Select data segment "CI2C1_DATA" */
#pragma CODE_SEG CI2C1_CODE
/*SerFlag bits*/
#define OVERRUN_ERR      0x01U         /* Overrun error flag bit   */
#define WAIT_RX_CHAR     0x02U         /* Wait for received char. flag bit (Master)  */
#define CHAR_IN_TX       0x04U         /* Char is in TX buffer (Master)    */
#define CHAR_IN_RX       0x08U         /* Char is in RX buffer     */
#define FULL_TX          0x10U         /* Full transmit buffer     */
#define BUSY             0x20U         /* Communication is in progress (Master) */
#define FULL_RX          0x40U         /* Full receive buffer      */
#define MSxSL            0x80U         /* Master x Slave flag bit  */

static bool EnUser;                    /* Enable/Disable device */
static word InpLenS;                   /* Length of input buffer's content */
static byte *InpPtrRS;                 /* Pointer for reading from input buffer */
static byte *InpPtrWS;                 /* Pointer for writing to input buffer */
static byte InpBufferS[64];            /* Input buffer I2C commmunication */
static word OutLenS;                   /* Length of output bufer's content */
static byte *OutPtrRS;                 /* Pointer for reading from output buffer */
static byte *OutPtrWS;                 /* Pointer for writing to output buffer */
static byte OutBufferS[64];            /* Output buffer for I2C commmunication */
word CI2C1_SndRcvTemp;                 /* Temporary variable for SendChar (RecvChar) when they call SendBlock (RecvBlock) */
static byte ChrTemp;                   /* Temporary variable for SendChar method */
static byte CI2C1_SerFlag;             /* Flags for serial communication */
                                       /* Bits: 0 - OverRun error */
                                       /*       1 - Wait for received char. flag bit (Master) */
                                       /*       2 - Char is in TX buffer (Master) */
                                       /*       3 - Char in RX buffer */
                                       /*       4 - Full TX buffer */
                                       /*       5 - Running int from TX */
                                       /*       6 - Full RX buffer */
                                       /*       7 - Master x Slave */


/*
** ===================================================================
**     Method      :  CI2C1_Interrupt (component InternalI2C)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the components event(s).
**         This method is internal.
** ===================================================================
*/
#define RXAK 0x01U
#define SRW  0x04U
#define IBAL 0x10U
#define IAAS 0x40U

#define ON_ARBIT_LOST 0x01U
#define ON_FULL_RX    0x02U
#define ON_RX_CHAR    0x04U
#define ON_FREE_TX    0x08U
#define ON_TX_CHAR    0x10U
#define ON_OVERRUN    0x20U
#define ON_TX_EMPTY   0x40U

#pragma CODE_SEG __NEAR_SEG NON_BANKED

ISR(CI2C1_Interrupt)
{
  byte Flags = 0U;                     /* Temporary variable for flags */
  byte Status = IIC0IBSR;              /* Safe status register */
  byte temp;
  IIC0IBSR_IBIF = 1U;                  /* Clear interrupt flag */
  if(IIC0IBCR_MS_SL){                  /* Is device in master mode? */
    return;
  }
  else {
    if(Status & IAAS) {                /* Addressed as a slave? */
      if(Status & IBAL) {              /* Arbitration lost? */
        Flags |= ON_ARBIT_LOST;        /* Set the OnArbitLost flag */
      }
      if(Status & SRW) {               /* Read? */
         __DI();
        CI2C1_OnReadReq();             /* Invoke OnReadReq event */
        IIC0IBCR_TX_RX = 1U;           /* Switch to Tx mode */
        if (OutLenS) {                 /* Is number of bytes in the transmit buffer greater then 0? */
          OutLenS--;                   /* Decrease number of chars in the transmit buffer */
          IIC0IBDR = *(OutPtrRS++);    /* Store char to transmitter register */
          /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
          if(OutPtrRS >= (OutBufferS + 64U)) { /* Is the pointer out of the transmit buffer? */
            OutPtrRS = OutBufferS;     /* Set pointer on the first item into the transmit buffer */
          }
          /*lint -restore Enable MISRA rule (17.2) checking. */
          Flags |= ON_TX_CHAR;         /* Set OnTxChar flag */
          if(OutLenS == 0U) {
            Flags |= ON_FREE_TX;       /* Set OnFreeTXBuf flag if last character was sent */
          }
        }
        else {
          IIC0IBDR = CI2C1_EOF;        /* Store the empty char to the transmit register */
          Flags |= ON_TX_EMPTY;        /* Set OnTxEmpty flag */
        }
      }
      else{
         __DI();
        CI2C1_OnWriteReq();            /* Invoke OnWriteReq event */
        IIC0IBCR_TX_RX = 0U;           /* Switch to Rx mode */
        (void)IIC0IBDR;                /* Dummy read character */
      }
    }
    else {
      if(Status & IBAL) {              /* Arbitration lost? */
        Flags |= ON_ARBIT_LOST;        /* Set the OnArbitLost flag */
      }
      else {
        if(IIC0IBCR_TX_RX) {           /* Transmit? */
          if(Status & RXAK) {          /* NACK from receiver */
            IIC0IBCR_TX_RX = 0U;       /* Switch to Rx mode */
            temp = IIC0IBDR;            /* Dummy read character */
          }
          else {
            if (OutLenS) {             /* Is number of bytes in the transmit buffer greater then 0? */
              OutLenS--;               /* Decrease number of chars in the transmit buffer */
              IIC0IBDR = *(OutPtrRS++); /* Store char to transmitter register */
              /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
              if(OutPtrRS >= (OutBufferS + 64U)) { /* Is the pointer out of the transmit buffer? */
                OutPtrRS = OutBufferS; /* Set pointer on the first item into the transmit buffer */
              }
              /*lint -restore Enable MISRA rule (17.2) checking. */
              Flags |= ON_TX_CHAR;     /* Set OnTxChar flag */
              if(OutLenS == 0U) {
                Flags |= ON_FREE_TX;   /* Set OnFreeTXBuf flag if last character was sent */
              }
            }
            else {
              IIC0IBDR = CI2C1_EOF;    /* Store the empty char to the transmit register */
              Flags |= ON_TX_EMPTY;    /* Set OnTxEmpty flag */
            }
          }
        }
        else {
          if(InpLenS < 64U) {          /* Is number of bytes in the receive buffer lower than size of buffer? */
            InpLenS++;                 /* Increse number of chars in the receive buffer */
            *(InpPtrWS)++ = IIC0IBDR;  /* Save received char to the receive buffer */
            /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
            if(InpPtrWS >= (InpBufferS + 64U)) { /* Is the pointer out of the receive buffer? */
              InpPtrWS = InpBufferS;   /* Set pointer on the first item into the receive buffer */
            }
            /*lint -restore Enable MISRA rule (17.2) checking. */
            Flags |= ON_RX_CHAR;       /* If yes then set the OnRxChar flag */
            if(InpLenS == 64U) {       /* Is number of bytes in the receive buffer equal to the size of buffer? */
              Flags |= ON_FULL_RX;     /* Set OnFullRxBuf flag */
            }
          }
          else {
            (void)IIC0IBDR;            /* Dummy read data register */
            CI2C1_SerFlag |= FULL_RX;  /* Set flag "full RX buffer" */
            Flags |= ON_OVERRUN;       /* Set the OnOverrun flag */
          }
        }
      }
    }
    if(Flags & ON_ARBIT_LOST) {        /* Is OnArbitLost flag set? */
       __DI();
      CI2C1_OnArbitLost();             /* If yes then invoke user event */
    }
    if(Flags & ON_OVERRUN) {           /* Is OnOverrun flag set? */
       __DI();
      CI2C1_OnError();                 /* If yes then invoke user event */
    }
    else {
      if(Flags & ON_RX_CHAR) {         /* Is OnRxChar flag set? */
         __DI();
        CI2C1_OnRxChar();              /* If yes then invoke user event */
      }
      if(Flags & ON_FULL_RX) {         /* Is OnFullRxBuff flag set? */
         __DI();
        ;           				   /* If yes then invoke user event */
      }
    }
    if (Flags & ON_TX_CHAR) {          /* Is OnTxChar flag set? */
       __DI();
      CI2C1_OnTxChar();                /* If yes then invoke user event */
    }
    if (Flags & ON_FREE_TX) {          /* Is OnFreeTxBuf flag set? */
       __DI();
      CI2C1_OnFreeTxBuf();             /* If yes then invoke user event */
    }
    if (Flags & ON_TX_EMPTY) {         /* Is OnTxEmptyChar flag set? */
       __DI();
      ;           					   /* If yes then invoke user event */
    }
  }
}

#pragma CODE_SEG CI2C1_CODE
/*
** ===================================================================
**     Method      :  CI2C1_Enable (component InternalI2C)
**     Description :
**         Enables I2C component. Events may be generated
**         ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte CI2C1_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    CI2C1_SerFlag &= (byte)~(byte)0x6FU; /* Clear the status variable */
    IIC0IBCR_IBEN = 1U;                /* Enable device */
    /* IIC0IBCR: IBEN=1,IBIE=1,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
    IIC0IBCR = 0xC0U;                  /* Control register settings */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CI2C1_Disable (component InternalI2C)
**     Description :
**         Disables I2C component. No events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte CI2C1_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    /* IIC0IBCR: IBEN=0,IBIE=0,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
    IIC0IBCR = 0U;                     /* Disable device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CI2C1_SendChar (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 0 to the I2C bus and then writes one
**         character (byte) to the bus. The slave address must be
**         specified before, by the "SelectSlave" or "SelectSlave10"
**         method or in the component initialization section, "Target
**         slave address init" property. If interrupt service is
**         enabled and the method returns ERR_OK, it doesn't mean that
**         transmission was successful. The state of transmission is
**         obtainable from (OnTransmitData, OnError or OnArbitLost)
**         events. 
**         When working as a SLAVE, this method writes a character to
**         the internal output slave buffer and, after the master
**         starts the communication, to the I2C bus. If no character is
**         ready for a transmission (internal output slave buffer is
**         empty), the Empty character will be sent (see "Empty
**         character" property).
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by an acknowledge (only in
**                           master mode and when interrupt service is
**                           disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot transmit data
**                           ERR_TXFULL - Transmitter is full (slave
**                           mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
** ===================================================================
*/
byte CI2C1_SendChar(byte Chr)
{
  ChrTemp = Chr;                       /* Save character */
  return (CI2C1_SendBlock(&ChrTemp, 1U, &CI2C1_SndRcvTemp)); /* Send character and return */
}

/*
** ===================================================================
**     Method      :  CI2C1_RecvChar (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 1 to the I2C bus, then reads one
**         character (byte) from the bus and then sends the stop
**         condition. The slave address must be specified before, by
**         the "SelectSlave" or "SelectSlave10" method or in component
**         initialization section, property "Target slave address init".
**         If interrupt service is enabled and the method returns
**         ERR_OK, it doesn't mean that transmission was finished
**         successfully. The state of transmission must be tested by
**         means of events (OnReceiveData, OnError or OnArbitLost). In
**         case of successful transmission, received data is ready
**         after OnReceiveData event is called. 
**         When working as a SLAVE, this method reads a character from
**         the input slave buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Received character.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledge (only
**                           in master mode and when interrupt service
**                           is disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot receive data
**                           ERR_RXEMPTY - No data in receiver (slave
**                           mode only)
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last character or block received
**                           (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
**                           ERR_NOTAVAIL - Method is not available in
**                           current mode - see the comment in the
**                           generated code
** ===================================================================
*/
/*
byte CI2C1_RecvChar(byte *Chr)

**  This method is implemented as a macro. See CI2C1.h file.  **
*/

/*
** ===================================================================
**     Method      :  CI2C1_SendBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 0 to the I2C bus and then writes the
**         block of characters to the bus. The slave address must be
**         specified before, by the "SelectSlave" or "SlaveSelect10"
**         method or in component initialization section, "Target slave
**         address init" property. If interrupt service is enabled and
**         the method returns ERR_OK, it doesn't mean that transmission
**         was successful. The state of transmission is detectable by
**         means of events (OnTransmitData, OnError or OnArbitLost).
**         Data to be send is not copied to an internal buffer and
**         remains in the original location. Therefore the content of
**         the buffer should not be changed until the transmission is
**         complete. Event OnTransmitData can be used to detect the end
**         of the transmission.
**         When working as a SLAVE, this method writes a block of
**         characters to the internal output slave buffer and then,
**         after the master starts the communication, to the I2C bus.
**         If no character is ready for a transmission (internal output
**         slave buffer is empty), the "Empty character" will be sent
**         (see "Empty character" property). In SLAVE mode the data are
**         copied to an internal buffer, if specified by "Output buffer
**         size" property.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send.
**         Siz             - Size of the block.
**       * Snt             - Amount of data sent (moved to a buffer).
**                           In master mode, if interrupt support is
**                           enabled, the parameter always returns the
**                           same value as the parameter 'Siz' of this
**                           method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by the acknowledge (only
**                           in master mode and when interrupt service
**                           is disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot transmit data
**                           ERR_TXFULL - Transmitter is full. Some data
**                           has not been sent. (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
** ===================================================================
*/
/*lint -save  -e818 Disable MISRA rule (16.7) checking. */
byte CI2C1_SendBlock(void* Ptr,word Siz,word *Snt)
{
  word count;                          /* Number of sent chars */

  if (Siz == 0U) {                     /* Test variable Size on zero */
    *Snt = 0U;
    return ERR_OK;                     /* If zero then OK */
  }
  EnterCritical();                     /* Enter the critical section */
  *Snt = 0U;                           /* Return number of sent chars */
  for(count=0U; count < Siz; count++) {
    if(OutLenS < 64U) {                /* Is number of bytes in the receive buffer lower than size of buffer? */
      OutLenS++;                       /* Increase number of bytes in the transmit buffer */
      *(OutPtrWS++) = *((byte *)Ptr + count); /* Store char to buffer */
      /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
      if (OutPtrWS >= (OutBufferS + 64U)) { /* Is the pointer out of the transmit buffer? */
        OutPtrWS = OutBufferS;         /* Set pointer to the first item in the transmit buffer */
      }
      /*lint -restore Enable MISRA rule (17.2) checking. */
      *Snt = *Snt + 1U;                /* Increment number of sent chars */
    }
    else {
      ExitCritical();                  /* Exit the critical section */
      return ERR_TXFULL;               /* Return with error */
    }
  }
  ExitCritical();                      /* Exit the critical section */
  return ERR_OK;                       /* OK */
}
/*lint -restore Enable MISRA rule (16.7) checking. */

/*
** ===================================================================
**     Method      :  CI2C1_RecvBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address bytes
**         inclusive of R/W bit = 1 to the I2C bus, then reads the
**         block of characters from the bus and then sends the stop
**         condition. The slave address must be specified before, by
**         the "SelectSlave" or "SelectSlave10" method or in component
**         initialization section, "Target slave address init" property.
**         If interrupt service is enabled and the method returns
**         ERR_OK, it doesn't mean that transmission was finished
**         successfully. The state of transmission must be tested by
**         means of events (OnReceiveData, OnError or OnArbitLost). In
**         case of successful transmission, received data is ready
**         after OnReceiveData event is called. 
**         When working as a SLAVE, this method reads a block of
**         characters from the input slave buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - A pointer to the block space for received
**                           data.
**         Siz             - The size of the block.
**       * Rcv             - Amount of received data. In master mode,
**                           if interrupt support is enabled, the
**                           parameter always returns the same value as
**                           the parameter 'Siz' of this method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED -  Device is disabled
**                           ERR_BUSY - The slave device is busy, it
**                           does not respond by an acknowledge (only in
**                           master mode and when interrupt service is
**                           disabled)
**                           ERR_BUSOFF - Clock timeout elapsed or
**                           device cannot receive data
**                           ERR_RXEMPTY - The receive buffer didn't
**                           contain the requested number of data. Only
**                           available data (or no data) has been
**                           returned  (slave mode only).
**                           ERR_OVERRUN - Overrun error was detected
**                           from last character or block receiving
**                           (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
**                           ERR_NOTAVAIL - Method is not available in
**                           current mode - see the comment in the
**                           generated code.
** ===================================================================
*/
byte CI2C1_RecvBlock(void* Ptr,word Siz,word *Rcv)
{
  word count;                          /* Number of sent chars */
  byte errrc = ERR_OK;                 /* Most serious error */

  if (Siz == 0U) {                     /* Test variable Size on zero */
    *Rcv = 0U;
    return ERR_OK;                     /* If zero then OK */
  }
  EnterCritical();                     /* Enter the critical section */
  if ((CI2C1_SerFlag & (OVERRUN_ERR | FULL_RX)) != 0U) { /* Has the overrun occured? */
    errrc = ERR_OVERRUN;               /* If yes then return OVERRUN error */
  }
  CI2C1_SerFlag &= (byte)~(byte)(OVERRUN_ERR | CHAR_IN_RX | FULL_RX); /* Clear flag "char in RX buffer" */
  *Rcv = 0U;                           /* Clear number of received chars */
  for(count=0U; count < Siz; count++) {
    if(InpLenS) {                      /* Is number of bytes in the receive buffer lower than size of buffer? */
      InpLenS--;                       /* Decrease number of received chars */
      *((byte *)Ptr + count) = *(InpPtrRS++); /* Read the char */
      /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
      if (InpPtrRS >= (InpBufferS + 64U)) { /* Is the pointer out of the receive buffer? */
        InpPtrRS = InpBufferS;         /* Set pointer to the first item into the receive buffer */
      }
      /*lint -restore Enable MISRA rule (17.2) checking. */
      (*Rcv)++;                        /* Increment number of sent chars */
    }
    else {
      ExitCritical();                  /* Exit the critical section */
      if(errrc==ERR_OVERRUN) {
        return ERR_OVERRUN;            /* Return with error */
      }
      else {
        return ERR_RXEMPTY;            /* Return with error */
      }
    }
  }
  ExitCritical();                      /* Exit the critical section */
  return errrc;                        /* Return error code */
}

/*
** ===================================================================
**     Method      :  CI2C1_ClearTxBuf (component InternalI2C)
**     Description :
**         This method clears all characters in internal slave output
**         buffer. This method is not available for the MASTER mode.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte CI2C1_ClearTxBuf(void)
{
  EnterCritical();                     /* Enter the critical section */
  OutLenS = 0U;                        /* Set number of chars in the receive buffer to 0 */
  OutPtrWS = OutBufferS;               /* Set pointers on the first item in the receive buffer */
  OutPtrRS = OutBufferS;
  CI2C1_SerFlag &= (byte)~(byte)(FULL_TX|CHAR_IN_TX);
  ExitCritical();                      /* Exit the critical section */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CI2C1_ClearRxBuf (component InternalI2C)
**     Description :
**         This method clears all characters in internal slave input
**         buffer. This method is not available for the MASTER mode.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte CI2C1_ClearRxBuf(void)
{
  EnterCritical();                     /* Enter the critical section */
  InpLenS = 0U;                        /* Set number of chars in the transmit buffer to 0 */
  InpPtrWS = InpBufferS;               /* Set pointers on the first item in the transmit buffer */
  InpPtrRS = InpBufferS;               /* Set pointers on the first item in the transmit buffer */
  CI2C1_SerFlag &= (byte)~(byte)(OVERRUN_ERR | CHAR_IN_RX | FULL_RX);
  ExitCritical();                      /* Exit the critical section */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  CI2C1_GetCharsInTxBuf (component InternalI2C)
**     Description :
**         Returns number of characters in the output buffer. In SLAVE
**         mode returns the number of characters in the internal slave
**         output buffer. In MASTER mode returns number of characters
**         to be sent from the user buffer (passed by SendBlock method).
**         This method is not supported in polling mode.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/
word CI2C1_GetCharsInTxBuf(void)
{
  return((word)OutLenS);               /* Return number of chars in the transmit buffer */
}

/*
** ===================================================================
**     Method      :  CI2C1_GetCharsInRxBuf (component InternalI2C)
**     Description :
**         Returns number of characters in the input buffer. In SLAVE
**         mode returns the number of characters in the internal slave
**         input buffer. In MASTER mode returns number of characters to
**         be received into a user buffer (passed by RecvChar or
**         RecvBlock method).
**         This method is not supported in polling mode.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer.
** ===================================================================
*/
word CI2C1_GetCharsInRxBuf(void)
{
  return((word)InpLenS);               /* Return number of chars in receive buffer */
}

/*
** ===================================================================
**     Method      :  CI2C1_GetMode (component InternalI2C)
**     Description :
**         This method returns the actual operating mode of this
**         component.
**     Parameters  : None
**     Returns     :
**         ---             - Actual operating mode value <true> -
**                           Master <false> - Slave
** ===================================================================
*/
/*
bool CI2C1_GetMode(void)

**  This method is implemented as a macro. See CI2C1.h file.  **
*/

/*
** ===================================================================
**     Method      :  CI2C1_Init (component InternalI2C)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal.
** ===================================================================
*/
void CI2C1_Init(void)
{
  /* IIC0IBCR: IBEN=0,IBIE=0,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
  IIC0IBCR = 0U;                       /* Clear control register */
  CI2C1_SerFlag = 0U;                  /* Reset all flags */
  EnUser = TRUE;                       /* Enable device */
  InpLenS = 0U;                        /* No char in the receive buffer */
  InpPtrRS = InpBufferS;               /* Set pointer on the first item in the receive buffer */
  InpPtrWS = InpBufferS;
  OutLenS = 0U;                        /* No char in the transmit buffer */
  OutPtrRS = OutBufferS;               /* Set pointer on the first item in the transmit buffer */
  OutPtrWS = OutBufferS;
  /* IIC0IBAD: ADR7=1,ADR6=1,ADR5=1,ADR4=1,ADR3=0,ADR2=1,ADR1=0,??=0 */
  IIC0IBAD = 0xF4U;                    /* Define slave address */
  /* IIC0IBCR2: GCEN=0,ADTYPE=0,??=0,??=0,??=0,ADR10=0,ADR9=0,ADR8=0 */
  IIC0IBCR2 = 0x00U;
  /* IIC0IBFD: IBC7=0,IBC6=0,IBC5=0,IBC4=0,IBC3=1,IBC2=0,IBC1=0,IBC0=1 */
  IIC0IBFD = 0x09U;                    /* Set prescaler bits */
  IIC0IBCR_IBEN = 1U;                  /* Enable device */
  /* IIC0IBCR: IBEN=1,IBIE=1,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
  IIC0IBCR = 0xC0U;                    /* Control register settings */
}

/*
** ===================================================================
**     Method      :  CI2C1_CheckBus (component InternalI2C)
**     Description :
**         This method returns the status of the bus. If the START
**         condition has been detected, the method returns
**         'ComponentName'_BUSY. If the STOP condition has been
**         detected, the method returns 'ComponentName'_IDLE.
**     Parameters  : None
**     Returns     :
**         ---             - Status of the bus.
** ===================================================================
*/
/*
byte CI2C1_CheckBus(void)

**  This method is implemented as a macro. See CI2C1.h file.  **
*/


/* END CI2C1. */

/*!
** @}
*/
