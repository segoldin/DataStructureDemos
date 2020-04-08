/*
 * treeHeapTester
 *
 * Min heap implemented as partially sorted binary tree.
 * This is not a general heap. Instead it demonstrates the
 * complexity of implementing a heap using an actual binary
 * tree as opposed to the conventional array.
 *
 * Includes a simple queue as part of the module, for breadth first
 * traversals and insertions.
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
#include <math.h>

typedef struct _treenode
{
    int nodeValue;		/* value to be stored in the heap */
    struct _treenode *left;	/* link to left child */
    struct _treenode *right;	/* link to right child */
    struct _treenode *parent;	/* backwards link to parent
				 * for convenience
				 */
} TREENODE_T;

/* To do level order insertion we need a queue */
/* Rather than linking in another module, a local queue is
 * defined, after the main
 */
void localQueueClear();
void localEnqueue(TREENODE_T *);
TREENODE_T *localDequeue();


/* global pointers to root and last added node */
TREENODE_T *pRoot = NULL;	/* root node */
TREENODE_T *pLastAdded = NULL;	/* keep track of the last added, for
				 * convenience */

/* Do a breadth first (level order) traversal to
 * discover the node that is the latest added position
 * Returns a pointer to that node
 */
TREENODE_T *findLastNode()
{
    TREENODE_T *lastNode = NULL;
    TREENODE_T *currentNode = NULL;
    if (pRoot == NULL)
	return NULL;
    /* since we doing a traversal in level order, we need a queue */
    localQueueClear();
    localEnqueue(pRoot);
    /* the last node we find on the queue will be the final
     * one in the tree.
     */
    while ((currentNode = localDequeue()) != NULL)
    {
	lastNode = currentNode;
	if (currentNode->left)
	{
	    localEnqueue(currentNode->left);
	}
	if (currentNode->right)
	{
	    localEnqueue(currentNode->right);
	}
    }
    return lastNode;
}

/* Do a breadth first (level order) traversal.
 * At each node, print the current node value and its
 * children, so we can verify that the heap contraint
 * is being followed.
 */
void printTree()
{
    TREENODE_T *currentNode = NULL;
    if (pRoot == NULL)
    {
	printf("Tree is now empty!");
	return;
    }
    int nodecount = 0;		/* how many nodes at this level */
    int level = 0;		/* level of tree - starts at 0 for root */
    int bPrintLevel = 1;	/* flag to print whenever level changes */
    printf("\nCurrent Tree Contents\n");
    /* since we doing a traversal in level order, we need a queue */
    localQueueClear();
    localEnqueue(pRoot);
    /* the last node we find on the queue will be the final
     * one in the tree.
     */
    while ((currentNode = localDequeue()) != NULL)
    {
	if (bPrintLevel)
	{
	    printf("LEVEL %d\n", level);
	    bPrintLevel = 0;
	}
	nodecount++;
	/* each level can hold at most 2**level nodes */
	if (nodecount == pow(2, level))
	{
	    level++;
	    nodecount = 0;
	    bPrintLevel = 1;
	}
	printf("Current node %d\n", currentNode->nodeValue);
	if (currentNode->left)
	{
	    printf("\tLeft child %d\n", currentNode->left->nodeValue);
	    localEnqueue(currentNode->left);
	}
	else
	    printf("\tNo left child\n");
	if (currentNode->right)
	{
	    printf("\tRight child %d\n", currentNode->right->nodeValue);
	    localEnqueue(currentNode->right);
	}
	else
	    printf("\tNo right child\n");
    }
}

/* Swap a child and parent node. This involves
 * adjusting not only the links of these nodes
 * but also the "grandparent" and "grandchildren"
 * Used by both swapUp() - when we add a new node
 * to the tree - and swapDown() - when we remove
 * a node then move the last added to the root.
 * Arguments
 *    parent   -   current parent node
 *    child    -   current child node
 * Note that this function does NOT
 * change the value of the global pRoot, but this
 * might be necessary after the swap. This is
 * handled by the calling function.
 */
