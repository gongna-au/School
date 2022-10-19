// 输入一字符串，由先序遍历创建一颗二叉树，然后分别以：中序遍历、后序遍历、层次遍历输出
#include "8Experiment.h"
#define NodeNum 100

//利用先序遍历建立二叉树
void CreateBiTree(BiTree &T)    
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
 //中序遍历
void MidOrder(BiTree T)       
{
    if(T){
        MidOrder(T->lchild);
        cout<<T->data<<" ";
        MidOrder(T->rchild);
    }
}
//后序遍历
void PostOrder(BiTree T)   
{
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        cout<<T->data<<" ";
    }
}
//层次遍历
void LayerOrder(BiTree T)     
{
    SqQueue A;
    InitQueue_Sq(A, NodeNum);
    BiTNode *p;
    //二叉树非空
    if(T!=NULL)               
    EnQueue_Sq(A,T);

    while(!QueueEmpty_Sq(A))
    {
        DeQueue_Sq(A,p);
        cout<<p->data<<" ";
        //非空左孩子指针入队列
        if(p->lchild!=NULL) {
            EnQueue_Sq(A,(p->lchild));
        }  
        
        if(p->rchild!=NULL) {
           //非空右孩子指针入队列
            EnQueue_Sq(A,(p->rchild)); 
        }  
    }
}

void main()
{
    BiTree T;

    cout<<"请输入二叉树对应的字符串: ";
    CreateBiTree(T);

    cout<<"中序遍历: ";
    MidOrder(T);
    cout<<endl;

    cout<<"后序遍历: ";
    PostOrder(T);
    cout<<endl;

    cout<<"层次遍历: ";
    LayerOrder(T);
    cout<<endl;
}