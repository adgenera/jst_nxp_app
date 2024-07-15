/*
 * BL.c
 *
 *  Created on: Mar 21, 2024
 *      Author: Andrea Cencio
 */

#include "BL.h"

#define BUSY 1
#define FREE 0

static byte bl_state = BL_IDLE;

fsm_status_st bl_fsm_status;
data_program_st bl_program;
byte bl_temp_payload[256];
commands_ut commands;
bl_flags_ut bl_flags;
byte ret;

byte parse_header(void);
byte parse_payload(void);
byte check_checksum(void);

byte parse_header() {
	byte ret = ERR_OK;

	bl_program.record_type = commands.program_header.payload.record_type;
	bl_program.data_len = commands.program_header.payload.payload_len;
	bl_program.composition.offset = commands.program_header.payload.addr_start;
	return ret;
}

byte check_checksum() {
	dword result;
	byte i;

	// add or not the address on the header, depending the message type
	switch (bl_program.record_type) {
	case DATA:
		result = bl_program.data_len + bl_program.record_type
				+ bl_program.composition.offset_MSB
				+ bl_program.composition.offset_LSB;
		break;
	case END_OF_FILE:
	case EXTENDED_SEGMENT_ADDRESS:
	case START_SEGMENT_ADDRESS:
	case EXTENDED_LINEAR_ADDRESS:
	case START_LINEAR_ADDRESS:
		result = bl_program.data_len + bl_program.record_type;
		break;

	default:
		break;
	}

	// add payload to the sum
	for (i = 0; i < bl_program.data_len; i++) {
		result += bl_program.payload[i];
	}

	// last but not least, add checksum
	result += bl_program.checksum;

	// if LSB is equals to 0, the checksum is ok
	if ((result & 0x000000FF) == 0) {
		return ERR_OK;
	} else {
		return ERR_VALUE;
	}
}

byte parse_payload() {
	byte ret = ERR_OK;
	memcpy(bl_program.payload, commands.program_payload.payload.payload, 0x10);
	bl_program.checksum = commands.program_payload.payload.checksum;
	switch (bl_program.record_type) {
	case DATA:
		ret = check_checksum();
		break;
	case END_OF_FILE:
		ret = check_checksum();
		break;
	case EXTENDED_SEGMENT_ADDRESS:
		memcpy(&(bl_program.composition.location), bl_program.payload, 2);
		ret = check_checksum();
		break;
	case START_SEGMENT_ADDRESS:
		ret = check_checksum();
		break;
	case EXTENDED_LINEAR_ADDRESS:
		memcpy(&(bl_program.composition.location), bl_program.payload, 2);
		ret = check_checksum();
		break;
	case START_LINEAR_ADDRESS:
		ret = check_checksum();
		break;
	default:
		break;
	}
	return ret;
}

