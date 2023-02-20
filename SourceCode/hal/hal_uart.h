#ifndef HAL_UART_H
#define HAL_UART_H

#include "n32g030.h"

#define HOST_BUFFER_SIZE				255

#define HOST_UART						USART2
#define HOST_UART_CLK          			RCC_APB1_PERIPH_USART2
#define HOST_GPIO_PORT	         		GPIOA
#define HOST_UART_GPIO_CLK     			RCC_APB2_PERIPH_GPIOA
#define HOST_RX_PIN        				GPIO_PIN_3
#define HOST_TX_PIN        				GPIO_PIN_2
#define HOST_RX_GPIO_AF   				GPIO_AF4_USART2
#define HOST_TX_GPIO_AF   				GPIO_AF4_USART2

#define HOST_UART_IRQN					USART2_IRQn
#define HOST_UART_IR_HANDLE				USART2_IRQHandler

#define HOST_UART_BAUD_RATE				115200
//#define GPIO_APBxClkCmd     RCC_EnableAPB2PeriphClk
//#define USART_APBxClkCmd    RCC_EnableAPB1PeriphClk


void HostUartInit(void);
uint8_t HostCheck(void);
uint8_t HostGetData(void);
void HostUartSend(uint8_t *buf, uint8_t len);
#endif