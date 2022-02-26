#include "syscall.h"

int main()
{
  // use ReadString, PrintString, PrintChar function to test
  char *buffer;
  int n = 0;

  PrintString(">>> Number of characters you want to print to the console: ");
  n = ReadNum();

  PrintString(">>> Input that string here: ");
  ReadString(buffer, n);
  PrintString(">>> Your string: ");
  PrintString(buffer);
  PrintChar('\n');

  PrintString(">>> CS333\n");
  PrintString(">>> Introduction To Operating Systems\n");
  PrintString(">>> Project 1\n");
  PrintString(">>> 19CTT2\n");
  PrintString(">>> Sauce\n\n");

  Halt();
}