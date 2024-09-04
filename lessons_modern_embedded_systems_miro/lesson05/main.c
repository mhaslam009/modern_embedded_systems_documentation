#include "lm4f120h5qr.h"

/*
//use preprocessors to define macros
#define RCGCGPIO (*((unsigned int *) 0x400FE608U)) //Clock gating register defined

#define GPIOF_BASE 0x40025000U
#define GPIO_PIN_DIR (*((unsigned int *)(GPIOF_BASE + 0x400U)))
#define GPIO_DIG_OUT (*((unsigned int *)(GPIOF_BASE + 0x51CU)))
#define GPIO_DATA (*((unsigned int *)(GPIOF_BASE + 0x3FCU)))
*/



int main()
{
  //RCGCGPIO = 0x20U; //Turn on GPIOF by disabling clock gating register
  //GPIO_PIN_DIR = 0x0EU; //Configure LED pin's direction
  //GPIO_DIG_OUT = 0x0EU; //To set the pins as digital output
  
  
  
  SYSCTL_RCGCGPIO_R = 0x20U; //Turn on GPIOF by disabling clock gating register
  GPIO_PORTF_DIR_R = 0x0EU; //Configure LED pin's direction
  GPIO_PORTF_DEN_R = 0x0EU; //To set the pins as digital output
  
  //NOW MANIPULATE THE DATA REGISTER 0x400253FCU
  /*
->	0x400253FC = 0x00000000 -> no color
->	0x400253FC = 0x00000002 -> RED
->	0x400253FC = 0x00000004 -> Blue
->	0x400253FC = 0x00000008 -> Green
->	0x400253FC = 0x0000000A -> Blue and Red ==Yellow
->	0x400253FC = 0x0000000C -> Blue and Green == Sky Blue
->	0x400253FC = 0x0000000E -> All colors on == White

*/
  while(1){
    GPIO_PORTF_DATA_R = 0x00U;
    int counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  GPIO_PORTF_DATA_R = 0x02U;
      counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  GPIO_PORTF_DATA_R = 0x04U;
      counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  GPIO_PORTF_DATA_R = 0x08U;
      counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  }
  return 0;
}
 