#include "lm4f120h5qr.h"
#include "delay.h"

//To improve the readibility of code
#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)

#include <stdint.h>





//function prototype 
//unsigned fact(unsigned n);

//void swap(int *x, int *y);

/*
int *swap(int *x, int *y);


int *swap(int *x, int *y){
  static int tmp[2];
  tmp[0] = *x;
  tmp[1] = *y;
  *x = tmp[1];
  *y = tmp[0];
  return tmp;

}

*/

uint8_t  u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t  s8;
int16_t s16;
int32_t s32;



int main()
{
 /*
  unsigned volatile x;
  x = fact(0U);
  x = 2U + 3U * fact(1U);
  (void)fact(7U);
*/
  
  
  u8a  = sizeof(u8a);
    u16c = sizeof(uint16_t);
    u32e = sizeof(uint32_t);

    u8a  = 0xa1U;
    u16c = 0xc1c2U;
    u32e = 0xe1e2e3e4U;

    u8b  = u8a;
    u16d = u16c;
    u32f = u32e;

    u16c = 40000U;
    u16d = 30000U;
    
    
    //u32e = u16c + u16d; // NOT portable!
    u32e = (uint32_t)u16c + u16d;

    u16c = 0x7FFFU + 20U;
    //s32  = 10 - u16c;  // NOT portable!
    //s32  = 10 - (int16_t)u16c; // INCORRECT: insufficient dynamic range
    s32  = 10 - (int32_t)u16c; // CORRECT: cast to the lvalue type

    //if (u32e > -1) {  // ALWAYS false!
    if ((int32_t)u32e > -1) {
        u8a = 1U;
    }
    else {
        u8a = 0U;
    }

    u8a = 0xffU;
    //if (~u8a == 0x00U) { // ALWAYS false!
    if ((uint8_t)(~u8a) == 0x00U) {
        u8b = 1U;
    }

  
  
  //int16_t x = u32b;
  //int16_t y;
  
  
  //SYSCTL_RCGCGPIO_R = 0x20U; //Turn on GPIOF by disabling clock gating register
  SYSCTL_RCGCGPIO_R |= (1<<5); //EQUIVALENT TO ABOVE LINE
  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* enable AHB for GPIOF */
  GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);

  /* start with turning all LEDs off (note the use of array []) */
  GPIO_PORTF_AHB_DATA_BITS_R[LED_RED | LED_BLUE | LED_GREEN] = 0;

  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;

  while(1){
    int x = 1000000;
    int y = 1000000/2;
    //int *p = swap(&x, &y);
    
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;

    
    //function calling
//    int volatile x = 1000000;
    //delay(p[0]);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
    //delay(p[1]);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = LED_GREEN;
    //delay(p[0]);
    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = 0;
    //delay(p[1]);

  }
  //return 0;
}









 