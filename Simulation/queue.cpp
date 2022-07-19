#include "queue.h"
#include <cstdlib>

queue* createQueue(unsigned capacity, int *error)   //Creates an empty queue with given capacity. Returns NULL if error occurs
{
    queue *q = (queue*) malloc(sizeof(queue));

    if(q == NULL)
    {
        *error = 1;
        return NULL;
    }

    q->capacity = capacity;
    q->size = 0;
    q->front = NULL;
    q->rear = NULL;

    *error = 0;
    return q;
}

int isQueueFull(queue *q, int *error)   //Checks if queue is full. Outputs 1 - if full, 0 - if not full or if error occurs
{
    if(q == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;

    if(q->size == q->capacity)
    {
        return 1;
    }
        
    return 0;
}

int isQueueEmpty(queue *q, int *error)  //Checks if queue is empty. Outputs 1 - if empty, 0 - if not empty or if error occurs
{
    if(q == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;

    if(q->size == 0)
    {

        return 1;
    }
    
    return 0;
}

void enqueue(queue *q, double value, int *error)   //Puts given value to a queue
{
    if(q == NULL)
    {
        *error = 2;
        return;
    }

    if(isQueueFull(q, error))
    {
        *error = 3;
        return;
    }

    struct NodeQ *tmp = (struct NodeQ*) malloc(sizeof(struct NodeQ));

    if(tmp == NULL)
    {
        *error == 1;
        return;
    }

    tmp->data = value;
    tmp->next = NULL;

    if(q->front == NULL && q->rear == NULL)
    {
        q->front = tmp;
        q->rear = tmp;
        q->size++;
        
    }
    else
    {
        q->rear->next = tmp;
        q->rear = tmp;
        q->size++;
    }

    *error = 0;
}

double dequeue(queue *q, int *error)   //Removes first element from queue and outputs it. If error occurs then outputs 0
{
    if(q == NULL)
    {
        *error = 2;
        return 0;
    }

    if(isQueueEmpty(q, error))
    {
        *error = 4;
        return 0;
    }

    struct NodeQ *tmp = (struct NodeQ*) malloc(sizeof(struct NodeQ));

    if(tmp == NULL)
    {
        *error == 1;
        return 0;
    }

    double value = q->front->data;
    q->size--;

    if(q->size == 0)
    {
        q->front = NULL;
        q->rear = NULL;
    }
    else
    {
        tmp = q->front;
        q->front = q->front->next;
        free(tmp);
    }

    *error = 0;
    return value;
}

double getQueueFirstElement(queue *q, int *error)  //Outputs first element in queue without removing it. If error occurs then outputs 0
{

    if(isQueueEmpty(q, error) == 1 && *error == 0)
    {
        *error = 4;
        return 0;
    }
    else if(*error == 2)
    {
        return 0;
    }

    *error = 0;
    return q->front->data;
}

int getQueueSize(queue *q, int *error)  //Outputs queue's current size. If error occurs then outputs 0
{
    if(q == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;
    return q->size;
}

int getQueueCapacity(queue *q, int *error)  //Outputs queue's capacity. If error occurs then outputs 0
{
    if(q == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;
    return q->capacity;
}

void destroyQueue(queue *q, int *error)  //Frees memory of a given queue and all elements in it and makes queue to NULL
{
    if(q == NULL)
    {
        *error = 2;
        return;
    }

    while (!isQueueEmpty(q, error))
    {
        dequeue(q, error);
    }

    free(q);
    q = NULL;
    *error = 0;
}
