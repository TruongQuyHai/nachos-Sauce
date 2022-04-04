/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__
#define __USERPROG_KSYSCALL_H__

#include "kernel.h"
#include "synchconsole.h"
#include <stdlib.h>

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')

#define MAX_NUM_LENGTH 11
char numBuffer[MAX_NUM_LENGTH + 2];

void SysHalt()
{
  kernel->interrupt->Halt();
}

bool isEnter(char c) { return c == LF || c == CR; }

bool isBlank(char c) { return c == LF || c == CR || c == TAB || c == SPACE; }

void readRemainingConsoleInput()
{
  char c = kernel->synchConsoleIn->GetChar();
  while (!(isEnter(c)))
  {
    c = kernel->synchConsoleIn->GetChar();
  }
}

void SysHaltWithMessage(string message)
{
  readRemainingConsoleInput();
  DEBUG(dbgSys, message);
  cerr << message;
  SysHalt();
}

int ReadNumFromConsole()
{
  memset(numBuffer, '\0', sizeof(numBuffer));
  char c = kernel->synchConsoleIn->GetChar();
  while (c == EOF)
  {
    c = kernel->synchConsoleIn->GetChar();
  }

  if (isBlank(c))
  {
    c = kernel->synchConsoleIn->GetChar();
  }

  int i = 0;
  while (!isEnter(c))
  {
    numBuffer[i++] = c;
    if (i == 1 && c == '-')
    {
      c = kernel->synchConsoleIn->GetChar();
      continue;
    }
    else if (i > 1)
    {
      if (c == '-')
        SysHaltWithMessage("Unexpected '-' sign. \n");
      else if (isBlank(c))
        SysHaltWithMessage("Unexpected white-space. \n");
      else if (i > MAX_NUM_LENGTH)
      {
        SysHaltWithMessage("Number is too long, overflow!!!\n");
      }
    }
    else if (((int)c < (int)'0') || ((int)c > (int)'9'))
    {
      SysHaltWithMessage("Number expected!!!\n");
    }

    c = kernel->synchConsoleIn->GetChar();
  }
  // while (!(isBlank(c)) || c == EOF)
  // {
  //   numBuffer[i++] = c;
  //   if (i == 1 && c == '-')
  //   {
  //     c = kernel->synchConsoleIn->GetChar();
  //     continue;
  //   }
  //   else if (i > 1 && c == '-')
  //   {
  //     SysHaltWithMessage("Unexpected '-' sign. \n");
  //   }
  //   else if (((int)c < (int)'0') || ((int)c > (int)'9'))
  //   {
  //     SysHaltWithMessage("Number expected!!!\n");
  //   }
  //   else if (i > MAX_NUM_LENGTH)
  //   {
  //     SysHaltWithMessage("Number is too long, overflow!!!\n");
  //   }
  //   c = kernel->synchConsoleIn->GetChar();
  // }
  return 1;
}

/**
 * This function read a sequence of characters from the console and convert to a number
 * @return number
 */
int ReadNumSys()
{
  // if users input 0 or some errors occur => return 0
  if (ReadNumFromConsole() == 0)
  {
    return 0;
  }
  // handle INT32_MIN because INT32_MIN can not be converted from positive number
  // 214783647 < 2147483648
  if (strcmp(numBuffer, "-2147483648") == 0)
  {
    return INT32_MIN;
  }
  int num = 0;
  bool isNegative = numBuffer[0] == '-';
  // if not negative then store the first number of the numBuffer to num
  if (!isNegative)
  {
    num = numBuffer[0] - '0';
  }

  // run loop from 1 -> strlen and add to num the correct amount
  for (int i = 1; i < (int)strlen(numBuffer); i++)
  {
    num = num * 10 + (numBuffer[i] - '0');
  }
  // if is negative, inverse the number. because we already handle the INT32_MIN => no overflow
  if (isNegative)
  {
    num = -num;
  }

  // if isNegative but num > 0 => overflow => return 0
  // if not isNegative but num < 0 => overflow => return 0
  if ((isNegative && num > 0) || (!isNegative && num < 0))
  {
    DEBUG(dbgSys, "INT32 expected, " << numBuffer << " found");
    return 0;
  }

  // if negative -> inverse
  int numTemp = isNegative ? -num : num;
  // compare number numTemp to numBuffer
  // if different => some errors occurred => return 0
  for (int i = strlen(numBuffer) - 1; i >= isNegative; i--)
  {
    if ((numBuffer[i] - '0') != (numTemp % 10))
    {
      return 0;
    }
    numTemp = numTemp / 10;
  }

  return num;
}

/**
 * Function print number to console
 * @param number
 */
void PrintNumSys(int number)
{
  if (number == 0)
  {
    kernel->synchConsoleOut->PutChar('0');
    return;
  }

  // handle INT32_MIN case to prevent overflow
  if (number == INT32_MIN)
  {
    for (int i = 0; i < 11; i++)
    {
      kernel->synchConsoleOut->PutChar("-2147483648"[i]);
    }
    return;
  }

  // if number < 0 => inverse and print to console '-'
  if (number < 0)
  {
    kernel->synchConsoleOut->PutChar('-');
    number = -number;
  }

  int i = 0;
  while (number)
  {
    numBuffer[i++] = (number % 10) + '0';
    number /= 10;
  }

  // print the number part
  for (int j = i - 1; j >= 0; j--)
  {
    kernel->synchConsoleOut->PutChar(numBuffer[j]);
  }
}

void PrintCharSys(char character)
{
  kernel->synchConsoleOut->PutChar(character);
}

// this function prints system string
void PrintStringSys(char *buffer, int length)
{
  // use for loop to print each character of the string
  for (int i = 0; i < length; i++)
  {
    kernel->synchConsoleOut->PutChar(buffer[i]);
  }
}

// this function generates random integer
int RandomNumSys() { return random(); }

// this function reads system char
char ReadCharSys() { return kernel->synchConsoleIn->GetChar(); }

// this function reads system string
char *ReadStringSys(int length)
{
  char *buffer = new char[length + 1];

  // use for loop and ReadCharSys from above to append all characters of the string
  for (int i = 0; i < length; i++)
  {
    buffer[i] = ReadCharSys();
  }
  // appending whitespace at the end of the string
  buffer[length] = '\0';
  return buffer;
}

int CreateSys(char *fileName)
{
  if (strlen(fileName) == 0 || fileName == NULL || !kernel->fileSystem->Create(fileName))
  {
    return -1;
  }
  return 0;
}

int OpenSys(char *fileName, int type)
{
  if (type != 0 && type != 1)
    return -1;

  int id = kernel->fileSystem->Open(fileName, type);
  if (id == -1)
    return -1;
  DEBUG(dbgSys, "\nOpened file");
  return id;
}

int ReadSys(char *buffer, int charCount, int fileId)
{
  if (fileId == 0)
  {
    return kernel->synchConsoleIn->GetString(buffer, charCount);
  }
  return kernel->fileSystem->Read(buffer, charCount, fileId);
}

int SeekSys(int seekPos, int fileId)
{
  if (fileId <= 1)
  {
    DEBUG(dbgSys, "\nCan't seek in console");
    return -1;
  }
  return kernel->fileSystem->Seek(seekPos, fileId);
}

int WriteSys(char *buffer, int charCount, int fileId)
{
  if (fileId == 1)
  {
    return kernel->synchConsoleOut->PutString(buffer, charCount);
  }
  return kernel->fileSystem->Write(buffer, charCount, fileId);
}

int SysClose(int id) { return kernel->fileSystem->Close(id); }

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
