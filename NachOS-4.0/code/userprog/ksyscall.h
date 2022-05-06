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

/**
 * Utility functions
 */
#define CR (char)13
#define LF (char)10
#define TAB (char)9
#define SPACE ' '

bool isEnter(char c)
{
  return c == CR || c == LF;
}

/**
 * @brief Create a buffer with size limit + 1 and initializes it with NULL
 *
 * @param int limit
 * @return char*
 */
char *assignBuffer(int limit)
{
  char *buffer = NULL;
  buffer = new char[limit + 1]{0};
  if (buffer == NULL)
    return NULL;

  return buffer;
}

bool isEmptyString(char *buffer)
{
  return buffer == NULL || strlen(buffer) == 0;
}

bool isIntMin(char *buffer)
{
  return strcmp(buffer, "-2147483648") == 0;
}

bool isNegative(char *numBuffer)
{
  return numBuffer[0] == '-';
}

bool isNegative(int num)
{
  return num < 0;
}

bool isNotNumber(char c)
{
  return c < '0' || c > '9';
}

bool isSpace(char c)
{
  return c == CR || c == LF || c == TAB || c == SPACE;
}

/**
 * @brief Check whether the buffer is equal the number
 *          Help in checking overflow or underflow
 *
 * @param char* buffer
 * @param bool _isNegative
 * @param int number
 * @return true if two numbers are equal, false if two numbers are not equal
 */
bool isStringTheSameWithNumber(char *buffer, bool _isNegative, int number)
{
  int i;
  if (_isNegative)
  {
    number = -number;
  }

  for (i = strlen(buffer) - 1; i >= _isNegative; i--)
  {
    if ((int)(buffer[i] - '0') != (number % 10))
    {
      return false;
    }
    number /= 10;
  }
  return true;
}

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

/**
 * @brief copy user memory to system memory
 *
 * @param int virtAddr
 * @param int limit
 * @return char*
 */
char *User2System(int virtAddr, int limit = -1)
{
  int i = 0;
  int oneChar;
  int length = 0;
  char *kernelBuf;

  if (limit > 0)
  {
    kernelBuf = assignBuffer(limit);
    if (kernelBuf == NULL)
      return NULL;
    for (; i < limit; i++)
    {
      kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
      kernelBuf[i] = (char)oneChar;
    }
    kernelBuf[i] = '\0';
    return kernelBuf;
  }

  do
  {
    kernel->machine->ReadMem(virtAddr + length, 1, &oneChar);
    length++;
  } while (oneChar != 0);
  kernelBuf = assignBuffer(length);
  for (; i < length; i++)
  {
    kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
    kernelBuf[i] = (char)oneChar;
  }
  kernelBuf[i] = '\0';
  return kernelBuf;
}

/**
 * @brief Copy system memory to user memory
 *
 * @param int virtAddr
 * @param int len
 * @param char* buffer
 * @return int
 */
int System2User(int virtAddr, int len, char *buffer)
{
  if (len < 0)
    return -1;
  if (len == 0)
    return 0;

  int i = 0;
  int oneChar;
  do
  {
    oneChar = (int)buffer[i];
    kernel->machine->WriteMem(virtAddr + i, 1, oneChar);
    i++;
  } while (i < len);
  kernel->machine->WriteMem(virtAddr + i, 1, 0);
  return i;
}

void modifyReturnPoint()
{
  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

/**
 * Utility functions
 */

/**
 * declare functions that is defined in exception.cc
 */
void handleSC_Halt();
void handleSC_Add();
void handleSC_Create();
void modifyReturnPoint();
void handleSC_ReadNum();
void handleSC_PrintNum();
void handleSC_ReadChar();
void handleSC_PrintChar();
void handleSC_RandomNum();
void handleSC_ReadString();
void handleSC_PrintString();
void handleSC_Open();
void handleSC_Close();
void handleSC_Remove();
void handleSC_Read();
void handleSC_Write();
void handleSC_Seek();
/**
 * declare functions that is defined in exception.cc
 */

#endif /* ! __USERPROG_KSYSCALL_H__ */
