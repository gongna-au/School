#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



// 函数功能:得到给定键的后继节点

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
     printf(" %d -> ", node->data);
     node = node->next;
  }
  printf("\n");
}
// 查找后继
Node * GetSuccessor(Node * head,int x){
    Node * current=head;


    while(current->next!=NULL){
        if (current->data==x){
            if(current->next!=NULL){
                return current->next;
            }else{
                printf("所给元素对应的节点为链表的最后一个节点！\n该节点没有后继节点\n");
                return NULL;
            }
            
        }else{

            current=current->next; 
        }

    }
    printf("所给元素不在链表中，找不到该节点的后继节点！\n");
    return NULL ;

}