/* ###################################################################
**     Filename    : IFsh1.h
**     Project     : jst_bl
**     Processor   : MC9S12ZVHL32CLL
**     Component   : IntFLASH
**     Version     : Component 02.409, Driver 02.18, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2024-03-11, 16:07
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
** @file IFsh1.h
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


#ifndef __IFsh1
#define __IFsh1

/* MODULE IFsh1. */

#include "Cpu.h"

#pragma DATA_SEG IFsh1_DATA            /* Select data segment "IFsh1_DATA" */
#pragma CODE_SEG IFsh1_CODE


/* Flash area 0 start address (in the format used by component methods). */
#define IFsh1_AREA_0_START              (0x00FF8000UL)
/* Flash area 0 size (in bytes). */
#define IFsh1_AREA_0_SIZE               (0x8000UL)
/* Flash area 0 last address (in the format used by component methods). */
#define IFsh1_AREA_0_END                (0x00FFFFFFUL)
/* Flash area 0 sector size: minimal erasable unit (in bytes). */
#define IFsh1_AREA_0_SECTOR_SIZE        (0x0200U)
/* Number of flash memory areas. */
#define IFsh1_AREA_COUNT                (0x01U)

/* Flash area sector size valid for all areas: minimal erasable unit (in bytes). */
#define IFsh1_AREA_SECTOR_SIZE          (0x0200U)
/* Size of programming phrase, i.e. number of bytes that must be programmed at once */
#define IFsh1_PROGRAMMING_PHRASE        (0x08U)
/* TRUE if the component setting allows rewrite of already programmed flash memory location (only clear those bits that in 1) without destruction of the value in surrounding addresses by sector erase. */
#define IFsh1_ALLOW_CLEAR               (FALSE)

#ifndef __BWUserType_IFsh1_TAddress
#define __BWUserType_IFsh1_TAddress
  typedef dword IFsh1_TAddress;        /* component type for address to the FLASH. Address is 24-bit GLOBAL address*/
#endif
#ifndef __BWUserType_IFsh1_TDataAddress
#define __BWUserType_IFsh1_TDataAddress
  typedef byte *IFsh1_TDataAddress;    /* component type for pointer to data. Data are either source, when writting a block to flash, or output, when reading a block from flash */
#endif

#define IFsh1_DummyData    (0x10U)     /* This number is used as data word when erase command is invoked */

#define IFsh1_EraseVerify(Block,Blank) IFsh1_EraseVerify_(Blank)
byte IFsh1_EraseVerify_(bool *Blank);
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

#define IFsh1_SetProtection(ProtectType,ProtectHigh,ProtectLow,Block) IFsh1_SetProtection_(ProtectType,ProtectHigh,ProtectLow)
byte IFsh1_SetProtection_(bool ProtectType,byte ProtectHigh,byte ProtectLow);
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

byte IFsh1_EnableEvent(void);
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

byte IFsh1_DisableEvent(void);
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

#define IFsh1_Busy(Block) ((FSTAT_CCIF == 0U) ? 1U : 0U)
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


void IFsh1_Init(void);
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

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void IFsh1_Interrupt(void);
#pragma CODE_SEG IFsh1_CODE
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

byte IFsh1_SetByteFlash(IFsh1_TAddress Addr,byte Data);
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

byte IFsh1_GetByteFlash(IFsh1_TAddress Addr,byte *Data);
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

byte IFsh1_SetWordFlash(IFsh1_TAddress Addr,word Data);
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

byte IFsh1_GetWordFlash(IFsh1_TAddress Addr,word *Data);
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

byte IFsh1_SetLongFlash(IFsh1_TAddress Addr,dword Data);
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

byte IFsh1_GetLongFlash(IFsh1_TAddress Addr,dword *Data);
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

byte IFsh1_SetBlockFlash(IFsh1_TDataAddress Source, IFsh1_TAddress Addr, word Count);
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

byte IFsh1_GetBlockFlash(IFsh1_TAddress Addr, IFsh1_TDataAddress Dest, word Count);
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

byte IFsh1_EraseSector(IFsh1_TAddress Addr);
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

IFsh1_TAddress IFsh1_DataPtr2Addr(const void * Addr);
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

IFsh1_TAddress IFsh1_FuncPtr2Addr(void(* Addr)());
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


#pragma CODE_SEG DEFAULT
#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */

/* END IFsh1. */

#endif /* ifndef __IFsh1 */
/*!
** @}
*/
