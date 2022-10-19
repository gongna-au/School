#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 函数功能：删除链表

struct LinkedList{
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList  Node;

//遍历链表，将所有节点一一删除。这里的要点是如果当前指针被删除，则不访问当前指针的下一个。

void DeleteList (Node** head_ref){
/* deref head_ref 得到真正的头部 */   
    Node* current = *head_ref;
    Node* next;
 
   while (current != NULL)
   {
       //在删除当前节点前先保存下一个节点
       next=current->next;
       // 删除当前节点
       free(current);
       //让当前节点指向保存的节点
       current=next;
   }
   
   /*  deref head_ref 影响真正的头部返回在调用者中。 */
   *head_ref = NULL;
}

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
}