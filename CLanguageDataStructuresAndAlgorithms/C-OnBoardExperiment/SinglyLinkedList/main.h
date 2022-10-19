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

// 1创建链表
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

void AddNodeInEnd(Node**head,int value){
    /* 1. 分配节点 */
    Node* newNode = (Node*) malloc(sizeof(struct LinkedList));
    Node* last = *head;

    /* 2. 输入数据 */
    newNode->data=value;
    /* 3. 这个新节点将是最后一个节点，所以下一个将其设为 NULL*/
    newNode->next=NULL;
    /* 4. 如果链表为空，则将新节点作为头节点 */
    if (*head==NULL){
        *head=newNode;
        return ;
    }
    //遍历到最后一个节点
    while (last->next != NULL){
        last = last->next;
    }
    //更改最后一个节点的下一个
    last->next = newNode;
    return;
}


struct Node* Merge( Node* a,  Node*b, Node** newHead)
{
    
    // a dummy first node to hang the result on 
    // 一个虚拟的第一个节点来挂起结果 
     //Node* dummy=NULL;
     Node* currentA=a;
     Node* currentB=b;

 
    /* tail points to the last result node  */
    //Node* tail = &dummy;

    /* so tail->next is the place to add new nodes
      to the result. */
    //dummy.next = NULL;
    while(currentA!=NULL){
        if(!SearchIteration(b,currentA->data)){
            AddNodeInEnd(newHead,currentA->data);
        }

       currentA=currentA->next;  
    }
    while (currentB!=NULL)
    {
        AddNodeInEnd(newHead,currentB->data);
        currentB=currentB->next; 
    }
    

}


void FindDuplicates(Node *headA,Node* headB,Node**newHead){
    Node* currentA=headA;
    //Node* currentB=headB;
    while(currentA!=NULL){
        if(SearchIteration(headB,currentA->data)){
             AddNodeInEnd(newHead,currentA->data);
        }
        currentA=currentA->next;
    }

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

void SetSubtraction(Node *headA,Node* headB,Node**newHead){
    Node* currentA=headA;
    Node* currentB=headB;
    while(currentA!=NULL){
        if(!SearchIteration(headB,currentA->data)){
            push(newHead,currentA->data);  
        }
        currentA=currentA->next;
    }
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


/* Takes two lists sorted in increasing order, and splices
   their nodes together to make one big sorted list which
   is returned.  */
void MoveNode( Node** destRef,  Node** sourceRef)
{
    /* the front source node  */
    Node* newNode = *sourceRef;
   // assert(newNode != NULL);
 
    /* Advance the source pointer */
    *sourceRef = newNode->next;
 
    /* Link the old dest off the new node */
    newNode->next = *destRef;
 
    /* Move dest to point to the new node */
    *destRef = newNode;
}





