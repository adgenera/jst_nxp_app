/*
 * Config.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Andrea Cencio
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "MC9S12ZVHL32.h"
//==============================================================================
// Configure Derivative
//============================================================================== 
//Please select your derivative 
//#define FLASH_START_ADD 0xFC0000UL //for 256kB derivatives
//#define FLASH_START_ADD 0xFD0000UL //for 192kB derivatives
//#define FLASH_START_ADD 0xFE0000UL //for 128kB derivatives
//#define FLASH_START_ADD 0xFE8000UL //for 96kB derivatives
//#define FLASH_START_ADD 0xFF0000UL //for 64kB derivatives
#define FLASH_START_ADD 0xFF8000UL //for 32kB derivatives
//#define FLASH_START_ADD 0xFFD000UL //for 16kB derivatives
//#define FLASH_START_ADD 0xFFE000UL //for 8kB derivatives

//==============================================================================
// Bootloader request definition - Push Button
//==============================================================================
#define PUSH_BUTTON        PTF_PTF4
#define PB_ACTIVE_LEVEL    0

//==============================================================================
// P-Flash Addresses
//==============================================================================
//Please configure Bootloader area in *.prm linker file

extern int __SEG_START__PRESTART[];

#define BOOTLOADER_START_ADD              ((unsigned long)__SEG_START__PRESTART) //Bootloader start address defined by Bootloader linker file (ROM segment).
#define BOOTLOADER_END_ADD                0xFFFFFF
#define BOOTLOADER_SIZE                   (BOOTLOADER_END_ADD-BOOTLOADER_START_ADD)

#define APPLICATION_RESET_VEC_SRC         0xFFFFE0                  //last 32bytes in Flash with reset vector. Reset vector starts at 0xFFFFFD
#define APPLICATION_END_ADD               (BOOTLOADER_START_ADD-4)  //last four bytes from Application are allocated for Application Reset Vector
#define APPLICATION_RESET_VEC_ADD         APPLICATION_END_ADD       //here is stored reset vector of user application

#define JST_MAGIC_WORD					  0xFFE600
//Please select Bootloader area which will be protected //TODO not implemented in this release
//#define BL_FPROT  0xDF       //upper 16kB of P-Flash protected.
#define BL_FPROT  0xD7       //upper 8kB of P-Flash protected.
//#define BL_FPROT  0xCF       //upper 4kB of P-Flash protected.
//#define BL_FPROT  0xFF       //unprotected.

#define BL_DFPROT 0xFF       //EEPROM unprotected.

#endif /* CONFIG_H_ */
