#include"9Experiment.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
//如果左子节点和右子节点都不为空（或不为 NULL），则节点为“完整节点”。
//从根开始进行级别顺序遍历。
//在遍历中，一旦发现一个节点不是完整节点，那么后面的所有节点都必须是叶节点。 

int main()
{
    BiTree T;

    cout<<"请输入二叉树对应的字符串: ";
    CreateBiTree(T);

    
    //创建结点对列
    LinkQueue q;
    InitQueue_L(q);

    
    //先把根节点入队列
    EnQueue_L(q, T);
    //检查的标志变量
    int flag=0;
    int tag=0;
    //层次遍历，队列为空结束循环
    while(QueueEmpty_L(q)==FALSE){
        BiTree T;
        //一个临时的节点
        BiTree T_1;
        DeQueue_L(q,T);

       
        //要么有两个节点，要么有一个左孩子，没有右边孩子
        if(T->lchild==NULL&&T->rchild!=NULL){
            printf("不是完全二叉树！\n");
            flag=1;
            break;
        }
        //对于只有左孩子的节点来说，它的孩子节点一定是叶子节点
        if(T->lchild!=NULL&&T->rchild==NULL){
            //做标记是为了下一次判断左孩子节点是不是叶子节点
            tag=1;
            //记录该左结点
            //T_1为它的左孩子
            T_1=T->lchild;
            //左孩子入队列
            EnQueue_L(q, T->lchild);
            
        }
        if(tag){
            //判断左右孩子是否为叶子节点
            if(T_1->lchild!=NULL||T_1->rchild!=NULL){
                printf("不是完全二叉树！\n");
                break;
            }
        }
        //对于左右节点不为空的节点，保证自己已经进入队列，并且下一次front一定得到的是自己，
        //以此达到回溯的目的来访问右边孩子，并把右边的孩子入队列
        if(T->lchild!=NULL&&T->rchild!=NULL){
           EnQueue_L(q, T->lchild);
        }
        if(T->rchild!=NULL) {
            EnQueue_L(q, T->rchild);
        }
        
    }
    if(flag==0) {
        printf("是完全二叉树！\n");
    }
    return 0;
}

