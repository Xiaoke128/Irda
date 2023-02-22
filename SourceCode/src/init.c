#include "init.h"

SysFlag SysFlagVal;

SystemStr SysInfo = {
	{0x00000000},
	0,
	0,
	0,
};

void MCU_Init(void)
{
	GpioInit();
	HostUartInit();
	DebugUartInit();
	TimerInit();
	printf("Build Data and Time: %s %s", __DATE__, __TIME__);
	DebugUartSend("DEBUG UART!", 12);
}
