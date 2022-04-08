#include "syscall.h"

int main()
{
    // PrintNum(Create("")); // should return -1
    // PrintChar('\n');
    PrintNum(Create("123")); // should return 0
    PrintChar('\n');
    Halt();
}