void BL_FSM() {
	// FSM
	switch (bl_state) {
	case BL_INIT:
		bl_state = BL_IDLE;
		break;
	case BL_IDLE:
		WDog1_Clear();
		if (TRUE == bl_fsm_status.command_recv
				&& FALSE == bl_fsm_status.command_in_prog) {
			bl_state = BL_PARSE_COMMAND;
			bl_flags.detail.status = BUSY;
		} else if (FALSE == bl_fsm_status.command_recv
				&& TRUE == bl_fsm_status.command_in_prog) {
			bl_state = BL_EXECUTE_COMMAND;
		} else {
			bl_state = BL_IDLE;
			bl_flags.detail.status = FREE;
		}
		break;
	case BL_PARSE_COMMAND:
		bl_fsm_status.command_recv = FALSE;
		bl_fsm_status.command_in_prog = TRUE;
		bl_state = BL_EXECUTE_COMMAND;
		break;
	case BL_EXECUTE_COMMAND:
		switch (commands.generic.command) {
		case ERASE:
			bl_flags.detail.erase = BUSY;
			ret = IFsh1_EraseSector(APPLICATION_RESET_VEC_ADD);
			while (commands.erase.payload.addr_start < BOOTLOADER_START_ADD ) {
				ret = IFsh1_EraseSector(commands.erase.payload.addr_start);
				commands.erase.payload.addr_start += 0x200;
				if (ERR_OK != ret) {
					break;
				} else {
					WDog1_Clear();
					continue;
				}
			}
			bl_flags.detail.error = ret;
			if (ERR_OK == ret) {
				bl_fsm_status.command_in_prog = FALSE;
				bl_flags.detail.erase = FREE;
				bl_state = BL_WAIT_COMMAND;
			} else {
				asm(NOP);
				bl_state = BL_ERROR;
			}
			break;
		case WRITE_HEADER:
			bl_flags.detail.header = BUSY;
			ret = parse_header();
			bl_flags.detail.error = ret;
			if (ERR_OK == ret) {
				bl_fsm_status.command_in_prog = FALSE;
				bl_flags.detail.header = FREE;
				bl_state = BL_WAIT_COMMAND;
			} else {
				asm(NOP);
				bl_state = BL_ERROR;
			}
			break;
		case WRITE_PAYLOAD:
			bl_flags.detail.payload = BUSY;
			ret = parse_payload();
			bl_flags.detail.error = ret;
			if (ERR_OK == ret) {
				if ((DATA == bl_program.record_type)
						&& (bl_program.address < 0x00FFE800)) {
					if (bl_program.data_len & 0x00000001) {
						ret = IFsh1_SetBlockFlash(bl_program.payload,
								bl_program.address, bl_program.data_len + 1);
					} else {
						ret = IFsh1_SetBlockFlash(bl_program.payload,
								bl_program.address, bl_program.data_len);
					}
					bl_flags.detail.error = ret;
					if (ERR_OK == ret) {
						bl_state = BL_READ_WRITED_PAYLOAD;
					} else {
						asm(NOP);
					}
				} else {
					bl_fsm_status.command_in_prog = FALSE;
					bl_flags.detail.payload = FREE;
					bl_state = BL_WAIT_COMMAND;
				}
			} else {
				asm(NOP);
				bl_state = BL_ERROR;
			}
			break;
		case FUNCTION:
			bl_flags.detail.function = BUSY;
			bl_flags.detail.function = FREE;
			bl_fsm_status.command_in_prog = FALSE;
			bl_state = BL_WAIT_COMMAND;
			break;
		case STATUS:
			bl_flags.detail.status = BUSY;
			bl_flags.detail.status = FREE;
			bl_fsm_status.command_in_prog = FALSE;
			bl_state = BL_WAIT_COMMAND;
			break;
		case RESET:
			WDog1_Trigger();
			break;
		default:
			bl_fsm_status.command_in_prog = FALSE;
			bl_state = BL_WAIT_COMMAND;
			break;
		}
		break;
	case BL_READ_WRITED_PAYLOAD:
		if (bl_program.data_len & 0x00000001) {
			ret = IFsh1_GetBlockFlash(bl_program.address, bl_program.payload,
					bl_program.data_len + 1);
		} else {
			ret = IFsh1_GetBlockFlash(bl_program.address, bl_program.payload,
					bl_program.data_len);
		}
		bl_flags.detail.error = ret;
		if (ERR_OK == ret) {
			ret = check_checksum();
			bl_flags.detail.error = ret;
			if (ERR_OK == ret) {
				bl_fsm_status.command_in_prog = FALSE;
				bl_flags.detail.payload = FREE;
				bl_state = BL_WAIT_COMMAND;
			} else {
				asm(NOP);
				bl_state = BL_ERROR;
			}
		} else {
			asm(NOP);
			bl_state = BL_ERROR;
		}
		break;
	case BL_WAIT_COMMAND:
		if (FALSE == bl_fsm_status.command_in_prog) {
			bl_state = BL_IDLE;
		} else {
			asm(NOP);
			bl_flags.detail.error = ret;
			bl_state = BL_ERROR;
		}
		break;
	case BL_ERROR:
		asm(NOP);
		break;
	default:
		bl_state = BL_INIT;
		break;
	}

}
