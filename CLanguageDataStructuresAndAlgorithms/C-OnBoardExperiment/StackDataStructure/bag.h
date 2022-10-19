#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// There are two ways to implement a stack: 
// Using array
// Using linked list
// Implementing Stack using Arrays

struct StackStruct {
    int top;
    int capacity;
    int* array;
};

typedef struct StackStruct  Stack;


// function to create a stack of given capacity. 
// It initializes size of  stack as 0
Stack * CreateStack(unsigned capacity){
    Stack * stack =(Stack *)malloc(sizeof(Stack));
    stack->capacity=capacity;
    stack->top=-1;
    stack->array=(int *)malloc((stack->capacity)*sizeof(int));
    return stack;  
}

 
// Stack is full when top is equal to the last index
// Judge Stack is Full or not
bool  IsFull(Stack*  stack ){

    if (stack->top == stack->capacity-1){
        return true;
    }else{
        return false;
    }
}

// Judge Stack is empty or not
// Stack is full when top is equal to the last index
bool IsEmpty(Stack* stack){

    if(stack->top==-1){
        return true;
    }else{
        return false;
    }
} 

// Function to add an item to stack.  It increases top by 1
void push(Stack* stack, int item ){

    if(IsFull(stack)){
        return;
    }
    stack->top=stack->top+1;
    stack->array[stack->top]=item;
    //printf("%d is pushed to stack\n",item);
}


// Function to remove an item from stack.  It decreases top by 1
int Pop(Stack* stack){
    if(IsEmpty(stack)){
        return INT_MIN;
    }

    int item=stack->array[stack->top];
    stack->top=stack->top-1;
    return item;
}

// Function to return the top from stack without removing it
int Peek(Stack* stack){
    if(IsEmpty(stack)){
        return INT_MIN;
    }
    int item=stack->array[stack->top];
    return item;
}

void StackTraverse(Stack* stack,int W[]){
    
    int item=0;
    int index;
    int elem;
    printf("The object's index  are:\n");
    printf("<  ");
    for (int i=0;i<=stack->top;i++){
        index=stack->top-i;
        item=stack->array[index];
        
        printf("%-4d",item+1);
    }
    printf(">\n");
/*
    printf("The object's volumn are:\n");
    printf("<  ");
    for (int i=0;i<=stack->top;i++){
        index=stack->top-i;
        item=stack->array[index];
        elem=W[item];
        printf("%-4d",elem);
    }
    printf(">\n");
    */

     
}





