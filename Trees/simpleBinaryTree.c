/*
 * simpleBinaryTree.c
 *
 * Functions for a very simple binary
 * tree. This tree does not keep its data sorted. It simply
 * fills up the tree from left to right as new calls to
 * 'insertItem' are made.
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simpleBinaryTree.h"
#include "abstractQueue.h"


/** private **/

/* Return the number of children a node has 
 * Arguments 
 *   pNode      - node we are inquiring about
 * Return 0, 1 or 2
 */
int childCount(NODE_T* pNode)
{
    int count = 0;
    if (pNode->left != NULL)
	count++;
    if (pNode->right != NULL)
	count++;
    return count;
}

/* Function to insert a new node in its
 * correct location in the tree (next free spot, starting from the left) 
 * Arguments
 *    pRoot       - pointer to a node
 *    pNewNode    - new node - data already assigned
 */
void insertNode(NODE_T* pRoot, NODE_T* pNewNode)
{
     NODE_T * pNextNode = NULL;
     queueClear();
     enqueue(pRoot);
     while ((pNextNode = dequeue()) != NULL)
         {
         if (pNextNode->left == NULL)
            {
	    pNextNode->left = pNewNode;
            printf("Added new node(%s) as left child of (%s)\n",
		pNewNode->data,pNextNode->data);
	    break;
            }
         else if (pNextNode->right == NULL)
            {
	    pNextNode->right = pNewNode;
            printf("Added new node(%s) as right child of (%s)\n",
		pNewNode->data,pNextNode->data);
            break;
            }
         else 
            {
	    enqueue(pNextNode->left);
            enqueue(pNextNode->right);
	    }
	 }
}


void freeNode(NODE_T* pNode)
{
  free(pNode->data);  /* we allocated this, so we delete it */
  free(pNode);
}

/* Traverse a tree (in order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traverseInOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
    if (pCurrent->left != NULL)
       {
       traverseInOrder(pCurrent->left,nodeFunction); 
       }
    (*nodeFunction)(pCurrent);
    if (pCurrent->right != NULL)
       {
       traverseInOrder(pCurrent->right,nodeFunction); 
       }
}

/* Traverse a tree (post order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traversePostOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
    if (pCurrent->left != NULL)
       {
       traversePostOrder(pCurrent->left,nodeFunction); 
       }
    if (pCurrent->right != NULL)
       {
       traversePostOrder(pCurrent->right,nodeFunction); 
       }
    (*nodeFunction)(pCurrent);
}


/* Traverse a tree (pre order traversal) and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pCurrent     -   current node
 *    nodeFunction -   function to execute on each node
 */
void traversePreOrder(NODE_T* pCurrent,void (*nodeFunction)(NODE_T* pNode ))
{
    (*nodeFunction)(pCurrent);
    if (pCurrent->left != NULL)
       {
       traversePreOrder(pCurrent->left,nodeFunction); 
       }
    if (pCurrent->right != NULL)
       {
       traversePreOrder(pCurrent->right,nodeFunction); 
       }
}


/* Traverse a tree using level order and execute the
 * function 'nodeFunction' on each element
 * Argument
 *    pRoot     -      root node
 *    nodeFunction -   function to execute on each node
 */
void traverseLevelOrder(NODE_T* pRoot,void (*nodeFunction)(NODE_T* pNode ))
{
    NODE_T* pNode = NULL;
    queueClear();
    enqueue(pRoot);
    /* when the queue is empty, there are no more nodes to visit */
    while (queueSize() > 0)
       {
       pNode = (NODE_T*) dequeue(); 
       (*nodeFunction)(pNode);
       if (pNode->left != NULL)
          {
	  /* put the left child on the queue */
	  enqueue(pNode->left); 
          }
       if (pNode->right != NULL)
          {
	  /* put the right child on the queue */
	  enqueue(pNode->right); 
          }
       }
}


/*
 *  Function to print data from a node. Passed to
 *  various traversal functions.
 *  Argument
 *     pNode   -  Node to process
 */
void printNodeData(NODE_T* pNode)
{
    printf("Node %p ==> %s\n", pNode, pNode->data);
}

/** PUBLIC FUNCTIONS */

/* Create a new tree and return a pointer to that tree
 * This is a "handle". Other modules should never look at
 * or modify the contents of the structure. The calling 
 * module should call 'freeTree' when it no longer needs
 * the tree.
 * Returns pointer to allocated tree, or null if memory allocation fails 
 */
TREE_T * createTree()
{
    TREE_T * pTree = calloc(1,sizeof(TREE_T));
    queueClear();
    return pTree;
}


/* Insert a new node into the next available location in the tree.
 * Arguments
 *    pTree       - pointer
 *    pDataItem    - new data to be inserted in the tree 
 * Returns 1 for success, 0 if memory allocation error occurred.
 */
int insertItem(TREE_T* pTree, char* pDataItem)
{
    int status = 1;
    char* pNewDataItem = NULL;
    NODE_T * pNewNode = NULL;
    /* create a copy of the data */
    pNewDataItem = strdup(pDataItem);
    /* create the new node */
    pNewNode = (NODE_T*) calloc(1,sizeof(NODE_T));
    if ((pNewNode == NULL) || (pNewDataItem == NULL))
       {
       status = 0;
       }
    else
       {
       pNewNode->data = pNewDataItem;
       pNewNode->count = 1;
       if (pTree->root == NULL)
          {
          pTree->root = pNewNode;
          printf("Node (%s) is the root\n", pNewNode->data);
          }
       else
	  {    
          insertNode(pTree->root,pNewNode);
          }
       pTree->itemcount++; 
       } 
    return status;
}

