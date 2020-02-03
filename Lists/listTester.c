/*  
 *  listTester.c
 *
 *  Driver module that exercises an abstractList implementation.
 *
 *  This module can be linked with either arrayList or linkedList
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "abstractList.h"

int getMenuOption();


/* Main function, shows menu and then does what the user
 * has asked.
 */
int main(int argc, char* argv[])
{

    char input[64];
    char stringval[64];
    char* removedString = NULL;
    char* dupString = NULL;
    int retval = 0;
    
    int choice = getMenuOption();
    while (choice != 6)
    {
	switch (choice)
	{
	    case 1:
	        {
		retval = listInit();
		if (retval)
		    printf("List created or re-created\n");
		else
		    printf("Memory allocation error\n");
		break;
	        }
	    case 2:
	        {
		printf("About to call listDestroy\n");
		listDestroy();
		break;
	        }
	    case 3:
	        {
		printf("Enter string to add to list: ");
		fgets(input,sizeof(input),stdin);
		/* keep any blanks in the string */
		memset(stringval,0,sizeof(stringval));
		strncpy(stringval,input,strlen(input)-1);
		dupString = strdup(stringval);
		retval = listInsertEnd(dupString);
		if (retval == 1)
		    {
		    printf("Success - list now holds %d elements\n",
			   listSize());
		    }
		else if (retval == 0)
		    {
		    printf("No more room in list - list already has %d elements\n",
			   listSize());
		    }
                else if (retval < 0)
		    {
		    printf("List has not been initialized yet!\n");
		    }

		break;
		}
	    case 4:
	        {
		removedString = listRemoveEnd();
		if (removedString != NULL)
		    {
		    printf("Success - removed {%s}\nList now holds %d elements\n",
			   removedString, listSize());
		    free(removedString);
		    }
		else 
		    {
		    printf("List was empty or never initialized\n");
		    }
		break;
	        }
	    case 5:
	        {
		retval = listReset();
		if  (retval < 0)
		    {
		    printf("List has not been initialized yet!\n");
		    }
		else if (retval == 0)
		    {
		    printf("List is empty\n");
		    }
		else
		    {
		    char * listItem = NULL;
		    while ((listItem = listGetNext()) != NULL)
		       {
		       printf("Got item: %s\n",listItem);
		       }
		    }
		break;
		}
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
       printf("\nList Tester options:\n");
       printf("  1 - Initialize the list\n");
       printf("  2 - Destroy the list\n");
       printf("  3 - Insert item onto list\n");
       printf("  4 - Remove item from list\n");
       printf("  5 - Show all items on list\n");
       printf("  6 - Exit\n");
       printf("Which option? ");
       fgets(input,sizeof(input),stdin);
       sscanf(input,"%d",&option);
       if ((option > 6) || (option < 1))
           {
	   printf("Invalid selection - choose 1 to 6\n");
	   option = -1;
	   }
       }
    printf("\n");
    return option;
}

