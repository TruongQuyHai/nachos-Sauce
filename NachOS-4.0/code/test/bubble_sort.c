#include "syscall.h"
#define MAX_SIZE (100)

int main()
{
    int n, array[MAX_SIZE + 1], order, temp, i, j;

    do
    {
        PrintString("Please input the size of the array (0 <= n <= 100): ");
        n = ReadNum();
        if (n < 0 || n > 100)
        {
            PrintString("Wrong input, please try again (0 <= n <= 100).\n");
        }
    } while (n < 0 || n > 100);

    for (i = 0; i < n; i++)
    {
        PrintString("Array[");
        PrintNum(i);
        PrintString("] = ");
        array[i] = ReadNum();
    }

    do
    {
        PrintString("Choose sort order (1: increasing, 2: decreasing): ");
        order = ReadNum();
        if (order != 1 && order != 2)
        {
            PrintString("Wrong input, please try again (1 or 2).\n");
        }
    } while (order != 1 && order != 2);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (order == 1)
            {
                if (array[j] > array[j + 1])
                {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
            else if (order == 2)
            {
                if (array[j] < array[j + 1])
                {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    PrintString(">>> Result: ");
    for (i = 0; i < n; i++)
    {
        PrintNum(array[i]);
        PrintChar(" ");
    }
    PrintChar(".\n");
}