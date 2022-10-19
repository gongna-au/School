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

// SplitLinkedList把循环链表分为两个链表
// 如果有奇数个节点，那么第一个链表应该包含一个额外的。
// 将下半部分做成圆形。 
// 把前半部分做成圆形。 
// 设置两个链表的头（或起始）指针。
void  SplitLinkedList(Node * head,Node ** head_ref1,Node ** head_ref2){
    // 找到链表最中间的那个节点
    Node * temp=head;
    int num=0;
    int location;
   do {
       temp=temp->next;
       num++;
   }while(temp!=head);

  // 如果为奇数那么就是+1在除以2
  // 如果为偶数那么就是除以2

    if(num%2==0){
        location=num/2;
    }else{
        location=(num+1)/2;
    }
    // 找到要删除节点的指针
    int tag=1;
    Node* mid =NULL;
    do {
        temp=temp->next;
        tag++;
        if (tag==location){
            mid=temp;
            break;
        }
    }while(temp!=head);

    // 找到head的前一个指针
    Node *tail;
    do {
        temp=temp->next;
    }while(temp->next!= head);

    tail=temp;


    // mid指针的下一个是第二个循环链表的头指针
    * head_ref2=mid->next;
    mid->next=head;

    tail->next= * head_ref2;
    *head_ref1=head;

}

// 1 2 3 4 5 6 7 1 
// fast_ptr->next == head 说明是有奇数个节点
// 此时 slow_ptr所指的节点为 4 是第一个循环链表的尾节点
//  fast_ptr 第二个循环链表的尾节点
// 1 2 3 4 5 6 1
// fast_ptr->next->next == head 说明是有偶数个节点
// 此时 slow_ptr所指的节点为3  是第一个循环链表的尾节点
// slow_ptr所指的节点就是要断开的地方
// fast_ptr 第二个循环链表的尾节点的前一个节点
// slow_ptr的下一个节点就是第二个循环链表的头部

void SplitListOptimization(Node * head,Node ** head_ref1,Node ** head_ref2){
    Node* fastNode=head;
    Node* slowNode=head;
    if (head==NULL){
        return;
    }
    while((fastNode->next!=head)&&(fastNode->next->next!=head)){
        fastNode=fastNode->next->next;
        slowNode=slowNode->next;
    }
    //判断是否为偶数节点，因为偶数节点时，fastNode所指不是第二个循环链表的尾节点
    if (fastNode->next->next==head){
        fastNode=fastNode->next;
    }

    //确定头部的位置
    *head_ref1=head;
    if(head->next!=head){
        *head_ref2=slowNode->next;
    }
    

    //断开节点
    fastNode->next=slowNode->next;
    slowNode->next=head;
   

}








         