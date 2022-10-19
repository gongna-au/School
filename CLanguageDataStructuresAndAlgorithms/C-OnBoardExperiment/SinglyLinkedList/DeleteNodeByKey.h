#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// 函数功能：删除给定位置的键

/*
输入：position = 1，Linked List = 8->2->3->1->7
输出：Linked List = 8->3->1->7

输入：position = 0，Linked List = 8->2 ->3->1->7
输出：链表 = 2->3->1->7
*/


// 如果要删除的节点是根节点，直接删除即可。
// 要删除中间节点，我们必须有一个指向要删除的节点之前的节点的指针。
// 因此，如果位置不为零，我们将循环 position-1 次并获得指向前一个节点的指针。

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

void DeleteNodeByLocation(Node** head_ref, int position ){
    if (*head_ref == NULL){
        return;
    }
    // 储存头结点
    Node* temp = *head_ref;
    
    if (position==0){
        *head_ref=temp->next;
        free(temp);
        return;
    }
    //查找要删除的节点的前一个节点
    for (int i=0; temp!=NULL && i<position-1; i++){
        temp = temp->next;
    }
    //没找到要删除的节点
    if(temp==NULL ||temp->next==NULL ){
        return;
    }
    //节点temp->next是要删除的节点
    //存储指向下一个要删除的节点的下一个节点
    Node *next = temp->next->next;
    free(temp->next);
    temp->next=next;
}

void PrintList(Node *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}



