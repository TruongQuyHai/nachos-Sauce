#include "syscall.h"

#define MODE_READWRITE 0
#define MODE_READ 1
#define MODE_WRITE 2

int main()
{
    char c;
    char fileName1[100];
    char fileName2[100];
    char fileName3[100];
    char buffer[500];
    int filenameLength;
    int fileid;
    int filesize;
    int i;
    int j;
    PrintString("Nhập chiều dài của tên file 1: ");
    filenameLength = ReadNum();

    PrintString("Nhập tên file cần đọc\n");
    ReadString(fileName1, filenameLength);

    fileid = Open(fileName1, MODE_READ);
    if (fileid == -1)
    {
        PrintString("Error reading file: ");
        PrintString(fileName1);
        Halt();
    }

    filesize = Seek(-1, fileid);
    Seek(0, fileid);

    i = 0;
    for (; i < filesize; i++)
    {
        Read(&c, 1, fileid);
        buffer[i] = c;
    }

    Close(fileid);

    PrintString("Nhập chiều dài của tên file 2: ");
    filenameLength = ReadNum();

    PrintString("Nhập tên file cần nối: ");
    ReadString(fileName2, filenameLength);

    fileid = Open(fileName2, MODE_READ);
    if (fileid == -1)
    {
        PrintString("Error reading file: ");
        PrintString(fileName2);
        Halt();
    }
    filesize = Seek(-1, fileid);
    Seek(0, fileid);

    j = 0;
    for (; j < filesize; j++)
    {
        Read(&c, 1, fileid);
        buffer[i + j] = c;
    }
    Close(fileid);

    PrintString("Nhập chiều dài của tên file 3: ");
    filenameLength = ReadNum();

    PrintString("Nhập tên file cần output: ");
    ReadString(fileName3, filenameLength);

    fileid = Open(fileName3, MODE_READWRITE);
    if (fileid == -1)
    {
        if (Create(fileName3) == -1) // try to create file
        {
            PrintString("Error reading and creating file: ");
            PrintString(fileName3);
            PrintString("\n");
            Halt();
        }
    }

    Write(buffer, i + j, fileid);

    Close(fileid);

    Halt();
}
