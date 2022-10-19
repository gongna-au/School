#include "RemoveDuplicates.h"
#include <stdio.h>
#include <stdlib.h>

// 把链表1->11->11->21->43->43->60，
// 转换为 11->21->43->60。
int main()
{
    /* Start with the empty list */
     Node* head = NULL;
   
    /* Let us create a sorted linked list to test the functions
     Created linked list will be 11->11->11->13->13->20 */
    push(&head, 1);
    push(&head, 11);
    push(&head, 11); 
    push(&head, 21);
    push(&head, 43);
    push(&head, 43);
    push(&head, 60);                                  
 
    printf("Linked list before duplicate removal:");
    PrintList(head);
 
    /* Remove duplicates from linked list */
    RemoveDuplicateUnSorted(head);
 
    printf("Linked list after duplicate removal:");        
    PrintList(head);           
   
    return 0;
}