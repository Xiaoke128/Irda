#include "init.h"
#include "hal_gpio.h"
#include "protocol.h"
SysFlag SysFlagVal;

SystemStr SysInfo = {
	{IO_OUTPUT_STATUS | IO_OUTPUT_STATUS << 8 | IO_OUTPUT_STATUS << 16 | IO_OUTPUT_STATUS << 24},
	0,
	0,
	0,
	IO_GPIO,
};

static void VarInit(void)
{
	memset(&confData, 0, sizeof(confData));
	confData.uartConf.baudRate = 0xC200;
	confData.uartConf.otherConf.bit.dataBits = 0x03;
	confData.uartConf.otherConf.bit.stopBits = 0x00;
	confData.uartConf.otherConf.bit.checkBits = 0x00;
}

void MCU_Init(void)
{
	VarInit();
	GpioInit();
	HostUartInit();
	DebugUartInit();
	TimerInit();
	DelayInit();
	printf("Build Data and Time: %s %s", __DATE__, __TIME__);
	DebugUartSend("DEBUG UART!", 12);
}
