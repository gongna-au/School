#include <stdio.h>
#include <stdlib.h>

void PrintArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){

        printf("%-4d",arr[i]);
    }
    printf("\n");

}
// 合并 arr[] 的两个子数组。
// 第一个子数组是 arr[l..m]
// 第二个子数组是 arr[m+1..r]
void merge(int arr[],int l,int m,int r){
    /* create temp arrays */
    int n1=m-l+1;
    int n2=r-m;
    int L[n1];
    int R[n2];
    /* Copy data to temp arrays L[] and R[] */
    for(int i=0;i<n1;i++){
        L[i]=arr[l+i];
    }
    for(int j=0;j<n2;j++){
        R[j]=arr[m+1+j];
    }
     /* Merge the temp arrays back into arr[l..r]*/
   int  i = 0; // Initial index of first subarray
   int  j = 0; // Initial index of second subarray
   int  k = l; // Initial index of merged subarray

   while (i < n1 && j < n2) {
       if(L[i]<=R[j]){
           arr[k]=L[i];
           i++;
           //k++;
        }else{
           arr[k]=R[j];
           j++;
           // k++;
        }
        k++;
    }
    while(i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k]=R[j];
        j++;
        k++;
    }


}


void MergeSort(int arr[],int l, int r){
    int m;
    if(l<r){
        m=l+(r-l) /2 ;
        MergeSort(arr,l,m);
        MergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }

}

