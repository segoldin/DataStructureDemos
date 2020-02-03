/*
 *  arrayList.c
 *
 *  Implementation of abstract list that an array.
 *  The arrays is dynamically allocated but fixed in size
 *  to 5 elements.
 *
 *  Note this list assumes that it has its own copies of all data, 
 *  and so it frees the data as part of destroy.
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
#include "abstractList.h"

/* maximum number of items a list can hold */
#define MAXSIZE 5

/* Current position the list */
int currentPosition = 0;

/* Last position for the list */
/* Will be -1 if the list has not been initialized */
int lastIndex = -1;

/* Pointer to the list itself */
/* Will be NULL if not initialized */
void ** arrayList = NULL;

/****************************************
 * Public functions
 */

/* Initialize or reinitialize the list. This may involve allocating memory. 
 * Returns 1 (true) if successful, 0 (false) if some error.
 * (e.g memory allocation error). Each time this function is
 * called, it will throw away any previous list.
 */
int listInit()
{
    int retval = 1; /* return value */
    if (arrayList != NULL)
       {
       listDestroy();    /* will also reset currentPosition, last Index */
       }
    arrayList = (void**) calloc(MAXSIZE,sizeof(void*));
    if (arrayList == NULL)  /* allocation error */
       {
       retval = 0;
       }
    return retval;
}

/* Throw away the data in the list and free any memory 
 * associated with this list.
 */
void listDestroy()
{
    int i = 0;
    if (arrayList == NULL)
	return; /* no list, so just ignore */
    for (i = 0; i <= lastIndex; i++)
	free(arrayList[i]);  /* free the data items */
    free(arrayList);
    arrayList = NULL;  /* now we can reuse */
    currentPosition  = 0;
    lastIndex = -1;
}


/* Find out how many items currently are stored in the list
 * Returns the number of elements (could be zero)
 * a -1 if the list has not been created/initialized.  
 */
int listSize()
{
   if (arrayList == NULL)
      return -1;  /* not initialized */
   else
      return (lastIndex + 1);
}


/* Add a new element to the end of the list
 * Arguments:
 *   data     - pointer to the information to store in the list
 *              assumes that this pointer can be freed when
 *              the list is destroyed.
 * Returns the 1 if successful or 0 if there is no more 
 * room. Returns -1 if the list has not been created/initialized.   
 */
int listInsertEnd(void * data)
{
   int retval = 1;  /* assume success */
   if (arrayList == NULL)
       retval = -1;  /* invalid handle */
   else if (lastIndex == (MAXSIZE - 1))
       retval = 0;   /* no more room in the list */
   else 
       {
       int pos = lastIndex + 1;
       arrayList[pos] = data;
       lastIndex = pos;
       }
   return retval;
}


/* Removes the element at the end of the list and
 * returns the data stored there. Returns NULL 
 * if the list is empty or
 * if the list has not been initialized.  
 */
void* listRemoveEnd()
{
   void* data = NULL;
   /* If list initialized */
   if (arrayList != NULL)
      {
      /* if there are any items in the list */ 
      if (lastIndex >= 0)	  
         {
         int pos = lastIndex;
         data = (void*) arrayList[pos];
         lastIndex -= 1;
         /* adjust current position (back up) if it was
          * pointing to the end of the list 
	  */
	 if (currentPosition > lastIndex)
	     currentPosition = lastIndex;
         }
      }
   return data;
}

/* Resets the "current" list pointer to the beginning
 * of the list.
 * Arguments:
 * Returns 1 if successful, 0 if the list is empty,
 * -1 if the list has not been initialized.  
 */
int listReset()
{
   int retval = 1;  /* assume success */ 
   if (arrayList == NULL)
       retval = -1;  /* invalid handle */
   else if (lastIndex == -1)
       retval = 0;   /* list is empty */
   else
       currentPosition = 0;
   return retval;
}

/* Returns the data stored at the "current" list 
 * position, then moves the current position to the 
 * next position in the list.
 * Returns data if successful, null if we are
 * already at the end of the list or if the
 * list has not been initialized.  
 */
void* listGetNext()
{
    void * data = NULL;
   /* If list is initialized */
   if (arrayList != NULL)
      {
      /* if there are any items in the list */ 
      if ((lastIndex >= 0) && 
          (currentPosition <= lastIndex))	  
         {
         int pos = currentPosition;
         data = arrayList[pos];
         currentPosition++;
         }
      }
   return data;
}

/* Find out if the current list position is past the
 * end. 
 * Return 1 if the position is past the end of the list,
 * Return 0 if the position is not past the end.
 * Return -1 if the list has not been initialized.
 */
int listAtEnd()
{
    int retval = 0;
    if (arrayList == NULL)
	retval = -1;  /* not initialized */
    else if (currentPosition > lastIndex)
	retval = 1;   /* this means we're at the end */
    return retval;
}
