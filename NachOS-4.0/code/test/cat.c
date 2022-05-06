/**
 * @file cat.c
 * @author Team Nachos - Sauce
 * @brief Read content from a file and then store the content into the buffer
 *        print that buffer into the console.
 * @date 2022-05-05
 */

#include "syscall.h"
#define MAX_FILE_NAME_SIZE 32
#define MAX_BUFFER_SIZE 800

int main()
{
  char filename[MAX_FILE_NAME_SIZE];
  char buffer[MAX_BUFFER_SIZE];
  OpenFileId id;
  int length;

  PrintString("Input your filename you want to read: ");
  ReadString(filename, MAX_FILE_NAME_SIZE);

  id = Open(filename);
  if (id == -1)
  {
    PrintString("Some errors happened when trying to open the file\n");
    Halt();
  }

  length = Read(buffer, MAX_BUFFER_SIZE, id);
  PrintString("Your file content: \n");
  PrintString(buffer);
  PrintString("\n--------------------------------------\n");

  PrintString("Read ");
  PrintNum(length);
  PrintString(" bytes \n");

  Close(id);

  Halt();
}