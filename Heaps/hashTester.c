/*
 *  heapTester.c 
 *
 *  Driver program for testing heap ADT
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
#include <ctype.h>
#include "abstractHeap.h"

int getMenuOption();

/* change source string to upper case and store in
 * destination string. 'len' is size of the destination.
 */
void upcase(char *destination, char *source, int len)
{
    int i;
    for (i = 0; (i < len) && (i < strlen(source)); i++)
	destination[i] = toupper(source[i]);
}

/* comparison function for strings, basically strcmp */
int stringCompare(void *item1, void *item2)
{
    int result = 0;
    result = (strcmp((char *) item1, (char *) item2));
    if (result > 0)
	result = 1;
    else if (result < 0)
	result = -1;
    return result;
}

/* Case insensitive comparison function for strings  */
int caseInsensitiveStringCompare(void *item1, void *item2)
{
    int result = 0;
    char buffer1[128];
    char buffer2[128];
    upcase(buffer1, (char *) item1, sizeof(buffer1));
    upcase(buffer2, (char *) item2, sizeof(buffer2));
    result = (strcmp(buffer1, buffer2));
    if (result > 0)
	result = 1;
    else if (result < 0)
	result = -1;
    return result;
}


/* Function to use in treeWalkHeap. 
 * Arguments
 *    buffer    place to write the string value of the data
 *    data      data object to write
 *    len       length of buffer
 */
void stringToString(char *buffer, void *data, int len)
{
    strncpy(buffer, (char *) data, len);
}


/* Loop asking for actions until the user chooses to exit */
int main(int argc, char *argv[])
{
    int capacity = 0;
    int bLargest = 0;
    char input[64];
    char *removedString = NULL;
    char *newString = NULL;
    int retval = 0;
    int i = 0;
    int choice = 0;

    choice = getMenuOption();
    while (choice != 8)
    {
	memset(input, 0, sizeof(input));
	newString = NULL;
	removedString = NULL;
	switch (choice)
	{
	case 1:		/* initialize */
	    printf("Enter initial capacity (number of items): ");
	    fgets(input, sizeof(input), stdin);
	    sscanf(input, "%d", &capacity);
	    if (capacity <= 0)
	    {
		printf(">>> Error! capacity should be positive\n");
	    }
	    else
	    {
		printf("Do you want a min heap (N = max heap)? ");
		fgets(input, sizeof(input), stdin);
		if ((input[0] == 'Y') || (input[0] == 'y'))
		    bLargest = 0;
		else
		    bLargest = 1;
		if (!initHeap(stringCompare, bLargest, capacity))
		{
		    printf(">>> Error! Cannot initialize heap\n");
		}
		else
		{
		    printf("Successfully initialized the heap\n");
		}

	    }
	    break;
	case 2:		/* insert an item into the heap */
	    memset(input, 0, sizeof(input));
	    printf("Enter string to insert: ");
	    fgets(input, sizeof(input), stdin);
	    input[strlen(input) - 1] = '\0';
	    newString = strdup(input);
	    if ((strlen(newString) == 0))
	    {
		printf(">>> Error! String is empty\n");
		free(newString);
	    }
	    else
	    {
		retval = heapInsert(newString);
		if (retval == 1)
		{
		    printf("String |%s| inserted in heap\n", newString);
		}
		else
		{
		    printf
			(">>> Memory allocation error or heap not initialized!\n");
		}
	    }
	    break;
	case 3:		/* remove the next item from the heap */
	    removedString = heapExtract();
	    if (removedString != NULL)
	    {
		printf("Extracted |%s|\n", removedString);
		free(removedString);
		removedString = NULL;
	    }
	    else
	    {
		printf
		    (">>> Error extracting - heap not initialized or empty!\n");

	    }
	    break;
	case 4:		/* peek at the next item from the heap */
	    removedString = heapPeek();
	    if (removedString != NULL)
	    {
		printf("Next item to be returned |%s|\n", removedString);
	    }
	    else
	    {
		printf
		    (">>> Error peeking - heap not initialized or empty!\n");

	    }
	    break;


	case 5:		/* get size of heap */
	    retval = heapSize();
	    printf("Current size of heap is %d items\n", retval);
	    break;
	case 6:		/* remove and print all items in order */
	    if (heapSize() == 0)
	    {
		printf("Heap is empty or not initialized\n");
	    }
	    else
	    {
		removedString = heapExtract();
		while (removedString != NULL)
		{
		    printf("Removed item: |%s|\n", removedString);
		    free(removedString);
		    removedString = NULL;
		    removedString = heapExtract();
		}
	    }
	    break;
	case 7:		/* remove and print all items in order */
	    treeWalkHeap(&stringToString);
	    break;
	default:
	    printf("Invalid option - we should never get here!\n");
	}			/* end switch  */
	choice = getMenuOption();
    }				/* end while loop */

/* exit here - we're done */
}


/* Show menu of options. Return the user-selected option
 */
int getMenuOption()
{
    char input[32];
    int option = -1;
    while (option < 0)
    {
	printf("\nHeap Tester options:\n");
	printf("  1 - Initialize heap\n");
	printf("  2 - Insert an item into the heap\n");
	printf("  3 - Extract next item from the heap\n");
	printf("  4 - Peek at next item without removing\n");
	printf("  5 - Print current heap size\n");
	printf("  6 - Extract and print all items in order\n");
	printf("  7 - Walk the heap as a tree without removing\n");
	printf("  8 - Exit\n");
	printf("Which option? ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%d", &option);
	if ((option > 8) || (option < 1))
	{
	    printf("Invalid selection - choose 1 to 6\n");
	    option = -1;
	}
    }
    printf("\n");
    return option;
}
