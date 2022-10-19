#include <stdio.h>
#include <stdlib.h>

void PrintArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){

        printf("%-4d",arr[i]);
    }
    printf("\n");

}

void swap(int* xp,int *yp){
    int temp;
    temp=*xp;
    *xp=*yp;
    *yp=temp;
}

int partition(int arr[],int low,int high) {
    // 用i来追踪比枢轴小的元素的下标
    // 也就是说，i所指的地方一定放的是小的元素
    // j追踪要放的小的元素
    int pivot=arr[high];
    int i=low-1;
    int j;
    for (j=low;j<=high-1;j++){
        if (arr[j]<pivot){
            //发现一个小的元素
            i++;
            //在交换的时候，arr[i]肯定是较大的元素，自然而然被移到后面
            swap(&arr[j],&arr[i]);
        }
    }
    // in the end the i+1 location is pivot location
    swap(&arr[high],&arr[i+1]);
    return (i+1);

}

void QuickSort(int arr[],int low,int high){
    int pi;
    if(low<high){

        pi=partition(arr,low,high);
        QuickSort(arr,low,pi-1);
        QuickSort(arr,pi+1,high);
    }
}
