#include <stdio.h>
#include <stdlib.h>
#include"QuickSort.h"
/* Driver program to test insertion sort */
// Driver Code
int main() 
{ 
    int arr[] = {10, 7, 8, 9, 1, 5}; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    QuickSort(arr, 0, n - 1); 
    printf("Sorted array: \n"); 
    PrintArray(arr, n); 
    return 0; 
}