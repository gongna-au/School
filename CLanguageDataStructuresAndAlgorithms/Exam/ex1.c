#include "ex1.h"
#include <stdio.h>
#include <stdlib.h>
// 函数功能：链表的插入

int main()
{
  /* Start with the empty list */
  Node* head1 = NULL;
  Node* head2 = NULL;
  Node* current= NULL;
  int n;
  int m;
  printf("Please input n=");
  scanf("%d",&n);
  printf("Please input m=");
  scanf("%d",&m);
  int temp=0;
 
  for (int i=0;i<n;i++){

      scanf("%d",&temp);
      AddNodeInEnd(&head1, temp);
      AddNodeInEnd(&head2, temp);


  }
  

  printf("Created Linked list is:");
  PrintList(head1);
  
    current=head2;
  for (int j=1;j<m;j++){
      current=current->next;  
  }
  current=current->next;
  //反转链表
  ReverseLinkedList(&head1,m);

  for (int j=0;j<n-m;j++){
      AddNodeInEnd(&head1, current->data); 
      current=current->next;
      
  }

  printf("\nAfter Reverser Linked list is: ");
  PrintList(head1);
  
  printf("\n");
 
  return 0;
}