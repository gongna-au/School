#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 函数功能：单向链表上的快速排序
// 关于实现的重要事情是，它改变指针而不是交换数据，时间复杂度与双向链表的实现相同。
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
