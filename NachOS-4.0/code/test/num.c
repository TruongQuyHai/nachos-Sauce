/**
 * @file num.c
 * @author Team Nachos - Sauce
 * @brief A file to test ReadNum and PrintNum syscalls
 * @date 2022-05-05
 */

#include "syscall.h"

int main()
{
    int num = ReadNum();
    PrintNum(num);
    PrintChar('\n');
    PrintNum(RandomNum());
    PrintChar('\n');
    Halt();
}