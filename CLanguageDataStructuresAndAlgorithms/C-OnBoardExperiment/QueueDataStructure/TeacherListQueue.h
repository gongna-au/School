#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef char TElemType;
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;//定义左右孩子指针
}*BiTree;

//链队列采用带头结点的单链表实现（教材P100）
typedef struct LQNode
{
    BiTree data;                     //队列的存储元素是二叉树结点类型的指针
    struct LQNode *next;
}*QueuePtr;

struct LinkQueue
{
    QueuePtr front;
    QueuePtr rear;
};

void InitQueue_L(LinkQueue &Q)        //构造一个只含头结点的空队列
{

    Q.front = Q.rear = new LQNode;
    Q.front->next = NULL;
}

void EnQueue_L(LinkQueue &Q, BiTree e)      //插入一个结点到队尾
{
    LQNode *p;
    p = new LQNode;
    p->data = e;
    p->next = NULL;

    Q.rear->next = p;
    Q.rear = p;
}

void DeQueue_L(LinkQueue &Q,BiTree &e)       //删除队头元素，用e返回其值
{
    if(Q.front == Q.rear)       //空队列
        exit(-1);

    LQNode *p;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;

    if(Q.rear==p) {
        //队列中只有一个结点的特殊情况
        Q.rear=Q.front;
    }          
        

    delete p;
}

bool QueueEmpty_L(LinkQueue Q)      //判断队列是否为空
{
    if(Q.front == Q.rear){
        return TRUE;
    }else{
        return FALSE;
    }
        
}

//---------------------------------------------------------
void CreateBiTree(BiTree &T)    //利用先序遍历建立二叉树
{
    char ch;
    cin>>ch;
    if(ch=='#'){
        T=NULL;
    }else{
        T=new BiTNode;
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void MidOrder(BiTree T)        //中序遍历
{
    if(T){
        MidOrder(T->lchild);
        cout<<T->data<<" ";
        MidOrder(T->rchild);
    }
}

void PostOrder(BiTree T)   //后序遍历
{
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        cout<<T->data<<" ";
    }
}

void LayerOrder(BiTree T)     //层次遍历
{
    LinkQueue A;
    InitQueue_L(A);
    BiTNode *p;
    //二叉树非空
    if(T!=NULL){
        EnQueue_L(A,T);
    }               
    while(!QueueEmpty_L(A)){
        DeQueue_L(A,p);
        cout<<p->data<<" ";
        //非空左孩子指针入队列
        if(p->lchild!=NULL)  {
            EnQueue_L(A,(p->lchild));
        }if(p->rchild!=NULL)   {
            EnQueue_L(A,(p->rchild));
        }
        
    }
}

