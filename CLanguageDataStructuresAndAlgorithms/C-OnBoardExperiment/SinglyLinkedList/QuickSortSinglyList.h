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

Node* GetTail(Node* cur){
    while(cur!=NULL&&cur->next != NULL ){
        cur=cur->next;
    }
    return cur;
}
// partition()把比pivot小的放在前面，把比pivot大的放在后面
// 在partition()中我们我们将最后一个元素视为枢轴。
// 我们遍历当前列表，如果一个节点的值大于枢轴，我们将它移到尾部之后。如果节点具有较小的值，我们将其保持在其当前位置。 
Node* partition(Node *head,Node* end,Node** newHead,Node** newEnd){

    // 以最后一个元素为基准对列表进行分区
    // current与pivot是新的指向链表头部与尾部的指针，并不是真正指向链表头部与尾部的指针
    Node* current=head;
    Node* pivot=end;

    Node* pre=NULL;
    Node *tail=pivot;
    // 在分区期间，列表的头和尾
    // 可能会更改在 newHead 和 newEnd中
    while(current!=pivot){
        if(current->data < pivot->data){
            // 第一个值小于枢轴 
            // 就把它变成新的头部
            if ((*newHead==NULL)){
                *newHead=current;
            }
            pre=current;
            current=current->next;

        }else{
            //pre至少为第一个节点
            //将 current 节点移动到尾部的下一个，并更改链表尾巴
            if(pre){
                
                pre->next=current->next;
            
            }
            // 保存这个要断开节点的下一个节点
            Node* temp=current->next;
            // 断开节点接到末尾
            current->next=NULL;
            tail->next=current;
            tail=current;
            // current变成断开节点的下一个
            current=temp;

        }



    }
    // 1-5-4-3-2

    // 如果枢轴数据是当前列表中数据中最小的元素
    // pivot 成为头部
    if ((*newHead) == NULL){
        (*newHead) = pivot;
    }
    (*newEnd) = tail;
     return pivot;
    /*Node* pre_pivot;
    while(current!=NULL){
        pre_pivot=current;
        current=current->next;
    }
    pivot=current;
    current=head;

    Node* pre_current=current;
    while(current!=NULL){

        if(current->data > pivot->data){
            // 断开末尾的节点
            // 断开这个节点接到末尾
            pre_current->next=pivot;
            pivot->next=current->next;
            current->next=NULL;
            pre_pivot->next=current;
            //此时pivot在前 current在后
            Node*temp =current;
            current=pivot;
            pivot=temp;
            //此时pivot在后，current在前

            pre_current=current;
            current=current->next;

        }  
    }
    return head;*/
}
// 在QuickSortRecur() 中，我们首先调用 partition() ，它将枢轴放置在正确的位置并返回枢轴
// 将pivot放置在正确位置后，我们找到左侧的尾节点（pivot之前的列表）并为左列表递归。最后，我们为正确的列表递归。
// 这里的排序不包括结束节点
Node * QuickSortRecur(Node* head,Node* end){
    if(!head || head==end){
        return head;
    }
    Node* newHead = NULL;
    Node* newEnd = NULL;
    // 对列表进行分区
    // newHead 和 newEnd 将被分区函数更新
    Node * pivot=partition(head,end,&newHead,&newEnd);
    // 如果枢轴是最小的元素 
    // 对于左侧部分。无需重复
    if (newHead != pivot) {
        // 将枢轴节点之前的节点设置为 NULL
        Node* tmp = newHead;
        while (tmp->next != pivot){
            tmp = tmp->next;
        }  
        tmp->next = NULL;
 
        // 在枢轴之前重复列表
        newHead = QuickSortRecur(newHead, tmp);
        //将左半部分最后一个节点的 next 更改为枢轴
        tmp = GetTail(newHead);
        tmp->next = pivot;
    }
    // 在枢轴元素之后重复列表
    pivot->next = QuickSortRecur(pivot->next, newEnd);
    return newHead;


}

// 快速排序的主要功能。 这是一个包装
// 递归函数 quickSortRecur()
void QuickSort(Node ** headRef){
    (*headRef)= QuickSortRecur(*headRef, GetTail(*headRef));
    return;
}