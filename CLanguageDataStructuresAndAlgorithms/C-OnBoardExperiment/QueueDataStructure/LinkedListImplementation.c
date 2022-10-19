#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include"LinkedListImplementation.h"
// Driver Program to test anove functions
int main()
{
     Queue* q = createQueue();
    EnQueue(q, 10);
    EnQueue(q, 20);
    DeQueue(q);
    DeQueue(q);
    EnQueue(q, 30);
    EnQueue(q, 40);
    EnQueue(q, 50);
    DeQueue(q);
    printf("Queue Front : %d \n", q->front->data);
    printf("Queue Rear : %d", q->rear->data);
    return 0;
}