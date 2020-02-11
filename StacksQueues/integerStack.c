/**
 *  integerStack.c
 *
 *  This is an array-based stack whose elements are integers.
 *
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 *
 */
#include <stdio.h>
#include "integerStack.h"

#define MAXSIZE 100

int stack[MAXSIZE];   /* this is where we store the stack data */
int top = -1;         /* the zeroth element is the base of the stack */

/**
 * Push a data item onto the stack 
 * Arguments:
 *   intdata      -   integer value to be pushed  
 * Returns 1 if successful, 0 if we have an overflow.
 */
int pushInt(int intdata)
{
    int bOk = 0;
    if (top < MAXSIZE - 1)
       {
       top++;
       stack[top] = intdata;
       bOk = 1; 	
       } 
    return bOk; 
}


/**
 * Removes and returns the top item on the stack.
 * Returns special value -9999 if the stack is empty 
 * (that is, underflow).
 */
int popInt()
{
   int val = UNDERFLOW;
   if (top >= 0)
      {
      val = stack[top];
      top--;
      }   
   return val; 
}


/**
 *  Find out how many items are currently in the stack.
 * Return number of items in the stack (could be zero)
 */
int stackSizeInt()
{
    return top+1;
}


/**
 *  Clear so we can reuse 
 *  All we really need to do is reset top
 */
void stackClearInt()
{
    top = -1;
}


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE STACK **/
void printDebugInt()
{
    int i;
    printf("%s","[STACK TOP]\n");
    for (i = top; i >= 0; i++)
        printf("%d\n",stack[i]);
    printf("%s","[STACK BOTTOM]\n");
}

