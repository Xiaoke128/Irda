/*****************************************************************************
 * Copyright (c) 2019, ..\readme.txt Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * ..\readme.txt' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ..\readme.txt "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ..\readme.txt BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file bsp_led.h
 * @author ..\readme.txt
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, ..\readme.txt Technologies Inc. All rights reserved.
 */
#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "n32g030.h"

//************************************************************************************//
/* Define the LED that is connected GPIO*/
// R-RED
#define LED1_GPIO_PORT GPIOB
#define LED1_GPIO_CLK  RCC_APB2_PERIPH_GPIOB
#define LED1_GPIO_PIN  GPIO_PIN_1
// G-GREEN
#define LED2_GPIO_PORT GPIOB
#define LED2_GPIO_CLK  RCC_APB2_PERIPH_GPIOB
#define LED2_GPIO_PIN  GPIO_PIN_6
// B-BLUE
#define LED3_GPIO_PORT GPIOB
#define LED3_GPIO_CLK  RCC_APB2_PERIPH_GPIOB
#define LED3_GPIO_PIN  GPIO_PIN_7

#define digitalHi(p, i)                                                                                                \
    {                                                                                                                  \
        p->PBSC = i;                                                                                                   \
    } // output high
#define digitalLo(p, i)                                                                                                \
    {                                                                                                                  \
        p->PBC = i;                                                                                                    \
    } // output low
#define digitalToggle(p, i)                                                                                            \
    {                                                                                                                  \
        p->POD ^= i;                                                                                                   \
    } // toggle

#define LED1_RED_TOGGLE digitalToggle(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_RED_OFF    digitalHi(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_RED_ON     digitalLo(LED1_GPIO_PORT, LED1_GPIO_PIN)

#define LED2_BLUE_TOGGLE digitalToggle(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED2_BLUE_OFF    digitalHi(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED2_BLUE_ON     digitalLo(LED2_GPIO_PORT, LED2_GPIO_PIN)

#define LED3_GREEN_TOGGLE digitalToggle(LED3_GPIO_PORT, LED3_GPIO_PIN)
#define LED3_GREEN_OFF    digitalHi(LED3_GPIO_PORT, LED3_GPIO_PIN)
#define LED3_GREEN_ON     digitalLo(LED3_GPIO_PORT, LED3_GPIO_PIN)

void LED_GPIO_Config(void);

#endif /* __BSP_LED_H__ */
