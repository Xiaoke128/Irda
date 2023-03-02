#include "hal_gpio.h"

void GpioInit(void)
{
	GPIO_InitType GPIO_InitStructure;
	
	RCC_EnableAPB2PeriphClk(LED_PORT_CLK | IO_PORT_CLK | RELAY_PORT_CLK, ENABLE);
	
	GPIO_InitStructure.Pin            = LED0_PIN;    
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(LED_KEY_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin            = LED1_PIN;
	GPIO_InitPeripheral(LED_KEY_PORT, &GPIO_InitStructure);
	
	//GPIO_InitStructure.Pin            = LED2_PIN;
	//GPIO_InitPeripheral(LED_KEY_PORT, &GPIO_InitStructure);
	
	//GPIO_InitStructure.Pin            = LED3_PIN;
	//GPIO_InitPeripheral(LED_KEY_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin            = IO1_PIN;
	GPIO_InitPeripheral(IO12_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin            = IO2_PIN;
	GPIO_InitPeripheral(IO12_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin            = IO3_PIN;
	GPIO_InitPeripheral(IO34_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin            = IO4_PIN;
	GPIO_InitPeripheral(IO34_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin            = RELAY_PIN;
	GPIO_InitPeripheral(RELAY_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin            = KEY_PIN;
	GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
	GPIO_InitPeripheral(LED_KEY_PORT, &GPIO_InitStructure);
	
	LED0_OFF;
	LED1_OFF;
	SysInfo.KeyLevel = GPIO_ReadInputDataBit(LED_KEY_PORT, KEY_PIN);//read the key level when power on
	//LED2_ON;
	//LED3_ON;
}

void IoDirSet(ChannelNumDefine channel, IoInOutStatus dir)
{
	GPIO_InitType GPIO_InitStructure;
	
	if(channel == CHANNEL_IO1 || channel == CHANNEL_IR1)
	{
		GPIO_InitStructure.Pin            = IO1_PIN;
	}
	else if(channel == CHANNEL_IO2 || channel == CHANNEL_IR2)
	{
		GPIO_InitStructure.Pin            = IO2_PIN;
	}
	else if(channel == CHANNEL_IO3)
	{
		GPIO_InitStructure.Pin            = IO3_PIN;
	}
	else if(channel == CHANNEL_IO4)
	{
		GPIO_InitStructure.Pin            = IO4_PIN;
	}
	
	if(dir == IO_OUTPUT_STATUS)
	{
		GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
	}
	
	if((channel == CHANNEL_IO1) || (channel == CHANNEL_IO2) || channel == CHANNEL_IR1 || channel == CHANNEL_IR2)
	{
		GPIO_InitPeripheral(IO12_PORT, &GPIO_InitStructure);
	}
	else if((channel == CHANNEL_IO3) || (channel == CHANNEL_IO4))
	{
		GPIO_InitPeripheral(IO34_PORT, &GPIO_InitStructure);
	}
}

void IoOutputLevel(ChannelNumDefine channel, Bit_OperateType level)
{
	IoDirSet(channel, IO_OUTPUT_STATUS);
	if(channel == CHANNEL_IO1 || channel == CHANNEL_IR1)
	{
		GPIO_WriteBit(IO12_PORT, IO1_PIN, level);
	}
	else if(channel == CHANNEL_IO2 || channel == CHANNEL_IR2)
	{
		GPIO_WriteBit(IO12_PORT, IO2_PIN, level);
	}
	else if(channel == CHANNEL_IO3)
	{
		GPIO_WriteBit(IO34_PORT, IO3_PIN, level);
	}
	else if(channel == CHANNEL_IO4)
	{
		GPIO_WriteBit(IO34_PORT, IO4_PIN, level);
	}
}

uint8_t IoReadLevel(ChannelNumDefine channel)
{
	IoDirSet(channel, IO_INPUT_STATUS);
	if(channel == CHANNEL_IO1 || channel == CHANNEL_IR1)
	{
		return (GPIO_ReadInputDataBit(IO12_PORT, IO1_PIN));
	}
	else if(channel == CHANNEL_IO2 || channel == CHANNEL_IR2)
	{
		return (GPIO_ReadInputDataBit(IO12_PORT, IO2_PIN));
	}
	else if(channel == CHANNEL_IO3)
	{
		return (GPIO_ReadInputDataBit(IO34_PORT, IO3_PIN));
	}
	else if(channel == CHANNEL_IO4)
	{
		return (GPIO_ReadInputDataBit(IO34_PORT, IO4_PIN));
	}
	return 0;
}

void ledTest(void)
{
#if 0
	static uint16_t count = 0;
	if(SysFlagVal.bit.sys_1ms)
	{
		SysFlagVal.bit.sys_1ms = 0;
		count++;
		if(count >= 1000)
		{
			count = 0;
			GPIO_TogglePin(LED_KEY_PORT, LED0_PIN);
			GPIO_TogglePin(LED_KEY_PORT, LED1_PIN);
			printf("LED Toggle!\r\n");
		}
	}
#else
	GPIO_TogglePin(LED_KEY_PORT, LED0_PIN);
	GPIO_TogglePin(LED_KEY_PORT, LED1_PIN);
	printf("LED Toggle!\r\n");
	Delay_ms(1000);	
#endif
}