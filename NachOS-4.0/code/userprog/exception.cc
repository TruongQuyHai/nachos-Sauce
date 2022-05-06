// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
#include "synchconsole.h"

#define MaxFileLength 32
#define MaxIntBufferLength 12 // an int can hold 11 number and the '-' character
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler(ExceptionType which)
{
  int type = kernel->machine->ReadRegister(2);

  DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

  switch (which)
  {
  case NoException:
    return;
  case SyscallException:
    switch (type)
    {
    case SC_Halt:
    {
      handleSC_Halt();
    }
    case SC_Add:
    {
      handleSC_Add();
      modifyReturnPoint();
      return;
    }
    case SC_Create:
    {
      handleSC_Create();
      modifyReturnPoint();
      return;
    }
    case SC_ReadNum:
    {
      handleSC_ReadNum();
      modifyReturnPoint();
      return;
    }
    case SC_PrintNum:
    {
      handleSC_PrintNum();
      modifyReturnPoint();
      return;
    }
    case SC_ReadChar:
    {
      handleSC_ReadChar();
      modifyReturnPoint();
      return;
    }
    case SC_PrintChar:
    {
      handleSC_PrintChar();
      modifyReturnPoint();
      return;
    }
    case SC_RandomNum:
    {
      handleSC_RandomNum();
      modifyReturnPoint();
      return;
    }
    case SC_ReadString:
    {
      handleSC_ReadString();
      modifyReturnPoint();
      return;
    }
    case SC_PrintString:
    {
      handleSC_PrintString();
      modifyReturnPoint();
      return;
    }
    case SC_Open:
    {
      handleSC_Open();
      modifyReturnPoint();
      return;
    }
    case SC_Close:
    {
      handleSC_Close();
      modifyReturnPoint();
      return;
    }
    case SC_Remove:
    {
      handleSC_Remove();
      modifyReturnPoint();
      return;
    }
    case SC_Read:
    {
      handleSC_Read();
      modifyReturnPoint();
      return;
    }
    case SC_Write:
    {
      handleSC_Write();
      modifyReturnPoint();
      return;
    }
    case SC_Seek:
    {
      handleSC_Seek();
      modifyReturnPoint();
      return;
    }
    default:
    {
      cerr << "Unexpected system call " << type << "\n";
      handleSC_Halt();
    }
    }
  case PageFaultException:
  case ReadOnlyException:
  case BusErrorException:
  case AddressErrorException:
  case OverflowException:
  case IllegalInstrException:
  case NumExceptionTypes:
  {
    cerr << "Not implemented exceptions " << which << "\n";
    handleSC_Halt();
  }

  default:
  {
    cerr << "Unexpected user mode exception" << (int)which << "\n";
    break;
  }
  }
  ASSERTNOTREACHED();
}

void handleSC_Halt()
{
  DEBUG(dbgSys, "Shutdown, initiated by user program.\n");
  SysHalt();
  ASSERTNOTREACHED();
}

void handleSC_Add()
{
  DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

  int result;
  result = SysAdd((int)kernel->machine->ReadRegister(4),
                  (int)kernel->machine->ReadRegister(5));

  DEBUG(dbgSys, "Add returning with " << result << "\n");

  kernel->machine->WriteRegister(2, (int)result);
}

// TODO: handle case file already exists
void handleSC_Create()
{
  int virtAddr;
  char *filename;

  // get the virtAddr and convert it to filename (char *)
  virtAddr = kernel->machine->ReadRegister(4);
  filename = User2System(virtAddr, MaxFileLength);
  DEBUG(dbgSys, "Inputted file name: " << filename);

  // If the filename is empty => return error
  if (isEmptyString(filename))
  {
    kernel->machine->WriteRegister(2, -1);
    modifyReturnPoint();
    delete[] filename;
    return;
  }

  DEBUG(dbgSys, "Creating file: " << filename);
  // If Create return false => error
  if (!kernel->fileSystem->Create(filename, 0))
  {
    kernel->machine->WriteRegister(2, -1);
    modifyReturnPoint();
    delete[] filename;
    return;
  }

  DEBUG(dbgSys, "Create file successfully");
  kernel->machine->WriteRegister(2, 0);
  delete[] filename;
}

