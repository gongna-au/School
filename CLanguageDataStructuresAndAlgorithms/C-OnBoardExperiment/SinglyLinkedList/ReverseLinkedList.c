#include "ReverseLinkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 给定指向链表头节点的指针，任务是反转链表。我们需要通过改变节点之间的链接来反转列表。
// 输入：以下链表的头部 
// 1->2->3->4->NULL 
// 输出：链表应改为， 
// 4->3->2->1->NULL

// 输入：以下链表的头部 
// 1->2->3->4->5->NULL 
// 输出：链表应改为， 
// 5->4->3->2->1->NULL

// 输入：NULL 
// 输出：NULL

int main()
{
    /* Start with the empty list */
     Node* head = NULL;
   
    /* Let us create a sorted linked list to test the functions
     Created linked list will be 11->11->11->13->13->20 */
    push(&head, 1);
    push(&head, 2);
    push(&head, 3); 
    push(&head, 4);
                                      
 
    printf("Linked list before reverse :");
    PrintList(head);
 
    /* Remove duplicates from linked list */
    ReverseLinkedList(&head);
 
    printf("Linked list after reverse:");        
    PrintList(head);           
   
    return 0;
}

