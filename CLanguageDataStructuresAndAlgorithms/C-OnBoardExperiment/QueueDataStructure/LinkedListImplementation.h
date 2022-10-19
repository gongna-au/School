#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct QueueNode {
    struct QueueNode* next;
    int data;
};

typedef struct QueueNode QueueNode;

struct Queue
{
    QueueNode* front;
    QueueNode* rear;  
};
typedef struct Queue Queue;

// A utility function to create a new linked list node.
QueueNode *createNode(int data){
   QueueNode * newNode =(QueueNode *)malloc(sizeof(QueueNode));
   newNode->data=data;
   newNode->next=NULL;
   return newNode;

}

Queue* createQueue(){
    //QueueNode * newNode=createNode(data);
    Queue* queue=(Queue* )malloc(sizeof(Queue));
    queue->front=NULL;
    queue->rear=NULL;
    return queue;
}
void EnQueue(Queue* queue,int data){
    QueueNode * newNode=createNode(data);
    if (queue->rear == NULL) {
        queue->rear=newNode;
        queue->front=newNode;
        return;
    }else{
        queue->rear->next=newNode;
        queue->rear=newNode;
    }
}


void DeQueue(Queue* queue){
    if (queue->front==NULL){
        return;
    }

    QueueNode* current=queue->front;
    queue->front=queue->front->next;
    // Only has one node  queue->rear is on the node we will delete
    if(queue->front==NULL){
        queue->rear=NULL;

    }
    //free(current);
}











