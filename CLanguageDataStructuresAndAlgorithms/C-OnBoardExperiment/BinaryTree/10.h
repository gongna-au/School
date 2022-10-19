#include<iostream>
#include<string>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
using namespace std;
typedef struct {
    int weight;
    int lchild;
    int rchild;
}HTNode;
typedef struct {   
    HTNode* HTree;
    int root;
}HuffmanTree;
void CreateHuffmanTree(HuffmanTree& HT,int *w,int n){



        if(n<=1){
            return ;
        }
        //赫夫曼共有这么多结点
        int m = 2*(n-1)+1; 
        HT.HTree= new HTNode[m+1];
        
        int i;
        HTNode* p=NULL;
        //往数组赋初值
        for( p=HT.HTree,i=0 ; i<n; ++i,++p,++w ){
           p->weight=*w;
           p->lchild=-1;
           p->rchild=-1;
        }
        for(i=n; i<m; ++i,++p){
            p->weight=0;
            p->lchild=-1;
            p->rchild=-1;
        }
        //建立哈夫曼树
        for(i=n;i<m;++i){
            //从数组中挑选可以选择的权值
            Select(HT.HTree,i-1;s1,s2);
        }
        
        
}


