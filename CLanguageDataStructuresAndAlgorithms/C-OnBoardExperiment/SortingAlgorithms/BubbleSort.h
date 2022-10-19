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
    int  swapped;
    for(int i=0;i<size-1;i++){
        swapped=false;
        for(int j=0;j<size-i-1;j++){
            if(arr[j]>arr[j+1]){
                swapped = true;
                swap(&arr[j],&arr[j+1]);
            }
        }
        if(swapped==false){
            break;
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