void swap(TREENODE_T *parent, TREENODE_T *child)
{
    TREENODE_T *grandparent = parent->parent;
    /* left and right 'grandchildren' of parent */
    TREENODE_T *nodeLeft = child->left;
    TREENODE_T *nodeRight = child->right;
    /* left and right children of the parent - one of these must be 'child' */
    TREENODE_T *parentLeft = parent->left;
    TREENODE_T *parentRight = parent->right;
    if (parentLeft == child)	/* this node is left child */
    {
	/* Parent becomes my left child */
	child->left = parent;
	/* My parent's parent becomes my parent */
	child->parent = grandparent;
	/* I become my old parent's parent */
	parent->parent = child;
	/* My parent's right child becomes mine */
	child->right = parentRight;
	if (parentRight)
	    parentRight->parent = child;
    }
    else			/* this node is right child */
    {
	/* Parent becomes my right child */
	child->right = parent;
	/* My parent's parent becomes my parent */
	child->parent = grandparent;
	/* I become my old parent's parent */
	parent->parent = child;
	/* My old parent's left child becomes mine */
	child->left = parentLeft;
	if (parentLeft)
	    parentLeft->parent = child;
    }
    /* I become my new parent's child - 
       R or L depending on my old parent */
    if (grandparent)		/* could be null if we're at the root */
    {
	if (parent == grandparent->right)
	    grandparent->right = child;
	else
	    grandparent->left = child;
    }
    /* My former parent takes over my right and left children */
    parent->left = nodeLeft;
    parent->right = nodeRight;
    /* My former left and right, if not null, now have new parent */
    if (nodeLeft)
	nodeLeft->parent = parent;
    if (nodeRight)
	nodeRight->parent = parent;

}

/* compares the values of two nodes and returns
 * -1 if node1 is smaller than node 2
 * 1 if node1 is larger than node 2
 * 0 if they are the same 
 */
int nodeCompare(TREENODE_T *node1, TREENODE_T *node2)
{
    if (node1->nodeValue < node2->nodeValue)
	return -1;
    else if (node1->nodeValue > node2->nodeValue)
	return 1;
    else
	return 0;
}



/* Compares the current passed node's value to
 * its parent, and moves it up the tree if the
 * relationship breaks the heap constraint rule,
 * that is, every node must have a value larger than
 * its parent's value. 
 */
void swapUp(TREENODE_T *node)
{
    TREENODE_T *myParent = node->parent;
    /* while the current node is smaller than its parent
     * swap it up the tree */
    while ((myParent != NULL) && (nodeCompare(node, myParent) < 0))
    {
	printf("Swapping %d with parent value %d\n",
	       node->nodeValue, myParent->nodeValue);
	swap(myParent, node);
	myParent = node->parent;
    }
    if (myParent == NULL)
	pRoot = node;		/* reached the top */
}

/* Compares the current passed node's value to
 * its children, and moves it down the tree if the
 * relationship breaks the heap constraint rule,
 * that is, every node must have a value larger than
 * its parent's value. Swaps with the child that
 * has the smaller value, if both children exist.
 */
void swapDown(TREENODE_T *node)
{
    TREENODE_T *swapChild = NULL;
    TREENODE_T *temp;
    int bFirst = 1;
    int bLeft = 1;
    /* while the current node is larger than its left or right child
     * swap it down the tree
     */
    while (((node->left != NULL) &&
	    (nodeCompare(node, node->left) > 0)) ||
	   ((node->right != NULL) && (nodeCompare(node, node->right) > 0)))
    {
	/* both children are non-null, swap with the smaller one */
	if ((node->left) && (node->right))
	{
	    if (nodeCompare(node->left, node->right) < 0)
	    {
		swapChild = node->left;
		bLeft = 1;
	    }
	    else
	    {
		swapChild = node->right;
		bLeft = 0;
	    }
	}
	else			/* only the left child exists */
	{
	    swapChild = node->left;
	    bLeft = 1;
	}
	if (bFirst)
	{
	    pRoot = swapChild;	/* first swap will produce new root */
	    bFirst = 0;
	}
	if (bLeft)
	{
	    printf("Swapping %d with left child value %d\n",
		   node->nodeValue, swapChild->nodeValue);
	}
	else
	{
	    printf("Swapping %d with right child value %d\n",
		   node->nodeValue, swapChild->nodeValue);
	}
	swap(node, swapChild);
    }
}



/* Add a node to the partially sorted tree. 
 * Put it at the next available spot, then swap it 
 * upwards until it satisfies the heap constraint, 
 * that is, until all its children have bigger nodeValues.
 * @param newNode      Node to be added, with nodeValue set
 */
void heapInsert(TREENODE_T *newNode)
{
    TREENODE_T *pNextNode = NULL;
    if (pRoot == NULL)
    {
	pRoot = newNode;
	printf("Added new node %d as root\n", newNode->nodeValue);
	return;
    }
    /* since we are building in level order, we need a queue */
    localQueueClear();
    localEnqueue(pRoot);
    while ((pNextNode = localDequeue()) != NULL)
    {
	if (pNextNode->left == NULL)
	{
	    pNextNode->left = newNode;
	    newNode->parent = pNextNode;
	    printf("Added new node %d as left child of %d\n",
		   newNode->nodeValue, pNextNode->nodeValue);
	    break;
	}
	else if (pNextNode->right == NULL)
	{
	    pNextNode->right = newNode;
	    newNode->parent = pNextNode;
	    printf("Added new node %d as right child of %d\n",
		   newNode->nodeValue, pNextNode->nodeValue);
	    break;
	}
	else
	{
	    localEnqueue(pNextNode->left);
	    localEnqueue(pNextNode->right);
	}
    }
    /* Now swap up if this new node breaks the heap constraint rule */
    swapUp(newNode);
    /* Do a breadth first traversal to find the new last node */
    pLastAdded = findLastNode();
}

