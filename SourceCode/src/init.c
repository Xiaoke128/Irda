#include "init.h"
#include "hal_gpio.h"

SysFlag SysFlagVal;

SystemStr SysInfo = {
	{IO_OUTPUT_STATUS | IO_OUTPUT_STATUS << 8 | IO_OUTPUT_STATUS << 16 | IO_OUTPUT_STATUS << 24},
	0,
	0,
	0,
	IO_GPIO,
};

void MCU_Init(void)
{
	GpioInit();
	HostUartInit();
	DebugUartInit();
	TimerInit();
	DelayInit();
	printf("Build Data and Time: %s %s", __DATE__, __TIME__);
	DebugUartSend("DEBUG UART!", 12);
}
