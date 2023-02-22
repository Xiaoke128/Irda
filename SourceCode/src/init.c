#include "init.h"

SysFlag SysFlagVal;

void MCU_Init(void)
{
	GpioInit();
	HostUartInit();
	DebugUartInit();
	TimerInit();
	printf("Build Data and Time: %s %s", __DATE__, __TIME__);
	DebugUartSend("DEBUG UART!", 12);
}
