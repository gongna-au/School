#include<iostream>
#include<stdlib.h>
//#include"Test.h"
#include<queue>
using namespace std;
typedef struct node
{
    char data;
    struct node *l,*r;
}Tree;
//如果左子节点和右子节点都不为空（或不为 NULL），则节点为“完整节点”。
//从根开始进行级别顺序遍历。
//在遍历中，一旦发现一个节点不是完整节点，那么后面的所有节点都必须是叶节点。 
void init(Tree *&l)
//先序遍历创建二叉树
{
    char ch;
    cin>>ch;
    if(ch=='#'){
        l=NULL;
    }else{
        l=(Tree *)malloc(sizeof(Tree));
        l->data=ch;
        init(l->l);
        init(l->r);
    }
}
int main()
{
    Tree *l;
    init(l);
    //创建结点对列
    queue<node*>q;
    //先把根节点入队列
    q.push(l);
    //检查的标志变量
    int flag=0;
    int tag=0;
    //层次遍历，队列为空结束循环
    while(q.empty()==0){
        Tree *T;
        //一个临时的节点
        Tree *T_1;
        T=q.front();
        q.pop();

       
        //要么有两个节点，要么有一个左孩子，没有右边孩子
        if(T->l==NULL&&T->r!=NULL){
            cout<<"不是完全二叉树！"<< endl;
            flag=1;
            break;
        }
        //对于只有左孩子的节点来说，它的孩子节点一定是叶子节点
        if(T->l!=NULL&&T->r==NULL){
            //做标记是为了下一次判断左孩子节点是不是叶子节点
            tag=1;
            //记录该左结点
            //T_1为它的左孩子
            T_1=T->l;
            //左孩子入队列
            q.push(T->l);
        }
        if(tag){
            //判断左右孩子是否为叶子节点
            if(T_1->l!=NULL||T_1->r!=NULL){
                cout<<"不是完全二叉树！"<< endl;
                break;
            }
        }
        //对于左右节点不为空的节点，保证自己已经进入队列，并且下一次front一定得到的是自己，
        //以此达到回溯的目的来访问右边孩子，并把右边的孩子入队列
        if(T->l!=NULL&&T->r!=NULL){
            q.push(T->l);
        }
        if(T->r!=NULL) {
            q.push(T->r);
        }
        
    }
    if(flag==0) {
        cout<<"是完全二叉树！"<< endl;
    }
    return 0;
}
