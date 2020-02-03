/*
 *  abstractList.h
 *
 *  Header file defining the operations that one can
 *  do on a generic or abstract list. The elements of
 *  the list can be pointers to anything. The list stores
 *  the actual pointers as data; it does not make a copy
 *  of the data. However, destroying the list frees the
 *  pointers - so callers should make their own copies and
 *  pass those copies as arguments.
 *
 *  This can be implemented in a variety of ways.
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */

#ifndef ABSTRACTLIST_H
#define ABSTRACTLIST_H

/* Initialize or reinitialize the list. This may involve allocating memory. 
 * Returns 1 (true) if successful, 0 (false) if some error.
 * (e.g memory allocation error). Each time this function is
 * called, it will throw away any previous list.
 */
int listInit();


/* Throw away the data in the list and free any memory 
 * associated with this list.
 */
void listDestroy();

/* Find out how many items currently are stored in the list
 * Returns the number of elements (could be zero)
 * a -1 if the list has not been created/initialized.  
 */
int listSize();


/* Add a new element to the end of the list
 * Arguments:
 *   data     - pointer to the information to store in the list
 *              assumes that this pointer can be freed when
 *              the list is destroyed.
 * Returns the 1 if successful or 0 if there is no more 
 * room. Returns -1 if the list has not been created/initialized.   
 */
int listInsertEnd(void * data);


/* Removes the element at the end of the list and
 * returns the data stored there. Returns NULL 
 * if the list is empty or
 * if the list has not been initialized.  
 */
void* listRemoveEnd();


/* Resets the "current" list pointer to the beginning
 * of the list.
 * Arguments:
 * Returns 1 if successful, 0 if the list is empty,
 * -1 if the list has not been initialized.  
 */
int listReset();


/* Returns the data stored at the "current" list 
 * position, then moves the current position to the 
 * next position in the list.
 * Returns data if successful, null if we are
 * already at the end of the list or if the
 * list has not been initialized.  
 */
void* listGetNext();

/* Find out if the current list position is past the
 * end. 
 * Return 1 if the position is past the end of the list,
 * Return 0 if the position is not past the end.
 * Return -1 if the list has not been initialized.
 */
int listAtEnd();

#endif
