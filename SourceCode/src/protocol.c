#include "protocol.h"
#include "hal_gpio.h"
#include "ir_control.h" 

ProStruct ProStr;
ComNeedConfStr ComConfData = {
	0,
	{0},
};

ConfDataStr confData;

static void ProtocolParse(uint8_t ch);
static void ControlAction(void);
static void ControlConfirmAction(void);
static void ConfigureAction(void);
static void ConfigureConfirmAction(void);
static void UartReadAction(void);
static void IO_Action(void);
static void InOutStatusAction(void);
static void NetLedStatusAction(void);
static void RunningLedStatusAction(void);

FuncStr FuncTable[] = {
	{COMMAND_81,				ControlAction},
	{COMMAND_CONFIRM_81,		ControlConfirmAction},
	{COMMAND_83,				ConfigureAction},
	{COMMAND_CONFIRM_83,		ConfigureConfirmAction},
	{COMMAND_88,				UartReadAction},
	{COMMAND_89,				IO_Action},
	{COMMAND_8A,				InOutStatusAction},
	{COMMAND_8B,				NetLedStatusAction},
	{COMMAND_8C,				RunningLedStatusAction},
};


void ComTask(void)
{
	uint8_t ch = 0;
	uint8_t i = 0;
	
	if(HostCheck())
	{
		ProTimerEnable();
		ch = HostGetData();
		//HostUartSend(&ch, 1);
		ProtocolParse(ch);
		if(ProStr.paraDone)
		{
			ProStr.paraDone = 0;
			for(i = 0; i < (sizeof(FuncTable) / sizeof(FuncStr)); i++)
			{
				if(FuncTable[i].Command == ProStr.command)
				{
					FuncTable[i].Func();
					break;
				}
			}
		}
	}
#if 0
	if(DebugCheck())
	{
		ch = DebugGetData();
		DebugUartSend(&ch, 1);
	}
#endif
}

static void ControlAction(void)
{
	ComConfData.index = ProStr.dataLen;
	memcpy(ComConfData.data, ProStr.data, ComConfData.index);
}

static void ControlConfirmAction(void)
{
	uint8_t resbuf[9] = {0x09, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x81};
	uint8_t index = 0;
	
	if(ProStr.data[0] <= 7)//channel number, UART
	{
		if(ProStr.data[0] == 0)
		{
			index = 7;
			for(; index < ComConfData.index; index++)
			{
				DebugUartSend(&ComConfData.data[index], 1);
			}
		}
	}
	else if(ProStr.data[0] <= 15)//IO
	{
		if(ProStr.data[7] == 0)
		{
			IoOutputLevel((ChannelNumDefine)ProStr.data[0], Bit_RESET);
		}
		else
		{
			IoOutputLevel((ChannelNumDefine)ProStr.data[0], Bit_SET);
		}
	}
	else if(ProStr.data[0] <= 23)//relay
	{
		if(ProStr.data[7] == 0)
		{
			RELAY_CLOSE;
		}
		else
		{
			RELAY_OPEN;
		}
	}
	else if(ProStr.data[0] <= 27)//ir
	{
		SendIrData((ChannelNumDefine)ProStr.data[0], 0x01, ProStr.data[7]);
	}
	ComConfData.index = 0;
	memset(ComConfData.data, 0, sizeof(ComConfData.data));
	HostUartSend(resbuf, sizeof(resbuf));
}

static void ConfigureAction(void)
{
	ComConfData.index = ProStr.dataLen;
	memcpy(ComConfData.data, ProStr.data, ComConfData.index);
}

