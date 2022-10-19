#include"ImplementStackByList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


// 优点：堆栈的链表实现可以根据运行时的需要增长和缩小。 
// 缺点：由于涉及指针，需要额外的内存。

int main()
{
    Stack* root = NULL;
 
    push(&root, '1');
    push(&root, '2');
    push(&root, '3');
 
    printf("%c popped from stack\n", Pop(&root));
 
    printf("Top element is %c\n", Peek(root));
 
    return 0;
}






