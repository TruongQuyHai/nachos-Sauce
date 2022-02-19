#include "syscall.h"

int main()
{
  int i = 32;
  for (; i <= 126; i++)
  {
    PrintChar((char)i);
  }
  PrintChar('\n');
  Halt();
}