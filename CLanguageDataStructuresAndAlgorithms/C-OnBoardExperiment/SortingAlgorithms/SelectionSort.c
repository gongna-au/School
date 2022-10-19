#include "SelectionSort.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    selectionSort(arr, n);
    printf("Sorted array: \n");
    PrintArray(arr, n);
    return 0;
}