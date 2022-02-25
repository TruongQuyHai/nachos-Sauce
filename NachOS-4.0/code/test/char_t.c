#include "syscall.h"

int main()
{
  // TODO: test read char here
  char c = ReadChar();
  PrintChar(c);
  PrintChar('\n');
  Halt();
}