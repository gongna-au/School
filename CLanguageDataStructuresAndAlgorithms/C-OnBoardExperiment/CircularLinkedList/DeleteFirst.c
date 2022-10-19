#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DeleteFirst.h"
int main (){
    /* Initialize lists as empty */
    Node* head = NULL;
 
    /* Created linked list will be 2->5->7->8->10 */
    InsertAtEnd(&head, 2);
    InsertAtEnd(&head, 5);
    InsertAtEnd(&head, 7);
    InsertAtEnd(&head, 8);
    InsertAtEnd(&head, 10);
 
    printf("List Before Delete First ");
    PrintList(head);
 
    DeleteFirst(&head);
 

    printf("List After Delete First ");
    PrintList(head);
 
    return 0;









}