#include "bag.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void knapsack(int W[],int T,int n ){
    
       Stack* stack = CreateStack(10);
        int  k=0;
        do{
            while(T>0 && k<n){
                //每个物品都依次考虑能不能压入到栈里面
                //把能放进去的就压入到栈里面
                // 把下标入栈
                if(T-W[k]>=0){  
                    push(stack,k); 
                    T=T-W[k];  
                }
                k++;    
            }
            //所有能放进去的物品都放进去了，
            if(T==0){
                //如果刚刚等于背包容量，那么我们则根据下标得到数组中的元素
                StackTraverse(stack,W);
            }

                //否则我们弹出栈中最上面的一个元素
               k= Pop(stack);
               T+=W[k];
               //考察下一个物品
               k++; 
        }while((!IsEmpty(stack)) || k<n);
}

int main(){
    int N;
    int W[6]={0};
    int T;
    printf("Please input object num N=");
    scanf("%d",&N);
    printf("Please input every object volume：");
    for (int i=0;i<N;i++){
         printf("\nPlease input W[%d] object volume\nW[%d]=",i,i);
         scanf("%d",&W[i]);
    }
    printf("Please input the bag's volume T=");
    scanf("%d",&T);
    knapsack(W,T,N);

}
