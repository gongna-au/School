#include <iostream>
using namespace std;

#define FALSE 0
#define TRUE 1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;  //栈的元素int类型

//采用顺序栈操作
typedef struct{
    SElemType *elem;
    int top;
    int stacksize;
    int incrementsize;
}SqStack;

void InitStack_Sq(SqStack &S)
{//构造一个空栈S，最大空间为STACK_INIT_SIZE
    S.elem = new SElemType[STACK_INIT_SIZE];
    S.top = -1;
    S.stacksize = STACK_INIT_SIZE;
    S.incrementsize = STACKINCREMENT; 
}

void DestroyStack_Sq (SqStack & S)
{//销毁顺序栈S
    delete []S.elem;
    S.top = -1;
    S.stacksize = 0;
    S.incrementsize = 0;
}

void ClearStack_Sq (SqStack & S)
{   //将顺序栈清空
    S.top = -1;
}

int StackLength_Sq(SqStack S)
{//返回顺序栈S中的元素个数，即顺序栈的长度
    return S.top+1;
}

bool GetTop_Sq(SqStack S, SElemType &e)
{//若栈不空，则用e返回S的栈顶元素，并返回TRUE；否则，返回FALSE
    if(S.top == -1)
    return FALSE;
    e = S.elem[S.top];
    return TRUE;
}

void Push_Sq(SqStack &S, SElemType e)
{//插入元素e为新的栈顶元素
    if (S.top == S.stacksize-1){
    
    int i;
    //创建一个新的指针
    SElemType * a;
    //创建一个新的存储数据的指针
    a=new SElemType[S.stacksize + S.incrementsize];

    for(i= 0; i < StackLength_Sq(S); i++){
        //给这个指针赋值
        a[i]=S.elem[i];
    }
    //删除原来的指针
    delete []S.elem;
    //把原来的指针赋值为新的指针
    S.elem = a;
    //给栈的新的元素个数赋值
    S.stacksize += S.incrementsize;

    }else {
        // 因为top指向的元素那个位置已经有元素储存了，所以先移动栈顶指针
        S.elem[++S.top] = e;
        // 因为修改了新的存储单元
        // 但是top记录的下标位置依旧没有变化
    }
    
}

bool Pop_Sq(SqStack &S, SElemType &e)
{//若栈不空，则删除栈S的栈顶元素，用e返回其值，并返回TRUE；否则返回FALSE
    if(S.top == -1){
        return FALSE;
    }
        
    //先弹出元素，再把下标往下面移动
    e = S.elem[S.top--];
    return TRUE;
}

bool StackEmpty_Sq(SqStack S)
{//若栈S为空栈，则返回TRUE；否则返回FALSE
    if(S.top == -1)
        return TRUE;
    else
        return FALSE;
}

void StackTraverse_Sq(SqStack S)
{//从栈底到栈顶依次输出S中的各个数据元素
    int i = 0;
    while(i <= S.top)
            cout<<S.elem[i++]+1<<" ";
    cout<<endl;
}