/* Remove the smallest item in the tree (which should always
 * be the root, then put the last item added to the tree
 * into the root spot. Finally, swap that item down the tree
 * if necessary until the heap constraint is satisfied.
 */
TREENODE_T *heapRemove()
{
    TREENODE_T *minNode = pRoot;
    if (pRoot == NULL)		/* Tree is empty */
    {
	printf("Tree is empty!\n");
	return minNode;
    }
    /* if this is the last node in the tree, just set the root to null
     * and return it
     */
    else if ((minNode->left == NULL) && (minNode->right == NULL))
    {
	pRoot = NULL;
	return minNode;
    }
    /* copy the root's children to the last added node */
    /* this makes the lastAdded be the root of the tree */
    /* also make the root's old children point to the new root 
     * as their parent */
    pLastAdded->left = pRoot->left;
    if (pLastAdded->left)
	pLastAdded->left->parent = pLastAdded;
    pLastAdded->right = pRoot->right;
    if (pLastAdded->right)
	pLastAdded->right->parent = pLastAdded;
    /* Reset the old parent's left or right child */
    if (pLastAdded->parent->left == pLastAdded)
	pLastAdded->parent->left = NULL;
    else
	pLastAdded->parent->right = NULL;
    pLastAdded->parent = NULL;
    pRoot = pLastAdded;
    /* Now swap the root down to the right place if necesary */
    swapDown(pLastAdded);
    /* Do a breadth first traversal to find the new last node */
    pLastAdded = findLastNode();
    return minNode;
}

/* print menu and get/return option - 0 to exit, 1 to insert, 2 to remove
 * Returns the option
 */
int getOption()
{
    char input[32];
    int opt = -1;
    while (opt < 0)
    {
	printf
	    ("\n\t0 - Exit\n\t1 - Insert node\n\t2 - Remove smallest node\n");
	printf("What do you want to do? ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%d", &opt);
	if ((opt < 0) || (opt > 2))
	    opt = -1;
    }
    return opt;
}

/*** Main function allows us to add and remove nodes *****/
/*** With each add or remove, we also print the tree *****/
int main()
{
    TREENODE_T *current = NULL;	/* for creating new nodes */
    char input[32];		/* input buffer */
    int value;			/* value to put in the tree */
    int option;			/* user's choice */
    int bContinue = 1;		/* flag to control loop */
    while (bContinue)
    {
	option = getOption();
	switch (option)
	{
	case 0:
	    bContinue = 0;
	    break;
	case 1:
	    printf("Enter value to store (positive integer): ");
	    fgets(input, sizeof(input), stdin);
	    sscanf(input, "%d", &value);
	    current = calloc(1, sizeof(TREENODE_T));
	    if (current)
	    {
		current->nodeValue = value;
		heapInsert(current);
		printTree();
	    }
	    else
	    {
		printf("Memory allocation error!\n");
		exit(1);
	    }
	    break;
	case 2:
	    current = heapRemove();
	    if (current != NULL)
	    {
		printf("Removed smallest node %d\n", current->nodeValue);
		printTree();
		free(current);
	    }
	    else
		printf("Tree is empty!\n");
	    break;
	}
    }

}


/************** Local Circular Queue Implementation *************************/
#define MAXITEMS 100
TREENODE_T *queueArray[MAXITEMS];
int headIndex = 0;
int tailIndex = -1;
int count = 0;

/* Clear the queue by zeroing it out 
 * and reset the count and item pointers
 */
void localQueueClear()
{
    memset(queueArray, 0, sizeof(queueArray));
    headIndex = 0;
    tailIndex = -1;
    count = 0;
}

/* Put a treenode pointer into the queue 
 * at the end. We don't check for a full
 * queue since this is pretty impossible
 * in this demo.
 */
void localEnqueue(TREENODE_T *item)
{
    tailIndex = (tailIndex + 1) % MAXITEMS;
    queueArray[tailIndex] = item;
    count += 1;
}

/* Remove  treenode pointer into the queue 
 * Returns the node at the head of the queue
 * or NULL if the queue is empty.
 */
TREENODE_T *localDequeue()
{
    TREENODE_T *returnNode = NULL;
    if (count > 0)
    {
	returnNode = queueArray[headIndex];
	headIndex = (headIndex + 1) % MAXITEMS;
	count -= 1;
    }
    return returnNode;
}
