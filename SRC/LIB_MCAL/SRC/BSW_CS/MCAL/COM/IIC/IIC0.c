#include "Events.h"
#include "IIC0.h"
#include "IIC0_Cfg.h"

/* Global variables */
volatile uint8 CCR_reg;                 /* Current CCR reegister */

#define __DI() \
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */\
                { __asm(sei); }      /* Disable global interrupts  */ \
/*lint -restore Enable MISRA rule (1.1) checking. */
#define __EI() \
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */\
                { __asm(cli); }      /* Enable global interrupts */ \
/*lint -restore Enable MISRA rule (1.1) checking. */
#define EnterCritical() \
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */\
    { __asm(PSH CCL); __asm(SEI); __asm(MOV.B (0,S),CCR_reg); __asm(LEA S,(1,S)); } /* This macro is used by Processor Expert. It saves CCR register and disable global interrupts. */ \
/*lint -restore Enable MISRA rule (1.1) checking. */
#define ExitCritical() \
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */\
    { __asm(LEA S,(-1,S)); __asm(MOV.B CCR_reg,(0,S)); __asm(PUL CCL); } /* This macro is used by Processor Expert. It restores CCR register saved in SaveStatusReg(). */ \
/*lint -restore Enable MISRA rule (1.1) checking. */

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void IIC0_ISR( void );
#pragma CODE_SEG DEFAULT

/*SerFlag bits*/
#define OVERRUN_ERR      0x01U         /* Overrun error flag bit   */
#define WAIT_RX_CHAR     0x02U         /* Wait for received char. flag bit (Master)  */
#define CHAR_IN_TX       0x04U         /* Char is in TX buffer (Master)    */
#define CHAR_IN_RX       0x08U         /* Char is in RX buffer     */
#define FULL_TX          0x10U         /* Full transmit buffer     */
#define BUSY             0x20U         /* Communication is in progress (Master) */
#define FULL_RX          0x40U         /* Full receive buffer      */
#define MSxSL            0x80U         /* Master x Slave flag bit  */

static boolean EnUser;                    /* Enable/Disable device */
static uint16 InpLenS;                   /* Length of input buffer's content */
static uint8 *InpPtrRS;                 /* Pointer for reading from input buffer */
static uint8 *InpPtrWS;                 /* Pointer for writing to input buffer */
uint8 InpBufferS[9];             /* Input buffer I2C commmunication */
static uint16 OutLenS;                   /* Length of output bufer's content */
static uint8 *OutPtrRS;                 /* Pointer for reading from output buffer */
static uint8 *OutPtrWS;                 /* Pointer for writing to output buffer */
uint8 OutBufferS[9];             /* Output buffer for I2C commmunication */
uint16 IIC0_SndRcvTemp;                 /* Temporary variable for SendChar (RecvChar) when they call SendBlock (RecvBlock) */
static uint8 ChrTemp;                   /* Temporary variable for SendChar method */
static uint8 IIC0_SerFlag;             /* Flags for serial communication */
                                       /* Bits: 0 - OverRun error */
                                       /*       1 - Wait for received char. flag bit (Master) */
                                       /*       2 - Char is in TX buffer (Master) */
                                       /*       3 - Char in RX buffer */
                                       /*       4 - Full TX buffer */
                                       /*       5 - Running int from TX */
                                       /*       6 - Full RX buffer */
                                       /*       7 - Master x Slave */

// TODO TEMP
nxp_info_s mcu_info;

static uint8 received;
uint8 Flags = 0U; 

extern uint16 rcv;

#define ENABLE_ALL_INTERRUPTS()    asm(CLI) /*lint !e960 */
#define DISABLE_ALL_INTERRUPTS()   asm(SEI) /*lint !e960 */

