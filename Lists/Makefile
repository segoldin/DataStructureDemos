# Makefile for demo programs illustrating
# Arrays of records and lists
# Copyright 2020 by Sally E. Goldin

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= simpleLinkedList$(EXECEXT) immigrationDemo$(EXECEXT) listTesterA$(EXECEXT) listTesterL$(EXECEXT) 

all : $(EXECUTABLES)

arrayList.o :	arrayList.c abstractList.h
	gcc -c arrayList.c

linkedList.o :	linkedList.c abstractList.h
	gcc -c linkedList.c


listTester.o :	listTester.c abstractList.h
	gcc -c listTester.c

simpleLinkedList$(EXECEXT) : simpleLinkedList.c
	gcc -o simpleLinkedList$(EXECEXT) simpleLinkedList.c

immigrationDemo$(EXECEXT) : immigrationDemo.c
	gcc -o immigrationDemo$(EXECEXT) immigrationDemo.c

# listTester using the arrayList implementation of the abstract list
listTesterA$(EXECEXT) : listTester.o arrayList.o
	gcc -o listTesterA$(EXECEXT) listTester.o arrayList.o


# listTester using the linkedList implementation of the abstract list
listTesterL$(EXECEXT) : listTester.o linkedList.o
	gcc -o listTesterL$(EXECEXT) listTester.o linkedList.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES)
