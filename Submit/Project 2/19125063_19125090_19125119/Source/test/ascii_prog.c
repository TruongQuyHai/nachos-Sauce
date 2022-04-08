#include "syscall.h"

int main()
{
  int i = 32;
  for (; i <= 126; i++)
  {
    PrintNum((i - 32));
    PrintString(": ");
    PrintChar((char)i);
    PrintChar('\n');
  }
  PrintChar('\n');
  Halt();
}