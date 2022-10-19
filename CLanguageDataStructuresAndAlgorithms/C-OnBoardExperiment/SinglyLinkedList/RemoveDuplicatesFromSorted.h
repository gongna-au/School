#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 函数功能：从排序的链表中删除重复项 removeDuplicates()
// 把链表1->11->11->21->43->43->60，
// 转换为 11->21->43->60。 

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



void RemoveDuplicates(Node * head){
      Node* current = head;
      // 存放待删除节点下一个指针的指针 被删除节点的下一个节点
      Node* next_next;
      if(current == NULL){
          printf("输入的链表为空\n");
          return;
      }
      while(current->next!=NULL){
          if(current->data == current->next->data){
              
              next_next=current->next->next;
              free(current->next);
              current->next=next_next;
          }else{
            current=current->next;
          }


      }



}


