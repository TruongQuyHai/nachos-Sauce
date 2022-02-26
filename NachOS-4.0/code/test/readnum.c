#include "syscall.h"

int main()
{
  int num;
  PrintString(">>> Input number to ReadNum function: ");
  num = ReadNum();
  PrintString(">>> You have just input: ");
  PrintNum(num);
  PrintChar('\n');
  PrintString("!!! If you don't input zero and it print out zero -> some errors occurred when we ReadNum()\n");
  Halt();
}
