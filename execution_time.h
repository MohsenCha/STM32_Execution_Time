/**************************************************************************//**
* @file 	execution_time.h
* @brief 	Code Execution Time Measurement header file
* @version 	V1.0
* @author 	M. Mohsen Chaghazardi

* This library is used for measuring code execution time on STM32 MCUs using a hardware timer.
* ## Features ##
* + _Simple to use and integrate_
* + _Measurement accuracy of 1us_
* + _Calculates caller function overheads automatically_
* + _Fast and lightweight macro-based functions with minimum overhead_
* + _No 3rd-party external library needed_
*
* ## Limitations ##
* + Maximum execution time to measure is 65 ms and 535 us.
* 	- If the routine takes longer time than that, the timer overflows and measured execution time is wrong.
* + 1MHz hardware-timer dependent
* + Limited to STM32 MCUs
* + Uses HAL Library
*
* ## How to use?
* + Configure a hardware timer with 1MHz of clock using proper clock input scalers and set the period of timer to max 65535.
* + Call code_execution_timer_init(&htimX) before your super-loop and pass the related timer handler.
* + Put the block of code to be measured between code_execution_timer_start() and code_execution_timer_stop().
* + Access execution.ctr_ms and execution.ctr_us to see how much your tested block of code takes to run.
* 	- You can use code_execution_timer_print() to print the result if printf is explicitly directed to serial USART.
 ******************************************************************************/

#ifndef EXECUTION_TIME_H_
#define EXECUTION_TIME_H_

#include "main.h"
#include <stdint.h>

/** @brief General Signals for Holding Code Execution duration */
typedef struct{
	uint16_t ctr_us;					///< Measured execution time in us
	uint16_t ctr_ms;					///< Measured execution time in ms
	uint8_t overhead_us;				///< Measured execution time overhead in us
    TIM_HandleTypeDef* TimerHandle;		///< Timer Handler
}execution_time_t;

extern execution_time_t execution;

/** @brief Clearing Execution Variables */
#define code_execution_timer_clear()	(execution.ctr_ms = execution.ctr_us = 0)

/** @brief Starts Code Execution Measurement */
#define code_execution_timer_start()do {			\
												__HAL_TIM_SET_COUNTER(execution.TimerHandle,0);	\
												 __HAL_TIM_ENABLE(execution.TimerHandle); 	\
									}while(0)
/** @brief Stops Code Execution Measurement */
#define code_execution_timer_stop()	do { 											\
												__HAL_TIM_DISABLE(execution.TimerHandle);	\
												uint16_t value_us = __HAL_TIM_GET_COUNTER( execution.TimerHandle);	\
												value_us -= execution.overhead_us;		\
												execution.ctr_ms = (value_us)/1000;	\
												execution.ctr_us = (value_us) % 1000;		\
									}while(0)
/** @brief Prints the result using printf */
#define code_execution_timer_print() do { 																											\
				printf("Execution Time = %d ms, %d us\r\n", \
               (int)execution.ctr_ms, \
               (int)execution.ctr_us); \
    } while (0)

/**
 * @brief Initialize Code Execution Library with Specific Hardware Timer
 * @param htim TimerHandler
 * @retval None
*/
void code_execution_timer_init(TIM_HandleTypeDef* htim);

#endif /* EXECUTION_TIME_H_ */
