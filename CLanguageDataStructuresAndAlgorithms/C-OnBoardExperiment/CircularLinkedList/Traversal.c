#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Traversal.h"

int main()
{
    /* Initialize lists as empty */
    Node *head = NULL;
 
    /* Created linked list will be 11->2->56->12 */
    push(&head, 12);
    push(&head, 56);
    push(&head, 2);
    push(&head, 11);
 
    printf("Contents of Circular Linked List\n ");
    PrintList(head);
 
    return 0;
}