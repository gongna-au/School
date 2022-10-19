#include "GetNthNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// 函数功能：获得链表中的第N个节点
int main(){
    Node* head = NULL;
    // Use push() to construct
    // below list
    // 1->12->1->4->1
    push(&head, 1);
    push(&head, 4);
    push(&head, 1);
    push(&head, 12);
    push(&head, 1);
    printf("Element at index 3 is %d", GetNth(head, 3));
    //getchar();
}

