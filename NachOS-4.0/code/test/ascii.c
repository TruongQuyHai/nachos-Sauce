/**
 * @file ascii.c
 * @author Team Nachos - Sauce
 * @brief Show every ascii character that is visible in the console
 *                                        (from 32 to 126 inclusive)
 * @date 2022-05-05
 */

#include "syscall.h"

int main()
{
  int i;
  for (i = 32; i < 127; i++)
  {
    if (i == 127)
      continue;
    PrintString("Char code: ");
    PrintNum(i);
    PrintString(" => ");
    PrintChar((char)i);
    PrintChar('\n');
  }
  Halt();
}