#include "syscall.h"

int main()
{
  char *buffer;
  ReadString(buffer, 10);
  PrintString(buffer);
  PrintChar('\n');
  PrintString(">>> CS333\n");
  PrintString(">>> Introduction To Operating Systems\n");
  PrintString(">>> Project 1\n");
  PrintString(">>> 19CTT2\n");
  PrintString(">>> Sauce\n\n");
  Halt();
}