/*
** ===================================================================
**     Method      :  IIC0_ISR (component InternalI2C)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the components event(s).
**         This method is internal. It is used by Processor Expert only.
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
__interrupt void IIC0_ISR(void)
{
   uint8 Status = IIC0IBSR;             /* Safe status register */

   IIC0IBSR_IBIF = 1U;                  /* Clear interrupt flag */
   
   Flags = 0;                          /* Temporary variable for flags */
   
   if(IIC0IBCR_MS_SL){                  /* Is device in master mode? */
      return;
   }
   else {
      if(Status & IAAS) {                /* Addressed as a slave? */
         if(Status & IBAL) {              /* Arbitration lost? */
            Flags |= ON_ARBIT_LOST;        /* Set the OnArbitLost flag */
         }
         if(Status & SRW) {               /* Read? */
            DISABLE_ALL_INTERRUPTS();

            IIC0_OnReadReq();             /* Invoke OnReadReq event */
            IIC0IBCR_TX_RX = 1U;           /* Switch to Tx mode */
            if (OutLenS) {                 /* Is number of bytes in the transmit buffer greater then 0? */
               OutLenS--;                   /* Decrease number of chars in the transmit buffer */
               IIC0IBDR = *(OutPtrRS++);    /* Store char to transmitter register */
               /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
               if(OutPtrRS >= (OutBufferS + 9U)) { /* Is the pointer out of the transmit buffer? */
                  OutPtrRS = OutBufferS;     /* Set pointer on the first item into the transmit buffer */
               }
               /*lint -restore Enable MISRA rule (17.2) checking. */
               Flags |= ON_TX_CHAR;         /* Set OnTxChar flag */
               if(OutLenS == 0U) {
                  Flags |= ON_FREE_TX;       /* Set OnFreeTXBuf flag if last character was sent */
               }
            }
            else {
               IIC0IBDR = IIC0_EOF;        /* Store the empty char to the transmit register */
               Flags |= ON_TX_EMPTY;        /* Set OnTxEmpty flag */
            }
         }
         else{
            DISABLE_ALL_INTERRUPTS();
            
            IIC0_OnWriteReq();            /* Invoke OnWriteReq event */
            IIC0IBCR_TX_RX = 0U;           /* Switch to Rx mode */
            received = IIC0IBDR;             /* read of IBDR register */
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
                  received = IIC0IBDR;             /* read of IBDR register */
               }
               else {
                  if (OutLenS) {             /* Is number of bytes in the transmit buffer greater then 0? */
                     OutLenS--;               /* Decrease number of chars in the transmit buffer */
                     IIC0IBDR = *(OutPtrRS++); /* Store char to transmitter register */
                     /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
                     if(OutPtrRS >= (OutBufferS + 9U)) { /* Is the pointer out of the transmit buffer? */
                        OutPtrRS = OutBufferS; /* Set pointer on the first item into the transmit buffer */
                     }
                     /*lint -restore Enable MISRA rule (17.2) checking. */
                     Flags |= ON_TX_CHAR;     /* Set OnTxChar flag */
                     if(OutLenS == 0U) {
                        Flags |= ON_FREE_TX;   /* Set OnFreeTXBuf flag if last character was sent */
                     }
                  }
                  else {
                     IIC0IBDR = IIC0_EOF;    /* Store the empty char to the transmit register */
                     Flags |= ON_TX_EMPTY;    /* Set OnTxEmpty flag */
                  }
               }
            }
            else {
               if(InpLenS < 9U) {           /* Is number of bytes in the receive buffer lower than size of buffer? */
                  InpLenS++;                 /* Increse number of chars in the receive buffer */
                  *(InpPtrWS)++ = IIC0IBDR;  /* Save received char to the receive buffer */
                  /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
                  if(InpPtrWS >= (InpBufferS + 9U)) { /* Is the pointer out of the receive buffer? */
                     InpPtrWS = InpBufferS;   /* Set pointer on the first item into the receive buffer */
                  }
                  /*lint -restore Enable MISRA rule (17.2) checking. */
                  Flags |= ON_RX_CHAR;       /* If yes then set the OnRxChar flag */
                  if(InpLenS == 9U) {        /* Is number of bytes in the receive buffer equal to the size of buffer? */
                     Flags |= ON_FULL_RX;     /* Set OnFullRxBuf flag */
                  }
               }
               else {
                  received = IIC0IBDR;       /* read of IBDR register */
                  IIC0_SerFlag |= FULL_RX;   /* Set flag "full RX buffer" */
                  Flags |= ON_OVERRUN;       /* Set the OnOverrun flag */
               }
            }
         }
      }
      if(Flags & ON_ARBIT_LOST) {        /* Is OnArbitLost flag set? */
         DISABLE_ALL_INTERRUPTS();

         IIC0_OnArbitLost();             /* If yes then invoke user event */
      }
      if(Flags & ON_OVERRUN) {           /* Is OnOverrun flag set? */
         DISABLE_ALL_INTERRUPTS();

         IIC0_OnError();                 /* If yes then invoke user event */
      }
      else {
         if(Flags & ON_RX_CHAR) {         /* Is OnRxChar flag set? */
            DISABLE_ALL_INTERRUPTS();
            
            IIC0_OnRxChar();              /* If yes then invoke user event */
         }
         if(Flags & ON_FULL_RX) {         /* Is OnFullRxBuff flag set? */
            DISABLE_ALL_INTERRUPTS();

            IIC0_OnFullRxBuf();           /* If yes then invoke user event */
         }
      }
      if (Flags & ON_TX_CHAR) {          /* Is OnTxChar flag set? */
         DISABLE_ALL_INTERRUPTS();
                  
         IIC0_OnTxChar();                /* If yes then invoke user event */
      }
      if (Flags & ON_FREE_TX) {          /* Is OnFreeTxBuf flag set? */
         DISABLE_ALL_INTERRUPTS();
                 
         IIC0_OnFreeTxBuf();             /* If yes then invoke user event */
      }
      if (Flags & ON_TX_EMPTY) {         /* Is OnTxEmptyChar flag set? */
         DISABLE_ALL_INTERRUPTS();
                  
         IIC0_OnTxEmptyChar();           /* If yes then invoke user event */
      }
   }
}
#pragma CODE_SEG DEFAULT

