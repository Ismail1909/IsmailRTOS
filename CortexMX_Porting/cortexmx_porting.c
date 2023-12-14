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

#if(defined(ARMCM0) || defined(ARMCM0plus))

	__asm volatile("TST LR, #0X04  \n\t" // test if the bit 2 of LR is set by bitwise AND
				   "BNE psp \n\t" // if the bit is not set, Z flag is raised else the Z flag is not raised.
		           "MRSEQ R0, MSP \n\t" //Load the value of MSP to R0
				   "B endif \n\t"
		           "psp: MRSNE R0, PSP \n\t" //Load the value of PSP to R0
		           "endif: B Kernel_SVC_Handler "
				   );

#else
	__asm volatile("TST LR, #0X04  \n\t" // test if the bit 2 of LR is set by bitwise AND
				   "ITE EQ \n\t" // if the bit is not set, Z flag is raised else the Z flag is not raised.
		           "MRSEQ R0, MSP \n\t" //Load the value of MSP to R0
		           "MRSNE R0, PSP \n\t" //Load the value of PSP to R0
		           "B Kernel_SVC_Handler "
				   );
#endif
}



void SystickTimer_init(uint16_t msTime)
{
	// convert time in ms to ticks
	uint32_t ticks;


	/* 8000000 F >> 1 tick
	 * TIME*1000   F >> ? tick
	 *1/F s >> tick
		  s >> ? ticks
						s
						---- = s*F = ticks
						1/F
	 */

	ticks = SystemCoreClock*(msTime*0.001); //Floating point ??

	//Timer init ??
	SysTick_Config(ticks);
}


