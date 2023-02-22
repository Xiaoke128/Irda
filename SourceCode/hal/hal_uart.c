#include <stdio.h>
#include "hal_uart.h"

static uint8_t HostHead = 0;
static uint8_t HostTail = 0;
static uint8_t HostCount = 0;
static uint8_t HostBuff[HOST_BUFFER_SIZE] = {0};

static uint8_t DebugHead = 0;
static uint8_t DebugTail = 0;
static uint8_t DebugCount = 0;
static uint8_t DebugBuff[DEBUG_BUFFER_SIZE] = {0};

void HostUartInit(void)
{
	GPIO_InitType GPIO_InitStructure;
	USART_InitType USART_InitStructure;
	NVIC_InitType NVIC_InitStructure;
	
	/* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = HOST_UART_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure); 
	USART_StructInit(&USART_InitStructure);
	RCC_EnableAPB2PeriphClk(HOST_UART_GPIO_CLK | HOST_UART_CLK, ENABLE);
	//RCC_EnableAPB1PeriphClk(HOST_UART_CLK, ENABLE);
	
	/* Configure USARTx Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = HOST_TX_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = HOST_TX_GPIO_AF;
    GPIO_InitPeripheral(HOST_GPIO_PORT, &GPIO_InitStructure);    

    /* Configure USARTx Rx as alternate function push-pull */
    GPIO_InitStructure.Pin            = HOST_RX_PIN;
    GPIO_InitStructure.GPIO_Alternate = HOST_RX_GPIO_AF;
    GPIO_InitPeripheral(HOST_GPIO_PORT, &GPIO_InitStructure); 
	
	USART_InitStructure.BaudRate            = HOST_UART_BAUD_RATE;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
	
    USART_Init(HOST_UART, &USART_InitStructure);
	USART_ConfigInt(HOST_UART, USART_INT_RXDNE, ENABLE);
    USART_Enable(HOST_UART, ENABLE);
}

void DebugUartInit(void)
{
	GPIO_InitType GPIO_InitStructure;
	USART_InitType USART_InitStructure;
	NVIC_InitType NVIC_InitStructure;
	
	/* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = DEBUG_UART_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	/* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure); 
	USART_StructInit(&USART_InitStructure);
	RCC_EnableAPB2PeriphClk(DEBUG_UART_GPIO_CLK, ENABLE);
	RCC_EnableAPB1PeriphClk(DEBUG_UART_CLK, ENABLE);

	/* Configure USARTx Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = DEBUG_TX_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = DEBUG_TX_GPIO_AF;
    GPIO_InitPeripheral(DEBUG_GPIO_PORT, &GPIO_InitStructure);    

    /* Configure USARTx Rx as alternate function push-pull */
    GPIO_InitStructure.Pin            = DEBUG_RX_PIN;
    GPIO_InitStructure.GPIO_Alternate = DEBUG_RX_GPIO_AF;
    GPIO_InitPeripheral(DEBUG_GPIO_PORT, &GPIO_InitStructure); 
	
	USART_InitStructure.BaudRate            = DEBUG_UART_DEFAULT_BAUD_RATE;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
	
    USART_Init(DEBUG_UART, &USART_InitStructure);
	USART_ConfigInt(DEBUG_UART, USART_INT_RXDNE, ENABLE);
    USART_Enable(DEBUG_UART, ENABLE);
}


//host receive data, add to a fifo
static void HostAdd(uint8_t data)
{
	USART_ConfigInt(HOST_UART, USART_INT_RXDNE, DISABLE);
	HostCount++;
	USART_ConfigInt(HOST_UART, USART_INT_RXDNE, ENABLE);
	HostBuff[HostTail++] = data;
	if(HostTail == HOST_BUFFER_SIZE)
	{
		HostTail = 0;
	}
}
//check fifo, whether have data not get out
uint8_t HostCheck(void)
{
	if(HostCount > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//get a character from fifo
uint8_t HostGetData(void)
{
	uint8_t data = 0;
	
	if(HostCount > 0)
	{
		data = HostBuff[HostHead++];
		if(HostHead == HOST_BUFFER_SIZE)
		{
			HostHead = 0;
		}
		USART_ConfigInt(HOST_UART, USART_INT_RXDNE, DISABLE);
		HostCount--;
		USART_ConfigInt(HOST_UART, USART_INT_RXDNE, ENABLE);
	}
	return data;
}

void HOST_UART_IR_HANDLE(void)
{
	uint8_t ch = 0;
	
	if (USART_GetIntStatus(HOST_UART, USART_INT_RXDNE) != RESET)
	{
		ch = USART_ReceiveData(HOST_UART);
		HostAdd(ch);
	}
}

void HostUartSend(uint8_t *buf, uint8_t len)
{
	uint8_t i = 0;
	
	for(i = 0; i < len; i++)
	{
		USART_SendData(HOST_UART, buf[i]);
		while (USART_GetFlagStatus(HOST_UART, USART_FLAG_TXDE) == RESET);
	}
}

//host receive data, add to a fifo
static void DebugAdd(uint8_t data)
{
	USART_ConfigInt(DEBUG_UART, USART_INT_RXDNE, DISABLE);
	DebugCount++;
	USART_ConfigInt(DEBUG_UART, USART_INT_RXDNE, ENABLE);
	DebugBuff[DebugTail++] = data;
	if(DebugTail == DEBUG_BUFFER_SIZE)
	{
		DebugTail = 0;
	}
}
//check fifo, whether have data not get out
uint8_t DebugCheck(void)
{
	if(DebugCount > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//get a character from fifo
uint8_t DebugGetData(void)
{
	uint8_t data = 0;
	
	if(DebugCount > 0)
	{
		data = DebugBuff[DebugHead++];
		if(DebugHead == DEBUG_BUFFER_SIZE)
		{
			DebugHead = 0;
		}
		USART_ConfigInt(DEBUG_UART, USART_INT_RXDNE, DISABLE);
		DebugCount--;
		USART_ConfigInt(DEBUG_UART, USART_INT_RXDNE, ENABLE);
	}
	return data;
}

void DEBUG_UART_IR_HANDLE(void)
{
	uint8_t ch = 0;
	
	if (USART_GetIntStatus(DEBUG_UART, USART_INT_RXDNE) != RESET)
	{
		ch = USART_ReceiveData(DEBUG_UART);
		DebugAdd(ch);
	}
}

void DebugUartSend(uint8_t *buf, uint8_t len)
{
	uint8_t i = 0;
	
	for(i = 0; i < len; i++)
	{
		USART_SendData(DEBUG_UART, buf[i]);
		while (USART_GetFlagStatus(DEBUG_UART, USART_FLAG_TXDE) == RESET);
	}
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE* f)
{
    USART_SendData(HOST_UART, (uint8_t)ch);
    while (USART_GetFlagStatus(HOST_UART, USART_FLAG_TXDE) == RESET);

    return (ch);
}