/*
** ===================================================================
**     Method      :  IIC0_Enable (component InternalI2C)
**     Description :
**         Enables I2C component. Events may be generated
**         ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           E_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
uint8 IIC0_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    IIC0_SerFlag &= (uint8)~(uint8)0x6FU; /* Clear the status variable */
    IIC0IBCR_IBEN = 1U;                /* Enable device */
    /* IIC0IBCR: IBEN=1,IBIE=1,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
    IIC0IBCR = 0xC0U;                  /* Control register settings */
  }
  return E_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  IIC0_Disable (component InternalI2C)
**     Description :
**         Disables I2C component. No events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           E_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
uint8 IIC0_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    /* IIC0IBCR: IBEN=0,IBIE=0,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
    IIC0IBCR = 0U;                     /* Disable device */
  }
  return E_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  IIC0_SendChar (component InternalI2C)
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
uint8 IIC0_SendChar(uint8 Chr)
{
  ChrTemp = Chr;                       /* Save character */
  return (IIC0_SendBlock(&ChrTemp, 1U, &IIC0_SndRcvTemp)); /* Send character and return */
}

/*
** ===================================================================
**     Method      :  IIC0_RecvChar (component InternalI2C)
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
uint8 IIC0_RecvChar(uint8 *Chr)

**  This method is implemented as a macro. See IIC0.h file.  **
*/

/*
** ===================================================================
**     Method      :  IIC0_EnableEvent (component InternalI2C)
**     Description :
**         Enables the events.
**         This method is enabled only if any event is generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           E_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
uint8 IIC0_EnableEvent(void)

**  This method is implemented as a macro. See IIC0.h file.  **
*/

