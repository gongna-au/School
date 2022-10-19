#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef char elemType;
struct StackNode {
    elemType data;
    struct StackNode* next;
};

typedef struct StackNode  Stack;





Stack* NewNode(elemType data)
{
    Stack* stackNode =(Stack*) malloc(sizeof(struct StackNode ));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int IsEmpty( Stack* root)
{
    return !root;
}


void push( Stack** root, elemType data)
{
    Stack* stackNewNode=NewNode(data);
    stackNewNode->next=(*root);
    (* root)=stackNewNode;
    //printf("%d is pushed to stack\n", data);  
}

elemType Pop(Stack** root ){
    if (IsEmpty(*root)){
        return ' ';
    }
    elemType item =(*root)->data;
    Stack* temp=(*root);
    
    (*root)=(*root)->next;
    free(temp);
    return item;
}

elemType Peek( Stack* root)
{
    if (IsEmpty(root))
        return ' ' ;
    return root->data;
}