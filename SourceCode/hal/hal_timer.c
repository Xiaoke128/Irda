#include "hal_timer.h"

static uint16_t ProTimerCount = 0;

void TimerInit(void)
{
	uint16_t PrescalerValue = 0;
	TIM_TimeBaseInitType TIM_TimeBaseStructure;
	
	NVIC_InitType NVIC_InitStructure;

    /* Enable the TIM2 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = LPTIM_TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
	/* PCLK1 = HCLK/4 */
    RCC_ConfigPclk1(RCC_HCLK_DIV1);

    /* TIM6 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
	/* Time base configuration */
    TIM_TimeBaseStructure.Period    = 47999;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM6, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_ConfigPrescaler(TIM6, PrescalerValue, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    /* TIM6 enable update irq */
    TIM_ConfigInt(TIM6, TIM_INT_UPDATE, ENABLE);

    /* TIM6 enable counter */
    TIM_Enable(TIM6, ENABLE);
}

/**
 * @brief  Configures tim3 clocks.
 */
void DelayTimerInit(void)
{
    /* Compute the prescaler value */
    uint16_t PrescalerValue = 0;
	TIM_TimeBaseInitType TIM_TimeBaseStructure;
	
	NVIC_InitType NVIC_InitStructure;

    /* Enable the TIM2 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM3 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 47;//1us
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_ConfigPrescaler(TIM3, PrescalerValue, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    /* TIM3 enable update irq */
    TIM_ConfigInt(TIM3, TIM_INT_UPDATE, ENABLE);

    /* TIM3 enable counter */
    //TIM_Enable(TIM3, ENABLE);
}

void ProTimerEnable(void)
{
	ProTimerCount = 0;
	SysFlagVal.bit.pro_timer_enable = 1;
}

void ProTimerDisable(void)
{
	SysFlagVal.bit.pro_timer_enable = 0;
}

/**
 * @brief  This function handles TIM3 global interrupt request.
 */
void TIM3_IRQHandler(void)
{
	uint32_t count = 0;
    if (TIM_GetIntStatus(TIM3, TIM_INT_UPDATE) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_UPDATE);
		if(SysFlagVal.bit.delay_enable)
		{
			count++;
			if(count >= delayCount)
			{
				SysFlagVal.bit.delay_enable = 0;
			}
		}
		else
		{
			count = 0;
		}
    }
}

/**
 * @brief  This function handles TIM6 global interrupt request.
 */
void LPTIM_TIM6_IRQHandler(void)
{
    if (TIM_GetIntStatus(TIM6, TIM_INT_UPDATE) != RESET)
    {
        TIM_ClrIntPendingBit(TIM6, TIM_INT_UPDATE);
		SysFlagVal.bit.sys_1ms = 1;
		if(SysFlagVal.bit.pro_timer_enable)
		{
			ProTimerCount++;
			if(ProTimerCount >= 300)
			{
				ProStr.step = HEAD_1;
				ProTimerCount = 0;
				ProTimerDisable();
			}
		}
    }
}