/*
** ===================================================================
**     Method      :  IIC0_SendBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address uint8s
**         inclusive of R/W bit = 0 to the I2C bus and then writes the
**         block of characters to the bus. The slave address must be
**         specified before, by the "SelectSlave" or "SlaveSelect10"
**         method or in component initialization section, "Target slave
**         address init" property. If interrupt service is enabled and
**         the method returns E_OK, it doesn't mean that transmission
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
**                           E_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           E_NOT_OK -  Device is disabled
**                           E_NOT_OK - The slave device is busy, it
**                           does not respond by the acknowledge (only
**                           in master mode and when interrupt service
**                           is disabled)
**                           E_NOT_OK - Clock timeout elapsed or
**                           device cannot transmit data
**                           ERR_TXFULL - Transmitter is full. Some data
**                           has not been sent. (slave mode only)
**                           ERR_ARBITR - Arbitration lost (only when
**                           interrupt service is disabled and in master
**                           mode)
** ===================================================================
*/
/*lint -save  -e818 Disable MISRA rule (16.7) checking. */
uint8 IIC0_SendBlock(uint8* Ptr,uint16 Siz,uint16 *Snt)
{
   uint16 count;                          /* Number of sent chars */

   if (Siz == 0U) {                     /* Test variable Size on zero */
     *Snt = 0U;
     return E_OK;                     /* If zero then OK */
   }
   EnterCritical();                     /* Enter the critical section */
   *Snt = 0U;                           /* Return number of sent chars */
   for(count=0U; count < Siz; count++) {
     if(OutLenS < 9U) {                 /* Is number of bytes in the receive buffer lower than size of buffer? */
       OutLenS++;                       /* Increase number of bytes in the transmit buffer */
       *(OutPtrWS++) = *((uint8 *)Ptr + count); /* Store char to buffer */
       /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
       if (OutPtrWS >= (OutBufferS + 9U)) { /* Is the pointer out of the transmit buffer? */
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
   
   return E_OK;                       /* OK */
}

/*lint -restore Enable MISRA rule (16.7) checking. */

/*
** ===================================================================
**     Method      :  IIC0_RecvBlock (component InternalI2C)
**     Description :
**         When working as a MASTER, this method writes one (7-bit
**         addressing) or two (10-bit addressing) slave address uint8s
**         inclusive of R/W bit = 1 to the I2C bus, then reads the
**         block of characters from the bus and then sends the stop
**         condition. The slave address must be specified before, by
**         the "SelectSlave" or "SelectSlave10" method or in component
**         initialization section, "Target slave address init" property.
**         If interrupt service is enabled and the method returns
**         E_OK, it doesn't mean that transmission was finished
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
**                           E_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           E_NOT_OK -  Device is disabled
**                           E_NOT_OK - The slave device is busy, it
**                           does not respond by an acknowledge (only in
**                           master mode and when interrupt service is
**                           disabled)
**                           E_NOT_OK - Clock timeout elapsed or
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
uint8 IIC0_RecvBlock(void* Ptr,uint16 Siz,uint16 *Rcv)
{
   uint16 count;                          /* Number of sent chars */
   uint8 errrc = ERR_OK;                 /* Most serious error */

   if (Siz == 0U) {                     /* Test variable Size on zero */
     *Rcv = 0U;
     return ERR_OK;                     /* If zero then OK */
   }
   EnterCritical();                     /* Enter the critical section */
   if ((IIC0_SerFlag & (OVERRUN_ERR | FULL_RX)) != 0U) { /* Has the overrun occured? */
     errrc = ERR_OVERRUN;               /* If yes then return OVERRUN error */
   }
   IIC0_SerFlag &= (uint8)~(uint8)(OVERRUN_ERR | CHAR_IN_RX | FULL_RX); /* Clear flag "char in RX buffer" */
   *Rcv = 0U;                           /* Clear number of received chars */
   for(count=0U; count < Siz; count++) {
     if(InpLenS) {                      /* Is number of bytes in the receive buffer lower than size of buffer? */
       InpLenS--;                       /* Decrease number of received chars */
       *((uint8 *)Ptr + count) = *(InpPtrRS++); /* Read the char */
       /*lint -save  -e946 Disable MISRA rule (17.2) checking. */
       if (InpPtrRS >= (InpBufferS + 9U)) { /* Is the pointer out of the receive buffer? */
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
uint8 IIC0_ClearTxBuf(void)
{
  EnterCritical();                     /* Enter the critical section */
  OutLenS = 0U;                        /* Set number of chars in the receive buffer to 0 */
  OutPtrWS = OutBufferS;               /* Set pointers on the first item in the receive buffer */
  OutPtrRS = OutBufferS;
  IIC0_SerFlag &= (uint8)~(uint8)(FULL_TX|CHAR_IN_TX);
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
uint8 IIC0_ClearRxBuf(void)
{
  EnterCritical();                     /* Enter the critical section */
  InpLenS = 0U;                        /* Set number of chars in the transmit buffer to 0 */
  InpPtrWS = InpBufferS;               /* Set pointers on the first item in the transmit buffer */
  InpPtrRS = InpBufferS;               /* Set pointers on the first item in the transmit buffer */
  IIC0_SerFlag &= (uint8)~(uint8)(OVERRUN_ERR | CHAR_IN_RX | FULL_RX);
  ExitCritical();                      /* Exit the critical section */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  IIC0_GetCharsInTxBuf (component InternalI2C)
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
uint16 IIC0_GetCharsInTxBuf(void)
{
  return(OutLenS);                     /* Return number of chars remaining in the Master Tx buffer */
}

/*
** ===================================================================
**     Method      :  IIC0_GetCharsInRxBuf (component InternalI2C)
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
uint16 IIC0_GetCharsInRxBuf(void)
{
  return(InpLenS);                     /* Return number of chars remaining in the Master Rx buffer */
}

/*
** ===================================================================
**     Method      :  IIC0_SelectSlave (component InternalI2C)
**     Description :
**         This method selects a new slave for communication by its
**         7-bit slave address value. Any send or receive method
**         directs to or from selected device, until a new slave device
**         is selected by this method. This method is not available for
**         the SLAVE mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Slv             - 7-bit slave address value.
**     Returns     :
**         ---             - Error code, possible codes:
**                           E_OK - OK
**                           E_NOT_OK - The device is busy, wait until
**                           the current operation is finished.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           E_NOT_OK -  The device is disabled
** ===================================================================
*/
uint8 IIC0_SelectSlave(uint8 Slv)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return E_NOT_OK;               /* If yes then error */
  }
  if (IIC0IBCR_MS_SL == 1U) {          /* Is the device in the active state? */
    return E_NOT_OK;                   /* If yes then error */
  }
  IIC0IBAD = (uint8)(Slv << 1);  /* Set slave address */
  return E_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  IIC0_Init (component InternalI2C)
**
**     Description :
**         Initializes the associated peripheral(s) and the components
**         internal variables. The method is called automatically as a
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void IIC0_Init(void)
{
   /* IIC0IBCR: IBEN=0,IBIE=0,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
   IIC0IBCR = 0U;                       /* Clear control register */
   IIC0_SerFlag = 0U;                  /* Reset all flags */
   
   EnUser = TRUE;                       /* Enable device */
   
   InpLenS = 0U;                        /* No char in the receive buffer */
   InpPtrRS = InpBufferS;               /* Set pointer on the first item in the receive buffer */
   InpPtrWS = InpBufferS;
   OutLenS = 0U;                        /* No char in the transmit buffer */
   OutPtrRS = OutBufferS;               /* Set pointer on the first item in the transmit buffer */
   OutPtrWS = OutBufferS;
   
   /* IIC0IBCR: IBIE=0 */
   IIC0IBCR = 0x40U;
   /* IIC0IBSR: IBIF=1 */
   IIC0IBSR = 0x02U;
   /* IIC0IBAD: ADR7=1,ADR6=1,ADR5=1,ADR4=1,ADR3=1,ADR2=0,ADR1=0,??=0 */
   IIC0IBAD = 0xF4U;                    /* Define slave address 0x7A */
      
   /* IIC0IBCR2: GCEN=0,ADTYPE=0,??=0,??=0,??=0,ADR10=0,ADR9=0,ADR8=0 */
   IIC0IBCR2 = 0x00U;
   /* IIC0IBFD: IBC7=0,IBC6=0,IBC5=0,IBC4=0,IBC3=0,IBC2=0,IBC1=0,IBC0=0 */
   IIC0IBFD = 0x00U;                    /* Set prescaler bits */
   IIC0IBCR_IBEN = 1U;                  /* Enable device */
   /* IIC0IBCR: IBEN=1,IBIE=1,MS_SL=0,TX_RX=0,TXAK=0,RSTA=0,??=0,IBSWAI=0 */
   IIC0IBCR = 0xC0U;                    /* Control register settings */
}

/**
 * \brief Function to get the frame for the received IIC frame.
 *
 * Returns the frame for the received LIN id.
 * Function is called by upper layer.
 *
 * \param [in]  id_ui8 - filtered id from LIN id
 * \param [out] frame_ps - pointer to struct of received LIN message
 * \return      newFrameReceived_b - information about new received frame
 * \retval      TRUE = LIN frame found in configuration
 * \retval      FALSE = LIN frame not found in LIN configuration or Frame is not updated
 */
boolean IIC0_GetBuffer (uint8* frame_ps)
{
	/* ------ variables declaration ------ */
	//uint8 frameIndex_ui8;
	boolean frameReady_b;

	/* --- init module global variables --- */

	/* ----- init internal variables ----- */
	frameReady_b = FALSE;

	/* ----------- source code ----------- */
	IIC0_RecvBlock(frame_ps, 9, &rcv);
	frameReady_b = TRUE;
	return frameReady_b;
}

/* END IIC0. */

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
