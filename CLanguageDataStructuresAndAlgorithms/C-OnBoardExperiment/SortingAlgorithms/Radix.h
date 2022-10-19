#include <iostream>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef int Boolean;
typedef int KeysType;

struct RcdType
{
    KeysType keys[3];
    char no[10];
    char name[20];
    int grade;
};

typedef RcdType ElemType;

#define LIST_INIT_SIZE 100 // 线性表存储空间的初始分配量
#define LISTINCREMENT 10   // 线性表存储空间的分配增量

struct SqList
{
ElemType* elem;
    int length;
    int listsize;
    int incrementsize;
};

void InitList_Sq(SqList& L)
{
    L.elem = new ElemType[LIST_INIT_SIZE];
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    L.incrementsize = LISTINCREMENT;
}

void DestroyList_Sq(SqList& L)
{
    delete(L.elem);
    L.listsize = 0;
    L.length = 0;
}

int ListLength_Sq(SqList L)
{
    return L.length;
}

void ListInsert_Sq(SqList& L, int i, ElemType e)
{
    ElemType* a, * p, * q;

    if (i<1 || i>L.length + 1)
    {
    printf("i值不合法!");
    exit(-1);
}

    if (L.length >= L.listsize)
    { 
        a = new ElemType[L.listsize + L.incrementsize];
    if (!a)
        exit(-1);
    for (i = 0; i < L.length; i++)
        a[i] = L.elem[i];
    delete[] L.elem;
    L.elem = a;
    L.listsize += L.incrementsize;
}

    q = L.elem + i - 1;
    for (p = L.elem + L.length - 1; p >= q; --p)
    *(p + 1) = *p;
    *q = e;
    ++L.length;
}