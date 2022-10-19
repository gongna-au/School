#include "QuickSortSinglyList.h"
#include <stdio.h>
#include <stdlib.h>

// 函数功能：单向链表上的快速排序
int main()
{
    Node* a = NULL;
    push(&a, 5);
    push(&a, 20);
    push(&a, 4);
    push(&a, 3);
    push(&a, 30);
 
    printf("Linked List before sorting \n");
    PrintList(a);
 
    QuickSort(&a);
 
    printf("Linked List after sorting \n");
    PrintList(a);
 
    return 0;
}