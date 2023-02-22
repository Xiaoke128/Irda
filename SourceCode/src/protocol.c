#include "protocol.h"

ProStruct ProStr;
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
	if(DebugCheck())
	{
		ch = DebugGetData();
		DebugUartSend(&ch, 1);
	}
}

static void ControlAction(void)
{
	
}

static void ControlConfirmAction(void)
{
	uint8_t resbuf[9] = {0x09, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x81};
	
	HostUartSend(resbuf, sizeof(resbuf));
}

static void ConfigureAction(void)
{
	
}

static void ConfigureConfirmAction(void)
{
	uint8_t resbuf[9] = {0x09, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x83};
	
	HostUartSend(resbuf, sizeof(resbuf));
}

static void UartReadAction(void)
{
	uint8_t resbuf[12] = {0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x31, 0x32, 0x33};
	
	HostUartSend(resbuf, sizeof(resbuf));
}

static void IO_Action(void)
{
	
}

static void InOutStatusAction(void)
{
	
}

static void NetLedStatusAction(void)
{
	
}

static void RunningLedStatusAction(void)
{
	
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
		}
		break;
	case DATA:
		ProStr.data[ProStr.dataLen++] = ch;
		len_temp--;
		if(len_temp == 0)
		{
			ProStr.step = HEAD_1;
			ProStr.paraDone = 1;
		}
		break;
	default:
		
		break;
	}
}