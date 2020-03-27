/*
 * simpleBinaryTree.h
 *
 * Functions and data structures for a simple binary
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
#ifndef SIMPLEBINARYTREE_H
#define SIMPLEBINARYTREE_H

#define PREORDER      1
#define INORDER       2
#define POSTORDER     3
#define LEVELORDER    4


/* Structure representing a node in the tree */
typedef struct _node
{
  char* data;               /* pointer to the data represented by this node */ 
  int count;                /* handle duplicates. If count > 1, means there */
                            /* were multiple inserts of the same value */
  struct _node * left;      /* left child node in the tree */
  struct _node * right;     /* right child node in the tree */
} NODE_T;


/* Structure representing a tree */
typedef struct _tree
{
  NODE_T * root;            /* root of the tree */
  int itemcount;            /* number of items in the tree */
                            /* could be more than the number of nodes */
                            /*   because duplicate items use a single node */
} TREE_T;


/** Public functions **/

/* Create a new tree and return a pointer to that tree
 * This is a "handle". Other modules should never look at
 * or modify the contents of the structure. The calling 
 * module should call 'freeTree' when it no longer needs
 * the heap.
 * Returns pointer to allocated tree, or null if memory allocation fails 
 */
TREE_T * createTree();


/* Insert a new node into the correct location in the tree.
 * Simply puts it in the next available spot, filling the
 * current level from left to right.
 * Arguments
 *    pTree       - pointer
 *    pDataItem    - new data to be inserted in the tree 
 * Returns 1 for success, 0 if memory allocation error occurred.
 */
int insertItem(TREE_T * pTree, char* pDataItem);


/* Traverse the tree and free all the nodes
 * Then free the TREE_T object itself.
 * This needs to be a post order traversal
 */
void freeTree(TREE_T * pTree);


/* Traverse and print using the specified order
 * structure
 * Argument
 *   pTree   - public structure
 *   order   - code for traversal order (see constants above)
 */
void printTree(TREE_T * pTree, int order);

/* Traverse and print only leaf data, going from left
 * to right. 
 * structure
 * Argument
 *   pTree   - public structure
 */
void printLeafData(TREE_T * pTree);

/* Return the maximum depth of the tree 
 * Argument
 *   pTree   - public structure
 */ 
int maxTreeDepth(TREE_T * pTree);

#endif
