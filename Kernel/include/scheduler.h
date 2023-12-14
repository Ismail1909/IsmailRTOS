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
#include "kernel_cfg.h"

FIFO_Buf_t Ready_QUEUE ;

TCB* Ready_QUEUE_FIFO[MAX_NUM_OF_TASKS]; //Description + Macro.

TCB* schTable[MAX_NUM_OF_TASKS];

uint32_t* schedule_activeTasks;

void Schedule_update_Table(void);

TCB* Schedule_getNextTask(TCB* currTask);


#endif /* SCHEDULER_H_ */
