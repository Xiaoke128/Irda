#include "protocol.h"

ProStruct ProStr;
static void ProtocolParse(uint8_t ch);


void ComTask(void)
{
	uint8_t ch = 0;
	
	if(HostCheck())
		{
			ch = HostGetData();
			//HostUartSend(&ch, 1);
			ProtocolParse(ch);
		}
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
		ProStr.comLen <<= 8;
		ProStr.step = LEN_HL;
		break;
	case LEN_HL:
		ProStr.comLen += ch;
		ProStr.comLen <<= 8;
		ProStr.step = LEN_LH;
		break;
	case LEN_LH:
		ProStr.comLen += ch;
		ProStr.comLen <<= 8;
		ProStr.step = LEN_LL;
		break;
	case LEN_LL:
		ProStr.comLen += ch;
		len_temp = ProStr.comLen - 11;
		ProStr.step = DATA;
		break;
	case DATA:
		if(len_temp > 0)
		{
			ProStr.data[ProStr.dataLen++] = ch;
			len_temp--;
			if(len_temp == 0)
			{
				ProStr.step = HEAD_1;
			}
		}
		else
		{
			ProStr.step = HEAD_1;
		}
		break;
	default:
		
		break;
	}
}