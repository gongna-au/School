#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedListImplementation.h"
/* Driver of the program */
void PrintYanghuiTriangle(Queue* q){
    int input;

    printf("Please input a number:");
    scanf("%d",&input);
    input=input+1;
    
    int tag = 2*input-1;
    int mid = (tag+1)/2;
    enQueue(q,0);
    enQueue(q,1);
    enQueue(q,0);
    for (int i=1;i<=input;i++){
        int elem1;
        int elem2;
        int k;
        //打印空格数
        for(k=0;k<mid-i;k++){
            printf(" ");
        }
        //每次打出一个数字后紧紧跟着一个空格
        for(int j=1;j<i+2;j++){
             elem1 =deQueue(q);
             
             if(elem1!=0){
                printf("%d",elem1);
                printf(" "); 
             }
             elem2=getHead(q);
             enQueue(q,elem1+elem2);
        }
        enQueue(q,0);
        printf("\n");
    }


}



int main()
{
    Queue* q=initializeQueue();
    PrintYanghuiTriangle(q);
    // Inserting elements in Circular Queue
    //enQueue(q, 14);
    //enQueue(q, 22);
    //enQueue(q, 6);
  
    // Display elements present in Circular Queue
    //displayQueue(q);
  
    // Deleting elements from Circular Queue
    //printf("\nDeleted value = %d", deQueue(q));
    //printf("\nDeleted value = %d", deQueue(q));
  
    // Remaining elements in Circular Queue
    displayQueue(q);
  
    enQueue(q, 9);
    enQueue(q, 20);
    displayQueue(q);
  
    return 0;
}