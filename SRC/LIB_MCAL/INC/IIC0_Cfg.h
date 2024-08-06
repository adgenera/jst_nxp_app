#ifndef IIC0_CFG_H_
#define IIC0_CFG_H_

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * Include Files                                                                                                      *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#include <Std_Types.h>
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * Module Defines                                                                                                   *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * TypeDefs                                                                                                  *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

typedef union {
	uint8 Byte;
	struct {
		uint8 :1;
		uint8 ADR1 :1; /* Slave Address Bit 1 */
		uint8 ADR2 :1; /* Slave Address Bit 2 */
		uint8 ADR3 :1; /* Slave Address Bit 3 */
		uint8 ADR4 :1; /* Slave Address Bit 4 */
		uint8 ADR5 :1; /* Slave Address Bit 5 */
		uint8 ADR6 :1; /* Slave Address Bit 6 */
		uint8 ADR7 :1; /* Slave Address Bit 7 */
	} Bits;
	struct {
		uint8 :1;
		uint8 grpADR_1 :7;
	} MergedBits;
} IIC0IBADSTR;
extern volatile IIC0IBADSTR _IIC0IBAD @0x000007C0;
#define IIC0IBAD                        _IIC0IBAD.Byte
#define IIC0IBAD_ADR1                   _IIC0IBAD.Bits.ADR1
#define IIC0IBAD_ADR2                   _IIC0IBAD.Bits.ADR2
#define IIC0IBAD_ADR3                   _IIC0IBAD.Bits.ADR3
#define IIC0IBAD_ADR4                   _IIC0IBAD.Bits.ADR4
#define IIC0IBAD_ADR5                   _IIC0IBAD.Bits.ADR5
#define IIC0IBAD_ADR6                   _IIC0IBAD.Bits.ADR6
#define IIC0IBAD_ADR7                   _IIC0IBAD.Bits.ADR7
#define IIC0IBAD_ADR_1                  _IIC0IBAD.MergedBits.grpADR_1
#define IIC0IBAD_ADR                    IIC0IBAD_ADR_1

#define IIC0IBAD_ADR1_MASK              0x02U
#define IIC0IBAD_ADR2_MASK              0x04U
#define IIC0IBAD_ADR3_MASK              0x08U
#define IIC0IBAD_ADR4_MASK              0x10U
#define IIC0IBAD_ADR5_MASK              0x20U
#define IIC0IBAD_ADR6_MASK              0x40U
#define IIC0IBAD_ADR7_MASK              0x80U
#define IIC0IBAD_ADR_1_MASK             0xFEU
#define IIC0IBAD_ADR_1_BITNUM           0x01U

/*** IIC0IBFD - IIC Frequency Divider Register; 0x000007C1 ***/
typedef union {
	uint8 Byte;
	struct {
		uint8 IBC0 :1; /* I-Bus Clock Rate 0 */
		uint8 IBC1 :1; /* I-Bus Clock Rate 1 */
		uint8 IBC2 :1; /* I-Bus Clock Rate 2 */
		uint8 IBC3 :1; /* I-Bus Clock Rate 3 */
		uint8 IBC4 :1; /* I-Bus Clock Rate 4 */
		uint8 IBC5 :1; /* I-Bus Clock Rate 5 */
		uint8 IBC6 :1; /* I-Bus Clock Rate 6 */
		uint8 IBC7 :1; /* I-Bus Clock Rate 7 */
	} Bits;
} IIC0IBFDSTR;
extern volatile IIC0IBFDSTR _IIC0IBFD @0x000007C1;
#define IIC0IBFD                        _IIC0IBFD.Byte
#define IIC0IBFD_IBC0                   _IIC0IBFD.Bits.IBC0
#define IIC0IBFD_IBC1                   _IIC0IBFD.Bits.IBC1
#define IIC0IBFD_IBC2                   _IIC0IBFD.Bits.IBC2
#define IIC0IBFD_IBC3                   _IIC0IBFD.Bits.IBC3
#define IIC0IBFD_IBC4                   _IIC0IBFD.Bits.IBC4
#define IIC0IBFD_IBC5                   _IIC0IBFD.Bits.IBC5
#define IIC0IBFD_IBC6                   _IIC0IBFD.Bits.IBC6
#define IIC0IBFD_IBC7                   _IIC0IBFD.Bits.IBC7

