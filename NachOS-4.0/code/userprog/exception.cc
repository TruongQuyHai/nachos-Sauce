// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
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

// Modify return point
void ModifyReturnPoint()
{
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

// Convert user string to system string
char *convertStringUserToSystem(int address, int max_length = -1)
{
	char *str;
	int length = 0;
	bool end = false;

	do
	{
		int character;
		kernel->machine->ReadMem(address + length, 1, &character);
		length++;
		end = ((character == '\0' && max_length == -1) || length == max_length);
	} while (!end);

	str = new char[length];
	for (int i = 0; i < length; i++)
	{
		int character;
		kernel->machine->ReadMem(address + i, 1, &character);
		str[i] = (unsigned char)character;
	}
	return str;
}

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	// no exception: return control to the operating system
	case NoException:
	{
		kernel->interrupt->setStatus(SystemMode);
		DEBUG(dbgSys, "Change to system mode.\n");
		break;
	}

	// syscall exceptions: user system calls
	case SyscallException:
	{
		switch (type)
		{
		case SC_Halt:
		{
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");
			SysHalt();
			ASSERTNOTREACHED();
			break;
		}

		case SC_Add:
		{
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			int result;
			result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
							/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << result << "\n");

			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)result);

			ModifyReturnPoint();
			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_ReadNum:
		{
			int result = ReadNumSys();
			kernel->machine->WriteRegister(2, result);

			ModifyReturnPoint();
			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_PrintNum:
		{
			int number = kernel->machine->ReadRegister(4);
			PrintNumSys(number);

			ModifyReturnPoint();
			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_PrintChar:
		{
			char character = kernel->machine->ReadRegister(4);
			PrintCharSys(character);

			ModifyReturnPoint();
			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_PrintString:
		{
			int memPtr = kernel->machine->ReadRegister(4);
			char *buffer = convertStringUserToSystem(memPtr);
			PrintStringSys(buffer, strlen(buffer));
			delete[] buffer;

			ModifyReturnPoint();
			return;
			ASSERTNOTREACHED();
			break;
		}

		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	}

	// other exceptions: print error and halt
	case PageFaultException:
	case ReadOnlyException:
	case BusErrorException:
	case AddressErrorException:
	case OverflowException:
	case IllegalInstrException:
	case NumExceptionTypes:
	{
		cerr << "Error: " << which << ".\n";
		SysHalt();
		ASSERTNOTREACHED();
	}

	default:
	{
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	}

	ASSERTNOTREACHED();
}
