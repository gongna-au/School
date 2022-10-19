#include "DeleteLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

// 函数功能：删除链表

int main()
{
    /* 空链表 */
    Node* head = NULL;
    
    /* 使用 push() 构造下面的列表1->12->1->4->1  */
    push(&head, 1);
    push(&head, 4);
    push(&head, 1);
    push(&head, 12);
    push(&head, 1); 
    printf("Linked list before deleting :");
    PrintList(head);
    printf("\nDeleting ...");
    printf("\nLinked list after deleting :");
    DeleteList(&head); 
    PrintList(head);
    //printf("\n");
    printf("\nLinked list deleted");
}
