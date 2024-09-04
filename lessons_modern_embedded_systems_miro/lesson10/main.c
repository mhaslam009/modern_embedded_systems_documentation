#include "lm4f120h5qr.h"
#include "delay.h"

//To improve the readibility of code
#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)


//function prototype 
//unsigned fact(unsigned n);

//void swap(int *x, int *y);
int *swap(int *x, int *y);


int *swap(int *x, int *y){
  static int tmp[2];
  tmp[0] = *x;
  tmp[1] = *y;
  *x = tmp[1];
  *y = tmp[0];
  return tmp;

}


//function defnition
/*
unsigned fact(unsigned n){
// 0! = 1
// n! = n*(n-1) for n>0
  unsigned foo[6];
  foo[n] = n;
  if(n==0U){
  return 1U;}
  else {
  return foo[n]*fact(n-1U); //recursive approach, function is calling itself 
  }
}
*/


int main()
{
 /*
  unsigned volatile x;
  x = fact(0U);
  x = 2U + 3U * fact(1U);
  (void)fact(7U);
*/
  
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
    int *p = swap(&x, &y);
    
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;

    
    //function calling
//    int volatile x = 1000000;
    delay(p[0]);
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
    delay(p[1]);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = LED_GREEN;
    delay(p[0]);
    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = 0;
    delay(p[1]);

  }
  //return 0;
}
 