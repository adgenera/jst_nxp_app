/* ###################################################################
 **     Filename    : IFsh1.c
 **     Project     : jst_bl
 **     Processor   : MC9S12ZVHL32CLL
 **     Component   : IntFLASH
 **     Version     : Component 02.409, Driver 02.18, CPU db: 3.00.000
 **     Compiler    : CodeWarrior HCS12Z C Compiler
 **     Date/Time   : 2024-03-11, 16:07, # CodeGen: 95
 **     Abstract    :
 **         This component "IntFLASH" implements an access to internal FLASH.
 **         The component support reading/writing data into FLASH, erasing of
 **         selected sector.
 **         The component supports events if the write interrupt is supported.
 **         The component supports following modes of write operations:
 **           - Write - writing without any test.
 **           - Destructive write - sector is erased if necessary.
 **           - Safe write - user event is invoked to save and resore data
 **                          from the current sector.
 **         The component requires on-chip FLASH memory (not used/allocated by
 **         other components).
 **     Settings    :
 **         Total FLASH memory size       : 32KB
 **         Number of FLASH memory blocks : 1
 **           Sector size                 : 0x0200
 **         Interrupt service             : Enabled
 **         Write method                  : Write
 **         Wait in RAM                   : yes
 **     Contents    :
 **         DisableEvent  - byte IFsh1_DisableEvent(void);
 **         EnableEvent   - byte IFsh1_EnableEvent(void);
 **         Busy          - bool IFsh1_Busy(byte Block);
 **         EraseVerify   - byte IFsh1_EraseVerify(byte Block, bool *Blank);
 **         EraseSector   - byte IFsh1_EraseSector(IFsh1_TAddress Addr);
 **         SetProtection - byte IFsh1_SetProtection(bool ProtectType, byte ProtectHigh, byte ProtectLow,...
 **         SetByteFlash  - byte IFsh1_SetByteFlash(IFsh1_TAddress Addr, byte Data);
 **         GetByteFlash  - byte IFsh1_GetByteFlash(IFsh1_TAddress Addr, byte *Data);
 **         SetWordFlash  - byte IFsh1_SetWordFlash(IFsh1_TAddress Addr, word Data);
 **         GetWordFlash  - byte IFsh1_GetWordFlash(IFsh1_TAddress Addr, word *Data);
 **         SetLongFlash  - byte IFsh1_SetLongFlash(IFsh1_TAddress Addr, dword Data);
 **         GetLongFlash  - byte IFsh1_GetLongFlash(IFsh1_TAddress Addr, dword *Data);
 **         SetBlockFlash - byte IFsh1_SetBlockFlash(IFsh1_TDataAddress Source, IFsh1_TAddress Dest, word...
 **         GetBlockFlash - byte IFsh1_GetBlockFlash(IFsh1_TAddress Source, IFsh1_TDataAddress Dest, word...
 **         DataPtr2Addr  - IFsh1_TAddress IFsh1_DataPtr2Addr(void* Addr);
 **         FuncPtr2Addr  - IFsh1_TAddress IFsh1_FuncPtr2Addr(void(*Addr)());
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
 ** @file IFsh1.c
 ** @version 02.18
 ** @brief
 **         This component "IntFLASH" implements an access to internal FLASH.
 **         The component support reading/writing data into FLASH, erasing of
 **         selected sector.
 **         The component supports events if the write interrupt is supported.
 **         The component supports following modes of write operations:
 **           - Write - writing without any test.
 **           - Destructive write - sector is erased if necessary.
 **           - Safe write - user event is invoked to save and resore data
 **                          from the current sector.
 **         The component requires on-chip FLASH memory (not used/allocated by
 **         other components).
 */
/*!
 **  @addtogroup IFsh1_module IFsh1 module documentation
 **  @{
 */

/* MODULE IFsh1. */

#include "IFsh1.h"
#include "Events.h"

#pragma DATA_SEG IFsh1_DATA            /* Select data segment "IFsh1_DATA" */
#pragma CODE_SEG IFsh1_CODE

/*lint -save  -e923 -e926 -e927 -e928 -e929 Disable MISRA rule (11.3,11.4) checking. */
/* Types definitions */

typedef struct {
	byte code[15]; /* Structure required to copy code to ram memory */
/* Size of this structure needs to be at least (but best) the size of the FnCmdInRam_ */
} FnCmdInRamStruct;

