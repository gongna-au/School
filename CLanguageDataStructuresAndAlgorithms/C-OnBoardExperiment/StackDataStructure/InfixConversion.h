#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

// There are two ways to implement a stack: 
// Using array
// Using linked list
// Implementing Stack using Arrays

struct StackStruct {
    int top;
    int capacity;
    char* array;
};

typedef struct StackStruct  Stack;


// function to create a stack of given capacity. 
// It initializes size of  stack as 0
Stack * CreateStack(unsigned capacity){
    Stack * stack =(Stack *)malloc(sizeof(Stack));
    stack->capacity=capacity;
    stack->top=-1;
    stack->array=(char *)malloc((stack->capacity)*sizeof(int));
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
void push(Stack* stack, char item ){

    if(IsFull(stack)){
        return;
    }
    stack->top=stack->top+1;
    stack->array[stack->top]=item;
    //printf("%d is pushed to stack\n",item);
}


// Function to remove an item from stack.  It decreases top by 1
char Pop(Stack* stack){
    if(IsEmpty(stack)){

        return ' ';
    }

    char item=stack->array[stack->top];
    stack->top=stack->top-1;
    return item;
}

// Function to return the top from stack without removing it
char Peek(Stack* stack){
    if(IsEmpty(stack)){
        return ' ';
    }
    char item=stack->array[stack->top];
    return item;
}







// A utility function to check if
// the given character is operand
bool isOperand(char ch)
{
   /*if (ch >= 'a' && ch <= 'z'){
        return true;
    }else if(ch >= 'A' && ch <= 'Z'){
        return true;
    }else{
        return false;
    }*/
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z');
}

// A utility function to return
// precedence of a given operator
// Higher returned value means
// higher precedence
int Prec(char ch){
    switch (ch)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;
        

    case '^':
        return 3;
        
    }
    return -1;
}


// The main function that
// converts given infix expression 中缀表达式
// to postfix expression.后缀表达式
int infixToPostfix(char* exp){
    Stack * stack=(Stack*)CreateStack(strlen(exp));
    if(stack==NULL){
      
        return -1;
    }
    int i=0;
    int k=-1;
    for(i,k;i<strlen(exp);i++){
        // If the scanned character is
        // an operand, add it to output.
        if(isOperand(exp[i])){
            exp[++k]=exp[i];
        // If the scanned character is an
        // ‘(‘, push it to the stack.
        }else if(exp[i]=='('){
            push(stack,exp[i]);
        }else if(exp[i]==')'){
            
            //ch = Peek(stack);
            while(!IsEmpty(stack) && Peek(stack)!='('){
                exp[++k]=Pop(stack);
            }
            if(!IsEmpty(stack)&& Peek(stack)=='('){
                Pop(stack);
            }else{
                // invalid expression
                return -1;
            }
        }else{
            char ch;

           while( Prec(exp[i]) <= Prec(Peek(stack)) &&  (!IsEmpty(stack)) ){
               
               exp[++k]=Pop(stack);
            }
            push(stack,exp[i]);
        }
    }
    while (!IsEmpty(stack))
    {
        exp[++k]=Pop(stack);

    }
    exp[++k] = '\0';
    printf( "%s", exp );

}

