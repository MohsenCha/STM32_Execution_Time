/**************************************************************************//**
* @file 	execution_time.c
* @brief 	Code Execution Time Measurement source file
* @date		Aug 12, 2025
* @author 	M. Mohsen Chaghazardi
 ******************************************************************************/
#include "../App/execution_time.h"

/** @brief Execution Timer Signals Instance*/
execution_time_t execution = {0};


inline void code_execution_timer_init(TIM_HandleTypeDef* htim)
{
    execution.TimerHandle = htim;
    code_execution_timer_clear();
    code_execution_timer_start();
    __HAL_TIM_DISABLE(execution.TimerHandle);
    execution.overhead_us = __HAL_TIM_GET_COUNTER(execution.TimerHandle);

}
