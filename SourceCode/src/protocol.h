#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdio.h>
#include "hal_uart.h"
#include "init.h"
#include <string.h>


#define PROTOCOL_HEAD_1							0xFF
#define PROTOCOL_HEAD_2							0xFF
#define PROTOCOL_HEAD_3							0x53
#define PROTOCOL_HEAD_4							0x43
#define PROTOCOL_HEAD_5							0x48
#define PROTOCOL_HEAD_6							0x44

#define COMMAND_MIN_LEN							11

typedef void (*Fctr)(void);

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

typedef union{
	uint8_t val;
	struct{
		uint8_t dataBits:		2;
		uint8_t stopBits:		1;
		uint8_t checkBits:		3;
		uint8_t rtsEnable:		1;
		uint8_t reserved:		1;
	}bit;
}UartOtherConfUnion;

typedef struct{
	uint8_t channel;
	uint8_t type;
	uint16_t baudRate;
	UartOtherConfUnion otherConf;
}UartConfStr;

typedef struct{
	uint8_t channel;
	uint16_t freq;
}IrConfStr;

typedef struct{
	uint8_t channel;
	uint8_t level;
	IoInOutStatus ioStatus; 
}IoConfStr;

typedef struct{
	uint8_t uartNum;
	UartConfStr uartConf;
	uint8_t irNum;
	IrConfStr irConf[2];
	uint8_t ioNum;
	IoConfStr ioConf[4];
}ConfDataStr;

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
	uint8_t paraDone;
}ProStruct;

typedef struct{
	uint8_t index;
	uint8_t data[100];
}ComNeedConfStr;

typedef struct{
	ComEnum Command;
	Fctr	Func;
}FuncStr;

extern ProStruct ProStr;
extern ConfDataStr confData;
void ComTask(void);

#endif