#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// 给定指向链表头节点的指针，任务是反转链表。我们需要通过改变节点之间的链接来反转列表。
struct LinkedList{
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList  Node;

void push( Node** head_ref, int new_data){
    Node* new_node= ( Node*)malloc(sizeof(struct LinkedList));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void PrintList(Node *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
  printf("\n");
}


// 给定指向链表头节点的指针，任务是反转链表。我们需要通过改变节点之间的链接来反转列表。
void ReverseLinkedList(Node **head_ref){
    //链表为空
    if ((*head_ref)==NULL){

        printf("NULL");
        return ;
    }else{
        Node* current=*head_ref;
        Node* Pre=NULL;
        while(current->next!=NULL){
             Node* Next=current->next;
             current->next=Pre;
             Pre=current;
             current=Next;
        }
        (*head_ref)=current;
         current->next=Pre;
    }

}