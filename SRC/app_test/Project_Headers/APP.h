/*
 * BL.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Andrea Cencio
 */

#ifndef BL_H_
#define BL_H_

#include "PE_Types.h"
#include "Events.h"
#include <string.h>

typedef enum {
	ERASE, WRITE_HEADER, WRITE_PAYLOAD, FUNCTION, STATUS
} Commands_ut;

typedef enum {
	BL_INIT, BL_IDLE, BL_PARSE_COMMAND, BL_EXECUTE_COMMAND, BL_READ_WRITED_PAYLOAD, BL_WAIT_COMMAND, BL_ERROR, NR_BL_STATES
} BL_States_ut;

typedef enum {
	DATA, END_OF_FILE, EXTENDED_SEGMENT_ADDRESS, START_SEGMENT_ADDRESS, EXTENDED_LINEAR_ADDRESS, START_LINEAR_ADDRESS, NR_RECORD_TYPE
} IHex_record_type_ut;

typedef struct {
	byte command_recv :1;
	byte command_in_prog :1;
} fsm_status_st;

typedef struct {
	dword addr_start;
	dword addr_stop;
} erase_payload_st;

typedef struct {
	byte payload_len;
	word addr_start;
	byte record_type;
} program_header_st;

typedef struct {
	byte payload[16]; // 16 = Maximum payload length
	byte checksum;
} program_payload_st;

// Struct Erase: Command with two long addresses
struct Erase {
	byte command;
	union {
		erase_payload_st payload;
		byte data[8];
	};
};

// Struct Program_Header: Command with payload length, address, and record type
struct Program_Header {
	byte command;
	union {
		program_header_st payload;
		byte data[4];
	};
};

// Struct Program_Payload: Command with payload and checksum
struct Program_Payload {
	byte command;
	union {
		program_payload_st payload;
		byte data[17];
	};
};

// Struct Function: Command with action
struct Function {
	byte command;
	union {
		byte action;
		byte data;
	};
};

// Struct Status: Command with result
struct Status {
	byte command;
	union {
		byte result;
		byte data;
	};
};

// Struct Generic: generic command with payload
struct Generic {
	byte command;
	byte payload[17];
};

// Union of all the command structs
typedef union {
	struct Generic generic;
	struct Erase erase;
	struct Program_Header program_header;
	struct Program_Payload program_payload;
	struct Function function;
	struct Status status;
} commands_ut;

typedef struct {
	byte command;
	byte record_type;
	union {
		struct {
			word location;
			union {
				struct {
					byte offset_MSB;
					byte offset_LSB;
				};
				word offset;
			};
		} composition;
		dword address;
	};
	byte data_len;
	byte payload[16];
	byte checksum;
} data_program_st;

struct bl_flags_st {
	byte r :1;
	byte w :1;
	byte erase :1;
	byte header :1;
	byte payload :1;
	byte function :1;
	byte status :1;
	byte dummy :1;
	byte error;
};

typedef union {
	struct bl_flags_st detail;
	word flags;
} bl_flags_ut;

extern fsm_status_st bl_fsm_status;
extern data_program_st bl_program;
extern byte bl_temp_payload[];
extern commands_ut commands;
extern bl_flags_ut bl_flags;

void APP_FSM();

#endif /* BL_H_ */