static void ConfigureConfirmAction(void)
{
	uint8_t index = 0;
	uint8_t resbuf[9] = {0x09, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x83};
	
	memset(&confData, 0, sizeof(confData));
	confData.uartNum = ComConfData.data[index++];
	confData.uartConf.channel = ComConfData.data[index++];
	confData.uartConf.type = ComConfData.data[index++];
	confData.uartConf.baudRate = ComConfData.data[index++];
	confData.uartConf.baudRate += (uint16_t)(ComConfData.data[index++] << 8);
	confData.uartConf.otherConf.bit.dataBits = ComConfData.data[index] & 0x03;
	confData.uartConf.otherConf.bit.stopBits = ComConfData.data[index] & 0x04;
	confData.uartConf.otherConf.bit.checkBits = ComConfData.data[index] & 0x38;
	confData.uartConf.otherConf.bit.rtsEnable = ComConfData.data[index++] & 0x40;
	//configure uart
	DebugUartReInit();
	
	index += (confData.uartNum - 1) * 5;
	confData.irNum = ComConfData.data[index++];
	confData.irConf[0].channel = ComConfData.data[index++];
	confData.irConf[0].freq = ComConfData.data[index++];
	confData.irConf[0].freq += (uint16_t)(ComConfData.data[index++] << 8);
	confData.irConf[1].channel = ComConfData.data[index++];
	confData.irConf[1].freq = ComConfData.data[index++];
	confData.irConf[1].freq += (uint16_t)(ComConfData.data[index++] << 8);
	index += (confData.irNum - 2) * 3;
	//configure IR, do nothing
	
	confData.ioNum = ComConfData.data[index++];
	confData.ioConf[0].channel = ComConfData.data[index++];
	confData.ioConf[0].level = ComConfData.data[index++];
	confData.ioConf[0].ioStatus = (IoInOutStatus)ComConfData.data[index++];
	SysInfo.IO_Status.byte.IO1_InOut = confData.ioConf[0].ioStatus;
	confData.ioConf[1].channel = ComConfData.data[index++];
	confData.ioConf[1].level = ComConfData.data[index++];
	confData.ioConf[1].ioStatus = (IoInOutStatus)ComConfData.data[index++];
	SysInfo.IO_Status.byte.IO2_InOut = confData.ioConf[1].ioStatus;
	confData.ioConf[2].channel = ComConfData.data[index++];
	confData.ioConf[2].level = ComConfData.data[index++];
	confData.ioConf[2].ioStatus = (IoInOutStatus)ComConfData.data[index++];
	SysInfo.IO_Status.byte.IO3_InOut = confData.ioConf[2].ioStatus;
	confData.ioConf[3].channel = ComConfData.data[index++];
	confData.ioConf[3].level = ComConfData.data[index++];
	confData.ioConf[3].ioStatus = (IoInOutStatus)ComConfData.data[index++];
	SysInfo.IO_Status.byte.IO4_InOut = confData.ioConf[3].ioStatus;
	//configure io
	IoDirSet((ChannelNumDefine)confData.ioConf[0].channel, confData.ioConf[0].ioStatus);
	if(confData.ioConf[0].ioStatus == IO_OUTPUT_STATUS)
	{
		IoOutputLevel((ChannelNumDefine)confData.ioConf[0].channel, (Bit_OperateType)confData.ioConf[0].level);
	}
	IoDirSet((ChannelNumDefine)confData.ioConf[1].channel, confData.ioConf[1].ioStatus);
	if(confData.ioConf[1].ioStatus == IO_OUTPUT_STATUS)
	{
		IoOutputLevel((ChannelNumDefine)confData.ioConf[1].channel, (Bit_OperateType)confData.ioConf[1].level);
	}
	IoDirSet((ChannelNumDefine)confData.ioConf[2].channel, confData.ioConf[2].ioStatus);
	if(confData.ioConf[2].ioStatus == IO_OUTPUT_STATUS)
	{
		IoOutputLevel((ChannelNumDefine)confData.ioConf[2].channel, (Bit_OperateType)confData.ioConf[2].level);
	}
	IoDirSet((ChannelNumDefine)confData.ioConf[3].channel, confData.ioConf[3].ioStatus);
	if(confData.ioConf[3].ioStatus == IO_OUTPUT_STATUS)
	{
		IoOutputLevel((ChannelNumDefine)confData.ioConf[3].channel, (Bit_OperateType)confData.ioConf[3].level);
	}
	ComConfData.index = 0;
	memset(ComConfData.data, 0, sizeof(ComConfData.data));
	HostUartSend(resbuf, sizeof(resbuf));
}

