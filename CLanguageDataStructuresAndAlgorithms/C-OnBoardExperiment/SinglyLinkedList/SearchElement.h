#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// 函数功能：搜索链表中的元素（迭代和递归）
// 编写一个函数，在给定的单向链表中搜索给定的键“x”。如果 x 存在于链表中，则该函数应返回 true，否则返回 false。 
// 14->21->11->30->10
// 搜索的键是 15
// 则该函数应返回 true



//迭代法实现搜索
// 1) 初始化一个节点指针，current = head。
// 2) 在 current 不为 NULL 时执行以下操作
// a) current->key 等于正在搜索的键返回 true。
// b) 当前 = 当前->下一个
// 3) 返回 false


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
}
// 迭代查找
bool SearchIteration(Node * head,int x){
    Node * current=head;
    while(current!=NULL){
        if (current->data==x){
            return true;
        }else{
           current=current->next; 
        }

    }
    return false;

}
//递归查找
bool SearchRecursive(Node * head,int x){
    // Base case
    if (head == NULL)
        return false;
      
    // 如果当前节点存在key，则返回true
    if (head->data == x)
        return true;
  
    // 重复剩余列表
    return SearchRecursive(head->next, x);
}








