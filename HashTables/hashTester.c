/*
 *  hashTester.c 
 *
 *  Driver program for testing hash tables with string keys
 *  Supplies several hash functions ranging from silly to reasonable
 *
 *  User can select the hash function based on the command line argument
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
#include "abstractHashTable.h"

int getMenuOption();

/* Rather stupid hash function that hashes all
 * strings of the same length to the same table element 
 */
unsigned int stringLengthHash(char* key)
{
    unsigned int result = 0;
    int size = hashTableSize();
    result = strlen(key) % size;
    return result;
}


/* Slightly more intelligent hash function that uses the
 * sum of ascii values in the key as the basis for the hash
 */
unsigned int asciiHash(char* key)
{
    unsigned int result = 0;
    int size = hashTableSize();
    int i = 0;
    for (i = 0; i < strlen(key); i++)
	result += (int) key[i];
    result = result % size;   /* make it fit in the table size */ 
    return result;
}


/* Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHash(char* key)
{
    unsigned int result = 0;
    unsigned int tmp = 0;
    int size = hashTableSize();
    int i = 0;
    for (i = 0; i < strlen(key); i++)
        {
	/* shift up four bits then add in next char */ 
	result = (result << 4) + key[i];
        if (tmp = (result & 0xf0000000))  /* if high bit is set */
	    {
	    /* XOR result with down shifted tmp */
	    result = result ^ (tmp >> 24);
            /* then XOR with tmp itself */
	    result = result ^ tmp;
	    }
        }
    result = result % size;   /* make it fit in the table size */ 
    return result;
}


/* Show the usage message showing how to choose a 
 * hash function
 */
void usage()
{
    printf("Missing or invalid required argument\n");
    printf("Usage:  hashTester [s|a|b]\n");
    printf("   s  ==> Use string length hash function\n");
    printf("   a  ==> Use ascii hash function\n");
    printf("   b  ==> Use bitwise hash function\n\n");
    exit(0);
}

/* Loop asking for actions until the user chooses to exit */
int main(int argc, char *argv[])
{
    int capacity = 0;
    char input[64];
    char key[128];
    char* dataString = NULL;
    int retval = 0;
    int i = 0;
    int choice = 0;
    int bCollision = 0;
    unsigned int (*hashFn)(char* key) = NULL;
    if (argc < 2)
      usage();  /* will exit */
    if (argv[1][0] == 's')
      { 
      hashFn = &stringLengthHash;
      printf("Using string length hash function\n"); 
      }
    else if (argv[1][0] == 'a')
      {
      hashFn = &asciiHash;
      printf("Using ascii hash function\n"); 
      }
    else if (argv[1][0] == 'b')
      {
      hashFn = &bitwiseOpHash;
      printf("Using bitwise operator hash function\n"); 
      }
    else 
      usage();  /* will exit */

    choice = getMenuOption();
    while (choice != 5)
    {
        memset(input,0,sizeof(input));
        dataString = NULL;
	memset(key,0,sizeof(key));
	switch (choice)
	{
	    case 1:  /* initialize  */ 
                printf("Enter size (number of items, should be prime): ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&capacity);
		if (capacity <= 1)
		   {
		   printf(">>> Error! capacity should be positive\n");
		   }
                else
		   {
		   if (!hashTableInit(capacity,hashFn))
		      {
		      printf(">>> Error! Cannot initialize hash table\n");
		      }
                   else
		      {
		      printf("Successfully initialized the hash table\n");
		      }

		   }
		break;
	    case 2:  /* insert an item into the hash table */
                memset(input,0,sizeof(input));
		printf("Enter key: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",key);
		printf("Enter data (string): ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		dataString = strdup(input);
                if ((strlen(key) == 0) || (strlen(dataString) == 0))
		   {
		   printf(">>> Error! A string is empty\n");
		   free(dataString);
		   }
                else
		   { 
		   retval = hashTableInsert(key,dataString,&bCollision);
		   if (retval == 1) 
		      {
		      printf(
                         "String |%s| inserted in hashTable with key |%s|\n",
	                 dataString,key);
		      if (bCollision)
                          printf("Collision occurred\n");
		      else
                          printf("No collision\n");
                      printf("Hash table now contains %d items, %d slots\n",
			     hashTableItemCount(), hashTableSize());
		      }
		   else 
		      {
		      printf(">>> Memory allocation error or table not initialized!\n");
		      }
		   }
		break;
	    case 3: /* lookup an item in the hashTable */
                memset(input,0,sizeof(input));
		printf("Enter key: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",key);
                dataString = hashTableLookup(key);
                if (dataString != NULL)
		   {
		   printf("Found data |%s|, associated with key |%s|\n",
			  dataString, key);
                   /* don't free it because it's still in the table! */
		   }
                else
		   {
		   printf(
   	       ">>> Key not found - or table not initialized\n");

		   }
		break;

	    case 4: /* remove an item from the hashTable */
                memset(input,0,sizeof(input));
		printf("Enter key: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",key);
                dataString = hashTableRemove(key);
                if (dataString != NULL)
		   {
		   printf("Removed |%s|, associated with key |%s|\n",
			  dataString, key);
		   free(dataString);
		   dataString = NULL;
		   printf("Hash table now contains %d items, %d slots\n",
			     hashTableItemCount(), hashTableSize());
		   }
                else
		   {
		   printf(
   	       ">>> Error removing - table not initialized or key not found\n");

		   }
		break;
	    default:
	        printf("Invalid option - we should never get here!\n");
	}  /* end switch  */
	choice = getMenuOption();
    }      /* end while loop */

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
       printf("  1 - Initialize hash table\n");
       printf("  2 - Insert an item into the table\n");
       printf("  3 - Lookup an item in the table\n");
       printf("  4 - Remove an item from the table\n");
       printf("  5 - Exit\n");
       printf("Which option? ");
       fgets(input,sizeof(input),stdin);
       sscanf(input,"%d",&option);
       if ((option > 5) || (option < 1))
           {
	   printf("Invalid selection - choose 1 to 6\n");
	   option = -1;
	   }
       }
    printf("\n");
    return option;
}

