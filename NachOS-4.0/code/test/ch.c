/**
 * @file ch.c
 * @author Team Nachos - Sauce
 * @brief Test ReadChar and PrintChar syscall
 * @date 2022-05-05
 */

#include "syscall.h"

int main()
{
  char c = ReadChar();
  PrintChar(c);
  PrintChar('\n');
  Halt();
}