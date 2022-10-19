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


typedef struct
{
    int w;
    int parent;
    int lchild,rchild;
}HTNode,*HuffmanTree;

//从数组中挑选可以选择的权值
void Select(HuffmanTree H,int i,int &s1,int &s2)
{
    //i是数组中可以挑选的范围 
    //从1到i一共是n个
    int n = 1;
    int j = 1;
    int z;
    while(j <= 2)
    {
        n = 1;
        while(H[n].parent != 0)
        {
            //寻找没有被挑选过的节点
            n++;
            //因为数组后面的parent 为0
        }
        z = n;
        //z为找到的没有被挑选到第一个数组的下标
        //因为数组后面的parent 为0
        //所以我们先判断一下是否超过了可以挑选的范围，只有是在范围里面的我们才可以取
        while(n<i)
        {
            //继续往后面找
            n = n+1;
            //再次找到一个parent=0的
            if(H[n].parent == 0){
                if(H[z].w > H[n].w){
                    //
                    z = n;
                }
            }
        }
        if(j == 1){
            s1 = z;
            H[s1].parent = 1;

            j++;
        }else{
            s2 = z;
            j++;
        }

    } 
}


void createmanTree(HuffmanTree &H,int n)
{
    if(n<=1){
        return ;
    }
    //赫夫曼共有这么多结点 
    // n +  n-1  

    int m = 2*(n-1)+1; 
    //先用数组来存放权值
    //还需要一个啥都不存的头节点
    // 2n
    H = new HTNode[m+1];
    //
    int i;
    //H[1]~H[m] 
    for(i = 1;i<=m;i++){
        H[i].parent = 0;
        H[i].lchild = 0;
        H[i].rchild = 0;
    }
    //往数组读入权值
    i = 1;
    cout<<"Please input w:"<<endl;
    while(i<=n){
        cin>>H[i].w;
        i++;
    }
    //i=n+1;

    int j = n;
    
    int s1,s2;
    //数组的后面存新的权数值
    // n + n-1 + 1
    for(i = n+1;i<=m;++i){
        //挑选的次数就是数组后面的个数
        // 1～n
        ////在HT[1～i-1]中选择parent为0 没有被挑选  且weight最小的两个结点，其序号分别为s1和s2 
        Select(H,i-1,s1,s2);

        
        //这两个节点已经被挑选过了 
        //标记节点已经被挑选 且这两个节点父节点在数组中的下标
        H[s1].parent = i;
        H[s2].parent = i;
        
        //这两个小的权是新的节点的左右孩子
        H[i].lchild = s1;
        H[i].rchild = s2;
        //权值最小两个节点构成的新的权值存到数组里
        H[i].w = H[s1].w+H[s2].w;
    }

}


void bianma(HuffmanTree H,int n,char* ptrarray)
{
    //保存所有的字符编码
    char c[n][n+1];
    //保存一次的字符编码的逆序
    char ch[n];
    
    int j,f,k = 0;
    int z,m;

    int i = 1;
    //i是控制我们数组的1～n个节点
    //通过j=H[i].parent得到父亲节点的下标
    //j=H[j].parent又得到父亲节点的下标
    for(i = 1;i<=n;++i){
        //j记录当前节点的权值
        j = i;
        //得到这个节点父亲节点的下标
        f = H[i].parent;
        // n   n-1 

        k = 0;
        //遍历树进行编码
        while(f != 0){
            
            if(H[f].lchild == j){
                ch[k] = '0';
                k++;
            }else{
                ch[k] = '1';
                k++;
            }
            //这里j随着f的移动也在移动
            //最后变为最后一个父节点的下标
            j = f;
            //父亲节点的父亲节点达到遍历树的目的
            f = H[f].parent;


        }
            ch[k] = '\0';

            z = strlen(ch);
            //strlen()用来计算指定的字符串s 的长度，不包括结束字符"\0"

            int u = 0;
            //逆序输出
            for( m = z-1;m>=0;m--){
                c[i-1][u] = ch[m];
                u++;

            }
            c[i-1][u] = '\0';

    }
        
        i = 0;

        while(i<=n-1){
            j = 0;
            cout<<"第"<<i+1<<"个字符是:"<<*ptrarray<< endl;
            ptrarray++;

            cout<<"第"<<i+1<<"个字符的编码是:";
            
            while(c[i][j] != '\0'){
                
                
                cout<<c[i][j];
                j++;
            }
            i++;
            cout<<endl;
            
        }
}


