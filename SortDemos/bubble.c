/*
 *  bubble.c
 *
 *  Sort a dynamically allocated array of integers 
 *  using bubble sort algorithm. Read the integers from a file
 *  where the first line is the count of the items in the file.
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

/*
 * Sort the array 'values' into ascending
 * order using the BubbleSort algorithm.
 * 'valueCount' is the number of values stored
 * in the 'values' array.
 */
void sortArray(int* values, int valueCount)
   {
   int i, tmp;
   int swapCount = 1;
  
   while (swapCount > 0)
       {
       swapCount = 0;
       /* we stop at valueCount-1 because we are always
        * looking at one position ahead of 'i'
        */
       for (i = 0; i < valueCount-1; i++)
           {
	   if (values[i] > values[i+1])
	       {
	       tmp = values[i];
	       values[i] = values[i+1];
	       values[i+1] = tmp;
	       swapCount = swapCount + 1;
	       }
	   }    
       }
   }

/* Write the values stored in 'values' into the file 'outputfile'
 * 'valueCount' is the number of
 * elements of 'values' that are in use
 */
void writeArray(int* values, int valueCount, char* outputfile)
   {
   int i;
   FILE* pFp = NULL;
   pFp = fopen(outputfile,"w");
   if (pFp == NULL)
      {
      printf("Error opening output file '%s'\n", outputfile);
      /* Just return to main. It's not a good idea to use
       * exit() inside a function.
       */
      }
   else
      {
      for (i = 0; i < valueCount; i++)
        {
	fprintf(pFp,"%d\n",values[i]);
        }
      fclose(pFp);
      }
   }


/*
 * Main function. Reads the values and then sorts and prints
 * them. The first number in the file is the number of values
 * to be sorted. 
 */
int main(int argc, char* argv[])
{
    int *values = NULL;  /* ptr to dynamic array of values to be sorted */
    int count = 0;       /* number of values entered */
    int i;               /* loop variable */
    char inputline[64];  /* for reading the text file */
    FILE * pFIn = NULL;  /* File pointer for reading */
    char inputfile[128]; /* filenames, from command line */
    char outputfile[128];

    if (argc < 3)
       {
       printf("Please supply input and output file names\n"); 
       printf("  ./bubble [inputfile] [outputfile]\n\n");
       exit(1); 
       }
    strcpy(inputfile,argv[1]);
    strcpy(outputfile,argv[2]);
    /* try to open the input file */
    pFIn = fopen(inputfile,"r");
    if (pFIn == NULL)
       {
       printf("Error opening input file '%s'\n",inputfile);
       exit(1);
       }
    /* read first line to get the count */
    if (fgets(inputline,sizeof(inputline),pFIn) == NULL)
       {
       printf("File '%s' appears to be empty\n",inputfile);
       exit(3);
       }
    sscanf(inputline,"%d",&count);
    if (count == 0)
       {
       printf("Read a count of zero. Probably the wrong file format\n");
       exit(4);
       }
    /* Allocate an array to hold the remaining values in the file */
    values = (int*) calloc(count,sizeof(int));
    if (values == NULL)
       {
       printf("Memory allocation failed\n");
       exit(5);
       }
    for (i = 0; i < count; i++)
       {
       if (fgets(inputline,sizeof(inputline),pFIn) == NULL)
          {
	  printf("Unexpected end of file. Adjusting count to %d\n",i);
          count = i; 
	  break;
	  }
       sscanf(inputline,"%d",&values[i]);
       }
    sortArray(values,count);
    writeArray(values,count,outputfile);
    free(values);
    printf("Finished sorting %d integers\n",count);
}
