#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/* Node of a doubly linked list */
struct LinkedList {
    int data;
    struct LinkedList* next; // Pointer to next node in DLL
    struct LinkedList* prev; // Pointer to previous node in DLL
};


typedef struct LinkedList  Node;

void DeleteNodeByKey(Node** head_ref,int data){
    Node*current=*head_ref;
    if((*head_ref)->data==data && (*head_ref)->next!=NULL){
        (*head_ref)=(*head_ref)->next;
        current=current->next;
        (*head_ref)->prev=NULL;
    }else if((*head_ref)->data==data && (*head_ref)->next==NULL){
        Node*temp=(*head_ref);
        free(temp);
        (*head_ref)=NULL;
        return;
    }else if((*head_ref)->data!=data &&(*head_ref)->next==NULL){
        printf("The key you input is not found!\n");
        return ;
    }else if((*head_ref)->data!=data && (*head_ref)->next!=NULL){
        current=current->next;
    }
    while(current!=NULL){
        Node* pre=current;
        current=current->next;
        if(pre->data==data){
            pre->prev->next=pre->next;
            if(current!=NULL){
                pre->next->prev=pre->prev;
            }
            free(pre);
        }

    }


}


void DeleteNodeByNode(Node** head_ref,Node* node){

    if(node ==*head_ref && (* head_ref)->next!=NULL){
        * head_ref=node->next;
        (* head_ref)->prev=NULL;
        node->next=NULL;
        free(node);
        return;
    }else if (node ==*head_ref && (* head_ref)->next==NULL )
    {
        * head_ref=NULL;
        printf("This LinkedList only has one node!\n");
    }else if (node !=*head_ref && *head_ref!=NULL)
    {
        Node * current=*head_ref;
            while(current!=NULL){
                
                if (current==node && current->next!=NULL){
                    current->prev->next=current->next;
                    current->next->prev=current->prev;
                    
                }else if (current==node && current->next==NULL)
                {
                    current->prev->next=NULL;
                    current->prev=NULL;
                    free(current); 
                }
                current=current->next;
    
            }
    }
    
    













}



void push(Node **head_ref,int data){
    //为新的节点分配内存
   Node *ptr = (Node *)malloc(sizeof(struct LinkedList ));
   ptr->data=data;
   // 因为插进去是作为第一个节点的所以把前驱设为NULL
    ptr->next=(*head_ref);
    ptr->prev=NULL;
    //ptr->next= current;
   if (*head_ref!=NULL){
       (*head_ref)->prev=ptr;
   }
   (*head_ref)=ptr;
}

void PrintList(Node *head){
    Node *current =head;
    if(head==NULL){
        printf("This linked list is empty linked list!\n");
        return;
    }

    printf("\nTraversal in forward direction \n");
    do{
        printf("%-4d",current->data);
        current=current->next;
    }while(current->next!=NULL);
    printf("%-4d",current->data);

    printf("\nTraversal in reverse direction \n");
    do{
        printf("%-4d",current->data);
        current=current->prev;
    }while(current!=NULL);


}

void Traversal(Node *head){
    Node *current =head;
    if(head==NULL){
        printf("This linked list is empty linked list!\n");
        return;
    }
    do{
        printf("%-4d",current->data);
        current=current->next;
    }while(current!=NULL);
    printf("\n");

}

//给定一个指向头部的引用（指向指针的指针）一个 DLL 和一个 int，在末尾附加一个新节点 
void PushAfter(Node **head_ref,int data){
    //为新的节点分配内存
   Node *ptr = (Node *)malloc(sizeof(struct LinkedList ));
   ptr->data=data;
   if (*head_ref==NULL){
       ptr->prev=NULL;
       ptr->next=*head_ref;
       //更改头结点
       *head_ref=ptr;
   }else{
       // 找到尾巴节点
        Node* tail = NULL;
        Node* current = *head_ref;
      
        while(current->next != NULL){
            current = current->next;
        }
        // 如果是do {current = current->next;}while(current->next != NULL);在这种情况下只适合在节点数为0，节点数大于2等于2的情况插入数据，
        // 如果只有一个节点，你插入时就会报错
       
        tail =current;

        ptr->next=NULL;
        ptr->prev=tail;
        tail->next=ptr;
   }
}
// 在给定节点之后添加一个节点 
// 我们得到一个节点的指针作为prev_node，并且在给定节点之后插入新节点。
void  InsertAfter(Node * preNode,int data){
    if (preNode==NULL){
        printf("The pointer given is empty！\n");
        return;
    }
    // 为新节点分配内存
    Node *ptr = (Node *)malloc(sizeof(Node ));
    ptr->data=data;
    // 判断是否为尾节点
    //if (preNode->next==NULL){
       // ptr->next=NULL;
    //}else{
    //    ptr->next=preNode->next;
    //}
    //或者直接写
    ptr->next=preNode->next;

    preNode->next=ptr;
    ptr->prev=preNode;

}



// 给定一个节点作为 next_node，在节点之前插入一个新节点 
void  InsertBefore(Node ** head_ref,Node* nextNode,int data){

    if (nextNode==NULL){
        printf("The pointer given is empty！\n");
        return;
    }
    // 为新节点分配内存
    Node *ptr = (Node *)malloc(sizeof(Node ));
    ptr->data=data;

    ptr->prev=nextNode->prev;
    // 连了第一条
    nextNode->prev=ptr;
    // 连了第三条
    ptr->next=nextNode;
    // 连了第二条
    if (ptr->prev!=NULL){
        // 连了第四条
        ptr->prev->next=ptr;
    }else{
        (*head_ref)=ptr;
    }

}





