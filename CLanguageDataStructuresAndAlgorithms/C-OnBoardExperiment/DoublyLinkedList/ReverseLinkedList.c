#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ReverseLinkedList.h"
void main(){
    Node *head = NULL;
 
    /* Created linked list will be 11->2->56->12 */
    PushAfter(&head, 12);
    PushAfter(&head, 56);
    PushAfter(&head, 2);
    PushAfter(&head, 11);
    printf("Contents of Doubly Linked List\n");
    Traversal(head);
    printf("Contents of Doubly Linked List  after reverse linked list\n");
    ReverseLinkedList(&head);
    Traversal(head);
}