/**
 * @brief read console till enter or limit
 * @param limit
 * @return char*
 */
char *readConsoleTillLimit(int limit)
{
  char c;
  char *buffer = assignBuffer(limit);
  int cnt = 0;

  do
  {
    if (cnt >= limit)
      return NULL;
    c = kernel->synchConsoleIn->GetChar();
    buffer[cnt++] = c;
  } while (!isEnter(c));

  buffer[cnt - 1] = '\0';
  return buffer;
}

/**
 * @brief Read number from console
 * @return int or 0 if invalid
 */
int readNumFromConsole()
{
  int result = 0;
  bool _isNegative;

  // read the string user input until find enter key or till limit
  char *numBuffer = readConsoleTillLimit(MaxIntBufferLength);
  if (isEmptyString(numBuffer))
    return 0;

  // check if the inputted number buffer is negative
  _isNegative = isNegative(numBuffer);

  int i = (int)_isNegative;

  // check for special case
  if (isIntMin(numBuffer))
    return -2147483648;

  for (; i < strlen(numBuffer); i++)
  {
    // if there is any character that is not a number => error
    if (isNotNumber(numBuffer[i]))
    {
      cerr << "Please input number only\n";
      return 0;
    }
    // otherwise accumulate the result
    result = result * 10 + (int)(numBuffer[i] - '0');
  }

  // if is negative the revert result
  if (_isNegative)
    result = -result;

  // if number buffer != the number itself => overflow or underflow => error
  if (!isStringTheSameWithNumber(numBuffer, _isNegative, result))
  {
    cerr << "Int overflow / underflow \n";
    return 0;
  }

  delete[] numBuffer;

  return result;
}

void handleSC_ReadNum()
{
  int num = readNumFromConsole();
  kernel->machine->WriteRegister(2, num);
}

void handleSC_PrintNum()
{
  int i;
  int temp;
  int cnt = 0;
  bool _isNegative;
  int number = kernel->machine->ReadRegister(4);
  char *buffer = assignBuffer(MaxIntBufferLength);

  // special case for 0
  if (number == 0)
  {
    kernel->synchConsoleOut->PutChar('0');
    delete[] buffer;
    return;
  }

  _isNegative = isNegative(number);
  if (_isNegative)
    number = -number;

  for (; number != 0; number /= 10)
  {
    temp = number % 10;
    buffer[cnt++] = '0' + temp; // Create the reverse buffer
  }

  if (_isNegative)
    kernel->synchConsoleOut->PutChar('-');

  // print buffer in reverse order
  for (i = cnt - 1; i >= 0; i--)
  {
    kernel->synchConsoleOut->PutChar(buffer[i]);
  }

  delete[] buffer;
}

void handleSC_ReadChar()
{
  char c = kernel->synchConsoleIn->GetChar();
  kernel->machine->WriteRegister(2, c);
}

void handleSC_PrintChar()
{
  char c = (char)kernel->machine->ReadRegister(4);
  kernel->synchConsoleOut->PutChar(c);
}

void handleSC_RandomNum()
{
  kernel->machine->WriteRegister(2, RandomNumber());
}

void handleSC_ReadString()
{
  int virtAddr = kernel->machine->ReadRegister(4);
  int length = kernel->machine->ReadRegister(5);
  int i = 0, returnLength;
  char c;
  char *buffer = assignBuffer(length);

  do
  {
    c = kernel->synchConsoleIn->GetChar();
    if (isEnter(c))
      break;
    buffer[i++] = c;
  } while (i < length);
  buffer[i] = '\0'; // end buffer with terminated character

  System2User(virtAddr, length, buffer);
  delete[] buffer;
}

