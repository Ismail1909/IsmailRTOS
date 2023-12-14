/********************************************************************************
 * @file           :  app.c
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : Main User Application
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#include"kernel.h"

TaskHandle task1_, task2_, task3_;

void task1(void)
{
	for(;;)
	{

	}
}

void task2(void)
{
	for(;;)
	{

	}
}

void task3(void)
{
	for(;;)
	{

	}
}

int main()
{
	RTOS_errorID error = NoError;
	if(RTOS_init() != NoError)
	{
		while(1){}
	}

	error += RTOS_CreateTask(task1, 100, 1, 20, "Task1", task1_);
	error += RTOS_CreateTask(task2, 100, 1, 20, "Task2", task2_);
	error += RTOS_CreateTask(task3, 100, 1, 20, "Task3", task3_);

	while(1)
	{

	}
    return 0;
}
