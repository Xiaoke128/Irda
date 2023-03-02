#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include "n32g030.h"
#include "init.h"

extern volatile uint32_t delayCount;
void TimerInit(void);
void DelayTimerInit(void);
void ProTimerEnable(void);
void ProTimerDisable(void);

#endif