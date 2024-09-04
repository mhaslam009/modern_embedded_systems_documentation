#include "lm4f120h5qr.h"


//To improve the readibility of code
#define LED_RED (1U<<1)
#define LED_BLUE (1U<<2)
#define LED_GREEN (1U<<3)
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
  //GPIO_PORTF_DIR_R = 0x0EU; //Configure LED pin's direction
  GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); //EQUIVALENT TO ABOVE LINE //BIT SET IDIOMS USE FOR READ-WRITE REGISTERS
  //GPIO_PORTF_DEN_R = 0x0EU; //To set the pins as digital output
  GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN); //EQUIVALENT TO ABOVE LINE
  
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
  GPIO_PORTF_DATA_R &= ~(LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_DATA_R |= LED_BLUE;
  while(1){
    
    //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | LED_RED; //LEAVE OUT OTHER LINES, leave blue LED remain on. AND WRITE ONTO THE 2ND BIT FROM RIGHT
    GPIO_PORTF_DATA_R |= LED_RED; //EQUIVALENT TO ***GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | LED_RED;*** which is above line //BASICALLY PERFORMING 0R OPERATION
    int counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
    //HOW TO TURN OFF THE RED ONLY!!???
  //GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R & ~LED_RED; //leaving out other bits and turn off 2nd bit  to 0.
  GPIO_PORTF_DATA_R &= ~LED_RED; //equivalent to above line //PERFORMING NOT ON RED LED AND TURNING OFF ITS LED AND THEN AND OPERATION
      counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }

  GPIO_PORTF_DATA_R |= LED_GREEN;
  counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
    GPIO_PORTF_DATA_R &= ~LED_GREEN;
    counter=0;
        while (counter<1000000){
    counter++;
    }

  }
  return 0;
}
 