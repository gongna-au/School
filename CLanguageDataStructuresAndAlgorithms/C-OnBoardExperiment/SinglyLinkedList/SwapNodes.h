#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
// 编写一个SwapNodes() 函数
// 给定一个链表和其中的两个键，交换两个给定键的节点。
// 应通过更改链接来交换节点。当数据包含许多字段时，在许多情况下交换节点的数据可能会很昂贵
// Input : 10->15->12->13->20->14,  x = 12, y = 20
// Output: 10->15->20->13->12->14
void SwapNodes(Node** head_ref,int x,int y){
    // 如果x和y相等
    if(x==y){
        printf("输入的x与y相等\n请重新输入!\n");
        return ;
    }
    Node *currentX=* head_ref;
    Node *preCurrentX=NULL;
    while(currentX->data!=x){
        preCurrentX=currentX;
        currentX=currentX->next;
    }

    Node *currentY=* head_ref;
    Node *preCurrentY=NULL;
    while(currentY->data!=y){
        preCurrentY=currentY;
        currentY=currentY->next;
    }

    //如果没有找到，那么两个指针就会变成空指针
    if(currentX==NULL||currentY==NULL){
        printf("输入的值在链表中不存在，请重新输入\n！");
        return ;
    }
    // 前驱起到了判断节点是否为第一个节点的作用
    if (preCurrentX!=NULL){
        preCurrentX->next=currentY;

    }else{
        //如果是头节点，那么头指针的引用就起到了作用
        *head_ref=currentY;
    }
    if (preCurrentY!=NULL){
        preCurrentY->next=currentX;

    }else{
        //如果是头节点，那么头指针的引用就起到了作用
        *head_ref=currentX;
    }
    Node* temp = currentY->next;
    currentY->next = currentX->next;
    currentX->next = temp;
}

void swap (Node *a,Node *b){
    Node *temp=a;
    a=b;
    b=temp;
}

// 优化SwapNodes()函数
void SwapNodesOptimizedVersion(Node** head_ref,int x,int y){
    // 如果x和y相等
    if(x==y){
        printf("输入的x与y相等\n请重新输入!\n");
        return ;
    }
    Node ** a=NULL;
    Node ** b=NULL;
    while((*head_ref)!=NULL){
        if((*head_ref)->data==x){
            a=head_ref;
        }
        if ((*head_ref)->data==y){
            b=head_ref;
        }
        if(a&&b){
            swap(*a,*b);
            swap(((*a)->next), ((*b)->next));
        }



        head_ref=&((*head_ref)->next);
    }



}



