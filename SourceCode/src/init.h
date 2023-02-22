#ifndef INIT_H
#define INIT_H

#include "hal_uart.h"
#include "hal_gpio.h"
#include <stdio.h>
#include "hal_timer.h"
#include "protocol.h"

typedef union{
	uint32_t val;
	struct{
		uint8_t sys_1ms:		1;
		uint32_t reserved:		31;
	}bit;
}SysFlag;

typedef union{
	uint32_t val;
	struct{
		uint8_t	IO1_InOut		:8;
		uint8_t	IO2_InOut		:8;
		uint8_t	IO3_InOut		:8;
		uint8_t	IO4_InOut		:8;
	}byte;
}IoStatus;

typedef struct{
	IoStatus					IO_Status;
	uint8_t						KeyLevel;
	uint8_t						NetLedStatus;
	uint8_t						RunningLedStatus;
}SystemStr;

void MCU_Init(void);


extern SysFlag SysFlagVal;
extern SystemStr SysInfo;
#endif
