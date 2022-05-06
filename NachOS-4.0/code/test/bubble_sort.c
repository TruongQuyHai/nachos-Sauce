/**
 * @file bubble_sort.c
 * @author Team Nachos - Sauce
 * @brief Input the array length, sort order, and the array itself
 *         Output the sorted array with the specified sort order
 * @date 2022-05-05
 */

#include "syscall.h"
#define MAX_ARR_LENGTH 100

void printTest(int j, int arr[])
{
  PrintString("arr[");
  PrintNum(j);
  PrintString("] = ");
  PrintNum(arr[j]);
  PrintString("\n");
}

int main()
{
  int i, j, n, temp, order, cond;
  int arr[MAX_ARR_LENGTH];

  PrintString("Please input the length of the array (length <= 100): ");
  do
  {
    n = ReadNum();
    // if the input is wrong, force user to input again
    if (n <= 0 || n > MAX_ARR_LENGTH)
    {
      PrintString("Wrong input, please try again (0 <= n <= ");
      PrintNum(MAX_ARR_LENGTH);
      PrintString("): ");
    }
  } while (n <= 0 || n > 100);

  PrintString("Choose sort order (1: increasing, 2: decreasing): ");
  do
  {
    order = ReadNum();
    // if the input is wrong, force user to input again
    if (order != 1 && order != 2)
    {
      PrintString("Wrong input, please try again (1 or 2): ");
    }
  } while (order != 1 && order != 2);

  // Input the array by ReadNum syscall
  for (i = 0; i < n; i++)
  {
    PrintString("a[");
    PrintNum(i);
    PrintString("] = ");
    arr[i] = ReadNum();
  }

  // bubble sort with condition
  for (i = n - 1; i > 0; i--)
  {
    for (j = 0; j < i; j++)
    {
      cond = (order == 1 && arr[j] > arr[j + 1]) || (order == 2 && arr[j] < arr[j + 1]);
      if (cond)
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  PrintString("Sorted array: ");
  for (i = 0; i < n; i++)
  {
    PrintNum(arr[i]);
    PrintString(" ");
  }
  PrintString("\n");

  Halt();
}