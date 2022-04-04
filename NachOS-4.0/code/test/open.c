#include "syscall.h"

int main()
{
    int result;

    result = Open("some.txt", 1);
    PrintNum(result);
    PrintChar('\n');
    Halt();
    /* not reached */
}
