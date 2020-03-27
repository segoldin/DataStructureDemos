Demos showing network concepts
-------------------------------

Makefile  - Linux make file for the demos in this subdirectory

abstractNetwork.h - Declarations for a general, abstract network data type

abstractQueue.h  - Declarations for a general queue data type

badtest1.net - Sample input file for networkTester which demonstrates error handling by the networkBuilder module.

badtest2.net - Sample input file for networkTester which demonstrates error handling by the networkBuilder module.

linkedListNetwork.c - Adjacency list implementation for an abstract network

linkedListQueue.c - Linked list implementation for an abstract queue

minPriorityQueue.c - Linked list implementation of min priority queue (for Dijkstra's algorithm)

minPriorityQueue.h - Declarations of functions in minPriorityQueue.c

networkBuilder.c - Module that reads and parses a file that defines a network, calling the functions in abstractNetwork.h to create it.

networkBuilder.h - Declarations for functions in networkBuilder.c

networkTester.c - Driver for testing and exploring networks. Allows initial, optional reading of a network definition file as well as interactive definition of vertices and edges.

simpleNetwork.c - Very simple, non-general adjacency matrix implementation of a network. Shows how Dijstra's algorithm can be implemented even in this very simple case.

test1.net - Sample input file for networkBuilder - no errors.

test2.net - Sample input file for networkBuilder - no errors.

