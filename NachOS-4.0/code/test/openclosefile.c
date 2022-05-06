/**
 * @file openclosefile.c
 * @author Team Nachos - Sauce
 * @brief A file to test Open (file) and Close (file) syscalls
 * @date 2022-05-05
 */

#include "syscall.h"
#define FILENAME "test_open_close_file.txt"

int main()
{
  OpenFileId fileId;
  int closeStatus;

  // Create a new file to test Open (file) and Close (file) syscalls
  if (Create(FILENAME) == -1)
  {
    PrintString("Error occured when creating ");
    PrintString(FILENAME);
  }
  else
  {
    // Create successfully so we try Open the file
    fileId = Open(FILENAME);
    if (fileId == -1)
    {
      PrintString("File can not be opened.\n");
      PrintString("Or the kernel maximum number of opened files reached.\n");
      Remove(FILENAME);
      Halt();
    }

    // After opened, close the file
    closeStatus = Close(fileId);
    if (closeStatus == -1)
    {
      PrintString("Error occured when closing file");
      Remove(FILENAME);
      Halt();
    }
  }

  ReadChar(); // Pause the process so we can actually see the file being created
  Remove(FILENAME);
  Halt();
}