#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_NUMBER 2147483646
#define MIN_NUMBER -2147483647

void openMenu(queue **q, int queueNumber, int capacity);
void getValidInteger(int *value, int min, int max);
void printQueue(node *n);

int main()
{
    int queueCount;
    int capacity = 0;
    int error;

    system("cls");
    printf("Uzduotis su eile\n");
    printf("----------------\n");

    printf ("\nSet the number of queues\n");
    getValidInteger(&queueCount, 1, MAX_NUMBER);
    system("cls");

    queue **queueArray = calloc(queueCount, sizeof(queue*));
    if(queueArray == NULL)
    {
        printf("Error while allocating memory\n\n");
        return 0;
    }

    printf ("Set the max number of elements in a queue\n");
    getValidInteger(&capacity, 1, MAX_NUMBER);
    system("cls");

    int queueNumber;
    while(1)
    {
        if(queueCount == 1)
        {
            printf ("Enter 1 to work with the queue (0 to exit the program)\n");
        }
        else
        {
            printf ("Choose a queue between 1 and %d (0 to exit the program)\n", queueCount);
        }
        getValidInteger(&queueNumber, 0, queueCount);
        system("cls");

        if (queueNumber == 0)
        {
            break;
        }
        else
        {
            queueNumber--;
            openMenu(&queueArray[queueNumber], queueNumber, capacity);
        }
    }

    printf("Exiting the program...\n");
    return 0;
}

void openMenu(queue **q, int queueNumber, int capacity)
{
    int optionNumber;
    int value;
    int error;

    while(1)
    {   
        printf ("\nChoose an option for queue %d\n\n", queueNumber+1);


        printf ("1: Create the queue\n");
        printf ("2: Destroy the queue\n");
        printf ("3: Display the queue\n\n");
        printf ("4: Add new element to the queue\n");
        printf ("5: Remove element from the queue\n\n");
        printf ("6: Show first element in the queue\n");
        printf ("7: Show size of queue\n\n");
        printf ("8: Check if the queue is full\n");
        printf ("9: Check if the queue is empty\n\n");
        printf ("10: Exit this menu\n");

        getValidInteger(&optionNumber, 1, 10);

        system("cls");

        switch(optionNumber)
        {
            case 1:
                destroyQueue(*q, &error);
                *q = createQueue(capacity, &error);

                if(error == 1)
                {
                    printf("Error while allocating memory\n\n");
                }
                else
                {
                    printf("A queue was created successfully\n\n");
                }

                continue;
            case 2:
                destroyQueue(*q, &error);
                *q = NULL;

                if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else
                {
                    printf("A queue was destroyed successfully\n\n");
                }

                continue;
            case 3:
                if((isQueueEmpty(*q, &error) == 1) && (error == 0))
                {
                    printf("Queue is empty\n\n");
                }
                else if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else
                {
                    printf("Printing a queue from first to last:\n");
                    printQueue((*q)->front);
                    printf("\n\n");
                }

                continue;
            case 4:
                printf("Enter an integer to add to a queue");
                getValidInteger(&value, MIN_NUMBER, MAX_NUMBER);
                enqueue(*q, value, &error);

                if(error == 3)
                {
                    printf("Queue is already full\n\n");
                }
                else if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else if(error == 1)
                {
                    printf("Error while allocating memory\n\n");
                }
                else
                {
                    printf("An element was added successfully\n\n");
                }

                continue;
            case 5:
                value = dequeue(*q, &error);

                if(error == 4)
                {
                    printf("Queue is already empty\n\n");
                }
                else if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else if(error == 1)
                {
                    printf("Error while allocating memory\n\n");
                }
                else
                {
                    printf("An element was removed successfully\n\n");
                }

                continue;
            case 6:
                value = getQueueFirstElement(*q, &error);

                if(error == 4)
                {
                    printf("Queue is empty\n\n");
                }
                else if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else
                {
                    printf("First queue element is: %d\n\n", value);
                }

                continue;
            case 7:
                value = getQueueSize(*q, &error);

                if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else
                {
                    printf("Queue's size is: %d\n\n", value);
                }

                continue;
            case 8:
                if(isQueueFull(*q, &error) == 1 && error == 0)
                {
                    printf("Queue is full\n\n");
                }
                else if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else
                {
                    printf("Queue is not full\n\n");
                }

                continue;
            case 9:
                if(isQueueEmpty(*q, &error) == 1 && error == 0)
                {
                    printf("Queue is empty\n\n");
                }
                else if(error == 2)
                {
                    printf("Queue is uninitialized\n\n");
                }
                else
                {
                    printf("Queue is not empty\n\n");
                }

                continue;
            case 10:
                return;
        }
    }
}

void getValidInteger(int *value, int min, int max)
{
    int input_count;
    char character;

    while(1)
    {
        printf("\nEnter a number: ");
        input_count = scanf("%d%c", value, &character);

        if ((input_count == 2) && (character == '\n') && (*value >= min) && (*value <= max))
        {
            break;
        }
        else if ((input_count == 2) && (character == '\n'))
        {
            printf("A number must be between %d and %d. Try again \n", min, max);
        }
        else
        {
            printf("Invalid input, try again \n");
            if (input_count == 0)
            {
                character = 0;
                while (character != '\n')
                {
                    character = getchar();
                }
            }
            else if (character != '\n')
            {
                while (character != '\n')
                {
                    character = getchar();
                }
            }
        }
    }
}

void printQueue(node *n)
{
    printf("%d ", n->data);

    if(n->next != NULL)
    {
        printQueue(n->next);
    }
}