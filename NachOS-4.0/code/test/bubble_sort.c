#include "syscall.h"
#define MAX_SIZE (100)

int main()
{
    // declare variables
    int n, array[MAX_SIZE + 1], order, temp, i, j;

    // get the size of the array from user
    do
    {
        PrintString("Please input the size of the array (0 <= n <= 100): ");
        n = ReadNum();
        // if the input is out of range, force user to input again
        if (n < 0 || n > 100)
        {
            PrintString("Wrong input, please try again (0 <= n <= 100).\n");
        }
    } while (n < 0 || n > 100);
    // get each element in the array from user
    for (i = 0; i < n; i++)
    {
        PrintString("Array[");
        PrintNum(i);
        PrintString("] = ");
        array[i] = ReadNum();
    }
    // get the sorting order from user
    do
    {
        PrintString("Choose sort order (1: increasing, 2: decreasing): ");
        order = ReadNum();
        // if the input is wrong, force user to input again
        if (order != 1 && order != 2)
        {
            PrintString("Wrong input, please try again (1 or 2).\n");
        }
    } while (order != 1 && order != 2);

    // handle sorting array
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

    // display result
    PrintString(">>> Result: ");
    for (i = 0; i < n; i++)
    {
        PrintNum(array[i]);
        PrintChar(' ');
    }
    PrintString("\n\n");

    Halt();
}