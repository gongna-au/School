#include "DeleteNodeByKey.h"
#include <stdio.h>
#include <stdlib.h>
// 函数功能：删除给定位置的键
int main()
{
    /* Start with the empty list */
    Node* head = NULL;
 
    push(&head, 7);
    push(&head, 1);
    push(&head, 3);
    push(&head, 2);
    push(&head, 8);
 
    puts("Created Linked List: ");
    PrintList(head);
    DeleteNodeByLocation(&head, 4);
    puts("\nLinked List after Deletion at position 4: ");
    PrintList(head);
    return 0;
}