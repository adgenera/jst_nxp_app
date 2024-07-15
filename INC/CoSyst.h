#ifndef COSYST_H
#define COSYST_H

/****************************** includes < > ******************************** */

/****************************** includes " " ******************************** */
#include <Platform_Types.h>

/****************************** typedefs     ******************************** */

/****************************** #defines     ******************************** */
#define CS_VENDOR_ID        99 /**<\brief CoSyst VendorID */
#define CS_AR_MAJOR_VERSION 3  /**<\brief AUTOSAR major version */
#define CS_AR_MINOR_VERSION 1  /**<\brief AUTOSAR minor version */
#define CS_AR_PATCH_VERSION 0  /**<\brief AUTOSAR patch version */
#define CS_SW_MAJOR_VERSION 1  /**<\brief Software major version */
#define CS_SW_MINOR_VERSION 0  /**<\brief Software minor version */
#define CS_SW_PATCH_VERSION 0  /**<\brief Software patch version */

#define CS_MSK_1   0x00000001U
#define CS_MSK_2   0x00000003U
#define CS_MSK_3   0x00000007U
#define CS_MSK_4   0x0000000FU
#define CS_MSK_5   0x0000001FU
#define CS_MSK_6   0x0000003FU
#define CS_MSK_7   0x0000007FU
#define CS_MSK_8   0x000000FFU
#define CS_MSK_9   0x000001FFU
#define CS_MSK_10  0x000003FFU
#define CS_MSK_11  0x000007FFU
#define CS_MSK_12  0x00000FFFU
#define CS_MSK_13  0x00001FFFU
#define CS_MSK_14  0x00003FFFU
#define CS_MSK_15  0x00007FFFU
#define CS_MSK_16  0x0000FFFFU
#define CS_MSK_17  0x0001FFFFU
#define CS_MSK_18  0x0003FFFFU
#define CS_MSK_19  0x0007FFFFU
#define CS_MSK_20  0x000FFFFFU
#define CS_MSK_21  0x001FFFFFU
#define CS_MSK_22  0x003FFFFFU
#define CS_MSK_23  0x007FFFFFU
#define CS_MSK_24  0x00FFFFFFU
#define CS_MSK_25  0x01FFFFFFU
#define CS_MSK_26  0x03FFFFFFU
#define CS_MSK_27  0x07FFFFFFU
#define CS_MSK_28  0x0FFFFFFFU
#define CS_MSK_29  0x1FFFFFFFU
#define CS_MSK_30  0x3FFFFFFFU
#define CS_MSK_31  0x7FFFFFFFU
#define CS_MSK_32  0xFFFFFFFFU

#if (0) /* Unused macro definitions, just cause MISRA hits */
/**
 * \brief Setzen eines Bits in einem 8-Bit Register.
 */
#define CS_SET_BIT_8(cs_reg_pui8, cs_bit_ui8) (*cs_reg_pui8) =\
        (uint8)((uint8)(1 << cs_bit_ui8) | (*cs_reg_pui8));

/**
 * \brief Loeschen eines Bits in einem 8-Bit Register.
 */
#define CS_CLR_BIT_8(cs_reg_pui8, cs_bit_ui8) (*cs_reg_pui8) =\
        (uint8)(((uint8)(~((uint8)(1 << cs_bit_ui8)))) & (*cs_reg_pui8));

/**
 * \brief Beschreiben eines Bits eines 8-Bit Registers mit einem Wert.
 */
#define CS_WR_BIT_8(cs_reg_pui8, cs_bit_ui8, cs_val_ui8) (*cs_reg_pui8) =\
        (uint8)(((uint8)(~((uint8)(1 << cs_bit_ui8)))) & (*cs_reg_pui8));\
        (*cs_reg_pui8) =\
        (uint8)(((uint8)(cs_val_ui8 << cs_bit_ui8)) | (*cs_reg_pui8));

/**
 * \brief Lesen eines Bits aus einem 8-Bit Register.
 */
#define CS_RD_BIT_8(cs_reg_pui8, cs_bit_ui8)\
        (uint8)((uint8)((uint8)(1 << cs_bit_ui8) &\
        (*cs_reg_pui8)) >> cs_bit_ui8)

/**
 * \brief Pruefen ob ein Bit eines 8-Bit Registers einen bestimmten Wert hat.
 */
