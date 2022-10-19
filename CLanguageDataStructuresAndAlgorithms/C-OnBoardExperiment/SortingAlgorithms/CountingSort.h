#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  RANGE 10
// 计数排序是一种基于特定范围之间的键的排序技术。
// 它的工作原理是计算具有不同键值（散列类型）的对象数量。
// 然后做一些算术运算来计算每个对象在输出序列中的位置。
// 输入数据：1, 4, 1, 2, 7, 5, 2
// 1) 取一个计数数组来存储每个唯一对象的计数。
// 索引：0 1 2 3 4 5 6 7 8 9
// 计数：0 2 2 0 1 1 0 1 0 0 
// 2) 修改计数数组，使每个索引处的每个元素
// 存储先前计数的总和。
// 索引：0 1 2 3 4 5 6 7 8 9
// 计数：0 2 4 4 5 6 6 7 7 7
// 修改后的计数数组表示每个对象在
// 输出序列中的位置。
// A function to do counting sort of arr[] according to
// the digit represented by exp.



void CountSort(int arr[], int n, int exp){
    // output array
    int output[n];
    int i,count[n];
    for (int i=0; i < n; i++){
        count[i] = 0;
    }
    //Store count of occurrences in count[]
    for (i = 0; i < n; i++){
        count[ (arr[i]/exp)%n ]++;
    }
        
        
    // Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
    for (i = 1; i < n; i++){
        count[i] += count[i - 1];
    }

    // Build the output array
	for (i = n - 1; i >= 0; i--)
	{
		output[count[ (arr[i]/exp)%n] - 1] = arr[i];
		count[(arr[i]/exp)%n]--;
	}
	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
        
}

void sort(int arr[],int n){
    // Do counting sort for first digit in base n. Note that
    // instead of passing digit number, exp (n^0 = 1) is passed.
    CountSort(arr, n, 1);
 
    // Do counting sort for second digit in base n. Note that
    // instead of passing digit number, exp (n^1 = n) is passed.
    CountSort(arr, n, n);
}




void PrintArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){

        printf("%-4d",arr[i]);
    }
    printf("\n");

}