#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 函数功能：从排序的链表中删除重复项 removeDuplicates()
// 把链表1->11->11->21->43->43->60，
// 转换为 11->21->43->60。 

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
// 编写一个 removeDuplicates() 函数，它接受一个列表并从列表中删除任何重复的节点。该列表未排序。 
// 例如 12->11->12->21->41->43->21， removeDuplicates() 
// 12->11->21->41->43 

void RemoveDuplicateUnSorted(Node * head){
   
    Node *ptr1=head;
    Node *ptr2=head->next;
    // 只要不是尾节点就可以往下移动
    while(ptr1!=NULL&& ptr1->next!=NULL){
        // 父节点充当了伴随节点
        ptr2=ptr1;
        
        while(ptr2->next!=NULL){
            //ptr2指向尾指针
            if(ptr2->next->data == ptr1->data){
               ptr2->next=ptr2->next->next;

            }else{
                ptr2=ptr2->next;
            }  
        }
        ptr1=ptr1->next;

    }
    
}


