#include <stdio.h>
#include <stdlib.h>
#include"MergeSort.h"

int main(){
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Given array is \n");
    PrintArray(arr, n);

    
    MergeSort(arr, 0,n-1);
    printf("\nSorted array is \n");
    PrintArray(arr, n);
 
    return 0;
}