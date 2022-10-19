#include <stdio.h>
#include <stdlib.h>
#include "main.h"
void PrintInputA(){
    printf("---------------------InputA----------------\n");
}
void PrintInputB(){
    printf("---------------------InputB----------------\n");
}
void PrintNum(int num){
    printf("num = %d\n",num);

}
void PrintElem(){
    printf("elem = ");
}
void PrintArray(int arr[],int num){
    for (int i=0;i<num;i++){
        printf("%-4d",arr[i]);
    }
    printf("\n");
}

void SetValue(int arr[],int num){
    printf("elem= ");
    for(int i=0;i<num;i++){
        scanf("%d",&arr[i]);
    }
}

void PrintResult(){
    printf("\n---------------------Result----------------\n"); 

}

void PrintEnd(char arr[]){
    printf("%s =  ",arr);
}







int main(){

    PrintInputA();

    printf("num= ");
    int numA;
    scanf("%d",&numA);
    int arrayA[numA];
    SetValue(arrayA,numA);

    printf("num= ");
    int numB;
    scanf("%d",&numB);
    int arrayB[numB];
    SetValue(arrayB,numB);

    /* 从空列表开始 */
    Node* headA= NULL;
    Node* headB= NULL;
    Node* headC= NULL;
    Node* headD= NULL;
    Node* headE= NULL;
    Node* headF= NULL;




    for(int i=0;i<numA;i++){
        push(&headA, arrayA[i]);
    }
    for(int i=0;i<numB;i++){
        push(&headB, arrayB[i]);
    }
    puts("Linked List Has Created");

    

    PrintNum(numA);
    PrintElem();
    PrintList(headA);

    PrintNum(numB);
    PrintElem();
    PrintList(headB);


    PrintResult();
    char strA[2]="A";
    char strB[2]="B";
    char strAB1[4]="AUB";
    char strAB2[4]="A*B";
    char strAB3[4]="A-B";
    char strAB4[4]="B-A";
    PrintEnd(strA);
    PrintList(headA);

    PrintEnd(strB);
    PrintList(headB);

    PrintEnd(strAB1);
    Merge(headA,headB,&headC);
    PrintList(headC);


    PrintEnd(strAB2);
    FindDuplicates(headA,headB,&headD);
    PrintList(headD);
    
    PrintEnd(strAB3);
    SetSubtraction(headA,headB,&headE);
    PrintList(headE);

    PrintEnd(strAB4);
    SetSubtraction(headB,headA,&headF);
    PrintList(headF);

}