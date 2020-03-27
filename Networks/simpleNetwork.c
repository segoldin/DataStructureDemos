/*  simpleNetwork.c
 *
 *  This module implements a simple, non-general adjacency matrix-based network.
 *  It shows how to implement Dijstra's algorithm using much simpler
 *  data structures.
 *
 *  Note this module needs to be linked with minPriorityQueue.c
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minPriorityQueue.h"

#define MAXVERT 20
#define HUGEVALUE 99999
#define WHITE 0  
#define BLACK 1

typedef struct
{
   int keyValue;       /* this network uses numeric keys */
   int myIndex;        /* simplify the translation from a pointer */
                       /* back to an integer index */
   int dValue;         /* total weight so far, for Dijkstra's algo */ 
   int parentIndex;    /* index in the vertices array for the vertex */
                       /* from which we reached this vertex */
                       /* Should be initialized to -1 before computation */
   int color;          /* used for coloring the vertices during traversal */
} VERTEX_T;

/* Array of vertex structures  */
VERTEX_T vertices[MAXVERT];


/* keep track of how many vertices we have */
int vertexCount = 0; 


/* Matrix of edges.
 * edges[x][y] is an edge between the xth and yth vertex
 * in the vertices array. If the value is 0, no edge
 * exists. Otherwise the array holds the weight of the edge
 */
int edges[MAXVERT][MAXVERT];

/* comparison function for the min priority queue
 * based on current dValue.
 * Arguments 
 *   V1            first vertex
 *   V2            second vertex
 * Returns 1 if V1 > V2, -1 if V1 < V2, else 0
 */
int vertexCompare(void* V1, void* V2)
{
   VERTEX_T * vertex1 = (VERTEX_T*) V1;
   VERTEX_T * vertex2 = (VERTEX_T*) V2;
   if (vertex1->dValue > vertex2->dValue)
     return 1;
   else if (vertex1->dValue < vertex2->dValue)
     return -1;
   else
     return 0;
} 

/* Check to see if the vertices array
 * holds a vertex with the specified key.
 * If so, return the index into the array.
 * Otherwise return -1
 */
int findVertex(int key)
{
  int found = -1;
  int i = 0;
  for (i = 0; (i < vertexCount) && (found < 0); i++)
    {
    if (vertices[i].keyValue == key)
	found = i;
    }
  return found;
}

/* Reinitialize all dValues, parentIndex and color
 */
void clearVertices()
{
  int i;
  for (i = 0; i < vertexCount; i++)
    {
    vertices[i].color = WHITE;
    vertices[i].dValue = HUGEVALUE;  
    vertices[i].parentIndex = -1;  
    }
}


/* Print the path and total weight from index1 to index 2.
 * Arguments
 *    index1    Index of start vertex in path
 *    index2    Index of end vertex in path.
 */
void printPathAndWeight(int index1, int index2)
{
  /** ADD YOUR CODE HERE **/
  int pathKeys[MAXVERT];  /* save the keys along path */
  int pathCount = 0;  /* number of vertices in the path */ 
  int parent;         /* index of parent */
  int i;
  if (vertices[index2].dValue == HUGEVALUE)
    {
    printf("Vertex '%d' is not reachable from vertex '%d'\n",
	     vertices[index2].keyValue,vertices[index1].keyValue);
    }
  else
    {
    printf("Min total weight of shortest path: %d\n",
           vertices[index2].dValue);
    pathKeys[pathCount] = vertices[index2].keyValue;
    pathCount++;
    parent = vertices[index2].parentIndex;
    while (parent >= 0)
       {
       pathKeys[pathCount] = vertices[parent].keyValue;
       pathCount++;
       parent = vertices[parent].parentIndex;
       }
    printf("Path: \n");
    for (i = pathCount-1; i >= 0; i--)
       {
       printf("'%d' ",pathKeys[i]); 
       if (i > 0)
           printf(" ==> "); 
       }
    printf("\n");
    }
}