typedef void (*pFnCmdInRam)(void);

/* Global variables */

static bool EnEvent; /* Enable/Disable events */

#pragma CODE_SEG __NEAR_SEG NON_BANKED

static void FnCmdInRam_(void) {
	FSTAT = 0x80U; /* Clear flag command buffer empty */
	while (FSTAT_CCIF == 0U) {
	} /* Wait to command complete */
	return;
}

/*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
static void CallFnCmdInRam() {
	FnCmdInRamStruct FnCmdInRam = *(FnCmdInRamStruct *) (FnCmdInRam_); /* Create a copy of Wait in RAM routine on stack */

	((pFnCmdInRam) &FnCmdInRam)(); /* Call code in RAM */
	return;
}
/*lint -restore Enable MISRA rule (1.2) checking. */

#pragma CODE_SEG IFsh1_CODE

/*
 ** ===================================================================
 **     Method      :  BlockOutOfRange (component IntFLASH)
 **
 **     Description :
 **         The method checks if selected block is present in the flash 
 **         module.
 **         This method is internal.
 ** ===================================================================
 */
#define BlockOutOfRange(Addr1, Addr2) ((Addr1 > Addr2) || (Addr2 > 0x00FFFFFFUL) || (Addr1 < 0x00FF8000UL))

/*
 ** ===================================================================
 **     Method      :  BlockAddress (component IntFLASH)
 **
 **     Description :
 **         The method returns address of a specific block.
 **         This method is internal.
 ** ===================================================================
 */
#define BlockAddress(Block) (0x00FF8000UL)

/*
 ** ===================================================================
 **     Method      :  ClearFlags (component IntFLASH)
 **
 **     Description :
 **         The method clear error flags of Flash module.
 **         This method is internal.
 ** ===================================================================
 */
#define ClearFlags()  (FSTAT = 0x30U)

/*
 ** ===================================================================
 **     Method      :  WriteWord (component IntFLASH)
 **
 **     Description :
 **         The method writes a word to the Flash memory.
 **         This method is internal.
 ** ===================================================================
 */
static byte WriteWord(IFsh1_TAddress Addr, word Data16) {
	byte err = 0U;
	dword PhraseAddr; /* Address of a phrase (8-byte aligned) */
	byte diff;

	EnterCritical()
	; /* Enter critical section */
	ClearFlags(); /* Clear all flags */
	if (FSTAT_CCIF == 0U) { /* Is command buffer full ? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_BUSY; /* If yes then error */
	}
	FCCOBIX = 5U; /* Indicate number of words being loaded */
	FCCOB0HI = 0x06U; /* Program P-Flash command */
	FCCOB0LO = (byte) (Addr >> 16U); /* High address word */
	PhraseAddr = Addr & 0xFFFFFFF8UL; /* Phrase is aligned to 8 bytes */
	FCCOB1 = (word) (PhraseAddr); /* Low address word */
	*((volatile dword*) &FCCOB2) = *((dword *) (PhraseAddr)); /* Load previously stored data */
	*((volatile dword*) &FCCOB4) = *((dword *) (PhraseAddr + 4U)); /* Load previously stored data */
	diff = ((byte) (Addr & 0x07U)) >> 1; /* difference between address and phrase */
	*(((volatile word*) &FCCOB2) + diff) = Data16; /* Load new data */
	CallFnCmdInRam(); /* Copy Wait in RAM routine to stack and launch the flash process */
	if (FSTAT_FPVIOL == 1U) { /* Is protection violation detected ? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_NOTAVAIL; /* If yes then error */
	}
	if (FSTAT_ACCERR == 1U) { /* Is access error detected ? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_NOTAVAIL; /* If yes then error */
	}
	if (FSTAT_MGSTAT) { /* Was attempt to write data to the given address errorneous? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_VALUE; /* If yes then error */
	}
	FCNFG_CCIE = 1U; /* Enable interrupt */
	ExitCritical()
	; /* Exit critical section */
	return ERR_OK; /* OK */
}
/*
 ** ===================================================================
 **     Method      :  WriteArray (component IntFLASH)
 **
 **     Description :
 **         The method writes a variable number of bytes  to the Flash 
 **         memory.
 **         This method is internal.
 ** ===================================================================
 */
