#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Insert.h"
int main(){
     /* Initialize lists as empty */
    Node *head = NULL;
 
    /* Created linked list will be 11->2->56->12 */
    PushAfter(&head, 12);
    PushAfter(&head, 56);
    PushAfter(&head, 2);
    PushAfter(&head, 11);
   
 
    printf("Contents of Doubly Linked List\n");
    Traversal(head);
    InsertBefore(&head,head,89);
    Traversal(head);
   // PrintList(head);
 
    return 0;

}