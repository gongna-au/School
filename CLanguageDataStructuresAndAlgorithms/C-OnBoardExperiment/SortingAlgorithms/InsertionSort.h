#include <stdio.h>
#include <stdlib.h>

void PrintArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){

        printf("%-4d",arr[i]);
    }
    printf("\n");

}
// 插入排序是一种简单的排序算法，
// 该数组实际上分为已排序和未排序部分。
// 未排序部分的值被拾取并放置在排序部分中的正确位置
/* Function to sort an array using insertion sort*/
void InsertionSort(int arr[], int n){
    int i, key,j;
    for(i=1;i<n;i++){
        key=arr[i];
        j=i-1;
        while (j>=0 && arr[j]>key)
        {
            arr[j+1]=arr[j];
            j=j-1;
        }
        //j因为减小了一，所以要插入的位置为j+1
        arr[j+1]=key;
    }
}

// 二分查找
int BinarySearch(int a[], int item,int low, int high){
    if (high <= low)
        return (item > a[low]) ?(low + 1) : low;
 
    int mid = (low + high) / 2;
 
    if (item == a[mid])
        return mid + 1;
 
    if (item > a[mid]){
        return BinarySearch(a, item, mid + 1, high);
    }else{
        return BinarySearch(a, item, low, mid - 1);
    }
        
    
}
// 二分查找
int binarySearch(int arr[], int item, int low, int high)
{
    while(low<=high){
       int mid =(low+high)/2;
       if(arr[mid]==item){
           return mid+1;
       }else if(arr[mid]<item){
            low=mid+1;
        }else{
            high=mid-1;
        }
    }
    return low;
}
 
// 我们可以使用二分查找来减少普通插入排序中的比较次数。二分插入排序使用二分搜索来找到在每次迭代时插入所选项目的正确位置。 
void BinaryInsertionSort(int arr[], int n){
    int j;
    int selected;
    int location;
    for(int i=1;i<n;i++){
        j=i-1;
        selected= arr[i];
        location =BinarySearch(arr,selected,0,j);
        while(j>=location){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=selected;
    }
}


