/********************************************************************************
 * @file           :  kernel.c
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel Main.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/



#include"kernel.h"
#include"timer.h"
#include"fifo.h"
#include"scheduler.h"


 typedef struct kernel {
	//Task_ref* OSTasks[100]; //Sch. Table
	uint32_t _S_MSP_Task ;
	uint32_t _E_MSP_Task ;
	uint32_t PSP_Task_Locator ;
	uint32_t NoOfActiveTasks ;
	TCB* CurrentTask ;
	TCB* NextTask ;
	enum{
		OSsuspend,
		OsRunning
	}OSmodeID;
}Kernel_Control;


void Kernel_callSVC( const uint8_t SVCID)
{

}

__attribute__((weak)) void IdleTask(void)
{

}


