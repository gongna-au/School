#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Delete.h"
int main(){
    // 删除双向链表中的节点可以分为三大类：
    // 删除头节点
    // 删除中间节点
    // 删除最后一个节点
    /* Initialize lists as empty */
    Node *head = NULL;
 
    /* Created linked list will be 11->2->56->12 */
    PushAfter(&head, 12);
    PushAfter(&head, 56);
    PushAfter(&head, 2);
    PushAfter(&head, 11);
    PushAfter(&head, 11);
   
 
    printf("Contents of Doubly Linked List\n");
    Traversal(head);

    printf("Contents of Doubly Linked List  after delete node by key\n");
    DeleteNodeByKey(&head,11);
    Traversal(head);
    //PrintList(head);
    //printf("Contents of Doubly Linked List  after delete node by node\n");
    //DeleteNodeByNode(&head,head->next);
    //Traversal(head);
    return 0;



}