#ifndef HAL_UART_H
#define HAL_UART_H

#include "n32g030.h"

#define HOST_BUFFER_SIZE				255
#define DEBUG_BUFFER_SIZE				255

#define HOST_UART						USART1
#define HOST_UART_CLK          			RCC_APB2_PERIPH_USART1
#define HOST_GPIO_PORT	         		GPIOA
#define HOST_UART_GPIO_CLK     			RCC_APB2_PERIPH_GPIOA
#define HOST_RX_PIN        				GPIO_PIN_3
#define HOST_TX_PIN        				GPIO_PIN_2
#define HOST_RX_GPIO_AF   				GPIO_AF1_USART1
#define HOST_TX_GPIO_AF   				GPIO_AF1_USART1

#define HOST_UART_IRQN					USART1_IRQn
#define HOST_UART_IR_HANDLE				USART1_IRQHandler

#define DEBUG_UART						USART2
#define DEBUG_UART_CLK          		RCC_APB1_PERIPH_USART2
#define DEBUG_GPIO_PORT	         		GPIOA
#define DEBUG_UART_GPIO_CLK     		RCC_APB2_PERIPH_GPIOA
#define DEBUG_RX_PIN        			GPIO_PIN_10
#define DEBUG_TX_PIN        			GPIO_PIN_9
#define DEBUG_RX_GPIO_AF   				GPIO_AF10_USART2
#define DEBUG_TX_GPIO_AF   				GPIO_AF10_USART2

#define DEBUG_UART_IRQN					USART2_IRQn
#define DEBUG_UART_IR_HANDLE			USART2_IRQHandler

#define HOST_UART_BAUD_RATE				115200
#define DEBUG_UART_DEFAULT_BAUD_RATE	115200
//#define GPIO_APBxClkCmd     RCC_EnableAPB2PeriphClk
//#define USART_APBxClkCmd    RCC_EnableAPB1PeriphClk


void HostUartInit(void);
void DebugUartInit(void);
void DebugUartReInit(void);
uint8_t HostCheck(void);
uint8_t HostGetData(void);
void HostUartSend(uint8_t *buf, uint8_t len);
uint8_t DebugCheck(void);
uint8_t DebugGetData(void);
void DebugUartSend(uint8_t *buf, uint8_t len);
#endif