/**
 *  linkedListStack.c
 *
 *  An implementation of abstractStack using a linked list.
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
#include "abstractStack.h"

/* Structure that represents one item of the list */
typedef struct _listitem
{
    void* pData;               /* Pointer to the data for this node */
    struct _listitem * pNext;  /* Link to the next item in the list */
} LISTITEM_T;


LISTITEM_T * head = NULL;      /* for a stack, we don't need the tail
                                * because everything happens at the 
                                * beginning of the list.
                                */

/**
 * Push a data item onto the stack 
 * Arguments:
 *   data      -   Pointer to generic data we want to add to stack   
 * Returns 1 if successful, 0 if we have an overflow.
 */
int push(void* data)
{
    int bOk = 1;    /* A linked list stack can never overflow! */
                    /* unless we run out of memory... */
    LISTITEM_T * newItem = (LISTITEM_T *)calloc(1,sizeof(LISTITEM_T));
    if (newItem == NULL)
       {
       bOk = 0;
       }
    else
       {
       newItem->pData = data;  /* store the data */
       newItem->pNext = head;
       head = newItem;
       }
    return bOk;
}


/* Removes and returns the top item on the stack.
 * Returns NULL if the stack is empty (that is, underflow).
 */
void * pop()
{
    LISTITEM_T * top = head;
    void * data = NULL;
    if (top != NULL)
       {
       data = top->pData;   /* this is what we will return */
       head = top->pNext;   /* make the following node the new head/top */
       free(top);          /* free the memory for this list item */
       }
    return data;
}



/* Find out how many items are currently in the stack.
 * Return number of items in the stack (could be zero)
 */
int stackSize()
{
    int count = 0;
    LISTITEM_T * current = head;
    while (current != NULL)
       {
       count++;
       current = current->pNext;
       }
    return count;
}


/* Clear so we can reuse 
 * We need to free both the data and the list items
 */
void stackClear()
{
    LISTITEM_T * current = head;
    while (current != NULL)
       {
       LISTITEM_T * discardNode = current;
       free(discardNode->pData);
       current = current->pNext;
       free(discardNode);
       }
    head = NULL;
}


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE STACK **/
void printDebug()
{

   if (head != NULL)
      {
      printf("Contents: \n");
      LISTITEM_T * current = head;
      while (current != NULL)
         {
	 printf("\t\t%s\n", (char*)current->pData);
         current = current->pNext;
	 }
      }
   else
      {
      printf("Stack is empty\n");
      }
}

