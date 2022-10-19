#include "ImplementStackByArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// There are two ways to implement a stack: 
// Using array
// Using linked list
// Implementing Stack using Arrays

// Driver program to test above functions
// 优点：易于实施。由于不涉及指针，因此节省了内存。 
// 缺点：它不是动态的。它不会根据运行时的需要增长和缩小
int main()
{
     Stack* stack = CreateStack(10);

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    StackTraverse(stack);
 
    printf("%d popped from stack\n", Pop(stack));
 
    return 0;
}