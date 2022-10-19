 #include <stdio.h> 
 #include <stdlib.h> // exit()
 #include <iostream>
 using namespace std;

 #define TRUE 1
 #define FALSE 0

 typedef int Boolean; // Boolean是布尔类型,其值是TRUE或FALSE
 typedef int KeysType;

 struct RcdType{    //定义记录学生信息类型的结构体
    KeysType keys[3];
    char no[10];     //学号
    char name[20];   //姓名
    int grade;       //成绩
 };

 typedef RcdType ElemType;
 
 /**********************************************************/
 /*              线性表的顺序存储结构                      */
 /**********************************************************/
 #define LIST_INIT_SIZE 100 // 线性表存储空间的初始分配量
 #define LISTINCREMENT 10   // 线性表存储空间的分配增量

 struct SqList
 {
   ElemType *elem; // 存储空间基址
   int length;     // 当前长度
   int listsize;   // 当前分配的存储容量(以ElemType为单位)
   int incrementsize; //约定的增补空间
 };

 /**********************************************************/
 /*          顺序表的基本操作(12个)                        */
 /**********************************************************/
 void InitList_Sq(SqList &L)                    // 算法2.4
 { // 操作结果：构造一个空的顺序线性表L---------------1
   L.elem = new ElemType[LIST_INIT_SIZE];
   //L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
   L.length = 0;                                // 空表长度为0    L.listsize = LIST_INIT_SIZE;                 // 初始存储容量
   L.incrementsize = LISTINCREMENT;           // 需要时可扩容的元素个数
 }

 void DestroyList_Sq(SqList &L)                // 算法2.8
 { // 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L--------2
   free(L.elem);
   L.listsize = 0;
   L.length = 0;
 }

 void ClearList_Sq(SqList &L)
 { // 初始条件：顺序线性表L已存在。操作结果：将L重置为空表----------3
   L.length=0;
 }

 Boolean ListEmpty_Sq(SqList L)
 { // 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE------4
   if(L.length == 0)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength_Sq(SqList L)
 { // 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数--------5
   return L.length;
 }

 void GetElem_Sq(SqList L,int i,ElemType &e)
 { // 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)-----------6
   // 操作结果：用e返回L中第i个数据元素的值
   if(i<1 || i>L.length)
   {
   printf("i值不合法！");
   exit(-1);
   }
   //e = *(L.elem+i-1);
   e = L.elem[i-1];
 }

 Boolean Eaqual_Sq(ElemType a, ElemType b)
 { // 
   if((strcmp(a.no, b.no) == 0) && (strcmp(a.name, b.name) == 0) && (a.grade == b.grade))
     return TRUE;
   else
     return FALSE;
 }
 
 ///*
 int LocateElem_Sq(SqList L,ElemType e)         // 算法2.5
 { // 在顺序线性表L中查找第一个值与e相等的数据元素------7
   // 操作结果：若找到，返回其在L中的位序，若这样的数据元素不存在，则返回值为0。
   int i=1;                       // i的初值为第1个元素的位序
   ElemType *p=L.elem;            // p的初值为第1个元素的存储位置
   while(i<=L.length && !Eaqual_Sq(*p++, e))  
     ++i;
   if(i<=L.length)
     return i;
   else
     return 0;
 }
 //*/

 ///*
 void PriorElem_Sq(SqList L,ElemType cur_e,ElemType &pre_e)
 { // 初始条件：顺序线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，-----------8
   //           否则操作失败，pre_e无定义
   ElemType *p=L.elem+1;
   while(p<=L.elem+L.length && !Eaqual_Sq(*p, cur_e))
   p++;
   if(p>L.elem+L.length)
   exit(-1);
   else
   pre_e=*--p;
 }
 //*/

 ///*
 void NextElem_Sq(SqList L,ElemType cur_e,ElemType &next_e)
 { // 初始条件：顺序线性表L已存在
   // 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，--------9
   //           否则操作失败，next_e无定义
   ElemType *p=L.elem;
   while(p<=L.elem+L.length-1 && !Eaqual_Sq(*p, cur_e))
   p++;
   if(p==L.elem+L.length)
   exit(-1);
   else
   next_e=*++p;    
 }
 //*/

 void ListInsert_Sq(SqList &L,int i,ElemType e)        // 算法2.6
 { // 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1--------------10
   // 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1
   ElemType *a,*p,*q;

   if( i<1 || i>L.length+1 )                 // i值不合法
   {
   printf("i值不合法！");
   exit(-1);
   }

   if(L.length>=L.listsize)             // 当前存储空间已满,增加分配
   {
   a = new ElemType[L.listsize+L.incrementsize];
   if(!a)
   exit(-1);                    // 存储分配失败
   for(i=0; i<L.length; i++)
   a[i] = L.elem[i];
   delete [] L.elem;
   L.elem = a;                      // 新基址
   L.listsize+=L.incrementsize;     // 增加存储容量
   }
   
   q = L.elem+i-1;                      // q为插入位置
   for(p=L.elem+L.length-1;p>=q;--p)    // 插入位置及之后的元素后移
   *(p+1) = *p;
   *q = e; // 插入e
   ++L.length; // 表长增1  
}

 void ListDelete_Sq(SqList &L,int i,ElemType &e)            // 算法2.7
{ // 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)----------------11
   // 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
   ElemType *p,*q;
   if( i<1 || i>L.length ) // i值不合法
   {
   printf("i值不合法！");
   exit(-1);
   }
   p = L.elem+i-1; // p为被删除元素的位置
   e = *p; // 被删除元素的值赋给e
   q = L.elem+L.length-1; // 表尾元素的位置
   for(++p;p<=q;++p) // 被删除元素之后的元素前移
   *(p-1)=*p;
   L.length--; // 表长减1  
}

 void ListTraverse_Sq(SqList L, void(*visit)(SqList))
 { // 初始条件：顺序线性表L已存在
   // 操作结果：通过函数指针*visit遍历顺序表中的每个数据元素-----------------------------12
   visit(L);
 }