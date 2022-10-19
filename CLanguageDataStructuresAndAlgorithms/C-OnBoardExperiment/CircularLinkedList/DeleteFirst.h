#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct LinkedList{
    int data;
    struct LinkedList *next;
};

typedef struct LinkedList  Node;


// 在循环链表中插入一个新的节点，把这个节点作为作为新的头部
void push( Node** head_ref, int new_data){
    // 为新节点分配内存
    Node* ptr=(Node*)malloc(sizeof(Node));
    Node* temp=*head_ref;
    ptr->data=new_data;
    //已近把ptr连到头的前面了，只需要找到尾部
    ptr->next=*head_ref;
    // 如果链表不为 NULL，则设置最后一个节点的下一个
    if (*head_ref!=NULL){
        while(temp->next!=*head_ref){
            //移动temp寻找尾部
            temp=temp->next;
        }
        //找到尾部
        //尾部的下一个就是头结点
        temp->next=ptr;
    }else{
        //原来的链表为空，新插入的节点就是头部，让它自己指向自己
        ptr->next=ptr;
    }

    // 让头节点指向新节点
    *head_ref=ptr;

   
}

// 函数功能，循环链表的遍历
// 在传统的链表中
// 我们从头节点开始遍历链表，当我们到达 NULL 时停止遍历。
// 在循环链表中，当我们再次到达第一个节点时，我们停止遍历。

void PrintList(Node *head)
{
    Node*temp=head;
    if (head!=NULL){
        do{
            printf(" %d ", temp->data);
            temp = temp->next;
        }while(temp!=head);
        
    }
  
  printf("\n");
}
// 在循环链表的尾部插入一个节点
void InsertAtEnd(Node** head_ref, int new_data){
    // 为新节点分配内存
    Node* ptr=(Node*)malloc(sizeof(Node));
    ptr->data=new_data;

     Node* temp=*head_ref;
     // 如果链表不为 NULL，则设置最后一个节点的下一个
    if (*head_ref!=NULL){
        while(temp->next!=*head_ref){
            //移动temp寻找尾部
            temp=temp->next;
        }
        //找到尾部
        //尾部的下一个就是头结点
        temp->next=ptr;
        ptr->next=*head_ref;
    }else{
        //原来的链表为空，新插入的节点就是头部，让它自己指向自己
        ptr->next=ptr;
       * head_ref=ptr;
    }  
}


// 删除第一个节点
void DeleteFirst(Node **head_ref){
    Node *current=*head_ref;
    // 判断是否为空
    if (*head_ref==NULL){
        printf("该链表为空链表！\n");
        return;
    }
    // 找到尾节点
    do {
        current=current->next;
    }while(current->next!=*head_ref);
    Node *temp=*head_ref;
    current->next=(*head_ref)->next;
    *head_ref=(*head_ref)->next;
    free(temp);
}
