#include "init.h"

SysFlag SysFlagVal;

void MCU_Init(void)
{
	GpioInit();
	HostUartInit();
	TimerInit();
	printf("Build Data and Time: %s %s", __DATE__, __TIME__);
}