#define CS_IS_BIT_SET_8(cs_reg_pui8, cs_bit_ui8, cs_val_ui8)\
        ((uint8)((uint8)((uint8)(1 << cs_bit_ui8) & (*cs_reg_pui8)) >>\
        cs_bit_ui8)) == cs_val_ui8

/**
 * \brief Beschreiben eines 8-Bit Registers mit einem Wert.
 */
#define CS_WR_REG_8(cs_reg_pui8, cs_bit_ui8, cs_mask_ui8, cs_val_ui8)\
        (*cs_reg_pui8) = (uint8)((*cs_reg_pui8) &\
        (uint8)(~((uint8)((uint8)cs_mask_ui8 << cs_bit_ui8))));\
        (*cs_reg_pui8) = (uint8)((*cs_reg_pui8) | (uint8)((uint8)(cs_val_ui8 &\
        (uint8)cs_mask_ui8) << cs_bit_ui8));

/**
 * \brief Lesen eines 8-Bit Registers.
 */
#define CS_RD_REG_8(cs_reg_pui8, cs_bit_ui8, cs_mask_ui8)\
        (uint8)((uint8)((*cs_reg_pui8) >> cs_bit_ui8) & (uint8)cs_mask_ui8)

/**
 * \brief Pruefen ob ein 8-Bit Register einen bestimmten Wert enthaelt.
 */
#define CS_IS_REG_8(cs_reg_pui8, cs_bit_ui8, cs_mask_ui8, cs_val_ui8)\
        ((uint8)((uint8)((*cs_reg_pui8) >> cs_bit_ui8) &\
        (uint8)cs_mask_ui8)) == cs_val_ui8

/**
 * \brief Setzen eines Bits in einem 16-Bit Register.
 */
#define CS_SET_BIT_16(cs_reg_pui16, cs_bit_ui16) (*cs_reg_pui16) =\
        (uint16)((uint16)(1 << cs_bit_ui16) | (*cs_reg_pui16));

/**
 * \brief Loeschen eines Bits in einem 16-Bit Register.
 */
#define CS_CLR_BIT_16(cs_reg_pui16, cs_bit_ui16) (*cs_reg_pui16) =\
        (uint16)(((uint16)(~((uint16)(1 << cs_bit_ui16)))) & (*cs_reg_pui16));

/**
 * \brief Beschreiben eines Bits eines 16-Bit Registers mit einem Wert.
 */
#define CS_WR_BIT_16(cs_reg_pui16, cs_bit_ui16, cs_val_ui16) (*cs_reg_pui16) =\
        (uint16)(((uint16)(~((uint16)(1 << cs_bit_ui16)))) & (*cs_reg_pui16));\
        (*cs_reg_pui16) =\
        (uint16)(((uint16)(cs_val_ui16 << cs_bit_ui16)) | (*cs_reg_pui16));

/**
 * \brief Lesen eines Bits aus einem 16-Bit Register.
 */
#define CS_RD_BIT_16(cs_reg_pui16, cs_bit_ui16)\
        (uint16)((uint16)((uint16)(1 << cs_bit_ui16) &\
        (*cs_reg_pui16)) >> cs_bit_ui16)

/**
 * \brief Pruefen ob ein Bit eines 16-Bit Registers einen bestimmten Wert hat.
 */
#define CS_IS_BIT_SET_16(cs_reg_pui16, cs_bit_ui16, cs_val_ui16)\
        ((uint16)((uint16)((uint16)(1 << cs_bit_ui16) & (*cs_reg_pui16)) >>\
        cs_bit_ui16)) == cs_val_ui16

/**
 * \brief Beschreiben eines 16-Bit Registers mit einem Wert.
 */
#define CS_WR_REG_16(cs_reg_pui16, cs_bit_ui16, cs_mask_ui16, cs_val_ui16)\
        (*cs_reg_pui16) = (uint16)((*cs_reg_pui16) &\
        (uint16)(~((uint16)((uint16)cs_mask_ui16 << cs_bit_ui16))));\
        (*cs_reg_pui16) = (uint16)((*cs_reg_pui16) | (uint16)((uint16)(cs_val_ui16 &\
        (uint16)cs_mask_ui16) << cs_bit_ui16));

/**
 * \brief Lesen eines 16-Bit Registers.
 */
#define CS_RD_REG_16(cs_reg_pui16, cs_bit_ui16, cs_mask_ui16)\
        (uint16)((uint16)((*cs_reg_pui16) >> cs_bit_ui16) & (uint16)cs_mask_ui16)

/**
 * \brief Pruefen ob ein 16-Bit Register einen bestimmten Wert enthaelt.
 */
