#ifndef __tim_h
#define __tim_h

#include "main.h"


void tim6_init(uint16_t period,uint16_t prescaler);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef * htim);
void TIM6_DAC1_IRQHandler(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim);
#endif 
