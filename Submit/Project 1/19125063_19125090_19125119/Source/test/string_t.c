#include "syscall.h"

int main()
{
  // use ReadString, PrintString, PrintChar function to test
  char *buffer;
  int n = 0;

  PrintString("Number of characters you want to print to the console: ");
  n = ReadNum();

  PrintString("Input that string here: ");
  ReadString(buffer, n);
  PrintString(">>> Your string: ");
  PrintString(buffer);
  PrintString("\n");

  Halt();
}