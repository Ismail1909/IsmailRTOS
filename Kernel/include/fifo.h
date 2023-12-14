/********************************************************************************
 * @file           :  fifo.h
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel FIFO Data Structure for tasks.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#ifndef FIFO_H_
#define FIFO_H_

#include<stdint.h>
#include<stdlib.h>

typedef struct tcb
{
	unsigned int Stack_Size;
	void (*p_TaskEntry)(void); //pointer to Task C Function
	uint32_t _S_PSP_Task ;
	uint32_t _E_PSP_Task ;
	uint32_t* Current_PSP ;
	uint8_t priority;
	uint8_t AutoStart;
	uint8_t period;
	uint8_t TaskName[29] ;
	enum{
		Dormant,
		Ready,
		Running,
		Waiting,
		Suspended
	}TaskState	;//Not Entered by the user
struct{
		enum{
			Enable,
			Disable
		}Blocking;
		uint8_t Ticks_Count ;
	}TimingWaiting;

}TCB;

#define element_type TCB*

typedef struct{
	unsigned int counter;
	element_type* head;
	element_type* tail;
	element_type* base;
	unsigned int  length;
}FIFO_Buf_t;

typedef enum{
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL,

}Buffer_status;

/*APIs*/

Buffer_status FIFO_init (FIFO_Buf_t* fifo,element_type* buff , unsigned int length);
Buffer_status FIFO_enqueue (FIFO_Buf_t* fifo,element_type item);
Buffer_status FIFO_dequeue (FIFO_Buf_t* fifo,element_type* item);
Buffer_status FIFO_is_full (FIFO_Buf_t* fifo);
void FIFO_print (FIFO_Buf_t* fifo);


#endif /* FIFO_H_ */
