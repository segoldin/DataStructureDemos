/*    
 *   Header file for an abstract heap, that is, a data structure
 *   which always returns the largest (or smallest, depending on
 *   the initialization) item it holds
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */

#ifndef HEAP_H
#define HEAP_H

/* Initialize or reinitialize the heap.
 * Arguments
 *    compare    -   Function to compare two items 
 *                   Assumed to behave like strcmp
 *    bMaxHeap  -    If true, the heap extract function
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
int initHeap(int (*compare)(void* item1, void* item2),
              int bMaxHeap, int capacity);


/* Insert an item into the heap.
 * Argument 
 *    data    -   Item to be stored
 * Returns 1 if successful, 0 if some error occurred.
 */
int heapInsert(void* data);


/* Extract the largest (or smallest) item from the heap,
 * removing it and returning its data.
 * Returns data item. Note that the caller is responsible
 * for managing the memory for this data. If the
 * heap is empty or not initialized, returns NULL.
 */
void* heapExtract();


/* Return data that will be extracted on the next call to 
 * heapExtract. This data should NOT be freed!
 * Does NOT change the heap contents or structure. 
 * Returns NULL if the heap is empty or not initialized.
 */
void* heapPeek();


/* Return the current number of items in the heap.
 */
int heapSize();


/* Walk the heap as a tree, printing all data
 * as parent/child relations
 * Arguments
 *    toStringFunction - turns a data item into a printable string
 */
void treeWalkHeap(void (*toStringFunction)(char* buffer, void* data, int len));

#endif
  
