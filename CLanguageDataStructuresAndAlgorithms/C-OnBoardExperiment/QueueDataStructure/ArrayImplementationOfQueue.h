// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int front;
    int rear;
    int size;
    unsigned capacity;
    int* array;
};
typedef struct Queue Queue;

Queue* CreateQueue(unsigned capacity){
    Queue* queue=(Queue*)malloc(sizeof(Queue));
    queue->array=(int*)malloc(sizeof(int)*capacity);
    queue->capacity=capacity;
    queue->size=0;
    queue->front=0;
    queue->rear=queue->capacity-1;
    return queue;    
}
int IsFull(Queue *queue){
    if(queue->size==queue->capacity){
        return 1;
    }else{
        return 0;
    }
}

// Queue is empty when size is 0
int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}
// Function to add an item to the queue.
// It changes rear and size
void Enqueue(Queue* queue,int data){
    if(IsFull(queue)){
        return;
    }
   
    queue->rear =(queue->rear+1)%queue->capacity;
    queue->array[queue->rear]=data;
    queue->size++;
   

}
int Dequeue(Queue* queue){
    if(isEmpty(queue)){
        printf("The Dequeue is Null");

        return -1;
    }
    int item=queue->array[queue->front];
    queue->size--;
    queue->front=(queue->front+1)%queue->capacity;

    return item;
}

 
// Function to get front of queue
int front( Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

int rear( Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}