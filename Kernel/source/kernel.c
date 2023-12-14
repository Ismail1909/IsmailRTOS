/********************************************************************************
 * @file           :  kernel.c
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : RTOS Kernel Main.
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/




#include"kernel.h"
#include"fifo.h"
#include"kernel_cfg.h"
#include"timer.h"
#include"scheduler.h"
#include"debug.h"

#define MIN_STACK_SIZE 100
#define MIN_PRIORITY 255


typedef enum
{
	SVC_ActivateTask,
	SVC_TerminateTask,
	SVC_SuspendTask,
	SVC_DelayTask,


}SVC_ID;


 typedef struct kernel {
	TCB Tasks[MAX_NUM_OF_TASKS];
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

Kernel_Control kernel;

TCB* idleTask = &kernel.Tasks[0];

void HW_init()
{
	//Set PendSV priority to be < Systick Priority
}

void Kernel_Create_TaskStack(TCB* task)
{
	/* Task Frame:
	 * xPSR
	 * PC
	 * LR
	 * R12
	 * R3
	 * R2
	 * R1
	 * R0
	 * The following must be saved manually during context switching
	 * R11
	 * R10
	 * R9
	 * R8
	 * R7
	 * R6
	 * R5
	 * R4
	 */
	task->Current_PSP = task->_S_PSP_Task;

	task->Current_PSP--;
	*(task->Current_PSP) = 0x01000000; //DUMMY_XPSR should T =1 to avoid BUS fault

	task->Current_PSP--;
	*(task->Current_PSP) = ((uint32_t)task->p_TaskEntry);

	task->Current_PSP--;
	*(task->Current_PSP) = 0xFFFFFFFD; //Thread Mode, PSP;


	for(uint8_t i=0;i<13;i++)
	{
		task->Current_PSP--;
		*(task->Current_PSP) = 0;
	}

}

void Kernel_Create_MainStack()
{
	//Set start of main stack
	kernel._S_MSP_Task = ((uint32_t)(&__StackTop));

	//Set main stack size and end of the stack.
	kernel._E_MSP_Task = (kernel._S_MSP_Task - MAIN_STACK_SIZE);

#ifdef DEBUG
	//Check if the stack doesn't exceed heap end.
	assert(kernel._E_MSP_Task > ((uint32_t)(&__HeapLimit)));
#endif

	//Align 8 bytes between main stack frame and first task frame.
	kernel.PSP_Task_Locator = (kernel._E_MSP_Task - 0x08);

}

__attribute__((weak)) void Kernel_IdleTask(void)
{
	for(;;)
	{
		//make the processor go to low power mode.
	}

}

RTOS_errorID RTOS_init()
{
	RTOS_errorID error = NoError ;

	// Init Kernel mode to Suspend.
	kernel.OSmodeID = OSsuspend;

	kernel.NoOfActiveTasks =0;

	//Create Kernel Main Stack
	Kernel_Create_MainStack();

	//Perform necessary HW INITS

	//Init Ready Queue fifo.

	if(FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) != FIFO_NO_ERROR)
	{
		error += Ready_Queue_init_error;
	}


	//Kernel Idle Task Configurations
	idleTask->Stack_Size = MIN_STACK_SIZE;

	idleTask->p_TaskEntry = Kernel_IdleTask;

	idleTask->priority = MIN_PRIORITY;

	idleTask->period = 1; //best period for idle task?


	//Create Kernel Idle Task.
	idleTask->_S_PSP_Task = kernel.PSP_Task_Locator;

	idleTask->_E_PSP_Task = (idleTask->_S_PSP_Task - idleTask->Stack_Size);

#ifdef DEBUG
	assert(idleTask->_E_PSP_Task > ((uint32_t)(&__HeapLimit)));
#endif


	//Create Task Stack
	Kernel_Create_TaskStack(idleTask);


	//Aligned 8 Bytes spaces between Task PSP and other
	kernel.PSP_Task_Locator = idleTask->_E_PSP_Task - 0x08;

	//Put the idle task in the schedule table.
	schedule_activeTasks = kernel.NoOfActiveTasks;
	schTable[kernel.NoOfActiveTasks] = idleTask;
	kernel.NoOfActiveTasks++;


	idleTask->TaskState = Dormant;

	return error;
}

