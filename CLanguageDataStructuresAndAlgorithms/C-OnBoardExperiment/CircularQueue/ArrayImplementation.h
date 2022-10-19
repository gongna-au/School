#include <iostream>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef int QElemType;
typedef int Boolean; // Boolean是布尔类型,其值是TRUE或FALSE

#define QUEUE_INIT_SIZE  100 //注意不能有分号
#define QUEUEINCREMENTSIZE  10


typedef struct
{
    QElemType* elem; //动态分配存储空间
    int front; //头指针，若队列不空，指向队列头元素
    int rear; //尾指针，若队列不空，指向队列尾元素的下一位置
    int queuesize; //循环队列“模”的大小
    int incrementsize; //约定的扩容增量
}SqQueue;

void InitQueue_Sq(SqQueue& Q)
{
    Q.elem = new QElemType[QUEUE_INIT_SIZE + 1];
    Q.queuesize = QUEUE_INIT_SIZE + 1;
    Q.incrementsize = QUEUEINCREMENTSIZE;
    Q.front = Q.rear = 0;
}

bool DestroyQueue_Sq(SqQueue& Q)
{
    //判断有没有内存分配
    if (!Q.elem)
    return FALSE;

    delete Q.elem;
    Q.queuesize = 0;
    Q.incrementsize = 0;
    Q.front = Q.rear = 0;
    return TRUE;
}

void ClearQueue_Sq(SqQueue& Q)
{
    Q.front = Q.rear = 0;
}

bool QueueEmpty_Sq(SqQueue Q)
{
    if (Q.front == Q.rear)
    return TRUE;
    return FALSE;
}

int QueueLenght_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}

bool DeQueue_Sq(SqQueue& Q, QElemType& e) //注意这里e必须要用引用&
{
    //若队列不为空，则删除Q的队头元素
    //用e返回其值，并返回TRUE；否则返回FALSE
    if (Q.front == Q.rear)
        return FALSE;
        e = Q.elem[Q.front];
        Q.front = (Q.front + 1) % Q.queuesize;
        return TRUE;
    }

void EnQueue_Sq(SqQueue& Q, QElemType e)
{
//插入元素e为Q的新的队尾元素
    if ((Q.rear + 1) % Q.queuesize == Q.front) // 堆满，扩容
    {
        int k;
        QElemType* a = new QElemType[Q.queuesize + Q.incrementsize];
        for (k = 0; k < Q.queuesize - 1; k++) //注意，循环队列为了区分堆满与对空，特意空出一个位置不用
        a[k] = Q.elem[(Q.front + k) % Q.queuesize];
        delete[]Q.elem; //释放原占数组空间
        Q.elem = a; //为Q.elem设置新的数组位置
        Q.front = 0; //设置新的头“指针”
        Q.rear = Q.queuesize - 1; //设置新的尾“指针”
        Q.queuesize += Q.incrementsize;
    }
        Q.elem[Q.rear] = e;
        Q.rear = (Q.rear + 1) % Q.queuesize;
}

void GetHead_Sq(SqQueue& Q, QElemType& e)
{
    e = Q.elem[Q.front];
}

