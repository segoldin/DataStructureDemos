/*  
 *  arrayHeap.c
 *
 *  Array based implementation of a heap as defined by abstractHeap.h
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractHeap.h"

/* Structure that represents one item of the heap */
typedef struct _listitem
{
    void *data;			/* Pointer to the data for this node */
} LISTITEM_T;

#define SIZEINC 100		/* how many items we add when we run out of space */

/* Global data items for managing the heap */

static int bMaxHeap = 1;	/* flag for direction of comparison */
static int heapCapacity = 0;	/* current capacity of array */
static int size = 0;		/* number of items currently in heap */
static int reverse = -1;	/* reverse the result of compare */
static LISTITEM_T *treeArray = NULL;	/* actual data storage */


/* comparison function must work like strcmp.
 * Return -1 if data1 < data2, 0 if they are equivalent, 1 if data1 > data2 */
int (*compareFn) (void *data1, void *data2) = NULL;

/* macros to let us get from an item to its parent or from a parent
 * to its left and right children
 */
#define parent(n)  ((int) (((n)-1)/2))
#define left(n)    (((n) * 2) + 1)
#define right(n)   (((n) * 2) + 2)

/* Swap the data for items a and b in the treeArray */
void swap(a, b)
{
    void *temp;
    temp = treeArray[a].data;
    treeArray[a].data = treeArray[b].data;
    treeArray[b].data = temp;
}

/***** PUBLIC FUNCTIONS ***/

/* Initialize or reinitialize the heap.
 * Arguments
 *    compare    -   Function to compare two items 
 *                   Assumed to behave like strcmp
 *    bMax      -    If true, the heap extract function
 *                   should return the largest value. If
 *                   false, return the smallest. Either way
 *                   the compare function is assumed to behave
 *                   like strcmp, that is, return -1 if item1 is
 *                   smaller than item2, 0 if they are equal,
 *                   1 if item1 is larger than item2
 *    capacity  -    Initial capacity (in items). Use to reduce the
 *                   number of memory allocations if we use an array 
 *                   implementation.
 * Return 1 for success, 0 if memory allocation failed.
 */
int initHeap(int (*compare) (void *item1, void *item2),
	     int bMax, int capacity)
{
    int bStatus = 1;
    if (treeArray != NULL)
    {
	free(treeArray);
	treeArray = NULL;
	size = 0;
	heapCapacity = 0;
    }
    heapCapacity = capacity;
    compareFn = compare;
    bMaxHeap = bMax;
    if (bMax)
	reverse = -1;
    else
	reverse = 1;
    /* try allocating the array */
    treeArray = (LISTITEM_T *) calloc(heapCapacity, sizeof(LISTITEM_T));
    if (treeArray == NULL)
    {
	bStatus = 0;
    }
    return bStatus;
}

/* Insert an item into the heap.
 * Argument 
 *    data    -   Item to be stored
 * Returns 1 if successful, 0 if some error occurred.
 */
int heapInsert(void *data)
{
    int ip = 0;			/* item position */
    int pp = 0;			/* parent position */
    /* is the heap initialized? */
    if (treeArray == NULL)
	return 0;
    /* do we have enough room? */
    if (size >= heapCapacity)
    {
	int p = 0;
	LISTITEM_T *temp = NULL;
	heapCapacity += SIZEINC;
	temp = (LISTITEM_T *) calloc(heapCapacity, sizeof(LISTITEM_T));
	if (temp == NULL)
	    return 0;		/* allocation failure */
	for (p = 0; p < size; p++)	/* copy the data - realloc doesn't work! */
	    temp[p].data = treeArray[p].data;
	free(treeArray);
	treeArray = temp;
    }
    /* store the data in the next available slot */
    treeArray[size].data = data;
    /* now "heapify" the data, bubbling it up until 
     * it is in the right location
     */
    ip = size;
    pp = parent(ip);
    while ((ip > 0) &&
	   (reverse * compareFn(treeArray[ip].data, treeArray[pp].data) < 0))
    {
	swap(ip, pp);
	/* move up to the next level of the tree */
	ip = pp;
	pp = parent(ip);
    }
    size += 1;
    return 1;
}

/* Extract the largest (or smallest) item from the heap,
 * removing it and returning its data.
 * Returns data item. Note that the caller is responsible
 * for managing the memory for this data. If the
 * heap is empty or not initialized, returns NULL.
 */
void *heapExtract()
{
    void *returnData = NULL;
    if ((treeArray != NULL) && (size > 0))
    {
	int ip = 0;		/* item pos */
	int lc = 0;		/* position of left child */
	int rc = 0;		/* position of right child */
	int swapp = 0;		/* position of item to swap with ip */
	/* the first element is always the root - max or min */
	returnData = treeArray[0].data;
	/* copy the last element in the array to the first element */
	treeArray[0].data = treeArray[size - 1].data;
	size -= 1;
	/* now push the new top down to its correct location */
	while (1)
	{
	    lc = left(ip);
	    rc = right(ip);
	    /* if the left child is smaller than the current */
	    if ((lc < size) &&
		(reverse * compareFn(treeArray[lc].data, treeArray[ip].data) <
		 0))
	    {
		swapp = lc;
	    }
	    else
	    {
		swapp = ip;
	    }
	    if ((rc < size) &&
		(reverse *
		 compareFn(treeArray[rc].data, treeArray[swapp].data) < 0))
	    {
		swapp = rc;
	    }
	    if (swapp == ip)	/* we are done */
	    {
		break;
	    }
	    else
	    {
		swap(ip, swapp);
		ip = swapp;
	    }
	}
    }
    return returnData;
}


/* Return data that will be extracted on the next call to 
 * heapExtract. This data should NOT be freed!
 * Does NOT change the heap contents or structure. 
 * Returns NULL if the heap is empty or not initialized.
 */
void *heapPeek()
{
    void *returnData = NULL;
    if ((treeArray != NULL) && (size > 0))
    {
	returnData = treeArray[0].data;
    }
    return returnData;
}



/* Return the current number of items in the heap.
 */
int heapSize()
{
    return size;
}

/* Walk the heap as a tree, printing all data
 * as parent/child relations
 * Arguments
 *    toStringFunction - turns a data item into a printable string
 */
void treeWalkHeap(void (*toStringFunction) (char *buffer, void *data, int len))
{
    int p = 0;
    int lp = 0;
    int rp = 0;
    char buffer[128];
    printf("** Current Tree **\n");
    for (p = 0; p < size; p++)
    {
	lp = left(p);
	rp = right(p);
	toStringFunction(buffer, treeArray[p].data, sizeof(buffer));
	printf("Parent (%d) data: |%s|\n", p, buffer);
	if (lp < size)
	{
	    toStringFunction(buffer, treeArray[lp].data, sizeof(buffer));
	    printf("     Left child  (%d): |%s|\n", lp, buffer);
	}
	if (rp < size)
	{
	    toStringFunction(buffer, treeArray[rp].data, sizeof(buffer));
	    printf("     Right child (%d): |%s|\n", rp, buffer);
	}
    }
}