#define IIC0IBFD_IBC0_MASK              0x01U
#define IIC0IBFD_IBC1_MASK              0x02U
#define IIC0IBFD_IBC2_MASK              0x04U
#define IIC0IBFD_IBC3_MASK              0x08U
#define IIC0IBFD_IBC4_MASK              0x10U
#define IIC0IBFD_IBC5_MASK              0x20U
#define IIC0IBFD_IBC6_MASK              0x40U
#define IIC0IBFD_IBC7_MASK              0x80U

/*** IIC0IBCR - IIC Control Register; 0x000007C2 ***/
typedef union {
	uint8 Byte;
	struct {
		uint8 IBSWAI :1; /* I-Bus Interface Stop in WAIT mode */
		uint8 :1;
		uint8 RSTA :1; /* Repeat Start */
		uint8 TXAK :1; /* Transmit Acknowledge enable */
		uint8 TX_RX :1; /* Transmit/Receive mode select bit */
		uint8 MS_SL :1; /* Master/Slave mode select bit */
		uint8 IBIE :1; /* I-Bus Interrupt Enable */
		uint8 IBEN :1; /* I-Bus Enable */
	} Bits;
} IIC0IBCRSTR;
extern volatile IIC0IBCRSTR _IIC0IBCR @0x000007C2;
#define IIC0IBCR                        _IIC0IBCR.Byte
#define IIC0IBCR_IBSWAI                 _IIC0IBCR.Bits.IBSWAI
#define IIC0IBCR_RSTA                   _IIC0IBCR.Bits.RSTA
#define IIC0IBCR_TXAK                   _IIC0IBCR.Bits.TXAK
#define IIC0IBCR_TX_RX                  _IIC0IBCR.Bits.TX_RX
#define IIC0IBCR_MS_SL                  _IIC0IBCR.Bits.MS_SL
#define IIC0IBCR_IBIE                   _IIC0IBCR.Bits.IBIE
#define IIC0IBCR_IBEN                   _IIC0IBCR.Bits.IBEN

#define IIC0IBCR_IBSWAI_MASK            0x01U
#define IIC0IBCR_RSTA_MASK              0x04U
#define IIC0IBCR_TXAK_MASK              0x08U
#define IIC0IBCR_TX_RX_MASK             0x10U
#define IIC0IBCR_MS_SL_MASK             0x20U
#define IIC0IBCR_IBIE_MASK              0x40U
#define IIC0IBCR_IBEN_MASK              0x80U

/*** IIC0IBSR - IIC Status Register; 0x000007C3 ***/
typedef union {
	uint8 Byte;
	struct {
		uint8 RXAK :1; /* Received Acknowledge */
		uint8 IBIF :1; /* I-Bus Interrupt */
		uint8 SRW :1; /* Slave Read/Write */
		uint8 :1;
		uint8 IBAL :1; /* Arbitration Lost */
		uint8 IBB :1; /* Bus busy bit */
		uint8 IAAS :1; /* Addressed as a slave bit */
		uint8 TCF :1; /* Data transferring bit */
	} Bits;
} IIC0IBSRSTR;
extern volatile IIC0IBSRSTR _IIC0IBSR @0x000007C3;
#define IIC0IBSR                        _IIC0IBSR.Byte
#define IIC0IBSR_RXAK                   _IIC0IBSR.Bits.RXAK
#define IIC0IBSR_IBIF                   _IIC0IBSR.Bits.IBIF
#define IIC0IBSR_SRW                    _IIC0IBSR.Bits.SRW
#define IIC0IBSR_IBAL                   _IIC0IBSR.Bits.IBAL
#define IIC0IBSR_IBB                    _IIC0IBSR.Bits.IBB
#define IIC0IBSR_IAAS                   _IIC0IBSR.Bits.IAAS
#define IIC0IBSR_TCF                    _IIC0IBSR.Bits.TCF

#define IIC0IBSR_RXAK_MASK              0x01U
#define IIC0IBSR_IBIF_MASK              0x02U
#define IIC0IBSR_SRW_MASK               0x04U
#define IIC0IBSR_IBAL_MASK              0x10U
#define IIC0IBSR_IBB_MASK               0x20U
#define IIC0IBSR_IAAS_MASK              0x40U
#define IIC0IBSR_TCF_MASK               0x80U

