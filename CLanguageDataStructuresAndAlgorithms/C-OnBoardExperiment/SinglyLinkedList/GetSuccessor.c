#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GetSuccessor.h"



// 函数功能:得到给定键的后继节点
int main(){
    Node* head = NULL;
    // Use push() to construct
    // below list
    // 1->2->3->4->5
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    puts("Created Linked List: ");
    PrintList(head);
    Node* successor=GetSuccessor(head,4);
    printf("The successor node of 4 is %d\n",successor->data );
    
    
}