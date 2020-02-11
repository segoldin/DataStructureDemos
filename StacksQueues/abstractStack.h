/**
 *  abstractStack.h
 *
 *  Header file defining the operations that one can
 *  do on a generic or abstract stack. The elements of
 *  the list can be pointers to anything.
 *
 *  This can be implemented in a variety of ways.
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 *
 */

#ifndef ABSTRACTSTACK_H
#define ABSTRACTSTACK_H

/**
 * Push a data item onto the stack 
 * Note: this should be a dynamically allocated
 * copy of the data to be stored.
 *
 * Arguments:
 *   data      -   Pointer to generic data we want to add to stack   
 * Returns 1 if successful, 0 if we have an overflow.
 */
int push(void* data);


/**
 * Removes and returns the top item on the stack.
 * Note: this memory should be freed after it is used.
 * Returns NULL if the stack is empty (that is, underflow).
 */
void * pop();



/**
 *  Find out how many items are currently in the stack.
 * Return number of items in the stack (could be zero)
 */
int stackSize();


/**
 *  Clear so we can reuse 
 */
void stackClear();


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE STACK **/
void printDebug();

#endif
