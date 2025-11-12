# STM32_Execution_Time
This library is used for measuring code execution time on STM32 MCUs using a hardware timer.
## Features ##
 + _Simple to use and integrate_
 + _Measurement accuracy of 1us_
 + _Calculates caller function overheads automatically_
 + _Fast and lightweight macro-based functions with minimum overhead_
 + _No 3rd-party external library needed_

## Limitations ##
 + Maximum execution time to measure is 65 ms and 535 us.
  - If the routine takes longer time than that, the timer overflows and measured execution time is wrong.
 + 1MHz hardware-timer dependent
 + Limited to STM32 MCUs
 + Uses HAL Library

## How to use?
 + Configure a hardware timer with 1MHz of clock using proper clock input scalers and set the period of timer to max 65535.
 + Call code_execution_timer_init(&htimX) before your super-loop and pass the related timer handler.
 + Put the block of code to be measured between code_execution_timer_start() and code_execution_timer_stop().
 + Access execution.ctr_ms and execution.ctr_us to see how much your tested block of code takes to run.
  - You can use code_execution_timer_print() to print the result if printf is explicitly directed to serial USART.
