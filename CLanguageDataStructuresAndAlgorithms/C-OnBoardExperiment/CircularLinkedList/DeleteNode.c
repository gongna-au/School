#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DeleteNode.h"
int main (){
    /* Initialize lists as empty */
    Node* head = NULL;
 
    /* Created linked list will be 2->5->7->8->10 */
    push(&head, 2);
    push(&head, 5);
    push(&head, 7);
    push(&head, 8);
    push(&head, 10);
 
    printf("List Before Deletion: ");
    PrintList(head);
 
    DeleteNode(head, 7);
 

    printf("List After Deletion: ");
    PrintList(head);
 
    return 0;









}
