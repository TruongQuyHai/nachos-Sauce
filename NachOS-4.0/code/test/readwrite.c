/**
 * @file readwrite.c
 * @author Team Nachos - Sauce
 * @brief A file to test Read (file / console) and Write (file / console) syscalls
 * @date 2022-05-05
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

#define MAX_TOTAL_BUFFER_SIZE 800

// TODO: Test more edge cases
int main()
{
  char buffer[MAX_TOTAL_BUFFER_SIZE];
  char buffer2[MAX_TOTAL_BUFFER_SIZE];
  OpenFileId id;

  id = Open("test_read.txt");
  Read(buffer, 20, id);  // read 20 first characters of file into buffer
  Seek(0, id);           // seek to the beginning of the file
  Read(buffer2, 20, id); // read 20 first characters of file into buffer2

  // write buffer & buffer2 to stdout
  Write(buffer, 20, stdout);
  Write(buffer2, 20, stdout);
  PrintChar('\n');
  Halt();
}