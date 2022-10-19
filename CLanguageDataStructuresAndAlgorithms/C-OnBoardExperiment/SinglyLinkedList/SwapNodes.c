#include "SwapNodes.h"
#include <stdio.h>
#include <stdlib.h>



int main()
{
    /* Start with the empty list */
     Node* head = NULL;
   
    /* Let us create a sorted linked list to test the functions
     Created linked list will be 11->11->11->13->13->20 */
    push(&head, 10);
    push(&head, 15);
    push(&head, 12); 
    push(&head, 13);
    push(&head, 20);
    push(&head, 14);                                   
 
    printf("Linked list before swap node:");
    PrintList(head);
 
    /* Remove duplicates from linked list */
    SwapNodesOptimizedVersion(&head,12,20);
 
    printf("Linked list after swap node:");        
    PrintList(head);           
   
    return 0;
}


