/****************************************************************************
* MInimal Real-time Operating System (MiROS), ARM-CLANG port.
* version 0.23 (matching lesson 23)
*
* This software is a teaching aid to illustrate the concepts underlying
* a Real-Time Operating System (RTOS). The main goal of the software is
* simplicity and clear presentation of the concepts, but without dealing
* with various corner cases, portability, or error handling. For these
* reasons, the software is generally NOT intended or recommended for use
* in commercial applications.
*
* Copyright (C) 2018 Miro Samek. All Rights Reserved.
*
* SPDX-License-Identifier: GPL-3.0-or-later
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*
* Git repo:
* https://github.com/QuantumLeaps/MiROS
****************************************************************************/




#include <stdint.h>
#include "miros.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE //Macro: name string of a file "qassert.h"


#include "TM4C123GH6PM.h" /* the TM4C MCU Peripheral Access Layer (TI) */

OSThread * volatile OS_curr; //pointer to the current thread
OSThread * volatile OS_next; //pointer to the next thread

/* Creating Thread Database */
OSThread *OS_thread[32 + 1]; //pointer to the current thread
uint8_t OS_threadNum; //number of threads have already started
uint8_t OS_currIdx; //current thread index during round robin


void OS_init(void){
	/* set the PendSV interrupt priority to the lowest preemption */
	*(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);

}


void OS_sched(void){
	/* OS_next = .... */
	++OS_currIdx; //1)Increment the index of the current thread from Thread db
	//2) if the currently executing thread reaches out the number of threads
	if (OS_currIdx == OS_threadNum){
		OS_currIdx = 0U; //3) if the currently executing thread's index reached to total number of threads then set current thread to 0
		
	}
	OS_next = OS_thread[OS_currIdx]; //save the index of current thread to OS_next pointer
	
	/* Change the thread only if the thread next thread != current thread */
	if (OS_next != OS_curr){
		*(uint32_t volatile *)0xE000ED04 = (1U<<28); //TRIGGERING PendSV
	
	}

}
void OS_run(void) {
    /* callback to configure and start interrupts */
    OS_onStartup();

    __asm volatile ("cpsid i");
    OS_sched();
    __asm volatile ("cpsie i");

    /* the following code should never execute */
    Q_ERROR();
}






/* Definition of a function for registers specification */
void OSThread_start(
	OSThread *me,//pointer to the TCB
	OSThreadHandler threadHandler, //pointer-to-function to the thread handler 
	void *stkSto, //memory of private stack
	uint32_t stkSize //size of stack
){
	/* To stich 2 pieces together you need to establish a 
	stack point from which stackframe will be built  
	Also roundup the bottom of the stack to the 8-byte boundary */
	uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize) / 8) * 8);
	//Pre-filling the remaining stack with 0xDEADBEEF
	uint32_t *stk_limit;
	
	
	//Fill-up blinky1 thread using CORTEX-M interrupt frame 
		*(--sp) = (1U <<24); /* xPSR */
		*(--sp) = (uint32_t)threadHandler; /* PC */
		*(--sp) = 0x0000000EU; /* LR */
		*(--sp) = 0x0000000CU; /* R12 */
		*(--sp) = 0X00000003U; /* R3 */
		*(--sp) = 0X00000002U; /* R2 */
		*(--sp) = 0X00000001U; /* R1 */
		*(--sp) = 0X00000000U; /* R0 */
	    /* additionally, fake registers R4-R11 */
    *(--sp) = 0x0000000BU; /* R11 */
    *(--sp) = 0x0000000AU; /* R10 */
    *(--sp) = 0x00000009U; /* R9 */
    *(--sp) = 0x00000008U; /* R8 */
    *(--sp) = 0x00000007U; /* R7 */
    *(--sp) = 0x00000006U; /* R6 */
    *(--sp) = 0x00000005U; /* R5 */
    *(--sp) = 0x00000004U; /* R4 */

    /* save the top of the stack in the thread's attibute */
    me->sp = sp;

    /* round up the bottom of the stack to the 8-byte boundary */
    stk_limit = (uint32_t *)(((((uint32_t)stkSto - 1U) / 8) + 1U) * 8);

    /* pre-fill the unused part of the stack with 0xDEADBEEF */
    for (sp = sp - 1U; sp >= stk_limit; --sp) {
        *sp = 0xDEADBEEFU;
    }
		/* Verification if insertion of new thread causes overflows */
		Q_ASSERT(OS_threadNum < Q_DIM(OS_thread));
		
		/* if number of thread doesnt reached the limit then ->register the thread with the OS */
		OS_thread[OS_threadNum] = me; //save the fabricated sp in the thread, into the array of OS_thread
		++OS_threadNum; //increase the number of threads 
}
//void PendSV_Handler(void){ 
	//void *sp; // 0)create a fake register
	//__disable_irq(); // 1) disable interrupt
	///* 1) Check whether  OS_curr is not 0*/ 
	//if (OS_curr != (OSThread *)0){
	//	/* 2) push registers r4-r11 on the stack */
	//	OS_curr->sp = sp; //3) Save the fake sp value on the sp member of the OS_curr
	//}
	///* 4)Save the sp member of OS_next to fake sp */
	//sp = OS_next->sp;
	///* 5) pop the registers r4-r11 */
	//OS_curr = OS_next; //6) save address of OS_next to OS_curr as you are changing the thread
	//__enable_irq(); //7) enable the interupt as the thread switch completed
	//
