# Makefile for graph demo programs
# We also need a queue to support breadth first search

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= graphTester$(EXECEXT) graphTesterM$(EXECEXT) 

all : $(EXECUTABLES)

linkedListQueue.o :	linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

linkedListGraph.o :	linkedListGraph.c abstractGraph.h abstractQueue.h
	gcc -c linkedListGraph.c

matrixGraph.o :	matrixGraph.c abstractGraph.h abstractQueue.h
	gcc -c matrixGraph.c

graphTester.o :	graphTester.c abstractGraph.h
	gcc -c graphTester.c

# graph implementation uses adjacency list
graphTester$(EXECEXT) : graphTester.o linkedListGraph.o linkedListQueue.o
	gcc -o graphTester$(EXECEXT) graphTester.o linkedListGraph.o linkedListQueue.o

# alternate implementation of a graph using adjacency matrix
graphTesterM$(EXECEXT) : graphTester.o matrixGraph.o linkedListQueue.o
	gcc -o graphTesterM$(EXECEXT) graphTester.o matrixGraph.o linkedListQueue.o


clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
