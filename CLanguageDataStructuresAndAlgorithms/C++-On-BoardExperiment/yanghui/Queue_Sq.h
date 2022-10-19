//遵循“少用一个元素空间”的约定
#include <stdio.h>
#include <stdlib.h>

typedef int QElemType;
typedef int Boolean; // Boolean是布尔类型,其值是TRUE或FALSE
 
#define TRUE 1
#define FALSE 0

typedef struct
{
    QElemType * elem;
    int front;
    int rear;
    int queuesize;
    int incrementsize;
}SqQueue;

void InitQueue_Sq(SqQueue &Q, int elenum)    //elenum为队列最多存储的元素个数
{
    Q.elem = new QElemType[elenum+1];  //队列实际占用的存储空间数（有一个元素空间未用）
    Q.queuesize = elenum+1;  //模的大小
    Q.front = Q.rear = 0;
}

int QueueLength_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}

void incrementQueuesize(SqQueue &Q)
{
    int k;
    QElemType * a = new QElemType[Q.queuesize + Q.incrementsize];
    for(k = 0 ; k < Q.queuesize - 1 ; k++)
    a[k] = Q.elem[(Q.front + k ) % Q.queuesize];  //腾挪原循环队列中的数据元素
    delete []Q.elem;   //释放原占数组空间
    Q.elem = a;      //为Q.elem设置新的数组位置
    Q.front = 0;     //设置新的头、尾“指针”
    Q.rear = Q.queuesize - 1;
    Q.queuesize += Q.incrementsize;
}

void EnQueue_Sq(SqQueue &Q, int e)
{
    if((Q.rear + 1) % Q.queuesize == Q.front )
        incrementQueuesize(Q);
    Q.elem[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.queuesize;
}

Boolean DeQueue_Sq(SqQueue &Q, QElemType &e)
{
    if ( Q.front == Q.rear)
        return FALSE;
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % Q.queuesize;
    return TRUE;
}

Boolean GetHead_Sq(SqQueue Q, QElemType &e)
{
    if ( Q.front == Q.rear)
        return FALSE;
    e = Q.elem[Q.front];
    return TRUE;
}

Boolean QueueEmpty(SqQueue Q)
{
    if(Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}