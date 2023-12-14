/********************************************************************************
 * @file           :  kernel.h
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel Main.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#ifndef KERNEL_H_
#define KERNEL_H_

#include"cortexmx_porting.h"


typedef uint32_t* TaskHandle;

#define TaskFunction void(*f_ptr)(void)

typedef enum {
	NoError,
	Ready_Queue_init_error,
	Task_exceeded_StackSize,
	Max_num_of_tasks_exceeded,
	MutexisReacedToMaxNumberOfUsers

}RTOS_errorID;

// User APIs
RTOS_errorID RTOS_init();

RTOS_errorID RTOS_CreateTask(void(*taskFunction)(void) , uint8_t size, uint8_t priority, uint8_t period, char* taskName, TaskHandle handle);

void RTOS_ActivateTask (TaskHandle handle);

void RTOS_TerminateTask (TaskHandle handle);

void RTOS_SuspendTask(TaskHandle handle);

void RTOS_ResumeTask(TaskHandle handle);

void RTOS_DelayTask(TaskHandle handle, uint16_t msTime);

void RTOS_startOS();



#endif /* KERNEL_H_ */