/* Traverse the tree and free all the nodes
 * Then free the TREE_T object itself.
 * This needs to be a post order traversal
 */
void freeTree(TREE_T * pTree)
{
   queueClear();
   if (pTree != NULL)
      {
      if (pTree->root != NULL)
          traversePostOrder(pTree->root,&freeNode);
      free(pTree);
      }
} 


/* Traverse and print using the specified order
 * structure
 * Argument
 *   pTree   - public structure
 *   order   - code for traversal order (see constants in .h file)
 */
void printTree(TREE_T * pTree, int order)
{
    if (pTree == NULL)
        printf("Tree not created yet!\n");
    else if (pTree->root == NULL)
        printf("Tree is empty!\n");
    else
        {
	switch (order)
	    {
	    case PREORDER:
		traversePreOrder(pTree->root,&printNodeData);
		break;
	    case INORDER:
		traverseInOrder(pTree->root,&printNodeData);
		break;
            case POSTORDER:
		traversePostOrder(pTree->root,&printNodeData);
		break;
            case LEVELORDER:
		traverseLevelOrder(pTree->root,&printNodeData);
		break;
	    default:
                printf("Invalid order constant in printTree!\n");
	    }
        } 

}

/** Functions for Lab **/

/*
 *  Function to print data from a node if and
 *  only if it is a leaf. Passed to
 *  various traversal functions.
 *  Argument
 *     pNode   -  Node to process
 */
void printLeafNodeData(NODE_T* pNode)
{
    if (childCount(pNode) == 0)
       printf("Leaf Node %p ==> %s\n", pNode, pNode->data);
}


/* Traverse and print only leaf data, going from left
 * to right. 
 * structure
 * Argument
 *   pTree   - public structure
 */
void printLeafData(TREE_T * pTree)
{
    if (pTree == NULL)
        printf("Tree not created yet!\n");
    else if (pTree->root == NULL)
        printf("Tree is empty!\n");
    else
	traversePostOrder(pTree->root,&printLeafNodeData);
    /* You could use any of the three traversals here. The
     * results should not change.
     */ 
 
}



/* Return the maximum depth of the tree
 * NON-RECURSIVE SOLUTION Applies only to Level-Order Tree
 * Argument
 *   pTree   - public structure
 * Return 0 if tree is empty, -1 if tree not created yet
 */ 
int maxTreeDepth(TREE_T * pTree)
{
    int count = 0;    
    if (pTree == NULL)
        {
	printf("Tree not created yet!\n");
        count = -1;
	}
    else if (pTree->root == NULL)
        {
        printf("Tree is empty!\n");
	}
    else
        {
	NODE_T * pCurrent = pTree->root;
        while (pCurrent != NULL)
	   {
	   count += 1;
	   pCurrent = pCurrent->left;
	   } 
        }
    return count;
}


/* Recursive subfunction to count levels in a level order filled
 * tree
 * Arguments
 *    pNode   -  current node
 *    pCount  -  pointer to accumulating count
 */
void countLevels(NODE_T* pNode, int * pCount)
{
    if (pNode != NULL)
       {
       *pCount = *pCount + 1;
       countLevels(pNode->left,pCount);
       }
}


/* Return the maximum depth of the tree
 * RECURSIVE SOLUTION for LEVEL ORDER TREE
 * Argument
 *   pTree   - public structure
 * Return 0 if tree is empty, -1 if tree not created yet
 */ 
int maxTreeDepthR(TREE_T * pTree)
{
    int count = 0;    
    if (pTree == NULL)
        {
	printf("Tree not created yet!\n");
        count = -1;
	}
    else if (pTree->root == NULL)
        {
        printf("Tree is empty!\n");
	}
    else
        {
	NODE_T * pCurrent = pTree->root;
        countLevels(pCurrent,&count);
        }
    return count;
}


/* Recursive subfunction to find maximum level in
 * ANY binary tree
 * Arguments
 *    pNode   -  current node
 *    level   -  tree level of parent - starts at 0 
 *    pMaxLevel  -  pointer to maximum level found so far
 */
void findMaxLevel(NODE_T* pNode, int level, int * pMaxLevel)
{
    if (pNode != NULL)
       {
       level = level + 1;
       if (level > *pMaxLevel)
           *pMaxLevel = level;
       findMaxLevel(pNode->left,level, pMaxLevel);
       findMaxLevel(pNode->right,level, pMaxLevel);
       }
}


/* Return the maximum depth of the tree
 * GENERAL RECURSIVE SOLUTION 
 * This function will work for any binary tree,
 * not just one which is constructed in level ordr
 * Argument
 *   pTree   - public structure
 * Return 0 if tree is empty, -1 if tree not created yet
 */ 
int maxTreeDepthG(TREE_T * pTree)
{
    int count = 0;    
    if (pTree == NULL)
        {
	printf("Tree not created yet!\n");
        count = -1;
	}
    else if (pTree->root == NULL)
        {
        printf("Tree is empty!\n");
	}
    else
        {
	NODE_T * pCurrent = pTree->root;
        findMaxLevel(pCurrent,0,&count);
        }
    return count;
}
