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

  PrintString("Input your source file you want to get content from: ");
  ReadString(file1, MAX_FILE_NAME_SIZE);

  id1 = Open(file1);
  if (id1 == -1)
  {
    PrintString("Some errors happened when trying to open the file 1\n");
    Halt();
  }

  PrintString("Input your destination file you want to append to: ");
  ReadString(file2, MAX_FILE_NAME_SIZE);

  id2 = Open(file2);
  if (id2 == -1)
  {
    PrintString("Some errors happened when trying to open the file 2\n");
    Halt();
  }

  // read the contents of file1 to buffer
  length = Read(buffer, MAX_BUFFER_SIZE, id1);

  // go to the last position in file 2 to append the buffer
  Seek(-1, id2);
  length = Write(buffer, length, id2);

  PrintString("Appended ");
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