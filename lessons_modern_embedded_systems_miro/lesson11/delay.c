#include "delay.h"

//function definition
void delay(int iter){
    int volatile counter=0; //To introduce the delay
    while (counter < iter){
    counter++;
    }

}