// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include"ArrayImplementationOfQueue.h"




// Driver program to test above functions./
int main()
{
    struct Queue* queue = CreateQueue(1000);
 
    Enqueue(queue, 10);
    Enqueue(queue, 20);
    Enqueue(queue, 30);
    Enqueue(queue, 40);
 
    printf("%d dequeued from queue\n\n",
           Dequeue(queue));
 
    printf("Front item is %d\n", front(queue));
    printf("Rear item is %d\n", rear(queue));
 
    return 0;


}