void handleSC_PrintString()
{
  int i;
  int virtAddr = kernel->machine->ReadRegister(4);
  char *buffer = User2System(virtAddr);

  for (i = 0; i < strlen(buffer); i++)
    kernel->synchConsoleOut->PutChar(buffer[i]);

  delete[] buffer;
}

void handleSC_Open()
{
  int virtualAddr;
  char *filename;

  virtualAddr = kernel->machine->ReadRegister(4);
  filename = User2System(virtualAddr, MaxFileLength);

  OpenFileId id = kernel->fileSystem->OpenF(filename);
  // return the result to user, user need to check for case error id = -1
  kernel->machine->WriteRegister(2, id);
}

void handleSC_Close()
{
  int openFileID = kernel->machine->ReadRegister(4);
  // user need to check for case error status = -1
  kernel->machine->WriteRegister(2, kernel->fileSystem->Close(openFileID));
}

void handleSC_Remove()
{
  int virtualAddr = kernel->machine->ReadRegister(4);
  char *name = User2System(virtualAddr);
  if (kernel->fileSystem->Remove(name)) // remove successfully
  {
    kernel->machine->WriteRegister(2, 0);
  }
  else
  {
    kernel->machine->WriteRegister(2, -1);
  }

  delete[] name;
}

void handleSC_Read()
{
  int virtualAddr = kernel->machine->ReadRegister(4);
  int size = kernel->machine->ReadRegister(5);
  OpenFileId id = kernel->machine->ReadRegister(6);
  OpenFile *file = kernel->fileSystem->GetOpenFile(id);

  // file not found & can not read from the stdout
  if (file == NULL || id == _ConsoleOutput)
  {
    kernel->machine->WriteRegister(2, -1);
    return;
  }

  char *buffer = assignBuffer(size);

  if (buffer == NULL) // can not allocate memory for the buffer
  {
    kernel->machine->WriteRegister(2, -1);
    return;
  }

  // if read from stdin, then wait for user input
  if (id == _ConsoleInput)
    size = kernel->synchConsoleIn->Read(buffer, size);
  // else read the file
  else
    size = file->Read(buffer, size);

  System2User(virtualAddr, size, buffer);
  // return the size of the file
  kernel->machine->WriteRegister(2, size);
  delete[] buffer;
}

void handleSC_Write()
{
  int virtualAddr = kernel->machine->ReadRegister(4);
  int size = kernel->machine->ReadRegister(5);
  OpenFileId id = kernel->machine->ReadRegister(6);
  OpenFile *file = kernel->fileSystem->GetOpenFile(id);

  // file not found and can not write to stdin
  if (file == NULL || id == _ConsoleInput)
  {
    kernel->machine->WriteRegister(2, -1);
    return;
  }

  char *buffer = User2System(virtualAddr, size);

  if (buffer == NULL)
  {
    kernel->machine->WriteRegister(2, -1);
    return;
  }

  // if write to stdout -> use synchConsoleOut->Write
  if (id == _ConsoleOutput)
    size = kernel->synchConsoleOut->Write(buffer, size);
  // else write to the file
  else
    size = file->Write(buffer, size);

  kernel->machine->WriteRegister(2, size);
  delete[] buffer;
}

void handleSC_Seek()
{
  int position = kernel->machine->ReadRegister(4);
  OpenFileId id = kernel->machine->ReadRegister(5);
  OpenFile *file = kernel->fileSystem->GetOpenFile(id);

  // can not find the file, or seek in console, or position is over the length of the file
  if (file == NULL || id == _ConsoleInput || id == _ConsoleOutput || position > file->Length())
  {
    kernel->machine->WriteRegister(2, -1);
    return;
  }

  if (position == -1) // seek to the end of the file
    position = file->Length();

  file->Seek(position);
  kernel->machine->WriteRegister(2, position);
}