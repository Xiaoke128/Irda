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

void MCU_Init(void);


extern SysFlag SysFlagVal;
#endif
