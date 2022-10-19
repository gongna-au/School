#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"InsertAfterSpecificElem.h"

int main(){
    /* Initialize lists as empty */
    Node* head = NULL;
 
    /* Created linked list will be 2->5->7->8->10 */
    InsertAtEnd(&head, 2);
    InsertAtEnd(&head, 5);
    InsertAtEnd(&head, 7);
    InsertAtEnd(&head, 8);
    InsertAtEnd(&head, 10);

    printf("List Before Insert ");
    PrintList(head);
    InsertAfterSpecificElem(head,5,3);
    printf("List After Insert: ");
    PrintList(head);
}