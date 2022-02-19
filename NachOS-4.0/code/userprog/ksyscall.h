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

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')

#define MAX_NUM_LENGTH 11
char numBuffer[MAX_NUM_LENGTH + 2];

bool isBlank(char c) { return c == LF || c == CR || c == TAB || c == SPACE; }

int ReadNumFromConsole()
{
  memset(numBuffer, '\0', sizeof(numBuffer));
  char c = kernel->synchConsoleIn->GetChar();

  if (c == EOF)
  {
    DEBUG(dbgSys, "Number expected but end of file found.\n");
    return 0;
  }

  if (isBlank(c))
  {
    DEBUG(dbgSys, "Number expected but white-space found.\n");
    return 0;
  }

  int i = 0;
  while (!(isBlank(c)) || c == EOF)
  {
    numBuffer[i++] = c;
    if (i == 1 && c == '-')
    {
      continue;
    }
    else if (i > 1 && c == '-')
    {
      DEBUG(dbgSys, "Unexpected '-' sign");
      return 0;
    }
    else if (((int)c < (int)'0') || ((int)c > (int)'9'))
    {
      DEBUG(dbgSys, "Number expected!!!");
      return 0;
    }
    else if (i > MAX_NUM_LENGTH)
    {
      DEBUG(dbgSys, "Number is too long");
      return 0;
    }
    c = kernel->synchConsoleIn->GetChar();
  }
  return 1;
}

int ReadNumSys()
{
  if (ReadNumFromConsole() == 0)
  {
    return 0;
  }
  if (strcmp(numBuffer, "-2147483648") == 0)
  {
    return INT32_MIN;
  }
  int num = 0;
  bool isNegative = numBuffer[0] == '-';
  if (!isNegative)
  {
    num = numBuffer[0] - '0';
  }
  for (int i = 1; i < (int)strlen(numBuffer); i++)
  {
    num = num * 10 + (numBuffer[i] - '0');
  }
  if (isNegative)
  {
    num = -num;
  }

  if ((isNegative && num > 0) || (!isNegative && num < 0))
  {
    DEBUG(dbgSys, "INT32 expected, " << numBuffer << " found");
    return 0;
  }

  int numTemp = isNegative ? -num : num;
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

void PrintNumSys(int number)
{
  if (number == 0)
  {
    kernel->synchConsoleOut->PutChar('0');
    kernel->synchConsoleOut->PutChar('\n');
    return;
  }
  if (number == INT32_MIN)
  {
    for (int i = 0; i < 10; i++)
    {
      kernel->synchConsoleOut->PutChar("2147483648\n"[i]);
    }
    kernel->synchConsoleOut->PutChar('\n');
    return;
  }

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

  for (int j = i - 1; j >= 0; j--)
  {
    kernel->synchConsoleOut->PutChar(numBuffer[j]);
  }
  kernel->synchConsoleOut->PutChar('\n');
}

void PrintCharSys(char character)
{
  kernel->synchConsoleOut->PutChar(character);
}

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
