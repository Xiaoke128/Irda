#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdio.h>
#include "hal_uart.h"

#define PROTOCOL_HEAD_1							0xFF
#define PROTOCOL_HEAD_2							0xFF
#define PROTOCOL_HEAD_3							0x53
#define PROTOCOL_HEAD_4							0x43
#define PROTOCOL_HEAD_5							0x48
#define PROTOCOL_HEAD_6							0x44

typedef enum{
	COMMAND_81 = 0x81,
	COMMAND_CONFIRM_81 = 0x01,
	COMMAND_83 = 0x83,
	COMMAND_CONFIRM_83 = 0x03,
	COMMAND_88 = 0x88,
	COMMAND_89 = 0x89,
	COMMAND_8A = 0x8A,
	COMMAND_8B = 0x8B,
	COMMAND_8C = 0x8C,
}ComEnum;

typedef enum{
	HEAD_1,
	HEAD_2,
	HEAD_3,
	HEAD_4,
	HEAD_5,
	HEAD_6,
	COMMAND,
	LEN_HH,
	LEN_HL,
	LEN_LH,
	LEN_LL,
	DATA,
}ProStep;

typedef struct{
	ProStep step;
	uint8_t head[6];
	ComEnum command;
	uint32_t comLen;
	uint8_t dataLen;
	uint8_t data[100];
}ProStruct;

void ComTask(void);

#endif