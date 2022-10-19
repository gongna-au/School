#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RemoveDuplicatesFromUnSorted.h"
void main(){
    Node *head = NULL;
 
    /* Created linked list will be 11->2->56->12 */
    PushAfter(&head, 12);
    PushAfter(&head, 56);
    PushAfter(&head, 2);
    PushAfter(&head, 11);
    PushAfter(&head, 2);
   
 
    printf("Contents of Doubly Linked List\n");
    Traversal(head);
    printf("Contents of Doubly Linked List after delete duplicates node by key\n");
    RemoveDuplicatesFromUnSorted1(&head);
    Traversal(head);
}