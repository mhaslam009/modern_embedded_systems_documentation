#include "TM4C123GH6PM.h" //for better compatibility than tm4c_cmsis->
//more compatiblITY to lateset CORTEX MICROCONTROLLER SOFTWARE INTERFACE

#include "core_cm4.h"
#include "bsp.h"
#include <stdint.h>


int main()
{

  //SYSCTL_GPIOHBCTL_R |= (1U << 5); /* enable AHB for GPIOF */
  SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */

   //SYSCTL_RCGCGPIO_R = 0x20U; //Turn on GPIOF by disabling clock gating register
  //SYSCTL_RCGCGPIO_R |= (1<<5); //EQUIVALENT TO ABOVE LINE
  SYSCTL->RCGC2 |= (1U << 5);  /* enable clock for GPIOF */
  
  //GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
  //GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIOF_AHB->DATA_Bits[LED_RED | LED_BLUE | LED_GREEN] = 0U;
  
  
 SysTick->LOAD = SYS_CLOCK_HZ/2U -1U;
 SysTick->VAL = 0U;
 SysTick->CTRL = (1U << 2) | (1U << 1) | 1U;
 
 
 //before enabling the interrupt
 SysTick_Handler();
 //enable premask bit->after enabling the interrupt
 __enable_irq();
  while(1){
      //apply Mutual Exclusion to avoid Race Condition by using __disable_irq() and __enable_irq()
      __disable_irq();
      GPIOF_AHB->DATA |= LED_GREEN;
      __enable_irq();
      /*CRITICAL SECTION HERE*/
      __disable_irq();
      GPIOF_AHB->DATA &= ~LED_GREEN;
      __enable_irq();
  
  }
  //return 0;
}









 