static void UartReadAction(void)
{
	uint8_t resbuf[9] = {0};
	uint8_t ch = 0;	
	uint32_t datalen = DebugCheck();
	resbuf[0] = (datalen + 5);
	resbuf[1] = (datalen + 5) >> 8;
	resbuf[2] = (datalen + 5) >> 16;
	resbuf[3] = (datalen + 5) >> 24;
	resbuf[4] = datalen;
	resbuf[5] = 0;
	resbuf[6] = 0;
	resbuf[7] = 0;
	resbuf[8] = 0;//channel number	
	HostUartSend(resbuf, sizeof(resbuf));
	while(DebugCheck())
	{
		ch = DebugGetData();
		HostUartSend(&ch, 1);
	};
}

static void IO_Action(void)
{
	uint8_t resbuf[13] = {0x09, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x89,};
	
	resbuf[9] = SysInfo.IO_Status.byte.IO1_InOut;
	resbuf[10] = SysInfo.IO_Status.byte.IO2_InOut;
	resbuf[11] = SysInfo.IO_Status.byte.IO3_InOut;
	resbuf[12] = SysInfo.IO_Status.byte.IO4_InOut;
	HostUartSend(resbuf, sizeof(resbuf));
}

static void InOutStatusAction(void)
{
	uint8_t resbuf[9] = {0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01};
	
	resbuf[8] = SysInfo.KeyLevel;
	HostUartSend(resbuf, sizeof(resbuf));
}

static void NetLedStatusAction(void)
{
	uint8_t resbuf[9] = {0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x8B};
	
	SysInfo.NetLedStatus = ProStr.data[0];
	if(SysInfo.NetLedStatus)
	{
		LED0_ON;
	}
	else
	{
		LED0_OFF;
	}
	HostUartSend(resbuf, sizeof(resbuf));
}

static void RunningLedStatusAction(void)
{
	uint8_t resbuf[9] = {0x05, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x8C};
	
	SysInfo.RunningLedStatus = ProStr.data[0];
	if(SysInfo.RunningLedStatus)
	{
		LED1_ON;
	}
	else
	{
		LED1_OFF;
	}
	HostUartSend(resbuf, sizeof(resbuf));
}

static void ProtocolParse(uint8_t ch)
{
	static uint32_t len_temp = 0;
	
	switch(ProStr.step)
	{
	case HEAD_1:
		if(ch == PROTOCOL_HEAD_1)
		{
			ProStr.dataLen = 0;
			ProStr.step = HEAD_2;
		}
		break;
	case HEAD_2:
		if(ch == PROTOCOL_HEAD_2)
		{
			ProStr.step = HEAD_3;
		}
		break;
	case HEAD_3:
		if(ch == PROTOCOL_HEAD_3)
		{
			ProStr.step = HEAD_4;
		}
		break;
	case HEAD_4:
		if(ch == PROTOCOL_HEAD_4)
		{
			ProStr.step = HEAD_5;
		}
		break;
	case HEAD_5:
		if(ch == PROTOCOL_HEAD_5)
		{
			ProStr.step = HEAD_6;
		}
		break;
	case HEAD_6:
		if(ch == PROTOCOL_HEAD_6)
		{
			ProStr.step = COMMAND;
		}
		break;
	case COMMAND:
		ProStr.command = (ComEnum)ch;
		ProStr.step = LEN_HH;
		break;
	case LEN_HH:
		ProStr.comLen = ch;
		ProStr.step = LEN_HL;
		break;
	case LEN_HL:
		ProStr.comLen += (uint32_t)(ch << 8);
		ProStr.step = LEN_LH;
		break;
	case LEN_LH:
		ProStr.comLen += (uint32_t)(ch << 16);
		ProStr.step = LEN_LL;
		break;
	case LEN_LL:
		ProStr.comLen += (uint32_t)(ch << 24);
		len_temp = ProStr.comLen - COMMAND_MIN_LEN;
		if(len_temp > 0)
		{
			ProStr.step = DATA;
		}
		else
		{
			ProStr.step = HEAD_1;
			ProStr.paraDone = 1;
			ProTimerDisable();
		}
		break;
	case DATA:
		ProStr.data[ProStr.dataLen++] = ch;
		len_temp--;
		if(len_temp == 0)
		{
			ProStr.step = HEAD_1;
			ProStr.paraDone = 1;
			ProTimerDisable();
		}
		break;
	default:
		
		break;
	}
}