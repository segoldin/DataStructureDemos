/*
 *  linkedList.c
 *
 *  Implementation of abstract list that uses a linked list
 *  Lists can be of unlimited length.
 *
 *  Note this list assumes that it has its own copies of all data, 
 *  and so it frees the data as part of destroy.
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */

#include <stdlib.h>
#include <stdio.h>
#include "abstractList.h"


/* Structure that represents one item of the list */
typedef struct _listitem
{
    void* pData;               /* Pointer to the data for this node */
    struct _listitem * pNext;  /* Link to the next item in the list */
} LISTITEM_T;

/* Structure to represent a list. Keeps track of head and tail of the 
 * list as well as the current node (for iterating through the list)
 */
typedef struct
{
    LISTITEM_T * head;    /* first item in list */  
    LISTITEM_T * tail;    /* last item in the list */
    LISTITEM_T * current; /* current item in the list */ 
} LIST_T;

/* Pointer to our list */
LIST_T * linkedList = NULL;

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
   int retval = 1; /* return value. Assume success */
   if (linkedList != NULL)
   {
      listDestroy();
   }
   linkedList = (LIST_T*) calloc(1,sizeof(LIST_T));
   /* note that since we use calloc, the head, tail and current 
    * will all be initialized to NULL */
   if (linkedList == NULL)
   {
      retval = 0;   /* allocation error */
   }
   return retval;
}


/* Throw away the data in the list and free any memory 
 * associated with this list.
 */
void listDestroy()
{
   if (linkedList != NULL) /* if list has been initialized  */
   {
      LISTITEM_T * pThisItem = linkedList->head;
      while (pThisItem != NULL)
      {
         LISTITEM_T * pNext = pThisItem->pNext;
         free(pThisItem->pData); /* Free the data for this list item */  
         free(pThisItem);        /* Free the item itself */
         pThisItem = pNext;      /* Reset current item to next item in
				   * the list if any. If pNext is null
				   * then we are at the end of the list
				   * and the loop will exit.*/
      }
      free(linkedList);
      linkedList = NULL;  /* now we can reuse */
   }
}

/* Find out how many items currently are stored in the list
 * Returns the number of elements (could be zero)
 * a -1 if the list has not been created/initialized.  
 */
int listSize()
{
   int count = 0;
   if (linkedList == NULL)
   {
      count = -1;  /* invalid handle - just ignore */
   }
   else
   {
      /* Traverse the list and count */
      /* This could also be implemented by keeping track 
       * in the LIST_T structure every time we insert or remove
       * an item. */
      LISTITEM_T * pThisItem = linkedList->head;
      while (pThisItem != NULL) /* if list is empty, we will never */
                                /* enter the loop, and count will be 0 */
      {
         count += 1;
         pThisItem = pThisItem->pNext;
      }
   }
   return count;
}

/* Add a new element to the end of the list
 * Arguments:
 *   data     - pointer to the information to store in the list
 *              assumes that this pointer can be freed when
 *              the list is destroyed.
 * Returns the 1 if successful or 0 if there is no more 
 * room. Returns -1 if the list has not been created/initialized.   
 *  Note that the linked list version of this function
 *  will NEVER return 0. However, we also can get an out of memory
 *  error in this function, which cannot occur in the array version.  
 */
int listInsertEnd(void * data)
{
   int retval = 1;  /* assume success */
   if (linkedList == NULL)
       retval = -1;  /* not initialized */
   else 
   {
      LISTITEM_T * pTail = linkedList->tail;
      LISTITEM_T * pNew = (LISTITEM_T *) calloc(1,sizeof(LISTITEM_T));
      if (pNew == NULL)
      {
         retval = -1;  /* allocation error */
      }
      else  /* allocation succeeded, so we can continue */
      {
         pNew->pData = data; /* store data in the item */
         if (pTail == NULL)  /* if the list is currently empty */
         {
            linkedList->head = pNew;  /* new item is head as well as tail*/
            linkedList->current = pNew;
         }
         else
         {
            pTail->pNext = pNew;     /* add the item as the next item after the current 'tail*/
         }
         linkedList->tail = pNew;  /* Either way, now our new item is the tail (last item on the list) */
      }  /* end else allocation is okay */
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
   /* If list exists */
   if (linkedList == NULL)
      return NULL;
   /* if there are any items in the list */ 
   if (linkedList->tail != NULL)	  
   {
      LISTITEM_T* pTail  = linkedList->tail; /* this is the one we will remove.*/
      LISTITEM_T* pThisItem = linkedList->head;
      data = (void*) pTail->pData;
         /* If head == tail, there's only one item in the
          * list. Deal with this special case first.*/
      if (pThisItem == pTail)
      {
         linkedList->head = NULL;  /* when we remove the tail the list will be empty.*/
         linkedList->tail = NULL;
         linkedList->current = NULL;
      }
      else
      { 
   	   /* otherwise we must find the second-to-last list item
	       * which will be the new tail. The only way to do
	       * this with a single-linked list is to start from
          * the beginning of the list 
	       */
         while ((pThisItem != NULL) && (pThisItem->pNext != pTail))
         {
            pThisItem = pThisItem->pNext;		
         }
         /* When we exit the loop above, pThisItem is the item right
          * before pTail, that is, the second to last item on the
	       * list. After we remove the current tail, this is the
	       * item that will be come the new tail.  */
         pThisItem->pNext = NULL;   /* remove old tail */
         linkedList->tail = pThisItem; /* second to last item is new tail */
         /* adjust current position (back up) if it was
	       * pointing to the end of the list */
         if (linkedList->current == pTail)
         {
            linkedList->current = pThisItem;
         }
      }
      /* Finally we can free the old tail item's memory */
      free(pTail);          
   }
   return data;  /* Will be null if list was empty or handle was invalid */
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
   if (linkedList == NULL)
       retval = -1;  /* list not initialized */
   else if (linkedList->head == NULL)
       retval = 0;   /* list is empty */
   else  /* Just set current to be the head of the list */
   {
      linkedList->current = linkedList->head;
   }
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
   /* If the list has been initialized */
   if (linkedList != NULL)
   {
      /* if there are any items in the list 
       * and we are not already at the end
       */ 
      if (linkedList->current != NULL)
      {
         data = linkedList->current->pData;
	      /* advance the current pointer to the next item */
         linkedList->current = linkedList->current->pNext;
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
   int retval = 0;/* assume we are not at the end */
   if (linkedList == NULL)
      retval = -1;  /* invalid handle */
      else if (linkedList->current == NULL)
         retval = 1;   /* this means we're at the end */
   return retval;
}

