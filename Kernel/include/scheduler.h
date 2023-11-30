/********************************************************************************
 * @file           :  scheduler.h
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel Scheduler.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "fifo.h"

FIFO_Buf_t Ready_QUEUE ;

void update_ScheduleTable();

void sortTasks();


#endif /* SCHEDULER_H_ */
