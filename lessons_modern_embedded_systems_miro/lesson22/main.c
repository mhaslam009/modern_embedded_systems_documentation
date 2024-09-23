#include <stdint.h> // C99 standard integers
#include "bsp.h"

/* create a febricated stack for blinky1 thread */
uint32_t stack_blinky1[40];
uint32_t *sp_blinky1 = &stack_blinky1[40]; //pointer variable have address of the blinky1 stack


/* background code: sequential with blocking version */
void main_blinky1(void) {
    while (1) {
        BSP_ledGreenOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledGreenOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}


/* create a febricated stack for blinky2 thread */
uint32_t stack_blinky2[40];
uint32_t *sp_blinky2 = &stack_blinky2[40]; //pointer variable have address of the blinky2 stack

/* background code: sequential with blocking version */
void main_blinky2(void) {
    while (1) {
        BSP_ledBlueOn();
        BSP_delay(BSP_TICKS_PER_SEC / 2U);
        BSP_ledBlueOff();
        BSP_delay(BSP_TICKS_PER_SEC / 3U);
    }
}

int main() {
	uint32_t volatile run = 0U;
	BSP_init();
	//Fill-up blinky1 thread using CORTEX-M interrupt frame 
		*(--sp_blinky1) = (1U <<24); /* xPSR */
		*(--sp_blinky1) = (uint32_t)&main_blinky1; /* PC */
		*(--sp_blinky1) = 0x0000000EU; /* LR */
		*(--sp_blinky1) = 0x0000000CU; /* R12 */
		*(--sp_blinky1) = 0X00000003U; /* R3 */
		*(--sp_blinky1) = 0X00000002U; /* R2 */
		*(--sp_blinky1) = 0X00000001U; /* R1 */
		*(--sp_blinky1) = 0X00000000U; /* R0 */
	    /* additionally, fake registers R4-R11 */
    *(--sp_blinky1) = 0x0000000BU; /* R11 */
    *(--sp_blinky1) = 0x0000000AU; /* R10 */
    *(--sp_blinky1) = 0x00000009U; /* R9 */
    *(--sp_blinky1) = 0x00000008U; /* R8 */
    *(--sp_blinky1) = 0x00000007U; /* R7 */
    *(--sp_blinky1) = 0x00000006U; /* R6 */
    *(--sp_blinky1) = 0x00000005U; /* R5 */
    *(--sp_blinky1) = 0x00000004U; /* R4 */
	
		//Fill-up blinky2 thread using CORTEX-M interrupt frame 
		*(--sp_blinky2) = (1U <<24); /* xPSR */
		*(--sp_blinky2) = (uint32_t)&main_blinky2; /* PC */
		*(--sp_blinky2) = 0x0000000EU; /* LR */
		*(--sp_blinky2) = 0x0000000CU; /* R12 */
		*(--sp_blinky2) = 0X00000003U; /* R3 */
		*(--sp_blinky2) = 0X00000002U; /* R2 */
		*(--sp_blinky2) = 0X00000001U; /* R1 */
		*(--sp_blinky2) = 0X00000000U; /* R0 */
		    /* additionally, fake registers R4-R11 */
    *(--sp_blinky2) = 0x0000000BU; /* R11 */
    *(--sp_blinky2) = 0x0000000AU; /* R10 */
    *(--sp_blinky2) = 0x00000009U; /* R9 */
    *(--sp_blinky2) = 0x00000008U; /* R8 */
    *(--sp_blinky2) = 0x00000007U; /* R7 */
    *(--sp_blinky2) = 0x00000006U; /* R6 */
    *(--sp_blinky2) = 0x00000005U; /* R5 */
    *(--sp_blinky2) = 0x00000004U; /* R4 */
	
	//wait loop to switch the threads
	while(1){}
	//return 0;
}