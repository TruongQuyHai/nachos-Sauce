/**
 * @file createfile.c
 * @author Team Nachos - Sauce
 * @brief Test Delete file syscall
 * @date 2022-05-05
 */

#include "syscall.h"
#define MAX_FILE_NAME_LENGTH 32

int main()
{
  int status;
  char filename[MAX_FILE_NAME_LENGTH];

  PrintString("Input file name you want to remove: ");
  ReadString(filename, MAX_FILE_NAME_LENGTH);
  status = Remove(filename);
  if (status == -1)
  {
    PrintString("Some error occurred when trying to remove ");
    PrintString(filename);
    PrintChar('\n');
  }
  else
  {
    PrintString("Remove file: ");
    PrintString(filename);
    PrintString(" successfully\n");
  }

  Halt();
}