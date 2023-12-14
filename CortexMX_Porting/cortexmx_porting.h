/********************************************************************************
 * @file           :  cortexmx_porting.h
 * @author         : Ismail Amr @ learn-in-depth.com : Mastering Embedded Systems by Eng. Keroles Shenoda
 * @brief          : ARM Cortex-M Porting layer based on CMSIS Core
 * IsmailRTOS Project : A Custom RTOS Project for ARM Cortex-M Architecture
 * www.learn-in-depth.com
 *******************************************************************************/

#ifndef CORTEXMX_PORTING_H_
#define CORTEXMX_PORTING_H_



#if defined (ARMCM7)
  #include "ARMCM7.h"
#elif defined (ARMCM4)
  #include "ARMCM4.h"
#elif defined (ARMCM3)
  #include "ARMCM3.h"
#elif defined (ARMCM0)
  #include "ARMCM0.h"
#elif defined (ARMCM0plus)
  #include "ARMCM0PLUS.h"
#else
  #error "Processor not specified or unsupported."
#endif


extern uint32_t __StackTop;
extern uint32_t __HeapLimit;

#define PENDSVSET 28



#define _cortex_svc(service_num) __asm volatile("SVC %[num] ": :[num] "I" (service_num))

// Wait For Event is a hint instruction that permits the processor to enter a low-power state until an events occurs:
#define _cortex_wfe() __WFE()

// Wait For Interrupt.
#define _cortex_wfi() __WFI()

#define _cortex_setUnPrivileged() __asm volatile("MRS r0, CONTROL \n\t" "ORR r0,r0, #0x1 \n\t" "MSR CONTROL, r0");

#define _cortex_setPrivileged() __asm volatile("MRS r0, CONTROL \n\t" "BFC r0,#0x0, #0x1 \n\t" "MSR CONTROL, r0");

#define _cortex_switch_to_psp() __asm volatile("MRS r0, CONTROL \n\t" "ORR r0,r0, #0x2 \n\t" "MSR CONTROL, r0");

#define _cortex_switch_to_msp() __asm volatile("MRS r0, CONTROL \n\t" "BFC r0,#0x1, #0x1 \n\t" "MSR CONTROL, r0");


__attribute__((always_inline)) static inline void _cortex_Save_Context(uint32_t* sp)
{
	sp--;
	__asm volatile("mov %[sp], r4":[sp] "=r" (*(sp)));
	sp--;
	__asm volatile("mov %[sp], r5":[sp] "=r" (*(sp)));
	sp--;
	__asm volatile("mov %[sp], r6":[sp] "=r" (*(sp)));
	sp--;
	__asm volatile("mov %[sp], r7":[sp] "=r" (*(sp)));
	sp--;
	__asm volatile("mov %[sp], r8":[sp] "=r" (*(sp)));
	sp--;
	__asm volatile("mov %[sp], r9":[sp] "=r" (*(sp)));
	sp--;
	__asm volatile("mov %[sp], r10":[sp] "=r" (*(sp)));
	sp--;
	__asm volatile("mov %[sp], r11":[sp] "=r" (*(sp)));
	sp--;
}

__attribute__((always_inline)) static inline void _cortex_Restore_Context(uint32_t* sp)
{
	__asm volatile("mov r11, %[sp]"::[sp] "r" (*(sp)));
	sp++;
	__asm volatile("mov r10, %[sp]"::[sp] "r" (*(sp)));
	sp++;
	__asm volatile("mov r9, %[sp]"::[sp] "r" (*(sp)));
	sp++;
	__asm volatile("mov r8, %[sp]"::[sp] "r" (*(sp)));
	sp++;
	__asm volatile("mov r7, %[sp]"::[sp] "r" (*(sp)));
	sp++;
	__asm volatile("mov r6, %[sp]"::[sp] "r" (*(sp)));
	sp++;
	__asm volatile("mov r5, %[sp]"::[sp] "r" (*(sp)));
	sp++;
	__asm volatile("mov r4, %[sp]"::[sp] "r" (*(sp)));
	sp++;
}


__attribute__((always_inline)) static inline void _cortex_triggerPENDSV(void)
{
	SCB->ICSR |= (PENDSVSET<<1);
}

__attribute__((always_inline)) static inline void _cortex_enable_irq(void)
{
	__enable_irq();
}

__attribute__((always_inline)) static inline void _cortex_disable_irq(void)
{
	__disable_irq();
}

__attribute__((always_inline)) static inline uint32_t _cortex_getPSP(void)
{
	return __get_PSP();
}

__attribute__((always_inline)) static inline uint32_t _cortex_getMSP(void)
{
	return __get_MSP();
}

__attribute__((always_inline)) static inline void _cortex_setPSP(uint32_t psp)
{
	return __set_PSP(psp);
}

__attribute__((always_inline)) static inline void _cortex_setMSP(uint32_t msp)
{
	return __set_MSP(msp);
}

__attribute__((always_inline)) static inline void _cortex_setControl(uint32_t control)
{
	return __set_CONTROL(control);
}

__attribute__((always_inline)) static inline uint32_t _cortex_getControl(void)
{
	return __get_CONTROL();
}

__attribute__((always_inline)) static inline void _cortex_store_Unprivileged(uint32_t value, volatile uint32_t* addr)
{
	__STRT(value,addr);
	return;
}

__attribute__((always_inline)) static inline uint32_t _cortex_load_Unprivileged(volatile uint32_t* addr)
{
	return __LDRT(addr);
}

#if(!defined(ARMCM0) && !defined(ARMCM0plus))

__attribute__((always_inline)) static inline void _cortex_enable_fault(void)
{
	__enable_fault_irq();
}

__attribute__((always_inline)) static inline void _cortex_disable_fault(void)
{
	__disable_fault_irq();
}

__attribute__((always_inline)) static inline uint32_t _cortex_get_BASEPRI(void)
{
	__get_BASEPRI();
}

__attribute__((always_inline)) static inline void _cortex_set_BASEPRI(uint32_t basePri)
{
	__set_BASEPRI(basePri);
}

__attribute__((always_inline)) static inline uint32_t _cortex_get_FAULTMASK(void)
{
	__get_FAULTMASK();
}

__attribute__((always_inline)) static inline void _cortex_set_FAULTMASK(uint32_t faultMask)
{
	__set_FAULTMASK(faultMask);
}

__attribute__((always_inline)) static inline uint32_t _cortex_store_ExclusiveWord(uint32_t value, volatile uint32_t* addr)
{
	return __STREXW(value,addr);
}

__attribute__((always_inline)) static inline uint32_t _cortex_load_ExclusiveWord(volatile uint32_t* addr)
{
	return __LDREXW(addr);
}

#endif



void SystickTimer_init(uint16_t msTime);


#endif /* CORTEXMX_PORTING_H_ */
