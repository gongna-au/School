#include <stdio.h>
#include <stdlib.h>
#define  true 1
#define  false 0

void swap(int* xp,int *yp){
    int temp;
    temp=*xp;
    *xp=*yp;
    *yp=temp;
}
void BubbleSort(int arr[],int size){
   if (size=1){
       return;
   }

    for(int i=0;i<size-1;i++){
        if (arr[i]>arr[i+1]){
            swap(&arr[i],&arr[i+1]);
        }
        
    }
}
void PrintArray(int arr[],int size){
    int i;
    for(i=0;i<size;i++){

        printf("%-4d",arr[i]);
    }
    printf("\n");

}
