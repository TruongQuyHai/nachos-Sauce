#include "syscall.h"

int main()
{
    PrintString("CS333 - 19CTT2 - SAUCE\n\n");

    PrintString("Team members:\n");
    PrintString(">>> 19125063 - Châu Hữu Phát\n");
    PrintString(">>> 19125090 - Trương Quý Hải\n");
    PrintString(">>> 19125119 - Trương Lăng Trường Sơn\n\n");

    PrintString("ASCII table:\n");
    PrintString(">>> build.linux/nachos -x test/ascii\n\n");

    PrintString("Sort (bubble sort):\n");
    PrintString(">>> build.linux/nachos -x test/bubble_sort\n");
    PrintString(">>> Input the size of the array (0 <= n <= 100).\n");
    PrintString(">>> Input elements of the array.\n");
    PrintString(">>> Choose sort order (1: increasing, 2: decreasing).\n");
}