/********************************************************************************
 * @file           :  cortexmx_porting.c
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : ARM Cortex-M Porting layer based on CMSIS Core
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#include"cortexmx_porting.h"


__attribute__((naked)) void SVC_Handler(void)
{

	__asm("MRS R0, MSP  \n\t"
		"B SVC_Handler_C "
		);
}


int SVC_Handler_C(int* stackframe_ptr )
{
	uint8_t service_num = (uint8_t)(*(((uint8_t*)stackframe_ptr[6])-2)); /* Access the stacked PC address then decrement by 2 bytes to 
																		 get the constant with SVC instruction */
	switch (service_num)
	{
	case 1: //Add
		stackframe_ptr[3] = stackframe_ptr[1] + stackframe_ptr[2]; // R0 = R1+R2
		break;
	case 2: //Sub
		stackframe_ptr[3] = stackframe_ptr[1] - stackframe_ptr[2]; // R0 = R1-R2
	case 3: //Mul
		stackframe_ptr[3] = stackframe_ptr[1] * stackframe_ptr[2]; // R0 = R1*R2
		break;
	}																
}


