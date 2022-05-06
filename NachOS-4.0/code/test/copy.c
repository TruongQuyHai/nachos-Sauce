/**
 * @file concatenate.c
 * @author Team Nachos - Sauce
 * @brief Read content from a file and then store the content into the buffer
 *        write that buffer into another file.
 * @date 2022-05-05
 */

#include "syscall.h"
#define MAX_FILE_NAME_SIZE 32
#define MAX_BUFFER_SIZE 800

int main()
{
  char file1[MAX_FILE_NAME_SIZE];
  char file2[MAX_FILE_NAME_SIZE];
  char buffer[MAX_BUFFER_SIZE];
  OpenFileId id1;
  OpenFileId id2;
  int length;

  PrintString("Input your source file you want to copy from: ");
  ReadString(file1, MAX_FILE_NAME_SIZE);

  id1 = Open(file1);
  if (id1 == -1)
  {
    PrintString("Some errors happened when trying to open the file 1\n");
    Halt();
  }

  PrintString("Input your destination file you want to copy to: ");
  ReadString(file2, MAX_FILE_NAME_SIZE);

  id2 = Open(file2);
  if (id2 == -1) // Can't open the file
  {
    PrintString("Trying to create file ");
    PrintString(file2);
    PrintChar('\n');

    if (Create(file2) == -1)
    {
      PrintString("Error occured when creating ");
      PrintString(file2);
      PrintString("\nCan not find or create your destination file. System Halt()\n");
      Halt();
    }

    id2 = Open(file2);
  }

  // assign length to the actual length the we can read from the file1
  length = Read(buffer, MAX_BUFFER_SIZE, id1);
  // assign again the length that we wrote successfully to the file2
  length = Write(buffer, length, id2);

  PrintString("Copied ");
  PrintNum(length);
  PrintString(" bytes from file ");
  PrintString(file1);
  PrintString(" to file ");
  PrintString(file2);
  PrintString("\n");

  Close(id1);
  Close(id2);

  Halt();
}