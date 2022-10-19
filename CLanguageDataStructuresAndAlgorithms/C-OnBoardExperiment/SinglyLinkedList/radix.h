#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 函数功能：删除给定的键
struct Student{
    int keys[3];
    char no[10];
    char name[20];
    int grade;
};

typedef struct Student ElemType ;

struct LinkedList{
    ElemType *data;
    struct LinkedList *next;
};

typedef struct LinkedList  Node;
//迭代法链表中删除一个节点

// 1创建链表
void push( Node** head_ref, ElemType new_data){
    Node* new_node= ( Node*)malloc(sizeof(struct LinkedList));
    new_node->data->grade=new_data.grade;
    //strcpy(new_node->data->keys,new_data.keys);
    strcpy(new_node->data->name,new_data.name);
    strcpy(new_node->data->no,new_data.no);
    (*head_ref) = new_node;
}

// 2删除链表
void DeleteList (Node** head_ref){
/* deref head_ref 得到真正的头部 */   
    Node* current = *head_ref;
    Node* next;
 
   while (current != NULL)
   {
       //在删除当前节点前先保存下一个节点
       next=current->next;
       // 删除当前节点
       free(current);
       //让当前节点指向保存的节点
       current=next;
   }
   
   /*  deref head_ref 影响真正的头部返回在调用者中。 */
   *head_ref = NULL;
}

// 3.把已经存在的链表表重置为空表


// 4.判断链表是否为空


// 5.返回链表中元素的个数


// 6.返回链表中位置为i的元素值



// 7.定位某个值在链表中的位序
bool SearchIteration(Node * head,ElemType x){
    Node * current=head;
    while(current!=NULL){
        if (current->data->grade==x.grade){
            return true;
        }else{
           current=current->next; 
        }

    }
    return false;

}


// 8.得到某个元素的前驱
Node * GetPrecursor(Node * head,ElemType x){
    Node * current=head;


    while(current->next!=NULL){
        if (current->next->data->grade==x.grade){
            return current;
        }else{
            current=current->next; 
        }

    }
    printf("所给元素不在链表中，找不到该节点的前驱节点！\n");
    return current ;

}


// 9.得到某个元素的后驱
Node * GetSuccessor(Node * head,ElemType x){
    Node * current=head;
    while(current->next!=NULL){
        if (current->data->grade==x.grade){
            if(current->next!=NULL){
                return current->next;
            }else{
                printf("所给元素对应的节点为链表的最后一个节点！\n该节点没有后继节点\n");
                return NULL;
            }
            
        }else{

            current=current->next; 
        }

    }
    printf("所给元素不在链表中，找不到该节点的后继节点！\n");
    return NULL ;

}

// 10.在链表的第i个节点之后插入一个元素
void InsertAfter(Node* prev_node, ElemType new_data){
    /*1. 检查给定的 prev_node 是否为 NULL */
    if (prev_node == NULL){
        printf("the given previous node cannot be NULL\n");    
        return;
    }    
    /* 2. 分配新节点 */
    Node* new_node =(Node*) malloc(sizeof(struct LinkedList));
 
    /* 3. 放数据 */
    new_node->data->grade = new_data.grade;
    strcpy(new_node->data->name,new_data.name);
    strcpy(new_node->data->no,new_data.no);

 
    /* 4. 将新节点的下一个设为 prev_node 的下一个 */
    new_node->next = prev_node->next;
 
    /* 5. 将 prev_node 的下一个移动为 new_node */
    prev_node->next = new_node;
}
// 11.删除第i个位置的元素
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

// 12.遍历打印链表

void PrintList(Node *node)
{
  while (node != NULL)
  {
     printf(" %s ", node->data->no);
     printf(" %s ", node->data->name);
     printf(" %d ", node->data->grade);
     node = node->next;
  }
}

// 13.从未排序的链表中删除重复项

