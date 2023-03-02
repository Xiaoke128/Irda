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
 * @file main.c
 * @author ..\readme.txt
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, ..\readme.txt Technologies Inc. All rights reserved.
 */
#include <stdio.h>
#include "main.h"
#include "init.h"
#include "hal_gpio.h"

ErrorStatus HSEStartUpStatus;
ErrorStatus HSIStartUpStatus;

#define SYSCLK_USE_HSI     0
#define SYSCLK_USE_HSE     1
#define SYSCLK_USE_HSI_PLL 2
#define SYSCLK_USE_HSE_PLL 3
#define SYSCLK_USE_LSE     4
#define SYSCLK_USE_LSI     5

/** @addtogroup N32G030_StdPeriph_Examples
 * @{
 */

/**
 * @brief  Selects PLL clock as System clock source and configure HCLK, PCLK2
 *         and PCLK1 prescalers.
* @note FIN/N must be set in 4MHz to 20MHz.
 *       FIN/N*M must be set in 48MHz to 72MHz
 */
void SetSysClockToPLL(uint32_t freq, uint8_t src)
{
    uint32_t pllmul;
    uint32_t plldiv = RCC_PLLOUT_DIV_1;
    uint32_t latency;
    uint32_t pclk1div, pclk2div;

    if ((src == SYSCLK_USE_HSE)&&(HSE_VALUE != 8000000))
    {
        /* HSE_VALUE == 8000000 is needed in this project! */
        while (1);
    }

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration
     * -----------------------------*/
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    if (src == SYSCLK_USE_HSI) 
    {
        /* Enable HSI */
        RCC_ConfigHsi(RCC_HSI_ENABLE);

        /* Wait till HSI is ready */
        HSIStartUpStatus = RCC_WaitHsiStable();

        if (HSIStartUpStatus != SUCCESS)
        {
            /* If HSI fails to start-up, the application will have wrong clock
               configuration. User can add here some code to deal with this
               error */

            /* Go to infinite loop */
            while (1);
        }

    }
    else if (src == SYSCLK_USE_HSE) 
    {
        /* Enable HSE */
        RCC_ConfigHse(RCC_HSE_ENABLE);

        /* Wait till HSE is ready */
        HSEStartUpStatus = RCC_WaitHseStable();

        if (HSEStartUpStatus != SUCCESS)
        {
            /* If HSE fails to start-up, the application will have wrong clock
               configuration. User can add here some code to deal with this
               error */

            /* Go to infinite loop */
            while (1);
        }

    }

    switch (freq)
    {
        case 32000000:
            latency  = FLASH_LATENCY_1;
            pllmul = RCC_PLL_MUL_16;
            pclk1div = RCC_HCLK_DIV2;
            pclk2div = RCC_HCLK_DIV1;
            plldiv = RCC_PLLOUT_DIV_2;
            break;
        case 48000000:
            latency  = FLASH_LATENCY_2;
		    pllmul = RCC_PLL_MUL_12;
            pclk1div = RCC_HCLK_DIV2;
            pclk2div = RCC_HCLK_DIV1;
		    plldiv = RCC_PLLOUT_DIV_1;
            break;
        default:
            while (1);
    }

    FLASH_SetLatency(latency);

    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);

    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(pclk2div);

    /* PCLK1 = HCLK */
    RCC_ConfigPclk1(pclk1div);
    if(src == SYSCLK_USE_HSE)
    {
        RCC_ConfigPll(RCC_PLL_SRC_HSE,pllmul, RCC_PLL_PRE_2, plldiv);
    }
    else
    {
        RCC_ConfigPll(RCC_PLL_SRC_HSI,pllmul, RCC_PLL_PRE_2, plldiv);
    }

    /* Enable PLL */
    RCC_EnablePll(ENABLE);

    /* Wait till PLL is ready */
   // while (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) == RESET);
     /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
    }
    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL);
}

/**
 * @brief  Main program
 */
int main(void)
{
	SetSysClockToPLL(48000000, SYSCLK_USE_HSI);
	MCU_Init();
    while (1)
    {
		ledTest();
		ComTask();
    }
}


