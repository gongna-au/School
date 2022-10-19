#include "BubbleSort.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    BubbleSort(arr, n);
    printf("Sorted array: \n");
    PrintArray(arr, n);
    return 0;
}


