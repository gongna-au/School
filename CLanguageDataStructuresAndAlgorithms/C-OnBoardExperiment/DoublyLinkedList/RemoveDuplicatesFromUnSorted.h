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
// 双链表相对于单链表的优缺点
// 一个 DLL 可以向前和向后两个方向遍历。
// 如果给出指向要删除的节点的指针，DLL 中的删除操作会更有效率
// 我们可以在给定节点之前快速插入一个新节点
// 在单链表中，要删除一个节点，需要指向前一个节点的指针。为了获得这个前一个节点，有时会遍历列表。在 DLL 中，我们可以使用前一个指针获取前一个节点。 
// DLL 的每个节点都需要额外的空间用于前一个指针。虽然可以用单指针实现 DLL




//例如，如果链表是 12->11->12->21->41->43->21
//那么 removeDuplicates() 应该将列表转换为 12->11->21->41->43。
//(使用两个循环） 
void  RemoveDuplicatesFromUnSorted1(Node **head_ref){
    Node* current=*head_ref;
    while(current!=NULL){

        Node* afterNode=current->next;
        while(afterNode!=NULL){
            Node* pre=afterNode;
            afterNode=afterNode->next;
            if(current->data==pre->data){
                pre->prev->next=pre->next;
                if(pre->next!=NULL){
                    pre->next->prev=pre->prev;
                }
            }
        }
        current=current->next;
    }
}



//例如，如果链表是 12->11->12->21->41->43->21
//那么 removeDuplicates() 应该将列表转换为 12->11->21->41->43。
//（使用排序） 
//一般来说，归并排序是最适合高效排序链表的排序算法。 
//使用归并排序对元素进行排序。O(nLogn) 
//使用在排序链表中删除重复项的算法在线性时间内删除重复项。O(n) 
//请注意，此方法不会保留元素的原始顺序。
//时间复杂度：O(nLogn)
//编写一个函数，该函数接受一个按非递减顺序排序的列表，并从列表中删除任何重复的节点。该列表应该只被遍历一次。 
//例如，如果链表是 11->11->11->21->43->43->60，那么 removeDuplicates() 应该将列表转换为 11->21->43->60。
void  RemoveDuplicatesFromUnSorted2(Node **head_ref){





}
//（使用哈希） 
// 我们从头到尾遍历链接列表。对于每个新遇到的元素，我们检查它是否在哈希表中：如果是，我们将其删除；否则我们把它放在哈希表中。
void  RemoveDuplicatesFromUnSorted3(Node **head_ref){




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



