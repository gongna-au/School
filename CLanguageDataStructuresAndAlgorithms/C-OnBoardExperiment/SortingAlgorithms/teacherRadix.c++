#include "teacherRadix.h"

#define RADIX 10

int bitsnum = 3;    //关键字的位数

void RadixPass(RcdType A[],RcdType B[],int n, int i)
{
int j,k;
int count[RADIX];

    for(j=0; j<RADIX; ++j) count[j]=0;
    for(k=0; k<n; ++k) count[A[k].keys[i]]++;
    for(j=1; j<RADIX; ++j)count[j]=count[j-1]+count[j];

for(k=n-1; k>=0; --k)
{
        j=A[k].keys[i];
        B[count[j]-1]=A[k];
        count[j]--;
    }//for

}//RsdixPass

void RadixSort(SqList &L)
{
    int j, i;

    RcdType * C = new RcdType[L.length];
    i = bitsnum - 1;
        
    while(i>=0){
            RadixPass(L.elem, C, L.length, i);
            i--;
            if(i>=0){
                RadixPass(C, L.elem, L.length, i);
                i--;
            }//if
            else
                for(j=0; j<L.length; ++j) L.elem[j]=C[j];
        }//while
}//RadixSort

void InputStudents(SqList &L)   //输入学生信息到线性表L中
{
    int i, num;
    ElemType e;

    cout<<"请输入学生人数:";
    cin>>num;
    cout<<endl;
    for(i = 1; i <= num; i++)
    {
    cout<<"请输入第"<<i<<"个学生的学号:";
    cin>>e.no;
    cout<<"请输入第"<<i<<"个学生的姓名:";
    cin>>e.name;
    cout<<"请输入第"<<i<<"个学生的成绩:";
    cin>>e.grade;

    //将学生的成绩（整型）转换为关键字（数组）
    e.keys[0] = e.grade/100;                    
            e.keys[1] = e.grade/10 - e.keys[0]*10;
    e.keys[2] = e.grade%10;
    cout<<endl;

    ListInsert_Sq(L, i, e); 
}
}

void OutputStudents_gradedown(SqList L)    //将排序后的学生信息按分数降序输出
{
    int i;
    cout<<"名次     学号          姓名     成绩"<<endl;
        for(i=L.length-1; i>=0; i--)
        printf(" %-2d      %-10s    %-4s     %-3d\n", L.length-i, L.elem[i].no, L.elem[i].name, L.elem[i].grade);
}

void OutputStudents_gradeup(SqList L)    //将排序后的学生信息按分数升序输出
{
    int i;
    cout<<"名次     学号          姓名     成绩"<<endl;
        for(i=0; i<=L.length-1; i++)
        printf(" %-2d      %-10s    %-4s     %-3d\n", L.length-i, L.elem[i].no, L.elem[i].name, L.elem[i].grade);
}

void main()
{
    SqList L;
    InitList_Sq(L);

    InputStudents(L);      //输入学生信息

    RadixSort(L);         //排序
   
    ListTraverse_Sq(L, OutputStudents_gradedown);

//ListTraverse_Sq(L, OutputStudents_gradeup);
}





