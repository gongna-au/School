#include <stdio.h>
#include <stdlib.h>
#include"InsertionSort.h"
/* Driver program to test insertion sort */
int main()
{
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    BinaryInsertionSort(arr, n);
    PrintArray(arr, n);
 
    return 0;
}