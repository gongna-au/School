#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 函数功能：删除给定的键

struct LinkedList{
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList  Node;
//迭代法链表中删除一个节点



void push( Node** head_ref, int new_data){
    Node* new_node= ( Node*)malloc(sizeof(struct LinkedList));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

/* 给定一个指向 a 头部的引用（指向指针的指针）列表和一个键，删除链表中第一次出现的键*/
void DeleteNode(Node** head_ref, int key)
{
    // 存储头节点
    Node *temp = *head_ref;
    Node *prev;
    // 如果头节点本身持有要删除的key
    if (temp != NULL && temp->data == key) {
        // 改变头结点
        *head_ref = temp->next; 
        // 释放旧的头结点的空间
        free(temp); 
        return;
    }
    // 搜索要删除的key
    // 跟踪上一个节点，因为我们需要更改 'prev->next'
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // 如果键不在链表中
    if (temp == NULL)
        return;
 
    // 从链表中取消链接节点
    prev->next = temp->next;
    // 释放内存
    free(temp); 
}
 
void PrintList(Node *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}
