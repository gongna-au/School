#include "RemoveDuplicatesFromSorted.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    /* Start with the empty list */
     Node* head = NULL;
   
    /* Let us create a sorted linked list to test the functions
     Created linked list will be 11->11->11->13->13->20 */
    push(&head, 20);
    push(&head, 13);
    push(&head, 13); 
    push(&head, 11);
    push(&head, 11);
    push(&head, 11);                                   
 
    printf("Linked list before duplicate removal:");
    PrintList(head);
 
    /* Remove duplicates from linked list */
    RemoveDuplicates(head);
 
    printf("Linked list after duplicate removal:");        
    PrintList(head);           
   
    return 0;
}