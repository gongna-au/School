#include "head1.h"
#include <stdio.h>
#include <stdlib.h>
void main(){
    Node* head=NULL;
    head = ( Node*)malloc(sizeof(struct Node));
    InsertFirst(head,1,10);
    InsertFirst(head,2,20);
    InsertFirst(head,3,30);
    InsertFirst(head,4,40);
    InsertFirst(head,5,50);
    InsertFirst(head,6,60);
    printf("Original List: "); 
    PrintList(head);
    while(IsEmpty(head)) {            
        Node *temp=DeleteFirst(head);
        printf("\nDeleted value:");
        printf("(%d,%d) ",temp->key,temp->data);
    }
    printf("\nList after deleting all items: ");
    PrintList(head);
    InsertFirst(head,1,10);
    InsertFirst(head,2,20);
    InsertFirst(head,3,30);
    InsertFirst(head,4,40);
    InsertFirst(head,5,50);
    InsertFirst(head,6,60);
    printf("\nRestored List: ");
    PrintList(head);
    printf("\n"); 
    Node *foundLink=FindByKey(head,4);
    if(foundLink != NULL) {
      printf("Element found: ");
      printf("(%d,%d) ",foundLink->key,foundLink->data);
      printf("\n");  
    }else {

      printf("Element not found.");
   }
    DeleteByKey(head,4);
    printf("List after deleting an item: ");
    PrintList(head);
    Reverse(&head);
    printf("\nList after reversing the data: ");
    PrintList(head);
}