/*** IIC0IBDR - IIC Data I/O Register; 0x000007C4 ***/
typedef union {
	uint8 Byte;
	struct {
		uint8 D0 :1; /* IIC Data Bit 0 */
		uint8 D1 :1; /* IIC Data Bit 1 */
		uint8 D2 :1; /* IIC Data Bit 2 */
		uint8 D3 :1; /* IIC Data Bit 3 */
		uint8 D4 :1; /* IIC Data Bit 4 */
		uint8 D5 :1; /* IIC Data Bit 5 */
		uint8 D6 :1; /* IIC Data Bit 6 */
		uint8 D7 :1; /* IIC Data Bit 7 */
	} Bits;
} IIC0IBDRSTR;
extern volatile IIC0IBDRSTR _IIC0IBDR @0x000007C4;
#define IIC0IBDR                        _IIC0IBDR.Byte
#define IIC0IBDR_D0                     _IIC0IBDR.Bits.D0
#define IIC0IBDR_D1                     _IIC0IBDR.Bits.D1
#define IIC0IBDR_D2                     _IIC0IBDR.Bits.D2
#define IIC0IBDR_D3                     _IIC0IBDR.Bits.D3
#define IIC0IBDR_D4                     _IIC0IBDR.Bits.D4
#define IIC0IBDR_D5                     _IIC0IBDR.Bits.D5
#define IIC0IBDR_D6                     _IIC0IBDR.Bits.D6
#define IIC0IBDR_D7                     _IIC0IBDR.Bits.D7

#define IIC0IBDR_D0_MASK                0x01U
#define IIC0IBDR_D1_MASK                0x02U
#define IIC0IBDR_D2_MASK                0x04U
#define IIC0IBDR_D3_MASK                0x08U
#define IIC0IBDR_D4_MASK                0x10U
#define IIC0IBDR_D5_MASK                0x20U
#define IIC0IBDR_D6_MASK                0x40U
#define IIC0IBDR_D7_MASK                0x80U

/*** IIC0IBCR2 - IIC Control Register 2; 0x000007C5 ***/
typedef union {
	uint8 Byte;
	struct {
		uint8 ADR8 :1; /* Slave Address Bit 8 */
		uint8 ADR9 :1; /* Slave Address Bit 9 */
		uint8 ADR10 :1; /* Slave Address Bit 10 */
		uint8 :1;
		uint8 :1;
		uint8 :1;
		uint8 ADTYPE :1; /* Address Type */
		uint8 GCEN :1; /* General Call Enable */
	} Bits;
	struct {
		uint8 grpADR_8 :3;
		uint8 :1;
		uint8 :1;
		uint8 :1;
		uint8 :1;
		uint8 :1;
	} MergedBits;
} IIC0IBCR2STR;
extern volatile IIC0IBCR2STR _IIC0IBCR2 @0x000007C5;
#define IIC0IBCR2                       _IIC0IBCR2.Byte
#define IIC0IBCR2_ADR8                  _IIC0IBCR2.Bits.ADR8
#define IIC0IBCR2_ADR9                  _IIC0IBCR2.Bits.ADR9
#define IIC0IBCR2_ADR10                 _IIC0IBCR2.Bits.ADR10
#define IIC0IBCR2_ADTYPE                _IIC0IBCR2.Bits.ADTYPE
#define IIC0IBCR2_GCEN                  _IIC0IBCR2.Bits.GCEN
#define IIC0IBCR2_ADR_8                 _IIC0IBCR2.MergedBits.grpADR_8
#define IIC0IBCR2_ADR                   IIC0IBCR2_ADR_8

#define IIC0IBCR2_ADR8_MASK             0x01U
#define IIC0IBCR2_ADR9_MASK             0x02U
#define IIC0IBCR2_ADR10_MASK            0x04U
#define IIC0IBCR2_ADTYPE_MASK           0x40U
#define IIC0IBCR2_GCEN_MASK             0x80U
#define IIC0IBCR2_ADR_8_MASK            0x07U
#define IIC0IBCR2_ADR_8_BITNUM          0x00U

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * Defines                                                                                                            *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

#define MCU2_ADDR 0x7A
#define MCU3_ADDR 0x7B
#define MCU1_ADDR 0x6A
#define NOP __asm__("NOP");
#define MAX_REGISTERS 0xFF
#define TWO_SLAVE 1

