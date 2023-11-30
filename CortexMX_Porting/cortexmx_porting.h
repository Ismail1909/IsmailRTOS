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

#define __svc(service_num) __asm("SVC %[num] ": :[num] "I" (service_num))


#endif /* CORTEXMX_PORTING_H_ */
