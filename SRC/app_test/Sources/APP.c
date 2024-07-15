/*
 * BL.c
 *
 *  Created on: Mar 21, 2024
 *      Author: Andrea Cencio
 */

#include "APP.h"

#define BUSY 1
#define FREE 0

static byte bl_state = BL_IDLE;

fsm_status_st bl_fsm_status;
data_program_st bl_program;
byte bl_temp_payload[256];
commands_ut commands;
bl_flags_ut bl_flags;
byte ret;

extern word sent; 

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

void APP_FSM() {
	// FSM
	if (TRUE == flags.Bits.R_READ_REQ) {
		flags.Bits.R_READ_REQ = FALSE;
		CI2C1_SendBlock(i2c_buf, sizeof(i2c_buf), &sent);
	}
}
