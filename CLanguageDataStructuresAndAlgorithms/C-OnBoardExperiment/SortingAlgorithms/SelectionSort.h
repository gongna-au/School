#include <stdio.h>
// 排序算法用于根据元素上的比较运算符重新排列给定的数组或列表元素。
// 比较运算符用于决定相应数据结构中元素的新顺序
// 选择排序算法通过从未排序部分重复查找最小元素（考虑升序）并将其放在开头来对数组进行排序。该算法在给定数组中维护两个子数组。
// 选择排序
void swap(int *elem1,int* elem2){
    int temp=*elem1;
    *elem1=*elem2;
    *elem2=temp;
}



void selectionSort(int arr[] ,int n){
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i=0;i<n-1;i++){
        // Find the minimum element in unsorted array
        min_idx = i;
        for(j=i+1;j<n;j++){
            if(arr[j]< arr[min_idx]){
                min_idx=j;
            }
        }
        swap(&arr[min_idx],&arr[i]);
    }
}

void PrintArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){

        printf("%-4d",arr[i]);
    }
    printf("\n");

}