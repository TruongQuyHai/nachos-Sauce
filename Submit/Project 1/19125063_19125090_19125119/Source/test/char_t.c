#include "syscall.h"

int main()
{
  // TODO: test read char here
  char c;
  PrintString(">>> Please input your character you want to print to the console: ");
  c = ReadChar();
  PrintString(">>> Your character: ");
  PrintChar(c);
  PrintChar('\n');
  Halt();
}