static byte WriteArray(IFsh1_TAddress Addr, const byte *Data, word Size) {
	word i;
	byte err = 0U;
	dword PhraseAddr; /* Address of a phrase (8-byte aligned) */
	byte diff;
	byte j;

	EnterCritical()
	; /* Enter critical section */
	ClearFlags(); /* Clear all flags */
	PhraseAddr = Addr & 0xFFFFFFF8UL; /* Phrase is aligned to 8 bytes */
	diff = (byte) (Addr & 0x07U);
	i = 0U;
	while (i < Size) {
		FCCOBIX = 5U; /* Clear index register */
		FCCOB0HI = 0x06U; /* Program P-Flash command */
		FCCOB0LO = (byte) (PhraseAddr >> 16U); /* High address word */
		FCCOB1 = (word) (PhraseAddr); /* Low address word */
		for (j = 0U; j < 8U; j += 2U) {
			if ((diff > 0U) || (i >= Size)) { /* Is address outside written range ? */
				*((volatile word*) &FCCOB2 + (j >> 1)) = *((word *) (PhraseAddr
						+ j)); /* Yes - Load previously stored data */
				diff -= 2U;
			} else {
				*((volatile word*) &FCCOB2 + (j >> 1)) = *((const word *) (Data
						+ i)); /* Load new data */
				i += 2U;
			}
		} /* for j */
		CallFnCmdInRam(); /* Copy Wait in RAM routine to stack and launch the flash process */
		if (FSTAT_FPVIOL == 1U) { /* Is protection violation detected ? */
			ExitCritical()
			; /* Exit critical section */
			return ERR_NOTAVAIL; /* If yes then error */
		}
		if (FSTAT_ACCERR == 1U) { /* Is access error detected ? */
			ExitCritical()
			; /* Exit critical section */
			return ERR_NOTAVAIL;
		}
		if (FSTAT_MGSTAT != 0U) { /* Was attempt to write data to the given address errorneous? */
			err = 1U;
		}
		PhraseAddr += 8U;
	}
	if (err != 0U) {
		ExitCritical()
		; /* Exit critical section */
		return ERR_VALUE; /* If yes then error */
	}
	FCNFG_CCIE = 1U; /* Enable interrupt */
	ExitCritical()
	; /* Exit critical section */
	return ERR_OK; /* OK */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_EraseVerify (component IntFLASH)
 */
/*!
 **     @brief
 **         Verifies entire memory array of the selected Flash block
 **         whether it is erased.
 **     @param
 **         Block           - Block number of the Flash memory block
 **                           that will be checked. Number is in range
 **                           zero to maximum available block number. Not
 **                           used for Freescale 56800 derivates except
 **                           for the Program_Boot_Flash on 56F83xx and
 **                           56F81xx derivatives. If the flash memory
 **                           contais only one block, this parameter is
 **                           ignored.
 **     @param
 **         Blank           - [true] = Flash block verifies as
 **                           erased, [false] = block is not erased.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - Block number is out of range 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode 
 **                           - ERR_BUSY - Device is busy
 */
/* ===================================================================*/
byte IFsh1_EraseVerify_(bool *Blank) {
	EnterCritical()
	; /* Enter critical section */
	ClearFlags(); /* Clear all flags */
	if (FSTAT_CCIF == 0U) { /* Is command complete cleared ? */
		ExitCritical()
		; /* Enter critical section */
		return ERR_BUSY; /* If yes then error */
	}
	FCCOBIX = 1U; /* Two FCCOB register loaded */
	FCCOB0HI = 0x02U; /* Erase Verify Block command */
	FCCOB0LO = (byte) (BlockAddress(0U) >> 16U); /* High address word of a block*/
	CallFnCmdInRam(); /* Copy Wait in RAM routine to stack and launch the flash process */
	if (FSTAT_ACCERR == 1U) { /* Return error code if previous operation finished not correctly */
		ExitCritical()
		; /* Exit critical section */
		return ERR_NOTAVAIL;
	}
	*Blank = (FSTAT_MGSTAT ? FALSE : TRUE); /* Check if blank */
	ExitCritical()
	; /* Exit critical section */
	return ERR_OK; /* OK */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_SetProtection (component IntFLASH)
 */
/*!
 **     @brief
 **         Method allows write into the protection register. Please see
 **         Flash Block User Guide.
 **     @param
 **         ProtectType     - Possible values: 0 or 1.
 **                           Depend on CPU type. Two meanings are
 **                           possible. 
 **                           First:
 **                           - 0 = whole Flash array is protected. In
 **                           this case other parameters are ignored.
 **                           - 1 = protection size depend on ProtectHigh
 **                           and ProtectLow parameters. Second:
 **                           - 0 = ProtectHigh and ProtectLow parameters
 **                           define range to be protected .
 **                           - 1 = ProtectHigh and ProtectLow parameters
 **                           define range to be unprotected .
 **     @param
 **         ProtectHigh     - Flash higher address range
 **                           protection. Possible values:
 **                           - 0 - 3 - defines range (size of range
 **                           depend on CPU type) 
 **                           - 4 - Protection disabled
 **     @param
 **         ProtectLow      - Flash lower address range
 **                           protection. Possible values:
 **                           - 0 - 3 - defines range (size of range
 **                           depend on CPU type) 
 **                           - 4 - Protection disabled
 **     @param
 **         Block           - Flash block number. The number of
 **                           blocks depends on CPU type. When the CPU
 **                           has only one block or block is not required
 **                           for protection setting, the value is don't
 **                           care.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Requested value not
 **                           available 
 **                           - ERR_RANGE - The value is out of range 
 **                           - ERR_VALUE - Parameter of incorrect value 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode
 */
/* ===================================================================*/
byte IFsh1_SetProtection_(bool ProtectType, byte ProtectHigh, byte ProtectLow) {
	byte TempFPROT;

	if ((ProtectHigh > 4U) || (ProtectLow > 4U) || (ProtectType > 1U)) { /* Range check */
		return ERR_RANGE;
	}
	TempFPROT = ((byte) (ProtectType << 7U)) | ((byte) (ProtectHigh << 3U))
			| ProtectLow; /* Set temporarly variable */
	if ((TempFPROT & 0x24U) != 0x24U) { /* Is FPHDIS or FPLDIS cleared ? */
		FPROT = TempFPROT | 0x24U; /* Set protection with FPHDIS and FPLDIS set first */
	}
	FPROT = TempFPROT; /* Set new protection */
	if ((FPROT & 0xBFU) != (TempFPROT & 0xBFU)) {
		return ERR_VALUE; /* Was protection register set correctly? */
	}
	return ERR_OK;
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_EnableEvent (component IntFLASH)
 */
/*!
 **     @brief
 **         This method enables all the events except [OnSaveBuffer],
 **         [OnRestoreBuffer] and [OnEraseError]. The method is
 **         available only if any event is enabled.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode
 */
/* ===================================================================*/
byte IFsh1_EnableEvent(void) {
	EnEvent = TRUE; /* Set the flag "events enabled" */
	return ERR_OK; /* OK */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_DisableEvent (component IntFLASH)
 */
/*!
 **     @brief
 **         This method disables all the events except [OnSaveBuffer],
 **         [OnRestoreBuffer] and [OnEraseError]. The method is
 **         available only if any event is enabled.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode
 */
/* ===================================================================*/
byte IFsh1_DisableEvent(void) {
	EnEvent = FALSE; /* Set the flag "events disabled" */
	return ERR_OK; /* OK */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_SetByteFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Writes a byte to an address in FLASH. The operation of this
 **         method depends on the "Write method" property and state of
 **         the flash. Please see more details on general info page of
 **         the help.
 **     @param
 **         Addr            - Address to FLASH.
 **     @param
 **         Data            - Data to write.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - Address is out of range 
 **                           - ERR_VALUE - Read value is not equal to
 **                           written value 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode 
 **                           - ERR_BUSY - Device is busy 
 **                           - ERR_PROTECT - Flash is write protect
 */
/* ===================================================================*/
byte IFsh1_SetByteFlash(IFsh1_TAddress Addr, byte Data) {
	byte err;

	if (BlockOutOfRange(Addr, Addr)) { /* Check range of address */
		return (ERR_RANGE);
	}
	if (FSTAT_CCIF == 0U) { /* Is previous command complete ? */
		return ERR_BUSY; /* If yes then error */
	}
	if (Addr & 1U) { /* Not Aligned word ? */
		err = WriteWord(Addr - 1U, ((*(word *) (Addr - 1U)) & 0xFF00U) | Data);
	} else {
		err = WriteWord(Addr, ((word) Data << 8U) | ((*(word *) Addr) & 0xFFU));
	}
	return (err); /* Return error code if previous operation finished not correctly */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_GetByteFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Gets byte from an address in FLASH.
 **     @param
 **         Addr            - Address to FLASH.
 **     @param
 **         Data            - A pointer to the returned 8-bit data.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_RANGE - Address is out of range 
 **                           - ERR_BUSY - Device is busy
 */
/* ===================================================================*/
byte IFsh1_GetByteFlash(IFsh1_TAddress Addr, byte *Data) {
	if (BlockOutOfRange(Addr, Addr)) { /* Check range of address */
		return (ERR_RANGE);
	}
	if (FSTAT_CCIF == 0U) { /* Is previous command complete ? */
		return ERR_BUSY; /* If yes then error */
	}
	*Data = *(byte *) (Addr); /* Read byte from FLASH */
	return ERR_OK;
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_SetWordFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Writes a word to an address in FLASH. The operation of this
 **         method depends on the "Write method" property and state of
 **         the flash. Please see more details on general info page of
 **         the help.
 **     @param
 **         Addr            - Address to FLASH.
 **     @param
 **         Data            - Data to write.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - Address is out of range 
 **                           - ERR_VALUE - Read value is not equal to
 **                           written value 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode 
 **                           - ERR_BUSY - Device is busy 
 **                           - ERR_PROTECT - Flash is write protect
 */
/* ===================================================================*/
byte IFsh1_SetWordFlash(IFsh1_TAddress Addr, word Data) {
	byte err;

	if (BlockOutOfRange(Addr, (Addr + 1U))) { /* Check range of address */
		return (ERR_RANGE);
	}
	if ((Addr & 1U) != 0U) { /* Aligned address ? */
		return ERR_NOTAVAIL;
	}
	if (FSTAT_CCIF == 0U) { /* Is previous command complete ? */
		return ERR_BUSY; /* If yes then error */
	}
	err = WriteWord(Addr, Data); /* Write new data to Flash */
	return (err); /* Return error */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_GetWordFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Gets a word from an address in FLASH.
 **     @param
 **         Addr            - Address to FLASH.
 **     @param
 **         Data            - A pointer to the returned 16-bit data.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - Address is out of range 
 **                           - ERR_BUSY - Device is busy
 */
/* ===================================================================*/
byte IFsh1_GetWordFlash(IFsh1_TAddress Addr, word *Data) {
	if (BlockOutOfRange(Addr, (Addr + 1U))) { /* Check range of address */
		return (ERR_RANGE);
	}
	if (Addr & 1U) { /* Aligned address ? */
		return ERR_NOTAVAIL;
	}
	if (FSTAT_CCIF == 0U) { /* Is previous command complete ? */
		return ERR_BUSY; /* If yes then error */
	}
	*Data = *(word *) Addr; /* Get word form Flash */
	return ERR_OK;
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_SetLongFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Writes a long word to an address in FLASH. The operation of
 **         this method depends on the "Write method" property and state
 **         of the flash. Please see more details on general info page
 **         of the help.
 **     @param
 **         Addr            - Address to FLASH.
 **     @param
 **         Data            - Data to write.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - The address is out of range 
 **                           - ERR_VALUE - The read value is not equal
 **                           to the written value 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode 
 **                           - ERR_BUSY - Device is busy 
 **                           - ERR_PROTECT - Flash is write protect
 */
/* ===================================================================*/
byte IFsh1_SetLongFlash(IFsh1_TAddress Addr, dword Data) {

	if (BlockOutOfRange(Addr, (Addr + 3U))) { /* Check range of address */
		return (ERR_RANGE);
	}
	if (Addr & 3U) { /* Aligned address ? */
		return ERR_NOTAVAIL;
	}
	return (WriteArray(Addr, (byte*) (&Data), 4U)); /* Write new data to Flash */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_GetLongFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Gets a long word from an address in FLASH.
 **     @param
 **         Addr            - Address to FLASH.
 **     @param
 **         Data            - A pointer to the returned 32-bit data.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - The address is out of range 
 **                           - ERR_BUSY - Device is busy
 */
/* ===================================================================*/
byte IFsh1_GetLongFlash(IFsh1_TAddress Addr, dword *Data) {
	if (BlockOutOfRange(Addr, (Addr + 3U))) { /* Check range of address */
		return (ERR_RANGE);
	}
	if (Addr & 3U) { /* Aligned address ? */
		return ERR_NOTAVAIL;
	}
	if (FSTAT_CCIF == 0U) { /* Is previous command complete ? */
		return ERR_BUSY; /* If yes then error */
	}
	*Data = (dword) (*(word *) Addr) << 0x10U; /* Return data from given address */
	*Data = *Data | (*(word *) (Addr + 2U));
	return ERR_OK;
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_SetBlockFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Writes data to FLASH. The operation of this method depends
 **         on the "Write method" property and state of the flash.
 **         Please see more details on general info page of the help.
 **     @param
 **         Source          - Source address of the data.
 **     @param
 **         Dest            - Destination address in FLASH.
 **     @param
 **         Count           - Count of the data fields (in the
 **                           smallest addressable units).
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - The address is out of range 
 **                           - ERR_BUSY - Device is busy 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode 
 **                           - ERR_PROTECT - Flash is write protect 
 **                           - ERR_VALUE - Read value is not equal to
 **                           written value
 */
/* ===================================================================*/
/*lint -save  -e818 Disable MISRA rule (16.7) checking. */
byte IFsh1_SetBlockFlash(IFsh1_TDataAddress Source, IFsh1_TAddress Addr,
		word Count) {
	byte err;

	if (BlockOutOfRange(Addr, ((Addr + Count)-1U))) { /* Check range of address */
		return (ERR_RANGE);
	}
	if (((Addr & 1U) != 0U) || ((Count & 1U) != 0U)) { /* Word aligned address and count? */
		return ERR_NOTAVAIL;
	}
	if (FSTAT_CCIF == 0U) { /* Is previous command complete ? */
		return ERR_BUSY; /* If yes then error */
	}
	err = WriteArray(Addr, Source, Count); /* Write new page to Flash */
	return (err); /* Return error */
}
/*lint -restore Enable MISRA rule (16.7) checking. */
/*
 ** ===================================================================
 **     Method      :  IFsh1_GetBlockFlash (component IntFLASH)
 */
/*!
 **     @brief
 **         Reads data from FLASH.
 **     @param
 **         Source          - Destination address in FLASH.
 **     @param
 **         Dest            - Source address of the data.
 **     @param
 **         Count           - Count of the data fields (in the
 **                           smallest addressable units).
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - The address is out of range 
 **                           - ERR_BUSY - Device is busy
 */
/* ===================================================================*/
byte IFsh1_GetBlockFlash(IFsh1_TAddress Addr, IFsh1_TDataAddress Dest,
		word Count) {
	if (BlockOutOfRange(Addr, ((Addr + Count)-1U))) { /* Check range of address */
		return (ERR_RANGE);
	}
	if (((Addr & 1U) != 0U) || ((Count & 1U) != 0U)) { /* Word aligned address and count? */
		return ERR_NOTAVAIL;
	}
	if (FSTAT_CCIF == 0U) { /* Is previous command complete ? */
		return ERR_BUSY; /* If yes then error */
	}
	while (Count--) {
		*Dest = *(byte *) (Addr); /* Set virtual page element according to value of Flash given by the appropriate address */
		Addr++;
		Dest++;
	} /* while Count */
	return ERR_OK;
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_EraseSector (component IntFLASH)
 */
/*!
 **     @brief
 **         Erases the sector to which address Addr belongs.
 **     @param
 **         Addr            - Address in FLASH.
 **     @return
 **                         - Error code, possible codes: 
 **                           - ERR_OK - OK 
 **                           - ERR_NOTAVAIL - Desired program/erase
 **                           operation is not available 
 **                           - ERR_RANGE - Address is out of range 
 **                           - ERR_SPEED - This device does not work in
 **                           the active speed mode 
 **                           - ERR_BUSY - Device is busy 
 **                           - ERR_PROTECT - Flash is write protect 
 **                           - ERR_VALUE - Flash sector erase was not
 **                           successful
 */
/* ===================================================================*/
byte IFsh1_EraseSector(IFsh1_TAddress Addr) {
	if (BlockOutOfRange(Addr, Addr)) { /* Check range of address */
		return (ERR_RANGE);
	}
	EnterCritical()
	; /* Enter critical section */
	ClearFlags(); /* Clear all flags */
	if (FSTAT_CCIF == 0U) { /* Is command buffer full ? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_BUSY; /* If yes then error */
	}
	FCCOBIX = 1U; /* Two FCCOB registers are loaded */
	FCCOB0HI = 0x0AU; /* Erase P-Flash sector command */
	FCCOB0LO = (byte) (Addr >> 16U); /* High address word */
	FCCOB1 = (word) (Addr & 0xFFFFFFF8UL); /* Low address word aligned to 8 byte phrase*/
	CallFnCmdInRam(); /* Copy Wait in RAM routine to stack and launch the flash process */
	if (FSTAT_FPVIOL == 1U) { /* Is protection violation detected ? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_NOTAVAIL; /* If yes then error */
	}
	if (FSTAT_ACCERR == 1U) { /* Is access error detected ? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_NOTAVAIL; /* If yes then error */
	}
	if (FSTAT_MGSTAT) { /* Was attempt to erase the sector errorneous? */
		ExitCritical()
		; /* Exit critical section */
		return ERR_VALUE; /* If yes then error */
	}
	FCNFG_CCIE = 1U; /* Enable interrupt */
	ExitCritical()
	; /* Exit critical section */
	return ERR_OK; /* OK */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_Busy (component IntFLASH)
 */
/*!
 **     @brief
 **         This method returns the status of the FLASH device. The
 **         method may be required and called from another component
 **         methods - in this case it cannot be disabled.
 **     @param
 **         Block           - Number of Flash block. Not used for
 **                           Freescale 56800, HCS08, HCS12X and
 **                           ColdFireV1 derivates - any value may be
 **                           passed.
 **     @return
 **                         - [true]/[false] - FLASH is busy/ready
 */
/* ===================================================================*/
/*
 bool IFsh1_Busy(byte Block)

 **      This method is implemented as macro. See IFsh1.h file.      **
 */

/*
 ** ===================================================================
 **     Method      :  IFsh1_DataPtr2Addr (component IntFLASH)
 */
/*!
 **     @brief
 **         This method converts data pointer to format of a component's
 **         method address parameter. Generally a data pointer format is
 **         different from format of a method Addr parameter.
 **     @param
 **         Addr            - Data pointer.
 **     @return
 **                         - Address in the format used in the component
 **                           methods.
 */
/* ===================================================================*/
IFsh1_TAddress IFsh1_DataPtr2Addr(const void * Addr) {
	return ((IFsh1_TAddress) ((const void *) Addr));
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_FuncPtr2Addr (component IntFLASH)
 */
/*!
 **     @brief
 **         This method converts function pointer to format of a
 **         component's method address parameter. Generally a function
 **         pointer format is different from format of a method Addr
 **         parameter.
 **     @param
 **         Addr            - Function pointer.
 **     @return
 **                         - Address in the format used in the component
 **                           methods.
 */
/* ===================================================================*/
IFsh1_TAddress IFsh1_FuncPtr2Addr(void (*Addr)()) {
	return ((IFsh1_TAddress) Addr);
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_Init (component IntFLASH)
 **
 **     Description :
 **         Initializes the associated peripheral(s) and the component 
 **         internal variables. The method is called automatically as a 
 **         part of the application initialization code.
 **         This method is internal.
 ** ===================================================================
 */
void IFsh1_Init(void) {
	FCLKDIV = 0x1FU; /* Set up Clock Divider Register */
	EnEvent = TRUE; /* Enable events */
}

/*
 ** ===================================================================
 **     Method      :  IFsh1_Interrupt (component IntFLASH)
 **
 **     Description :
 **         The method services the interrupt of the selected peripheral(s)
 **         and eventually invokes event(s) of the component.
 **         This method is internal.
 ** ===================================================================
 */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(IFsh1_Interrupt) {
	FCNFG &= 0x3FU; /* Clear flags */
	if (EnEvent) { /* Are the events enabled? */
		; /* Invoke user event */
	}
}

#pragma CODE_SEG IFsh1_CODE

/*lint -restore Enable MISRA rule (11.3,11.4) checking. */

/* END IFsh1. */

/*!
 ** @}
 */
