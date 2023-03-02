#ifndef INIT_H
#define INIT_H

#include "hal_uart.h"
#include <stdio.h>
#include "hal_timer.h"
#include "protocol.h"
#include "delay.h"

typedef union{
	uint32_t val;
	struct{
		uint8_t sys_1ms:			1;
		uint8_t pro_timer_enable:	1;
		uint8_t	delay_enable:		1;
		uint32_t reserved:			29;
	}bit;
}SysFlag;

typedef enum{
	IO_GPIO,
	IO_IR,
}IoFuncEnum;

typedef enum{
	IO_INPUT_STATUS,
	IO_OUTPUT_STATUS,
}IoInOutStatus;

typedef enum{
	CHANNEL_UART0 = 0x00,
	//1 ~ 7 not use
	CHANNEL_IO1 = 0x08,
	CHANNEL_IO2,
	CHANNEL_IO3,
	CHANNEL_IO4,
	
	CHANNEL_RELAY0 = 0x10,
	
	CHANNEL_IR1 = 0x18,
	CHANNEL_IR2,
}ChannelNumDefine;

typedef union{
	uint32_t val;
	struct{
		IoInOutStatus	IO1_InOut		:8;
		IoInOutStatus	IO2_InOut		:8;
		IoInOutStatus	IO3_InOut		:8;
		IoInOutStatus	IO4_InOut		:8;
	}byte;
}IoStatus;

typedef struct{
	IoStatus					IO_Status;
	uint8_t						KeyLevel;
	uint8_t						NetLedStatus;
	uint8_t						RunningLedStatus;
	IoFuncEnum					IoFunc;
}SystemStr;

void MCU_Init(void);


extern SysFlag SysFlagVal;
extern SystemStr SysInfo;
#endif
