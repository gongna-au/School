#include <iostream>		//当在VC6.0里时：#include <iostream.h> 此时不能写using namespace std; 
using namespace std;
#include <string.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENTSIZE 10
#define TRUE 1
#define FALSE 0

typedef  int  ElemType;

typedef struct{				//结构体类型定义，无名结构体，这里是定义别名操作 
	ElemType *elem;
	int length;
	int listsize;
	int incrementsize;
}SqList;

//初始化操作函数(1)
void InitList_Sq(SqList &L)
{
	L.elem=new ElemType[LIST_INIT_SIZE];
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	L.incrementsize=LISTINCREMENTSIZE;
}


//销毁操作函数
void DestroyList_Sq(SqList &L)
{
	delete[]  L.elem;
	L.listsize=0;
	L.length=0;
}

//清空表操作函数
void ClearList_Sq(SqList &L)
{
	memset (L.elem, 0, L.length*sizeof(ElemType));
}

//判断表是否为空操作函数
int ListEmpty_Sq(SqList L)
{
	if (L.length==0)
	  return TRUE;
	return FALSE;
}

//求表的长度函数
int ListLength_Sq(SqList L)
{
	return L.length;
}

void ErrorMessage(char *s)
{
	cout<<s<<endl;
	exit(1);
}

//获取某一元素的值（已知其位序）操作函数
ElemType GetElem_Sq(SqList L, int i, ElemType e)
{
	char a[]={"i的值不合法"}; 
	if ((i<1) || (i>L.length))
	{
		ErrorMessage(a);
		return 0;
	} 
	e=L.elem[i-1];
	return e;	
}

//获取某一元素的位序（已知其值）操作函数
int LocateElem_Sq(SqList L, ElemType e)
{
	int i=1;
	ElemType *p=L.elem;
	while(i <=L.length && *p++ !=e)
	  ++i;
	if (i<=L.length)
	  return i;
	return 0;
}
//获取某一元素（已知其值）的前驱元素的值操作函数
ElemType PriorElem_Sq(SqList L, ElemType cure_e, ElemType &pre_e)		 
{
	int i=2;					         //(a1, a2, ...., ai-1, ai, ai+1, ..., an-1, an), 但i=2, 3, 4,..., n时，  
	ElemType *p=&(L.elem[1]);		     //ai有且仅有一个直接前驱， 故从a2开始查找，a1没有直接前驱（这是顺序表）	 
	while(i <=L.length && *p++ !=cure_e) //注意，这里i从2开始，指针也应该指着第二个数
	  ++i;
	if (i<=L.length)					//注意，这里看作i是cure_e的位序， i-1是cure_e的数组下标， （i-1）-1=i-2就是
	  return L.elem[i-2];			    //cure_e直接前驱的数组下标了,(i-1)-1=i-2就是cure_e直接前驱的数组下标了 
	return 0;						    //注意，这里i是位序，不是数组下标
}

//获取某一元素（已知其值）的后继元素的值操作函数
ElemType NextElem_Sq(SqList L, ElemType cure_e, ElemType &next_e)
{
	int i=1;								//(a1, a2, ...., ai-1, ai, ai+1, ..., an-1, an), 但i=1, 2, 3,..., n-1时， 
	ElemType *p=L.elem;						//ai有且仅有一个直接后继， 故从a1开始，an-1结束 // an没有直接后继（这是顺序表）
	while(i <L.length && *p++ !=cure_e)		// an没有直接后继（这是顺序表）
	  ++i;
	if (i<L.length)
	  return L.elem[i];		//i是cure_e的位序， i+1是cure_e的直接后继的下标，(i+1)-1=i就是直接后继的数组下标 
	return 0;
}

//插入某一个元素（已知值）操作函数
void increment(SqList &L)
{
	int i;
	ElemType *a=new ElemType[L.listsize+L.incrementsize];
	for(i=0; i<L.length; i++)
	  a[i]=L.elem[i];
	delete[] L.elem;
	L.elem=a;
	L.listsize +=L.incrementsize;
}

void ListInsert_Sq(SqList &L, int i, ElemType e)
{
	if ((i<1) || (i>L.length+1))
	  cout<<"i值不合法";			//ErrorMessage("i值不合法");
	if (L.length >=L.listsize)
	  increment(L);
	ElemType *q=&(L.elem[i-1]);
	for (ElemType *p=&(L.elem[L.length-1]); p>=q; p--)
	  *(p+1)=*p;
	*q=e;
	++L.length;
}

//删除某一个元素（已知值）操作函数
ElemType ListDelete_Sq(SqList &L, int i, ElemType e)
{
	if ((i<1) || (i>L.length))
	  cout<<"i值不合法";								// ErroeMessage("i值不合法");
	ElemType *p=&(L.elem [i-1]);
	e=*p;
	ElemType *q=&(L.elem[L.length-1]);
	for (++p; p <=q; p++)
	  *(p-1)=*p;
	--L.length;
	return e;
}

//输出顺序表的每个元素操作函数 
void ListTraverse_Sq(SqList L)
{
	for(int i=0; i<L.length; i++)
	  cout<< *L.elem++;
}