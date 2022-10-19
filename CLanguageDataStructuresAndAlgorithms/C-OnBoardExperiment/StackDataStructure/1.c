#include "bag.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void knapsack(int W[],int T,int n ){
    
       Stack* stack = CreateStack(10);
        int  k=0;
    do {
            while(1){

                if(T-W[k]>=0 && k<n){
                    push(stack,k);
                    T=T-W[k] ;
                    k++;
                }else if(k==n){
                    break;
                }else if(T-W[k]<0){
                    break;
                }
            }
            // k==n
            // k为某个物品的下标，该物品放入会使得背包容量超标

            if(T==0){
                StackTraverse(stack,W);
            }else{
                int top= Pop(stack);
                //增大背包容量后，继续向后面考察
                //考察的前提是k<n
                T=T+W[k];
            }


    }while(k<n && (!IsEmpty(stack)));  
       
       

}