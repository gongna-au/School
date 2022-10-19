#include <stdio.h>
#include <stdlib.h>


void PrintArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){

        printf("%-4d",arr[i]);
    }
    printf("\n");

}

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int max=arr[0];
    for(int i=1;i<n;i++){
        if(arr[i]>max){
            max=arr[i];
        }
    }
    return max;
}


 
void CountSort(int arr[], int n, int exp){
    int output[n]; // output array
    int i, count[10] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
// The main function to that sorts arr[] of size n using
// Radix Sort
void RadixSort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    // 找到最大数字以知道位数
    int m = getMax(arr, n);
 
    // Do counting sort for every digit.
    // Note that instead of passing digit number, exp is passed. exp is 10^i
    // 请注意，不是传递数字，而是传递 exp。 exp 是 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        CountSort(arr, n, exp);
}


