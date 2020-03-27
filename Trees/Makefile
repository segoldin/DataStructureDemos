# Makefile for tree demo programs

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= simpleTreeTester$(EXECEXT) directoryTree$(EXECEXT)

all : $(EXECUTABLES)

linkedListQueue.o : linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

simpleBinaryTree.o : simpleBinaryTree.c simpleBinaryTree.h
	gcc -c simpleBinaryTree.c

simpleTreeTester.o : simpleTreeTester.c simpleBinaryTree.h
	gcc -c simpleTreeTester.c

filesearch.o :	filesearch.c filesearch.h
	gcc -c filesearch.c

directoryTree.o : directoryTree.c filesearch.h
	gcc -c directoryTree.c

directoryTree$(EXECEXT) : directoryTree.o filesearch.o
	gcc -o directoryTree$(EXECEXT) directoryTree.o filesearch.o

simpleTreeTester$(EXECEXT) : simpleTreeTester.o simpleBinaryTree.o \
				linkedListQueue.o
	gcc -o simpleTreeTester$(EXECEXT) simpleTreeTester.o simpleBinaryTree.o\
				linkedListQueue.o
clean : 
	-rm *.o
	-rm $(EXECUTABLES)


