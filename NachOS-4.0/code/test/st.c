/**
 * @file st.c
 * @author Team Nachos - Sauce
 * @brief A file to test ReadString and PrintString syscalls
 * @date 2022-05-05
 */

#include "syscall.h"

int main()
{
  char *buffer;
  ReadString(buffer, 12);
  PrintString(buffer);
  Halt();
}