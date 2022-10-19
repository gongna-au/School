#include "SearchElement.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
/* Start with the empty list */
    Node* head = NULL;
    int x = 21;
    /* Use push() to construct below list
     14->21->11->30->10  */
    push(&head, 10);
    push(&head, 30);
    push(&head, 11);
    push(&head, 21);
    push(&head, 14);
    SearchIteration(head,21)? printf("Yes!\nThe key you are looking for is in this linked list\n"):printf("No!\nThe key you are looking for is not in this linked list\n");
    SearchRecursive(head,21)? printf("Yes!\nThe key you are looking for is in this linked list\n"):printf("No!\nThe key you are looking for is not in this linked list\n");

    return 0;

}