#define CS_IS_REG_16(cs_reg_pui16, cs_bit_ui16, cs_mask_ui16, cs_val_ui16)\
        ((uint16)((uint16)((*cs_reg_pui16) >> cs_bit_ui16) &\
        (uint16)cs_mask_ui16)) == cs_val_ui16

/**
 * \brief Setzen eines Bits in einem 32-Bit Register.
 */
#define CS_SET_BIT_32(cs_reg_pui32, cs_bit_ui32) (*cs_reg_pui32) =\
        (uint32)((uint32)(1 << cs_bit_ui32) | (*cs_reg_pui32));

/**
 * \brief Loeschen eines Bits in einem 32-Bit Register.
 */
#define CS_CLR_BIT_32(cs_reg_pui32, cs_bit_ui32) (*cs_reg_pui32) =\
        (uint32)(((uint32)(~((uint32)(1 << cs_bit_ui32)))) & (*cs_reg_pui32));

/**
 * \brief Beschreiben eines Bits eines 32-Bit Registers mit einem Wert.
 */
#define CS_WR_BIT_32(cs_reg_pui32, cs_bit_ui32, cs_val_ui32) (*cs_reg_pui32) =\
        (uint32)(((uint32)(~((uint32)(1 << cs_bit_ui32)))) & (*cs_reg_pui32));\
        (*cs_reg_pui32) =\
        (uint32)(((uint32)(cs_val_ui32 << cs_bit_ui32)) | (*cs_reg_pui32));

/**
 * \brief Lesen eines Bits aus einem 32-Bit Register.
 */
#define CS_RD_BIT_32(cs_reg_pui32, cs_bit_ui32)\
        (uint32)((uint32)((uint32)(1 << cs_bit_ui32) &\
        (*cs_reg_pui32)) >> cs_bit_ui32)

/**
 * \brief Pruefen ob ein Bit eines 32-Bit Registers einen bestimmten Wert hat.
 */
#define CS_IS_BIT_SET_32(cs_reg_pui32, cs_bit_ui32, cs_val_ui32)\
        ((uint32)((uint32)((uint32)(1 << cs_bit_ui32) & (*cs_reg_pui32)) >>\
        cs_bit_ui32)) == cs_val_ui32

/**
 * \brief Beschreiben eines 32-Bit Registers mit einem Wert.
 */
#define CS_WR_REG_32(cs_reg_pui32, cs_bit_ui32, cs_mask_ui32, cs_val_ui32)\
        (*cs_reg_pui32) = (uint32)((*cs_reg_pui32) &\
        (uint32)(~((uint32)((uint32)cs_mask_ui32 << cs_bit_ui32))));\
        (*cs_reg_pui32) = (uint32)((*cs_reg_pui32) | (uint32)((uint32)(cs_val_ui32 &\
        (uint32)cs_mask_ui32) << cs_bit_ui32));

/**
 * \brief Lesen eines 32-Bit Registers.
 */
#define CS_RD_REG_32(cs_reg_pui32, cs_bit_ui32, cs_mask_ui32)\
        (uint32)((uint32)((*cs_reg_pui32) >> cs_bit_ui32) & (uint32)cs_mask_ui32)

/**
 * \brief Pruefen ob ein 32-Bit Register einen bestimmten Wert enthaelt.
 */
#define CS_IS_REG_32(cs_reg_pui32, cs_bit_ui32, cs_mask_ui32, cs_val_ui32)\
        ((uint32)((uint32)((*cs_reg_pui32) >> cs_bit_ui32) &\
        (uint32)cs_mask_ui32)) == cs_val_ui32
#endif

#define ENABLE_ALL_INTERRUPTS()    asm(CLI) /*lint !e960 */
#define DISABLE_ALL_INTERRUPTS()   asm(SEI) /*lint !e960 */

/****************************** enums        ******************************** */

/****************************** structs      ******************************** */

/****************************** global data  ******************************** */

/****************************** modul global prototypes  ******************** */

/****************************** global prototypes ************************** */
uint32 Cs_CreateMask
(
   uint32 cs_maskWidth_ui32,
   uint32 cs_maskPosition_ui32
);

uint32 Cs_ShiftBitgroupLeft
(
   uint32 cs_value_ui32,
   uint32 cs_offset_ui32,
   uint32 cs_groupWidth_ui32,
   uint32 cs_shiftWidth_ui32
);

#endif /* COSYST_H */
