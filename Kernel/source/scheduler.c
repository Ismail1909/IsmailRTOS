/********************************************************************************
 * @file           :  scheduler.c
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel Scheduler.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#include"scheduler.h"

uint16_t shellSort(uint8_t* priority)
{
	uint32_t gap,i,j;
	uint32_t n = *schedule_activeTasks;
	uint16_t index;
	TCB* temp;

	//First Sort the table in ascending order according to priority.
	for(gap =n/2;gap>0;gap /=2)
	{
		for(i = gap;i<n;i++)
		{
			temp = schTable[i];

			for(j=i;(j>=gap) && (schTable[j-gap]->priority > temp->priority);j -=gap)
			{
				schTable[j] = schTable[j-gap];
			}
			schTable[j] = schTable[j-gap];
		}
	}

	// Loop over the sorted table and get the index of the highest priority ready task
	i=0;
	while(schTable[i]->TaskState != Ready && i < n)
	{
		i++;
	}
	/* No Ready Tasks */
	if(i==n)
	{
		return -1;
	}
	index = i;
	*priority = schTable[i]->priority;

	return index;
}

uint16_t bubbleSort(uint8_t* priority)
{
	uint32_t i,j;
	uint32_t n = *schedule_activeTasks;
	uint16_t index;
	TCB* temp;

	//First Sort the table in ascending order according to priority.
	for(i=0;i<n-1;i++)
	{
			for(j=0;j<n-i-1;j++)
			{
				if(schTable[j]->priority > schTable[j+1]->priority)
				{
					temp = schTable[j];
					schTable[j] = schTable[j+1];
					schTable[j+1] = temp;

				}

			}
	}

	// Loop over the sorted table and get the index of the highest priority ready task
	i=0;
	while(schTable[i]->TaskState != Ready && i < n)
	{
		i++;
	}
	/* No Ready Tasks */
	if(i==n)
	{
		return -1;
	}
	index = i;
	*priority = schTable[i]->priority;

	return index;
}

void Schedule_update_Table()
{
	uint8_t priority;
	uint16_t index;
	TCB* temp;
	int i;

	//sort(&highestpriority) returns index
	index = shellSort(&priority);

	// clear queue
	while(FIFO_dequeue(&Ready_QUEUE, &temp) != FIFO_EMPTY);

	// update queue

	/* No Active Tasks to queue */
	if(index == -1)
	{
		return;
	}

	i = index;
	while(schTable[i]->priority == priority)
	{
		if(schTable[i]->TaskState == Ready)
		{
			FIFO_enqueue(&Ready_QUEUE, schTable[i]);
		}
		i++;
	}

}

TCB* Schedule_getNextTask(TCB* currTask)
{
	TCB* nextTask = NULL;

	//No tasks in queue
	if(Ready_QUEUE.counter == 0)
	{
		return nextTask;
	}

	FIFO_dequeue(&Ready_QUEUE, &nextTask);
	// Same task is running already
	if(currTask == nextTask)
	{
		FIFO_enqueue(&Ready_QUEUE, nextTask);
		return nextTask;
	}

	if( (currTask->TaskState == Ready) && (currTask->priority == nextTask->priority))
	{
			FIFO_enqueue(&Ready_QUEUE, currTask);
			return nextTask;
	}

	return nextTask;
}




