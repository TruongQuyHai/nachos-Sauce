#include "syscall.h"

#define MAX_LENGTH 32

int main()
{
    char fileName[MAX_LENGTH];
    int filenameLength;

    PrintString("Nhập chiều dài của tên file: ");
    filenameLength = ReadNum();

    PrintString("Nhập tên file cần đọc\n");
    ReadString(fileName, filenameLength);
    if (Remove(fileName) == 0)
    {
        PrintString("Remove file successfully\n");
    }
    else
    {
        PrintString("failed to remove file\n");
    }
    Halt();
}
