#include "stack.h"
#include <cstdlib>

stack* createStack(unsigned capacity, int *error)   //Creates an empty stack with given capacity. Returns NULL if error occurs
{
    stack *s = (stack*) malloc(sizeof(stack));

    if(s == NULL)
    {
        *error = 1;
        return NULL;
    }

    s->capacity = capacity;
    s->size = 0;
    s->top = NULL;

    *error = 0;
    return s;
}

int isStackFull(stack *s, int *error)   //Checks if stack is full. Outputs 1 - if full, 0 - if not full or if error occurs
{
    if(s == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;

    if(s->size == s->capacity)
    {
        return 1;
    }
        
    return 0;
}

int isStackEmpty(stack *s, int *error)  //Checks if stack is empty. Outputs 1 - if empty, 0 - if not empty or if error occurs
{
    if(s == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;

    if(s->size == 0)
    {

        return 1;
    }
    
    return 0;
}

void pushStack(stack *s, double value, int *error)   //Puts given value to a stack
{
    if(s == NULL)
    {
        *error = 2;
        return;
    }

    if(isStackFull(s, error))
    {
        *error = 3;
        return;
    }

    struct NodeS *tmp = (struct NodeS*) malloc(sizeof(struct NodeS));

    if(tmp == NULL)
    {
        *error == 1;
        return;
    }

    tmp->data = value;
    tmp->next = NULL;

    if(s->top == NULL)
    {
        s->top = tmp;
        s->size++;
    }
    else
    {
        tmp->next = s->top;
        s->top = tmp;
        s->size++;
    }

    *error = 0;
}

double popStack(stack *s, int *error)   //Removes first element from stack and outputs it. If error occurs then outputs 0
{
    if(s == NULL)
    {
        *error = 2;
        return 0;
    }

    if(isStackEmpty(s, error))
    {
        *error = 4;
        return 0;
    }

    struct NodeS *tmp = (struct NodeS*) malloc(sizeof(struct NodeS));

    if(tmp == NULL)
    {
        *error == 1;
        return 0;
    }

    double value = s->top->data;
    s->size--;

    if(s->size == 0)
    {
        s->top = NULL;
    }
    else
    {
        tmp = s->top;
        s->top = s->top->next;
        free(tmp);
    }

    *error = 0;
    return value;
}

double peekStack(stack *s, int *error)  //Outputs first element in stack without removing it. If error occurs then outputs 0
{

    if(isStackEmpty(s, error) == 1 && *error == 0)
    {
        *error = 4;
        return 0;
    }
    else if(*error == 2)
    {
        return 0;
    }

    *error = 0;
    return s->top->data;
}

int getStackSize(stack *s, int *error)  //Outputs stack's current size. If error occurs then outputs 0
{
    if(s == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;
    return s->size;
}

int getStackCapacity(stack *s, int *error)  //Outputs stack's capacity. If error occurs then outputs 0
{
    if(s == NULL)
    {
        *error = 2;
        return 0;
    }

    *error = 0;
    return s->capacity;
}

void destroyStack(stack *s, int *error)  //Frees memory of a given stack and all elements in it and makes stack to NULL
{
    if(s == NULL)
    {
        *error = 2;
        return;
    }

    while (!isStackEmpty(s, error))
    {
        popStack(s, error);
    }

    free(s);
    s = NULL;
    *error = 0;
}