//}






/*------------------------------------------------------------------------------*/


/* inline assembly syntax for Compiler 6 (ARMCLANG) */
__attribute__ ((naked))
void PendSV_Handler(void) {
__asm volatile (
    /* __disable_irq(); */
    "  CPSID         I                 \n"

    /* if (OS_curr != (OSThread *)0) { */
    "  LDR           r1,=OS_curr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  CMP           r1,#0             \n"
    "  BEQ           PendSV_restore    \n"

    /*     push registers r4-r11 on the stack */
#if (__ARM_ARCH == 6)               // if ARMv6-M...
    "  SUB           sp,sp,#(8*4)     \n" // make room for 8 registers r4-r11
    "  MOV           r0,sp            \n" // r0 := temporary stack pointer
    "  STMIA         r0!,{r4-r7}      \n" // save the low registers
    "  MOV           r4,r8            \n" // move the high registers to low registers...
    "  MOV           r5,r9            \n"
    "  MOV           r6,r10           \n"
    "  MOV           r7,r11           \n"
    "  STMIA         r0!,{r4-r7}      \n" // save the high registers
#else                               // ARMv7-M or higher
    "  PUSH          {r4-r11}          \n"
#endif                              // ARMv7-M or higher

    /*     OS_curr->sp = sp; */
    "  LDR           r1,=OS_curr       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  MOV           r0,sp             \n"
    "  STR           r0,[r1,#0x00]     \n"
    /* } */

    "PendSV_restore:                   \n"
    /* sp = OS_next->sp; */
    "  LDR           r1,=OS_next       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           r0,[r1,#0x00]     \n"
    "  MOV           sp,r0             \n"

    /* OS_curr = OS_next; */
    "  LDR           r1,=OS_next       \n"
    "  LDR           r1,[r1,#0x00]     \n"
    "  LDR           r2,=OS_curr       \n"
    "  STR           r1,[r2,#0x00]     \n"

    /* pop registers r4-r11 */
#if (__ARM_ARCH == 6)               // if ARMv6-M...
    "  MOV           r0,sp             \n" // r0 := top of stack
    "  MOV           r2,r0             \n"
    "  ADDS          r2,r2,#(4*4)      \n" // point r2 to the 4 high registers r7-r11
    "  LDMIA         r2!,{r4-r7}       \n" // pop the 4 high registers into low registers
    "  MOV           r8,r4             \n" // move low registers into high registers
    "  MOV           r9,r5             \n"
    "  MOV           r10,r6            \n"
    "  MOV           r11,r7            \n"
    "  LDMIA         r0!,{r4-r7}       \n" // pop the low registers
    "  ADD           sp,sp,#(8*4)      \n" // remove 8 registers from the stack
#else                               // ARMv7-M or higher
    "  POP           {r4-r11}          \n"
#endif                              // ARMv7-M or higher

    /* __enable_irq(); */
    "  CPSIE         I                 \n"

    /* return to the next thread */
    "  BX            lr                \n"
    );
}
