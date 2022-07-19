#ifndef STACK_FILE_H
#define STACK_FILE_H

struct NodeS
{
    double data;
    struct NodeS *next;
};

typedef struct Stack
{
    unsigned capacity, size;
    struct NodeS *top;
} stack;

stack* createStack(unsigned capacity, int *error);     //Creates an empty stack with given capacity. Returns NULL if error occurs
int isStackFull(stack *s, int *error);      //Checks if stack is full. Outputs 1 - if full, 0 - if not full or if error occurs
int isStackEmpty(stack *s, int *error);     //Checks if stack is empty. Outputs 1 - if empty, 0 - if not empty or if error occurs
void pushStack(stack *s, double value, int *error);     //Puts given value to a stack
double popStack(stack *s, int *error);     //Removes first element from stack and outputs it. If error occurs then outputs 0
double peekStack(stack *s, int *error);     //Outputs first element in stack without removing it. If error occurs then outputs 0
int getStackSize(stack *s, int *error);    //Outputs stack's current size. If error occurs then outputs 0
int getStackCapacity(stack *s, int *error);    //Outputs stack's capacity. If error occurs then outputs 0
void destroyStack(stack *s, int *error);     //Frees memory of a given stack and all elements in it and makes stack to NULL

/*
Error codes:
0 - no error
1 - error with memory allocation
2 - stack is uninitialized (is NULL)
3 - stack is full
4 - stack is empty
*/

#endif