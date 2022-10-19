#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Structure of a Node
struct Node {
    int data;
    struct Node* link;
};
typedef struct Node Node;

struct Queue{
     struct Node *front;
     struct Node *rear;

};

typedef struct Queue Queue;

// Create a queue and initialize front and rear
Queue* initializeQueue(){
    Queue* q =(Queue*) malloc(sizeof(Queue));
    q->front=q->rear=NULL;
    return q;
}

// Function to create Circular queue
void enQueue(Queue* q, int value)
{
    Node*node=(Node*)malloc( sizeof(Node) );
    node->data=value;
    if (q->front == NULL){
        q->front=node;
        q->rear=node;
        q->rear->link=q->front;
    
    }else{
        q->rear->link=node;
        q->rear=node;
        q->rear->link=q->front;   
    }

       
}
int getHead(Queue* q)
{
    if(q==NULL){
        printf("The queue is Null!\n");
        return -1;
    }
   return q->front->data;

       
}
// Function to delete element from Circular Queue
int deQueue(Queue* q)
{
    if(q==NULL){
        printf("The queue is Null!\n");
        return -1;
    }else if(q->front == q->rear){
        int temp=q->front->data;
        q->front=NULL;
        q->rear=NULL;
        return temp;
    }else{
        Node* temp=q->front;
        int value=temp->data;
        q->front=q->front->link;
        q->rear->link=q->front;
        free(temp);
        return value;
    }
}


// Function displaying the elements of Circular Queue
void displayQueue( Queue* q)
{
    Node* temp = q->front;
    printf("\nElements in Circular Queue are: ");
    while (temp->link != q->front) {
        printf("%-4d ", temp->data);
        temp = temp->link;
    }
    printf("%-4d", temp->data);
    printf("\n");
}

int IsFull(Queue* q){
    if(q==NULL){
        printf("The queue is Null!\n");
        return 1;
    }else{
        return 0;
    }
}

