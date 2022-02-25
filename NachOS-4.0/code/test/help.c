#include "syscall.h"

int main()
{
    // use PrintString function to print the introduction of the group, ascii, and sorting program
    PrintString("CS333 - 19CTT2 - SAUCE\n\n");

    PrintString("Team members:\n");
    PrintString(">>> 19125063 - Châu Hữu Phát\n");
    PrintString(">>> 19125090 - Trương Quý Hải\n");
    PrintString(">>> 19125119 - Trương Lăng Trường Sơn\n\n");

    PrintString("ASCII table:\n");
    PrintString(">>> ../NachOS-4.0/code/test$ make ascii_prog\n");
    PrintString(">>> ../NachOS-4.0/code/test$ ../build.linux/nachos -x ascii_prog\n\n");

    PrintString("Sort (bubble sort):\n");
    PrintString(">>> ../NachOS-4.0/code/test$ make bubble_sort\n");
    PrintString(">>> ../NachOS-4.0/code/test$ ../build.linux/nachos -x bubble_sort\n\n");

    Halt();
}