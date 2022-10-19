//遵循“少用一个元素空间”的约定，队列大小为n+3
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

void EnQueue_Sq(SqQueue &Q, int e)
{
    Q.elem[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.queuesize;
}

Boolean DeQueue_Sq(SqQueue &Q, QElemType &e)
{
    if ( Q.front == Q.rear){
        return FALSE;
    }
    
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % Q.queuesize;
    return TRUE;
}

Boolean GetHead_Sq(SqQueue Q, QElemType &e)
{
    if ( Q.front == Q.rear){
        return FALSE;
    }
    e = Q.elem[Q.front];
    return TRUE;
}

Boolean QueueEmpty(SqQueue Q)
{
    if(Q.front == Q.rear){
        return TRUE;
    }else{
        return FALSE;
    }

}

void yanghui(int n)
{
    int i,k;
    QElemType s,e;
    SqQueue q;
    for(i = 1;i <= n;i++){
        printf(" ");
    }
    printf("1\n");
    InitQueue_Sq(q, n+2);//队列实际最多存储n+2个元素
    EnQueue_Sq(q, 0);
    EnQueue_Sq(q, 1);
    EnQueue_Sq(q, 1);
    k = 1;
    while(k < n){
        for(i = 1;i <= n-k;i++){
            printf(" ");
        }
        EnQueue_Sq(q,0);

        do{
            DeQueue_Sq(q, s);
            GetHead_Sq(q, e);
            if(e){
                printf("%d ", e); 
            }else{
                printf("\n");
            }
        
            EnQueue_Sq(q, s+e);
        }while(e != 0);

        k++;
    }//while
    
    DeQueue_Sq(q, e);
    while(!QueueEmpty(q))
    {
        DeQueue_Sq(q, e);
        printf("%d ",e);
    }//while
    printf("\n");

}//yanghui

void main()
{
    int n;
    printf("Please input the number of rows:");
    scanf("%d",&n);
    yanghui(n);
}