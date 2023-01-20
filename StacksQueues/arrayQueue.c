/*
 *   arrayQueue.c 
 *
 *   "Circular" array implementation of an abstract queue
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "abstractQueue.h"

#define MAXSIZE 10

int headIndex = 0;
int tailIndex = -1;
int count = 0;

void *queue[MAXSIZE] = { NULL };

/**
 * Add a data item to the queue (end of the list)
 * Arguments:
 *   data      -   Pointer to generic data we want to add to queue   
 * Returns 1 if successful, 0 if we have run out of space.
 */
int enqueue(void *data)
{
    int bOk = 1;
    /* If there is room */
    if (count < MAXSIZE)
    {
	tailIndex = (tailIndex + 1) % MAXSIZE;
	queue[tailIndex] = data;
	count++;
    }
    else
    {
	bOk = 0;
    }
    return bOk;
}


/* Get the next item in the queue. This is the element 
 * at the front of the queue.
 * Returns the data stored at the front of the queue.
 * Also removes that item from the queue.
 * Returns NULL if the queue is empty.
 */
void *dequeue()
{
    void *returnData = NULL;
    if (count > 0)
    {
        returnData = queue[headIndex];
        queue[headIndex] = NULL;
        headIndex = (headIndex + 1) % MAXSIZE;
        count--;
    }
    return returnData;
}


/* Find out how many items are currently in the queue.
 * Return number of items in the queue (could be zero)
 */
int queueSize()
{
    return count;
}


/* Clear so we can reuse 
 */
void queueClear()
{
    int i = 0;
    for (i = 0; i < MAXSIZE; i++)
    {
        if (queue[i] != NULL)
            free(queue[i]);
        queue[i] = NULL;
    }
    /* reset head, tail and count */
    headIndex = 0;
    tailIndex = -1;
    count = 0;
}


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE QUEUE **/
void printDebug()
{
    int i, j;
    printf("arrayQueue - MAXSIZE is %d\n", MAXSIZE);
    printf("count = %d   headIndex=%d  tailIndex=%d\n",
	   count, headIndex, tailIndex);
    if (count > 0)
    {
	   printf("Contents: \n");
	   i = headIndex;
	   for (j = 0; j < count; j++)
	   {
            printf("\t\t%s\n", (char *) queue[i]);
            i = (i + 1) % MAXSIZE;
	   }
    }
}
