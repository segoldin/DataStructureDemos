/*
 *  simpleTreeTester.c 
 *
 *  Driver program for illustrating a simple binary tree
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
#include "simpleBinaryTree.h"

int getMenuOption();

/* Loop asking for actions until the user chooses to exit */
int main(int arc, char argv[])
{
    int handle = 0;
    char input[64];
    char stringval[64];
    char *removedString = NULL;
    char *newString = NULL;
    int retval = 0;
    TREE_T *pTree = NULL;

    int choice = getMenuOption();
    while (choice != 9)
    {
	switch (choice)
	{
	case 1:		/* create the tree */
	    if (pTree != NULL)
	    {
		freeTree(pTree);
		pTree = NULL;
	    }
	    pTree = createTree();
	    if (pTree == NULL)
	    {
		printf("Memory allocation error trying to create tree\n");
		printf("Exiting...\n");
		exit(1);
	    }
	    break;
	case 2:		/* insert */
	    if (pTree != NULL)
	    {
		printf("Insert what string in tree? ");
		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';
		newString = strdup(input);
		printf("     ");
		if (!insertItem(pTree, newString))
		{
		    printf("Memory allocation error trying to insert item\n");
		}
		else
		{
		    printf("Successfully added |%s| to tree\n", newString);
		}
	    }
	    else
	    {
		printf("You must create the tree first!\n");
	    }
	    break;
	case 3:		/* print tree - preorder */
	    if (pTree != NULL)
	    {
		printf("Preorder Tree Traversal\n");
		printTree(pTree, PREORDER);
	    }
	    else
	    {
		printf("You must create the tree first!\n");
	    }
	    break;
	case 4:		/* print tree - inorder */
	    if (pTree != NULL)
	    {
		printf("Inorder Tree Traversal\n");
		printTree(pTree, INORDER);
	    }
	    else
	    {
		printf("You must create the tree first!\n");
	    }
	    break;
	case 5:		/* print tree - post order */
	    if (pTree != NULL)
	    {
		printf("Postorder Tree Traversal\n");
		printTree(pTree, POSTORDER);
	    }
	    else
	    {
		printf("You must create the tree first!\n");
	    }
	    break;
	case 6:		/* print tree - level order */
	    if (pTree != NULL)
	    {
		printf("Level Order Tree Traversal\n");
		printTree(pTree, LEVELORDER);
	    }
	    else
	    {
		printf("You must create the tree first!\n");
	    }
	    break;
	case 7:		/* print leaf nodes */
	    if (pTree != NULL)
	    {
		printLeafData(pTree);
	    }
	    else
	    {
		printf("You must create the tree first!\n");
	    }
	    break;
	case 8:		/* print max depth */
	    {
		if (pTree != NULL)
		{
		    int depth = maxTreeDepthG(pTree);
		    //int depth = maxTreeDepth(pTree); /* loop based */
		    //int depth = maxTreeDepthR(pTree); /* special recursive */
		    if (depth > 0)
			printf("Maximum tree depth is %d\n", depth);
		    else
			printf("No nodes added to tree yet\n");
		}
		else
		{
		    printf("You must create the tree first!\n");
		}
		break;
	    }
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
	printf("\nSimple Tree Tester options:\n");
	printf("  1 - Create, or empty and recreate, tree\n");
	printf("  2 - Insert an item into the tree\n");
	printf("  3 - Print tree contents - Preorder traveral\n");
	printf("  4 - Print tree contents - Inorder traveral\n");
	printf("  5 - Print tree contents - Postorder traveral\n");
	printf("  6 - Print tree contents - Levelorder traveral\n");
	printf("  7 - Print all leaf nodes\n");
	printf("  8 - Print maximum depth of tree\n");
	printf("  9 - Exit\n");
	printf("Which option? ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%d", &option);
	if ((option > 9) || (option < 1))
	{
	    printf("Invalid selection - choose 1 to 8\n");
	    option = -1;
	}
    }
    printf("\n");
    return option;
}
