#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// 函数功能：链表的插入
struct LinkedList{
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList  Node;

Node* CreateNode(){
    Node*  temp;
     //创建一个link
    temp=(Node*)malloc(sizeof( struct LinkedList));
    temp->next=NULL;
    return temp;
}
//最后添加一个节点：（6 步过程）
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

//在给定节点之后添加一个节点：（5 步过程)
void InsertAfter(Node* prev_node, int new_data){
    /*1. 检查给定的 prev_node 是否为 NULL */
    if (prev_node == NULL){
        printf("the given previous node cannot be NULL\n");    
        return;
    }    
    /* 2. 分配新节点 */
    Node* new_node =(Node*) malloc(sizeof(struct LinkedList));
 
    /* 3. 放数据 */
    new_node->data = new_data;
 
    /* 4. 将新节点的下一个设为 prev_node 的下一个 */
    new_node->next = prev_node->next;
 
    /* 5. 将 prev_node 的下一个移动为 new_node */
    prev_node->next = new_node;
}
// 给定指向链表头节点的指针，任务是反转链表。我们需要通过改变节点之间的链接来反转列表。
void ReverseLinkedList(Node **head_ref,int m){
    //链表为空
     Node* tempList=NULL;
    if ((*head_ref)==NULL){

        printf("NULL");
        return ;
    }else{
        Node* current=*head_ref;
        Node* Pre=NULL;
        int tag=1;
       
        while(tag!=m){
             tag++;
             if(tag==m-1){
                 tempList=current->next;
             }
             Node* Next=current->next;
             current->next=Pre;
             Pre=current;
             current=Next;
        }
        (*head_ref)=current;
         current->next=Pre;

    }

}



//在前面添加一个节点：（4 步过程） 
void InsertAtBegin( Node** head, int new_data)
{
    /* 1. 分配新节点 */
     Node* new_node = ( Node*) malloc(sizeof(struct LinkedList));
  
    /* 2.  放数据 */
    new_node->data  = new_data;
  
    /* 3. 将新节点的下一个作为头 */
    new_node->next = *head;
  
    /* 4. 移动头部指向新节点 */
    (*head)    = new_node;
}


void PrintList(Node *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}









