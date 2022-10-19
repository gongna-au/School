#include "Radix.h"

void RadixPass(ElemType A[], ElemType B[], int n, int i)
{
    int j, k, count[10];

    for (j = 0; j < 10; ++j)
        count[j] = 0;
    for (k = 0; k < n; ++k)
        count[A[k].keys[i]]++;
    for (j = 1; j < 10; ++j)
        count[j] = count[j - 1] + count[j]; //累加 
    for (k = n - 1; k >= 0; --k)
    {
    j = A[k].keys[i];
    B[count[j] - 1] = A[k];
    count[j]--;
    }
}

void RadixSort(SqList& L)
{
    ElemType C[10];
    int i = 2, j;

    while (i >= 0)
    {
        RadixPass(L.elem, C, L.length, i);
        i--;
        if (i >= 0)
        {
            RadixPass(C, L.elem, L.length, i);
            i--;
        }else
        for (j = 0; j < L.length; ++j) 
            L.elem[j] = C[j];
    }
}

void InputElement(SqList& L)   //输入学生信息到线性表L中
{
    int i, num;
    ElemType e;

    cout << "请输入学生人数：num = ";
    cin >> num;
    cout << endl;

for (i = 1; i <= num; i++)
{
    cout << "请输入第" << i << "个学生的学号：";
    cin >> e.no;
    cout << "请输入第" << i << "个学生的姓名：";
    cin >> e.name;
    cout << "请输入第" << i << "个学生的成绩：";
    cin >> e.grade;
    cout << endl;

    e.keys[0] = e.grade / 100;
    e.keys[1] = (e.grade / 10) % 10;
    e.keys[2] = e.grade % 10;

    ListInsert_Sq(L, i, e);
}
}

void Display(SqList L)
    {cout << "名次 学号 姓名 成绩" << endl;
    for (int i = L.length - 1; i >= 0; i--)
    cout << L.length - i << " " << L.elem[i].no << " " << L.elem[i].name << " " << L.elem[i].grade << endl;
}


int main()
{
SqList L;

InitList_Sq(L);

//输入学生成绩相关信息 
InputElement(L);

//以成绩进行基数排序
RadixSort(L);

//输出排序后的学生信息
Display(L);
}