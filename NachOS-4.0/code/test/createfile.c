/**
 * @file createfile.c
 * @author Team Nachos - Sauce
 * @brief Test Create file syscall
 * @date 2022-05-05
 */

#include "syscall.h"
#define maxlen 32

int main()
{
    char buffer[maxlen];
    PrintString("Input your filename you want to create: ");
    ReadString(buffer, maxlen);

    if (Create(buffer) == -1)
    {
        PrintString("Error occured when creating text.txt\n");
    }
    else
    {
        PrintString("Created text.txt successfully\n");
    }

    Halt();
}