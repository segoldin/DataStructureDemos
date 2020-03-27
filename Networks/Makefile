# Makefile for demo programs related to Networks
# We also need a queue for breadth first traversal and a min priority queue
# for Dijkstra's algorithm

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= networkTester$(EXECEXT) simpleNetwork$(EXECEXT) 

all : $(EXECUTABLES)

linkedListQueue.o :	linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

minPriorityQueue.o :	minPriorityQueue.c minPriorityQueue.h
	gcc -c minPriorityQueue.c

linkedListNetwork.o :	linkedListNetwork.c abstractNetwork.h abstractQueue.h
	gcc -c linkedListNetwork.c

networkTester.o :	networkTester.c abstractNetwork.h networkBuilder.h
	gcc -c networkTester.c

networkBuilder.o :	networkBuilder.c abstractNetwork.h networkBuilder.h
	gcc -c networkBuilder.c

simpleNetwork.o :	simpleNetwork.c minPriorityQueue.h
	gcc -c simpleNetwork.c

networkTester$(EXECEXT) : networkTester.o linkedListNetwork.o linkedListQueue.o networkBuilder.o minPriorityQueue.o
	gcc -o networkTester$(EXECEXT) networkTester.o linkedListNetwork.o \
              linkedListQueue.o networkBuilder.o minPriorityQueue.o

simpleNetwork$(EXECEXT) : simpleNetwork.o minPriorityQueue.o
	gcc -o simpleNetwork$(EXECEXT) simpleNetwork.o minPriorityQueue.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
