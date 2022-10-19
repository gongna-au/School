#include "Queue_Sq.h"

void yanghui(int n)
{
    int i,k;
    QElemType s,e;
    SqQueue q;
    for(i = 1;i <= n;i++)
        printf(" ");
    printf("1\n");
    InitQueue_Sq(q, n+2);   //队列实际最多存储n+2个元素，初始化的时候开辟n+3个元素的存储空间
    EnQueue_Sq(q, 0);
    EnQueue_Sq(q, 1);
    EnQueue_Sq(q, 1);
    k = 1;
    while(k < n){
        for(i = 1;i <= n-k;i++)
            printf(" ");
        EnQueue_Sq(q,0);
        do{
            DeQueue_Sq(q, s);
            GetHead_Sq(q, e);
            if(e)
                printf("%d ", e);
            else
                printf("\n");
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