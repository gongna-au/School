#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SplitLinkedList.h"

int main (){
/* Initialize lists as empty */
    Node *head = NULL;
    Node *head1 = NULL;
    Node *head2 = NULL; 
    push(&head, 12);
    push(&head, 56);  
    push(&head, 2);  
    push(&head, 11);
    printf("Original Circular Linked List");
    PrintList(head); 
    SplitListOptimization(head,&head1,&head2);
    printf("\nFirst Circular Linked List");
    PrintList(head1); 
    printf("\nSecond Circular Linked List");
    PrintList(head2); 
    
    return 0;
}

