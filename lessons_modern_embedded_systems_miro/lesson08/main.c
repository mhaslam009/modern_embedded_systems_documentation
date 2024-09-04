#include "lm4f120h5qr.h"


//To improve the readibility of code
#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)

//function prototype:
void delay(int iter);

//function definition
void delay(int iter){
    int volatile counter=0; //To introduce the delay
    while (counter < iter){
    counter++;
    }

}

int main()
{
  
  /*
  unsigned int a = 0x5A5A5A5A;
  unsigned int b = 0xDEADBEEF;
  unsigned int c;
  
  c = a | b; //OR operator,
  c = a & b; //AND operator
  c = a ^ b; //XOR
  c = ~b; //NOT
  c = b >> 1; //right-shift
  c = b << 3; //left-shift
  
  
  int x = 1024;
  int y = -1024;
  int z;
  z = x>>3;
  z = y>>3;
  */
  
  
  //SYSCTL_RCGCGPIO_R = 0x20U; //Turn on GPIOF by disabling clock gating register
  SYSCTL_RCGCGPIO_R |= (1<<5); //EQUIVALENT TO ABOVE LINE
  SYSCTL_GPIOHBCTL_R |= (1U << 5); /* enable AHB for GPIOF */
  GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);

  /* start with turning all LEDs off (note the use of array []) */
  GPIO_PORTF_AHB_DATA_BITS_R[LED_RED | LED_BLUE | LED_GREEN] = 0;

  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  //GPIO_PORTF_DIR_R = 0x0EU; //Configure LED pin's direction
  //GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); //EQUIVALENT TO ABOVE LINE //BIT SET IDIOMS USE FOR READ-WRITE REGISTERS
  //GPIO_PORTF_DEN_R = 0x0EU; //To set the pins as digital output
  //GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN); //EQUIVALENT TO ABOVE LINE
  
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
  // start with turning all LEDs off
  //GPIO_PORTF_DATA_R &= ~(LED_RED | LED_BLUE | LED_GREEN);
  //GPIO_PORTF_DATA_R |= LED_BLUE;
  //GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE; 
  while(1){
    
    //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | LED_RED; //LEAVE OUT OTHER LINES, leave blue LED remain on. AND WRITE ONTO THE 2ND BIT FROM RIGHT
    //GPIO_PORTF_DATA_R |= LED_RED; //EQUIVALENT TO ***GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | LED_RED;*** which is above line //BASICALLY PERFORMING 0R OPERATION
    //*((unsigned long volatile *)(0x40025000 + (LED_RED << 2))) = LED_RED; //you have just change the specific bit without using a bitwise operator 
    //GPIO_PORTF_DATA_R[RED_LED] = RED_LED; //ARRAY ARTH
    //*(GPIO_PORTF_DATA_R + RED_LED) = RED_LED; //POINTER ARTH
    
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;

    //int volatile counter[4] = {0, 0, 0, 0}; //To introduce the delay
    //while (counter[0]<1000000){
    //counter[0]++;
    //}
    
    
    //function calling
     delay(1000000);
    
    //HOW TO TURN OFF THE RED ONLY!!???
  //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R & ~LED_RED; //leaving out other bits and turn off 2nd bit  to 0.
  //GPIO_PORTF_DATA_R &= ~LED_RED; //equivalent to above line //PERFORMING NOT ON RED LED AND TURNING OFF ITS LED AND THEN AND OPERATION
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
    delay(500000);

    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = LED_GREEN;
    delay(5000000);
    GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = 0;
    delay(1000000);

  }
  return 0;
}
 