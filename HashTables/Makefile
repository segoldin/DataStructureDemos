# Makefile for demo programs related to Hash tables

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= hashTester$(EXECEXT) applyHash$(EXECEXT)

all : $(EXECUTABLES)

applyHash$(EXECEXT) : applyHash.c
	gcc -o applyHash$(EXECEXT) applyHash.c

hashTester.o :	hashTester.c abstractHashTable.h
	gcc -c hashTester.c

chainedHashTable.o :	chainedHashTable.c abstractHashTable.h
	gcc -c chainedHashTable.c

hashTester$(EXECEXT) : hashTester.o chainedHashTable.o 
	gcc -o hashTester$(EXECEXT) hashTester.o chainedHashTable.o 

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
