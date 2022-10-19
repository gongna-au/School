#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    int key;
    struct Node* next;
};
typedef struct Node Node;



//定义头结点
//Node *head=NULL;
//定义当前的节点
//Node *current=NULL;

//打印链表的元素
void PrintList(Node * head){
    Node* ptr=head;
    printf("\n[ ");
    while(ptr != NULL) {
        printf("(%d,%d) ",ptr->key,ptr->data);
        ptr = ptr->next;
    }
    printf(" ]\n");

}



//在第一个位置插入link
void InsertFirst(Node ** head,int key,int data){
    //创建一个link
    Node *link=(Node *)malloc(sizeof(Node));
    link->key=key;
    link->data=data;
    //将其指向旧的第一个节点
    link->next=head;
    head=link;

}

//删除第一个link
Node * DeleteFirst(Node * head) {
    //ptr指向第一个节点
    Node *tempLink=head;
    //把头指针指向第二个节点
    head=head->next;
    //第一个节点指向空
    tempLink->next=NULL;
    return tempLink;
}

//判断链表是否为空
int IsEmpty(Node * head) {
    return head == NULL;
}

int ListLength(Node * head){
    //从零开始
    int length=0;
    //指向第一个节点
    Node  *current;
    for(current = head; current != NULL; current = current->next) {
      length++;
    }
    return length;

}

//根据给定的关键字找到节点
Node *FindByKey(Node * head,int key){
    //找个指针指向当前的头结点
    Node *current=head;
    //判断头结点是否为空
    if (head==NULL){
        return NULL;
    }

    while(current->key!=key){
        //判断下一个节点是不是最后一个节点
        if (current->next==NULL){
            return NULL;
        }else{
            current=current->next;
        }
    }
    return current;

}

Node *DeleteByKey(Node * head,int key){
    //从第一个节点开始
    Node* previous = NULL;
    Node* current=head;

    //判断链表是不是空的
    if (head==NULL){
        printf("输入的链表为空链表请重新输入!\n");

    }
    //while至少执行一次的话，默认第一个节点的key值与所给不同
    while(current->key!=key){
        //是最后一个节点
        if(current->next==NULL){
            printf("没有找到key所对应的节点！\n请检查你的输入是否正确！\n");
            return NULL;
        }else{
            previous = current;
            current=current->next;
        }
            
    }
    //while不执行说明第一个节点的key值和所给的key相等
    //找到了第一个节点是所求
    if(current==head){
           head=head->next;
    }else{
    //找到了除了第一个节点以外的节点 previous为它的前一个节点
        previous->next=current->next;
    }
        return current;

}


void SortReduce(Node * head){
    Node * current=NULL;
    Node * next=NULL;
    int i ,j,k,tempKey,tempData;
    //得到链表的长度
    int listLength=ListLength(head);
    k=listLength;

    for (i=0;i<listLength-1;i++,k--){
        //从第一个节点开始
        current=head;
        next=head->next;
        for(j=1;j<k;j++){
            if(current->data < next->data){
                //两个节点的数据进行交换
                tempData=next->data;
                tempKey=next->key;

                next->data=current->data;
                next->key=current->key;

                current->data=tempData;
                current->key=tempKey;
            }
            current = current->next;
            next = next->next;

        }

    }

}
void SortIncrease(Node * head){
    Node * current=NULL;
    Node * next=NULL;
    int i ,j,k,tempKey,tempData;
    //得到链表的长度
    int listLength=ListLength(head);
    k=listLength;

    for (i=0;i<listLength-1;i++,k--){
        //从第一个节点开始
        current=head;
        next=head->next;
        for(j=1;j<k;j++){
            if(current->data > next->data){
                //两个节点的数据进行交换
                tempData=next->data;
                tempKey=next->key;

                next->data=current->data;
                next->key=current->key;

                current->data=tempData;
                current->key=tempKey;
            }
            current = current->next;
            next = next->next;

        }

    }

}


void Reverse(Node ** head_ref){
    Node * prev=NULL;
    Node * current=*head_ref;
    Node * next;
    while (current != NULL) {
        //保存每一个没有改变指向的当前节点的下一个节点
        next=current->next;
        //改变当前节点的指向
        current->next=prev;
        //prev保存未移动前的节点 
        prev = current;
        //current移动
        current=next;
    }

    *head_ref = prev;

}



