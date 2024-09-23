#include <stdint.h> // C99 standard integers
#include "bsp.h"
#include "miros.h"

/* create a febricated stack for blinky1 thread */
uint32_t stack_blinky1[40];
//uint32_t *sp_blinky1 = &stack_blinky1[40]; //pointer variable have address of the blinky1 stack
OSThread blinky1;

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
//uint32_t *sp_blinky2 = &stack_blinky2[40]; //pointer variable have address of the blinky2 stack
OSThread blinky2;


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
    BSP_init();   // Initialize the board support package
		OS_init(); //calling priority of PENDSV 
    /* Passing the values to OSThread_start for the Cortex-M ISR stack frame */
    OSThread_start(&blinky1,          // Thread control block for blinky1
                   &main_blinky1,     // Function pointer to blinky1 function
                   stack_blinky1,     // Stack for blinky1
                   sizeof(stack_blinky1));  // Size of the stack for blinky1

    /* Fill-up blinky2 thread using Cortex-M interrupt frame */
    OSThread_start(&blinky2,          // Thread control block for blinky2
                   &main_blinky2,     // Function pointer to blinky2 function
                   stack_blinky2,     // Stack for blinky2
                   sizeof(stack_blinky2));  // Size of the stack for blinky2

    /* Start running the threads */
     while (1) {
        // Code here will run after both threads are initialized
    }
		//return 0;
}
