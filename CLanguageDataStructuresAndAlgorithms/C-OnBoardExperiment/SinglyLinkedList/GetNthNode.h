#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// C 程序查找第 n 个链表中的节点
#include <assert.h>

// 函数功能：获得链表中的第N个节点
// 输入：1->10->30->14，索引 = 2
// 输出：30  
// 索引 2 处的节点是 30
// 编写一个 GetNth() 函数，
// 该函数接受一个链表和一个整数索引，并返回存储在该索引位置的节点中的数据值。
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

void PrintList(Node *node){
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}


int GetNth(Node *head,int index){
    Node *current=head;
    int count=0;
    while(current!=NULL){
        if(count==index){
            return current->data;
        }else{
            count++;
            current=current->next;
        }
        /*如果我们到达这一行,
        对于不存在的元素
        所以我们断言失败 */
       
        
    }



}
