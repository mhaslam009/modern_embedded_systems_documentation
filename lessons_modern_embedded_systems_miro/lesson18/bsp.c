/* Board Support Package */
#include "TM4C123GH6PM.h" //for better compatibility than tm4c_cmsis->
//more compatiblITY to lateset CORTEX MICROCONTROLLER SOFTWARE INTERFACE
#include "bsp.h"

__stackless void assert_failed (char const *file, int line) {
  /* TBD: damage control */
  NVIC_SystemReset(); /* reset the system */
}

void SysTick_Handler(void) {
  GPIOF_AHB->DATA_Bits[LED_RED] ^= LED_RED;
} 