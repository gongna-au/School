#include<stdio.h>
#include<stdlib.h>
#define bool int

typedef   char ElemType;

struct treeNode
{
   ElemType data;
   struct treeNode* leftChild;
   struct treeNode* rightChild;
};
typedef   struct treeNode treeNode;

// 一个堆栈节点包含
// 一个指向树节点的指针
// 和一个指向下一个堆栈节点 
// Structure of a stack node.
// Linked List implementation is used for stack.
struct stackNode
{
    struct treeNode *ptrTree;
    struct stackNode *next;
};
typedef   struct stackNode stackNode;

/* Stack related functions */
void push(stackNode** top_ref, treeNode *t);
treeNode *pop(stackNode** top_ref);
bool isEmpty(stackNode *top);


void push(stackNode** top_ref, treeNode *t){
    /* allocate tNode */
    stackNode* newNode =(stackNode*) malloc(sizeof(stackNode));
    if(newNode == NULL){
        printf("Stack Overflow \n");
        getchar();
        exit(0);
    } 
    /* put in the data  */
    newNode->ptrTree  = t;
    /* link the old list off the new tNode */
    newNode->next=(* top_ref);
    (* top_ref)=newNode;

}

/* The function returns true if stack is empty, otherwise false */
bool isEmpty( stackNode *top)
{
    return (top == NULL)? 1 : 0;
} 

/* Iterative function for inorder tree traversal */
void inOrder(treeNode* root){
   //让当前指针指向二叉树的根节点
   treeNode* current =root;
   //初始化一个空栈
   stackNode* stack=NULL;
   bool done=0;
   while(!done){
       //到达当前节点的最左边的左孩子节点
       if(current!=NULL){
           push(&stack,current);
           current=current->leftChild;

       }else{
           if(!isEmpty(stack)){
               current=pop(&stack);
                printf("%c ", current->data);
                // 我们已经访问了节点及其左子树。
                // 现在，轮到右子树了 
                current = current->rightChild;
           }else{
               done=1;
           }
           //从空子树回溯并访问树的Node(存放在栈顶的元素)
           //如果栈空了，证明我完成了
       }
   }
}
/* Function to pop an item from stack*/
treeNode* pop(stackNode** topref)
{
    stackNode* popedStackNode;
    treeNode* temp;
    if (isEmpty(* topref)){
        printf("Stack Underflow \n");
        getchar();
        exit(0);
    }else{
        //先保存指针
        popedStackNode=(*topref);
        //后移动
        (*topref)=(*topref)->next;
        //取保存节点的值
        temp=popedStackNode->ptrTree;
        //释放指针所指的内存空间
        free(popedStackNode);

           return temp;
    }
}

/* Helper function that allocates a new tNode with the
   given data and NULL left and right pointers. */
treeNode*  newTreeNode(ElemType data){
    treeNode* newNode= (treeNode*) malloc(sizeof(treeNode));
    newNode->data=data;
    newNode->leftChild=NULL;
    newNode->rightChild=NULL;
    return newNode;
}


/* Function to insert element in binary tree */
treeNode* InsertNode(treeNode* root,ElemType data){
    if(root==NULL){
        root->data=data;
        root->leftChild=NULL;
        root->rightChild=NULL;
        return root;
    }else{
        //初始化一个空栈
        stackNode* stack;

        push(&stack,root);
        
        while(!isEmpty(stack)){
           treeNode*  temp= pop(&stack);
           if(temp->leftChild!=NULL){
                push(&stack,temp->leftChild);
            }else{
                temp->leftChild=newTreeNode(data);
                return root;
            }
            if (temp->rightChild!=NULL){
                push(&stack,temp->rightChild);
            }else{
                temp->rightChild=newTreeNode(data);
                return root;
            }

        }
        
    }

}
void Insert(treeNode** root,ElemType data){
    if((*root)==NULL){
        (*root)->data=data;
        (*root)->leftChild=NULL;
        (*root)->rightChild=NULL;
        
    }else{
        //初始化一个空栈
        stackNode* stack;

        push(&stack,(*root));
        
        while(!isEmpty(stack)){
           treeNode*  temp= pop(&stack);

           if(temp->leftChild!=NULL){
                push(&stack,temp->leftChild);
            }else{
                temp->leftChild=newTreeNode(data);
                break;
            }
            if (temp->rightChild!=NULL){
                push(&stack,temp->rightChild);
            }else{
                temp->rightChild=newTreeNode(data);
                break;
            }

        }
        
    }

}


