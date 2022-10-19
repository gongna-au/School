#include <stdio.h>
#include <stdlib.h>
#include"CountingSort.h"
/* Driver program to test insertion sort */

// Driver program to test above function
int main()
{
    int arr[] = {40, 12, 45, 32, 33, 1, 22};
	int n = sizeof(arr)/sizeof(arr[0]);
    printf("Given array is n\n");
    PrintArray(arr, n);
    sort(arr, n);

    printf("Sorted array is n\n");
    PrintArray(arr, n);


    return 0;
}