#define ERR_OK           0U            /* OK */
#define ERR_SPEED        1U            /* This device does not work in the active speed mode. */
#define ERR_RANGE        2U            /* Parameter out of range. */
#define ERR_VALUE        3U            /* Parameter of incorrect value. */
#define ERR_OVERFLOW     4U            /* Timer overflow. */
#define ERR_MATH         5U            /* Overflow during evaluation. */
#define ERR_ENABLED      6U            /* Device is enabled. */
#define ERR_DISABLED     7U            /* Device is disabled. */
#define ERR_BUSY         8U            /* Device is busy. */
#define ERR_NOTAVAIL     9U            /* Requested value or method not available. */
#define ERR_RXEMPTY      10U           /* No data in receiver. */
#define ERR_TXFULL       11U           /* Transmitter is full. */
#define ERR_BUSOFF       12U           /* Bus not available. */
#define ERR_OVERRUN      13U           /* Overrun error is detected. */
#define ERR_FRAMING      14U           /* Framing error is detected. */
#define ERR_PARITY       15U           /* Parity error is detected. */
#define ERR_NOISE        16U           /* Noise error is detected. */
#define ERR_IDLE         17U           /* Idle error is detected. */
#define ERR_FAULT        18U           /* Fault error is detected. */
#define ERR_BREAK        19U           /* Break char is received during communication. */
#define ERR_CRC          20U           /* CRC error is detected. */
#define ERR_ARBITR       21U           /* A node losts arbitration. This error occurs if two nodes start transmission at the same time. */
#define ERR_PROTECT      22U           /* Protection error is detected. */
#define ERR_UNDERFLOW    23U           /* Underflow error is detected. */
#define ERR_UNDERRUN     24U           /* Underrun error is detected. */
#define ERR_COMMON       25U           /* Common error of a device. */
#define ERR_LINSYNC      26U           /* LIN synchronization error is detected. */
#define ERR_FAILED       27U           /* Requested functionality or process failed. */
#define ERR_QFULL        28U           /* Queue is full. */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * Enums                                                                                                              *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

typedef enum {
	NO_ERROR = 0x00,
	MASTER_ERROR = 0x01,
	SLAVE_ERROR = 0x02,
	INCORRECT_PARAMS = 0xFE,
	UNKNOWN_ERROR = 0xFF
} STATES;

typedef enum {
	MOT1, MOT2, MOT3, N_MOTORS
} MOTORS;

typedef enum {
	MCU2, MCU3, N_DRIVERS
} M_DRIVERS;

typedef enum {
	ERROR_REG = 0x00,
	M1_TARGET_ALL = 0x1A,
	M1_TARGET_POS_H = 0x1B,
	M1_TARGET_POS_L = 0x1C,
	M1_TARGET_SPEED_H = 0x1D,
	M1_TARGET_SPEED_L = 0x1E,
	M1_CTRL_REG = 0x1F,
	M2_TARGET_ALL = 0x2A,
	M2_TARGET_POS_H = 0x2B,
	M2_TARGET_POS_L = 0x2C,
	M2_TARGET_SPEED_H = 0x2D,
	M2_TARGET_SPEED_L = 0x2E,
	M2_CTRL_REG = 0x2F,
	M1_CUR_ALL = 0x4A,
	M1_CUR_POS_H = 0x4B,
	M1_CUR_POS_L = 0x4C,
	M1_CUR_SPEED_H = 0x4D,
	M1_CUR_SPEED_L = 0x4E,
	M1_CUR_ACC_H = 0x4F,
	M1_CUR_ACC_L = 0x50,
	M2_CUR_ALL = 0x5A,
	M2_CUR_POS_H = 0x5B,
	M2_CUR_POS_L = 0x5C,
	M2_CUR_SPEED_H = 0x5D,
	M2_CUR_SPEED_L = 0x5E,
	M2_CUR_ACC_H = 0x5F,
	M2_CUR_ACC_L = 0x60,

	RESET = 0x7A,
	MCU_INFO = 0x8A
} st_nxp_registers;

typedef enum {
	APP_SW_VERSION = 0x05,
	APP_SW_NUMBER = 0x06,
	MODULE_HW_VERSION = 0x07,
	MODULE_HW_NUMBER = 0x08,
	MODULE_BATCH_NUMBER = 0x09,
	DIAG_KL30 = 0x10,
	DIAG_TEMP = 0x11,
	DIAG_RTC_HH = 0x12,
	DIAG_RTC_MM = 0x13,
	DIAG_RTC_SS = 0x14,
	PARAM_I2C_ADDR = 0x70
} nxp_only_registers;

typedef struct {
	uint8 app_sw_version[2];
	uint8 app_sw_number[11];
	uint8 module_hw_version[1];
	uint8 module_hw_number[11];
	uint8 module_batch_number[15];
} nxp_version;

typedef struct {
	uint8 mcu;
	uint8 status;
} nxp_info_s;

typedef struct {
	uint8 diag_kl30;
	uint8 diag_temp;
	uint8 diag_rtc_hh;
	uint8 diag_rtc_mm;
	uint8 diag_rtc_sss;
} nxp_diagnostic;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * Structs                                                                                                            *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * Function Prototypes                                                                                                *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

#endif /* IIC0_CFG_H_ */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ *
 * EOF                                                                                                                *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
