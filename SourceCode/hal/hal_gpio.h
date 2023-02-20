#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "n32g030.h"
#include "init.h"

#define LED_PORT_CLK			RCC_APB2_PERIPH_GPIOA
#define IO_PORT_CLK				RCC_APB2_PERIPH_GPIOF
#define RELAY_PORT_CLK			RCC_APB2_PERIPH_GPIOB

#define LED_KEY_PORT           	GPIOA
#define LED0_PIN                GPIO_PIN_7
#define LED1_PIN                GPIO_PIN_6
#define LED2_PIN                GPIO_PIN_10
#define LED3_PIN                GPIO_PIN_9
#define KEY_PIN					GPIO_PIN_0

#define IO12_PORT				GPIOF
#define IO34_PORT				GPIOA
#define IO1_PIN					GPIO_PIN_0
#define IO2_PIN					GPIO_PIN_1
#define IO3_PIN					GPIO_PIN_5
#define IO4_PIN					GPIO_PIN_4

#define RELAY_PORT				GPIOB
#define RELAY_PIN				GPIO_PIN_1

#define LED0_ON                 GPIO_SetBits(LED_KEY_PORT, LED0_PIN)
#define LED0_OFF                GPIO_ResetBits(LED_KEY_PORT, LED0_PIN)

#define LED1_ON                 GPIO_SetBits(LED_KEY_PORT, LED1_PIN)
#define LED1_OFF                GPIO_ResetBits(LED_KEY_PORT, LED1_PIN)

#define LED2_ON                 GPIO_SetBits(LED_KEY_PORT, LED2_PIN)
#define LED2_OFF                GPIO_ResetBits(LED_KEY_PORT, LED2_PIN)

#define LED3_ON                 GPIO_SetBits(LED_KEY_PORT, LED3_PIN)
#define LED3_OFF                GPIO_ResetBits(LED_KEY_PORT, LED3_PIN)

#define READ_KEY_VAL			GPIO_ReadInputDataBit(LED_KEY_PORT, KEY_PIN)


typedef enum{
	IO_OUTPUT,
	IO_INPUT,
}IoDir;

typedef enum{
	IO_CHANNEL_1,
	IO_CHANNEL_2,
	IO_CHANNEL_3,
	IO_CHANNEL_4,
}IoCh;

void GpioInit(void);
void IoDirSet(IoCh channel, IoDir dir);
void IoOutputLevel(IoCh channel, Bit_OperateType level);
uint8_t IoReadLevel(IoCh channel);
void ledTest(void);
#endif

