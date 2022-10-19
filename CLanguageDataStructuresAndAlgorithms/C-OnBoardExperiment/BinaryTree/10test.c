#include <stdio.h>
#include <stdlib.h>

/* 赫夫曼树和赫夫曼编码的存储表示 */
 typedef struct
 {
   unsigned int weight;
   unsigned int parent,lchild,rchild;
 }HTNode,*HuffmanTree; /* 动态分配数组存储赫夫曼树 */
 typedef char **HuffmanCode; /* 动态分配数组存储赫夫曼编码表 */
 
 /* 求赫夫曼编码 */

 void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n) /* 算法6.12 */
 { /* w存放n个字符的权值(均>0)，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC */
   int m,i,s1,s2,start;
   unsigned c,f;
   HuffmanTree p;
   char *cd;
   if(n<=1)
     return;
   m=2*n-1;
   *HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); /* 0号单元未用 */
   for(p=*HT+1,i=1;i<=n;++i,++p,++w)
   {
     (*p).weight=*w;
     (*p).parent=0;
     (*p).lchild=0;
     (*p).rchild=0;
   }
   for(;i<=m;++i,++p)
     (*p).parent=0;
   for(i=n+1;i<=m;++i) /* 建赫夫曼树 */
   { /* 在HT[1～i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2 */
     select(*HT,i-1,&s1,&s2);
     (*HT)[s1].parent=(*HT)[s2].parent=i;
     (*HT)[i].lchild=s1;
     (*HT)[i].rchild=s2;
     (*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
   }
   /* 从叶子到根逆向求每个字符的赫夫曼编码 */
   *HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
   /* 分配n个字符编码的头指针向量([0]不用) */
   cd=(char*)malloc(n*sizeof(char)); /* 分配求编码的工作空间 */
   cd[n-1]='\0'; /* 编码结束符 */
   for(i=1;i<=n;i++)
   { /* 逐个字符求赫夫曼编码 */
     start=n-1; /* 编码结束符位置 */
     for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)
     /* 从叶子到根逆向求编码 */
       if((*HT)[f].lchild==c)
         cd[--start]='0';
       else
         cd[--start]='1';
     (*HC)[i]=(char*)malloc((n-start)*sizeof(char));
     /* 为第i个字符编码分配空间 */
     strcpy((*HC)[i],&cd[start]); /* 从cd复制编码(串)到HC */
   }
   free(cd); /* 释放工作空间 */
 }
 void main()
 {
   HuffmanTree HT;
   HuffmanCode HC;
   int *w,n,i;
   printf("请输入权值的个数(>1): ");
   scanf("%d",&n);
   w=(int*)malloc(n*sizeof(int));
   printf("请依次输入%d个权值(整型):\n",n);
   for(i=0;i<=n-1;i++)
     scanf("%d",w+i);
   HuffmanCoding(&HT,&HC,w,n);
   for(i=1;i<=n;i++)
     puts(HC[i]);
 }
 
 