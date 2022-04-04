#include "syscall.h"

#define MODE_READ 1
#define MAX_LENGTH 32

int main()
{
    char buffer[100];
    int i;
    int write;
    int fileid;
    int filesize;
    int filenameLength;
    char c;

    PrintString("Nhập chiều dài của tên file: ");
    filenameLength = ReadNum();

    PrintString("Nhập tên file cần đọc\n");
    ReadString(buffer, filenameLength);

    fileid = Open("some.txt", 1); // Goi ham Open de mo file
    if (fileid == -1)
    {
        PrintString("No file to show\n");
        Halt();
    }
    filesize = Seek(-1, fileid);
    Seek(0, fileid);

    PrintString("File content: ");
    i = 0;
    for (; i < filesize; i++) // Cho vong lap chay tu 0 - filesize
    {
        Read(&c, 1, fileid); // Goi ham Read de doc tung ki tu noi dung file
        PrintChar(c);        // Goi ham PrintChar de in tung ki tu ra man hinh
    }
    PrintChar('\n');
    Close(fileid); // Goi ham Close de dong file
    Halt();
}