RTOS_errorID RTOS_CreateTask(void(*taskFunction)(void), uint8_t size, uint8_t priority, uint8_t period, char* taskName, TaskHandle handle)
{


	if(kernel.NoOfActiveTasks ==MAX_NUM_OF_TASKS)
	{
		return Max_num_of_tasks_exceeded;
	}

	// Set provided function parameters
	kernel.Tasks[kernel.NoOfActiveTasks].TaskState = Dormant;

	kernel.Tasks[kernel.NoOfActiveTasks].priority = priority;

	kernel.Tasks[kernel.NoOfActiveTasks].period = period;

	kernel.Tasks[kernel.NoOfActiveTasks].p_TaskEntry = taskFunction;

	// Set task stack size
	kernel.Tasks[kernel.NoOfActiveTasks]._S_PSP_Task = kernel.PSP_Task_Locator;

	kernel.Tasks[kernel.NoOfActiveTasks]._E_PSP_Task = (kernel.Tasks[kernel.NoOfActiveTasks]._S_PSP_Task - size);

	// Check if task stack doesn't exceed heap
#ifdef DEBUG
	assert(kernel.Tasks[kernel.NoOfActiveTasks]._E_PSP_Task > ((uint32_t)(&__HeapLimit)));
#endif

	// Aligned 8 Bytes spaces between Task PSP and other
	kernel.PSP_Task_Locator = kernel.Tasks[kernel.NoOfActiveTasks]._E_PSP_Task - 8;

	// Create task stack content
	Kernel_Create_TaskStack(&kernel.Tasks[kernel.NoOfActiveTasks]);

	// Set Task Handle to be used by the user.
	handle = (uint32_t*)(&kernel.Tasks[kernel.NoOfActiveTasks]);

	//Add task to Schedule Table
	schTable[kernel.NoOfActiveTasks] = &kernel.Tasks[kernel.NoOfActiveTasks];

	// Increment number of tasks.
	kernel.NoOfActiveTasks++;


	return NoError;

}


void Kernel_callSVC( const SVC_ID serviceID)
{

	switch(serviceID)
	{
		case SVC_ActivateTask:
			_cortex_svc(SVC_ActivateTask);
			break;
		case SVC_TerminateTask:
			_cortex_svc(SVC_TerminateTask);
			break;
		case SVC_DelayTask:
			_cortex_svc(SVC_DelayTask);
			break;
		case SVC_SuspendTask:
			_cortex_svc(SVC_SuspendTask);
			break;
		default:
			break;
		//Handle the error of calling wrong id
	}

}

void Kernel_SVC_Handler(uint32_t* taskFrame)
{
	SVC_ID serviceID = (SVC_ID)(*(((uint8_t*)taskFrame[6])-2));

	switch(serviceID)
	{
		case SVC_ActivateTask:
		case SVC_TerminateTask:
			// update Sch Table
			// update Ready queue
			Schedule_update_Table();

			// if OS is running
			if(kernel.OSmodeID == Running)
			{
				// Decide Next Task
				kernel.NextTask = Schedule_getNextTask(kernel.CurrentTask);
				kernel.NextTask->TaskState = Running;
				// trigger pendSV
				_cortex_triggerPENDSV();
			}
			break;
		case SVC_DelayTask:
			_cortex_svc(SVC_DelayTask);
			break;
		case SVC_SuspendTask:
			_cortex_svc(SVC_SuspendTask);
			break;
		default:
			break;
		//Handle the error of calling wrong id
	}

}

void RTOS_ActivateTask (TaskHandle handle)
{
	TCB* task = (TCB*)(handle);

	kernel.CurrentTask->TaskState = Ready;

	task->TaskState = Ready;

	Kernel_callSVC(SVC_ActivateTask);
}

void RTOS_TerminateTask (TaskHandle handle)
{
	TCB* task = (TCB*)(handle);

	kernel.CurrentTask->TaskState = Ready;

	task->TaskState = Dormant;

	Kernel_callSVC(SVC_TerminateTask);

}

__attribute__((naked)) void PendSV_Handler(void)
{
	//SAVE_CONTEXT
	kernel.CurrentTask->Current_PSP = (uint32_t*)_cortex_getPSP();

	_cortex_Save_Context(kernel.CurrentTask->Current_PSP);

	//RESTORE_CONTEXT
	if(kernel.NextTask != NULL)
	{
		kernel.CurrentTask = kernel.NextTask;
	}

	_cortex_Restore_Context(kernel.CurrentTask->Current_PSP);

	// Set PSP to Current Task PSP
	_cortex_setPSP(kernel.CurrentTask->Current_PSP);

}

void RTOS_startOS()
{
	//Set OS Mode to Running
	kernel.OSmodeID = Running;
	//Activate Idle Task
	RTOS_ActivateTask(idleTask);

	SystickTimer_init(1);

	//Change to psp
	_cortex_switch_to_psp();

	//Change to unprivileged
	_cortex_setUnPrivileged();

	//Call Current Task Fun
	kernel.CurrentTask->p_TaskEntry;
}



