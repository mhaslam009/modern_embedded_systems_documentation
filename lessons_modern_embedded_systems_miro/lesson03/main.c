int counter = 0;
int main()
{
  int *p_int;
  p_int = &counter; //storing the address of counter variable
  while(*p_int<21){
     ++(*p_int); //pointing to the value that pointer variable's value(address) pointing at
  }
  p_int = (int *)0x20000002U; //storing new address into a pointer
  *p_int = 0XDEADBEEF; //storing new value into the variable which pointed out by the address of pointer var
  return 0;
}
 