/* Find and print the shortest (minimum total weight) path
 * between two vertices using Dijkstra's algorithm.
 * Arguments
 *     index1     Index value (not key!) of start vertex
 *     index2     Index value of end vertex
 */
void  printShortestPath(int index1, int index2)
{
   VERTEX_T * currentVtx = NULL;
   int i;
   int currentIndex;
   int weight;
   queueMinInit(&vertexCompare);/* tell the queue how to do comparisons */
   clearVertices();  /* reset dValue, color, parent */ 
   vertices[index1].dValue = 0; /* so the start vertex will dequeue first */
   for (i = 0; i < vertexCount; i++)
     {
     enqueueMin(&vertices[i]);
     }
   /** ADD YOUR CODE HERE **/
   while (queueMinSize() > 0)
     {
     currentVtx = dequeueMin();
     currentIndex = currentVtx->myIndex;
     vertices[currentIndex].color = BLACK;
     for (i = 0; i < vertexCount; i++)
       {
       if (edges[currentIndex][i] > 0)
	 {
	 weight = edges[currentIndex][i];
         if ((vertices[i].color == WHITE) &&
             (vertices[currentIndex].dValue + weight < vertices[i].dValue))
	    {
	    vertices[i].dValue = vertices[currentIndex].dValue + weight;
            vertices[i].parentIndex = currentIndex;
	    }  /* end if white and shorter path */
	 } /* end if edge exists */         
       }   /* end loop through all possible edges */
     }     /* end while queue still holds items */

   printPathAndWeight(index1, index2);
}


int main()
{
  char inputline[32];
  int bDone = 0;
  int key1, key2;
  int startIndex, endIndex; 
  int weight;
  memset(vertices,0,sizeof(vertices));  /* zero everything */
  printf("First let's create some vertices!\n");
  while (!bDone)
    {
    printf("Enter a positive 3 digit integer (negative to stop): ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&key1);
    if (key1 < 0)
       bDone = 1;
    else if (vertexCount < MAXVERT)
      {
      vertices[vertexCount].keyValue = key1;
      vertices[vertexCount].myIndex = vertexCount;
      vertexCount++;	
      }
    else
      {
      printf("Sorry, you've defined the max number of vertices\n");
      bDone = 1;	
      }
    }
  
  bDone = 0;
  printf("\nNow let's create some edges!\n");
  while (!bDone)
    {
    printf("Enter key for start vertex (negative to stop): ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&key1);
    if (key1 < 0)
      bDone = 1;
    else
      {
      startIndex = findVertex(key1);
      if (startIndex >= 0)
	{
        printf("Enter key for end vertex: ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%d",&key2);
	endIndex = findVertex(key2);
	if (endIndex >= 0)
	   {
	   printf("Enter the weight for edge from '%d' to '%d': ",key1,key2);  
	   fgets(inputline,sizeof(inputline),stdin);
	   sscanf(inputline,"%d",&weight);

	   printf("Creating edge from '%d' to '%d'\n",key1,key2);
	   edges[startIndex][endIndex] = weight;
	   }
        else
	   printf("End vertex does not exist!\n");
	}
      else 
	printf("Start vertex does not exist!\n");
      } 
    } 

  bDone = 0;
  printf("\nFind shortest paths using Dijstra's algorithm\n");
  while (!bDone)
    {
    printf("Enter key for starting vertex (negative to stop): ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&key1);
    if (key1 < 0)
      bDone = 1;
    else
      {
      startIndex = findVertex(key1);
      if (startIndex >= 0)
	{
        printf("Enter key for ending vertex: ");
        fgets(inputline,sizeof(inputline),stdin);
        sscanf(inputline,"%d",&key2);
	endIndex = findVertex(key2);
	if (endIndex >= 0)
  	   printShortestPath(startIndex,endIndex);
        else
    	   printf("Specified ending vertex does not exist!\n");
	}
      else 
	printf("Specified starting vertex does not exist!\n");
      } 
    } 

}
