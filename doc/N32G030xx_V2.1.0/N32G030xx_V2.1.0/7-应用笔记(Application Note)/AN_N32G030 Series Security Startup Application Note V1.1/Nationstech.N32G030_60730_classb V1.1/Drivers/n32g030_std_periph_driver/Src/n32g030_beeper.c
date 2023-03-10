/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g030_beeper.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g030_beeper.h"

/** @addtogroup N32G030_StdPeriph_Driver
 * @{
 */

/** @addtogroup BEEPER
 * @brief BEEPER driver modules
 * @{
 */

/** @addtogroup BEEPER_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup BEEPER_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @addtogroup BEEPER_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup BEEPER_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup BEEPER_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup BEEPER_Private_Functions
 * @{
 */

/**
 * @brief  Initializes the BEEPER peripheral.
 * @param  buzzer_clksel
 */
void BEEPER_Init(uint32_t inv_en, uint32_t buzzer_clksel)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_BEEPER_INV_EN(inv_en));
    assert_param(IS_BEEPER_BUZZER_CLKSEL(buzzer_clksel));

    /* Set Buzzer inverter */
    tmpregister |= inv_en;
    /* Buzzer output clock select */
    tmpregister |= buzzer_clksel;
    /* Store the new value */
    BEEPER->CTRL = tmpregister;
}

/**
 * @brief  Enables or disables the specified BEEPER peripheral.
 * @param  Cmd new state of the BEEPER peripheral.
 *         This parameter can be: ENABLE or DISABLE.
 */
void BEEPER_Config(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable BEEPER */
        BEEPER->CTRL |= BEEPER_BUZZER_BUZZER_ENABLE;
    }
    else
    {
        /* Disable BEEPER */
        BEEPER->CTRL &= (~BEEPER_BUZZER_BUZZER_ENABLE);
    }
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
