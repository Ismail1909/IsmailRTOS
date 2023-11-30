/********************************************************************************
 * @file           :  timer.h
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel Timer Management.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

void SystickTimer_init();

void update_WaitingTime();

void handleTick();



#endif /* TIMER_H_ */
