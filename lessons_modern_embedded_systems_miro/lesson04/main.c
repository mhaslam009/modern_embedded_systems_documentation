int main()
{
  *((unsigned int *) 0x400FE608U) = 0x20U; //Turn on GPIOF by disabling clock gating register
  *((unsigned int *) 0x40025400U) = 0x0EU; //Configure LED pin's direction
  *((unsigned int *) 0x4002551CU) = 0x0EU; //To set the pins as digital output
  
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
    *((unsigned int *) 0x400253FCU) = 0x00U;
    int counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  *((unsigned int *) 0x400253FCU) = 0x02U;
      counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  *((unsigned int *) 0x400253FCU) = 0x04U;
      counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  *((unsigned int *) 0x400253FCU) = 0x08U;
      counter = 0; //To introduce the delay
    while (counter<1000000){
    counter++;
    }
  }
  return 0;
}
 