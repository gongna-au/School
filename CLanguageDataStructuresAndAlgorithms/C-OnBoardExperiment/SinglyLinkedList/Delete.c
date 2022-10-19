#include "Delete.h"
#include <stdio.h>
#include <stdlib.h>

// 函数功能：删除给定的键

int main()
{
    /* 从空列表开始 */
    Node* head = NULL;
 
    push(&head, 7);
    push(&head, 1);
    push(&head, 3);
    push(&head, 2);
 
    puts("Created Linked List: ");
    PrintList(head);
    DeleteNode(&head, 1);
    puts("\nLinked List after Deletion of 1: ");
    PrintList(head);
    return 0;
}