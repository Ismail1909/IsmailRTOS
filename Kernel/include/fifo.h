/********************************************************************************
 * @file           :  fifo.h
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel FIFO Data Structure for tasks.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

/*
 * fifo.h
 *
 *  Created on: Nov 26, 2023
 *
 *  Author:
 */

#ifndef FIFO_H_
#define FIFO_H_

typedef struct tcb
{
	unsigned int Stack_Size;
	void (*p_TaskEntry)(void); //pointer to Task C Function
	unsigned int _S_PSP_Task ;
	unsigned int _E_PSP_Task ;
	unsigned int* Current_PSP ;
	unsigned char priority;
	unsigned char AutoStart;
	unsigned char period;
	unsigned char TaskName[29] ;
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
		unsigned int Ticks_Count ;
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
