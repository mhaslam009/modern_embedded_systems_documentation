#include "tm4c_cmsis.h"
#include "core_cm4.h"
#include "delay.h"
#include <stdint.h>


//To improve the readibility of code
#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)


int16_t x = -1;
uint32_t y = LED_RED | LED_GREEN;

int16_t sqr[] = {
  1*1,
  2*2,
  3*3,
  4*4

};


 
//new strcuture Point haveing 2 memebers
typedef struct {
  uint8_t y;
  uint16_t x;
}Point;
//Point p1, p2; //creating hooks==instances of Point

//Creating and making features of hook
Point p1 = {
  123U,
  0x124U
};
Point p2;


//new structure, built on top of Point structure, have 2 memebers
typedef struct{
  Point top_def;
  Point bottom_def;
} Window; 

//new structure, built on top of Point structure, have 3 memebers
typedef struct{
  Point corners[3];
} Triangle;

//creating instances of the struct
Triangle t; //creating new hooks for Triangle, whihc has an array that contain same elements

Window w2; //creating new hook for Window struct which have 2 members

Window w1 ={
  { 123U, 0X1234U},
  { 234U, 0X6789U}

}; 


int main()
{
  p1.x = sizeof(Point); //accesing members of Point strcut through hook p1
  p1.y = 0xAAU; //accesing members of Point strcut through hook p1

  //accessing members of the instances of the struct
  //from top, access hook of window, which give access to its member, that member give access to memebers of Point
  w1.top_def.x = 1U;
  //from top, access hook of window, which give access to its member, that member give access to memebers of Point
  w1.bottom_def.y = 2U;
  //from top, access hook of Triangle, which give access to its member, that member give access to memebers of Point
  t.corners[0].x = 1U;
  t.corners[1].y = 2U;
  
  //Copy among the memebers of the instances of same strcut which is Point
  p2=p1;
  //Copy among the memebers of the instances of same strcut which is Window
  w2=w1;
  
  
  
  //creating pointers to structure
  Point *pp; //pointer variable of Point which eligible to store hook's address of Point 
  Window *wp; //pointer variable of Window which eligible to store hook's address of Window
  
  //take the addrrss of the pointer
  pp = &p1; //copy the address p1 hook/instance which means, the member of the Point struct copied to pointer of struct Point
  wp = &w2; //copy the address w2 hook/instance which means, the member of the Window struct copied to pointer of struct Window
  
  //after storing the address of pointer
  //How can you access the memeber at which pointer (pp, wp) is pointing at
  (*pp).x = 1U; //gettingg access of the member of Point
  (*wp).top_def = *pp; //save value stored at *pp
  

  

  //SYSCTL_GPIOHBCTL_R |= (1U << 5); /* enable AHB for GPIOF */
  SYSCTL->GPIOHSCTL |= (1U << 5); /* enable AHB for GPIOF */

   //SYSCTL_RCGCGPIO_R = 0x20U; //Turn on GPIOF by disabling clock gating register
  //SYSCTL_RCGCGPIO_R |= (1<<5); //EQUIVALENT TO ABOVE LINE
  SYSCTL->RCGC2 |= (1U << 5);  /* enable clock for GPIOF */
  
  //GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
  //GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

  /* start with turning all LEDs off (note the use of array []) */
  //GPIO_PORTF_AHB_DATA_BITS_R[LED_RED | LED_BLUE | LED_GREEN] = 0;
  /* turn all LEDs off */
  GPIOF_AHB->DATA_Bits[LED_RED | LED_BLUE | LED_GREEN] = 0U;

  
  //turn on LED Blue
  //GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;

  while(1){
    //int x = 1000000;
    //int y = 1000000/2;
    //int *p = swap(&x, &y);
    
  //Turn on RED LED  
  //GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
  GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;
  delay(500000);
  
  //Turn off RED LED
  //GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
  GPIOF_AHB->DATA_Bits[LED_RED] = 0;
  delay(1000000);
    
  //turn on green led
  //GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = LED_GREEN;
  GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
  delay(5000000);

    
  //turn of green led
  //GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = 0;
  GPIOF_AHB->DATA_Bits[LED_GREEN] = 0;
  delay(10000000);

  }
  //return 0;
}









 