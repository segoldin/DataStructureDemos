/*  family.c
 *
 *  Demo program showing how we can use pointers to indicate
 *  relationships.
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
#include <ctype.h>

char* relationNames = "CHILD |MOTHER|FATHER|SPOUSE|";

#define MAX 50  
/* maximum number of people we can handle */

/* Structure for a person */
typedef struct _person
{
    char name[64];                 /* person's name */
    char gender[2];                /* M or F */
    struct _person * pSpouse;      /* pointer to another person who is married to this person. */
    struct _person * pMother;      /* pointer to this person's mother */
    struct _person * pFather;      /* pointer to this person's father */
} PERSON_T;

/* Enum for type of relationship */
typedef enum
{
    REL_CHILD=0,
    REL_MOTHER,
    REL_FATHER,
    REL_SPOUSE
} RELTYPE_T;

/*** General functions ****/

/* print instructions for running the program 
 */
void usage()
{
    printf("Usage:\n");
    printf("    family <familyinputfile>\n\n");
    exit(0);

}

/* Find a person with a name that matches 'name'.
 *    name            -    Name of the person we want 
 *    personarray     -    Array of known people 
 *    count           -    Number of valid elements in personarray
 * Return the pointer to the person desired, or NULL if no match.
 */
PERSON_T * findPerson(char* name, PERSON_T* personarray[], int count)
{
    int i = 0;
    PERSON_T * pFound = NULL;
    /* Loop until we have looked at the whole array, or the name is found */
    for (i = 0; (i < count) && (pFound == NULL); i++)
        {
	if (strcasecmp(personarray[i]->name,name) == 0)
	    pFound = personarray[i];
        }
    return pFound;
}

/***** Functions used in building the relationship structure ***/

/* Add relationship between person A and person B
 *   pPersonA -   pointer to struct for first person
 *   pPersonB -   pointer to struct for second person
 *   relation -   enum indicating the type of relationship.
 * Returns 1 unless some error is found, then returns 0.
 */
int addRelationship(PERSON_T * pPersonA, PERSON_T * pPersonB, RELTYPE_T relation)
{
    int status = 1; /* assume no errors to start */

    /* In all cases, we can create a relationship by storing the pointer to
     * on person in some field of the other person. Which fields we set depends
     * on the type of relationship.
     */
    switch (relation)
       {
       case REL_CHILD:
           /* if personA is the child of personB, we have to set either 
            *  personA's pFather or pMother field, depending on the gender of
            *  personB. Errors are possible if the pMother or pFather field is already set.
            */
           if (strcmp(pPersonB->gender,"F") == 0) 
               {
               if (pPersonA->pMother == NULL)
                   pPersonA->pMother = pPersonB;
               else
	           {
		   printf(
                      "Cannot set %s to be the child of %s because %s already has a mother\n",  
		      pPersonA->name, pPersonB->name, pPersonA->name);
                   status = 0;
	           } 
	       }
            else /* assume that personB is male */
	       {
               if (pPersonA->pFather == NULL)
                   pPersonA->pFather = pPersonB;
               else
	           {
		   printf(
                      "Cannot set %s to be the child of %s because %s already has a father\n",  
		      pPersonA->name, pPersonB->name, pPersonA->name);
                   status = 0;
	           } 

               }
	   break;
       case REL_MOTHER: 
           if (strcmp(pPersonA->gender,"F") == 0)   /* A must be a woman to be a mother */
	       {
               if (pPersonB->pMother == NULL)
                   pPersonB->pMother = pPersonA;
               else
	           {
		   printf(
                      "Cannot set %s to be the mother of %s because %s already has a mother\n",  
		      pPersonA->name, pPersonB->name, pPersonB->name);
                   status = 0;
	           } 
	       }
	   else
	       {
	       printf("%s cannot be the mother of %s because %s is male\n",
		      pPersonA->name,pPersonB->name,pPersonA->name);
	       status = 0;
	       }
	   break;
       case REL_FATHER: 
           if (strcmp(pPersonA->gender,"M") == 0)   /* A must be a man to be a father */
	       {
               if (pPersonB->pFather == NULL)
                   pPersonB->pFather = pPersonA;
               else
	           {
		   printf(
                      "Cannot set %s to be the father of %s because %s already has a father\n",  
		      pPersonA->name, pPersonB->name, pPersonB->name);
                   status = 0;
	           } 
	       }
	   else
	       {
	       printf("%s cannot be the father of %s because %s is female\n",
		      pPersonA->name,pPersonB->name,pPersonA->name);
	       status = 0;
	       }
	   break;
       case REL_SPOUSE: 
           /* Neither A nor B should have a spouse yet */
	   if ((pPersonA->pSpouse == NULL) && (pPersonB->pSpouse == NULL))
	       {
               pPersonA->pSpouse = pPersonB;
               pPersonB->pSpouse = pPersonA;
               }
	   /* We might also want to check that A and B are of opposite genders 
            *  but let's assume that in the future we will have gay marriage!  
            */
           else
	       {
	       if (pPersonA->pSpouse != NULL)
                   printf("%s is already married!\n", pPersonA->name);
	       if (pPersonB->pSpouse != NULL)
                   printf("%s is already married!\n", pPersonB->name);
	       status = 0;
               } 
	   break;
       default:
	   printf("Sorry, this is not a known relationship\n");   
	   status = 0;
       }
    return status;
}

/*** Functions used in querying the relationship structure ***/

/* Display a menu of relationship. 
 * Let the user choose. Returns the option
 * chosen 
 *    1 = spouse
 *    2 = father
 *    3 = mother
 *    4 = children
 *    0 = exit
 */
int getRelationship()
{
    int option = -1;
    char input[16];
    while ((option < 0) || (option > 4))
       {
       printf("Enter relationship you want: \n");
       printf(" 1 - Spouse of selected person\n");
       printf(" 2 - Father of selected person\n");
       printf(" 3 - Mother of selected person\n");
       printf(" 4 - Children of selected person\n");
       printf(" 0 to exit\n");
       printf(">>> ");
       fgets(input,sizeof(input),stdin);
       sscanf(input,"%d",&option);
       }
    return option;
}

/* Print children of a particular person.
 * We do this by looking at all the people
 * and seeing if they have the focus person as
 * father or mother. If so, we print the name of that person.
 * (It would be better to return an array or list, but that 
 * would make the function a lot more complicated.)
 *    pFocusPerson  - person whose children we want
 *    people        - array of people
 *    count         - number of people in the array.
 */
void printChildren(PERSON_T * pFocusPerson,PERSON_T* people[], int count)
{
    int i = 0;
    PERSON_T *pThisPerson = NULL;
    for (i = 0; i < count; i++)
       {
       pThisPerson = people[i];
       if ((pThisPerson->pFather == pFocusPerson) ||
           (pThisPerson->pMother == pFocusPerson))
	   printf("    %s\n",pThisPerson->name); 
       } 
} 


/* let the user ask questions about various people 
 * and display the relationships
 *    people   -   array of PERSON_T records
 *    count    -   number of people in the array
 */
void askQuestions(PERSON_T * people[], int count)
{
    int option = 1;
    char name[64] = "";
    char input[128] = "";
    PERSON_T* pFocus = NULL;
    while (option > 0)
       {
       memset(input,0,sizeof(input));
       /* Get name of focus person */
       printf("\nEnter name of person (<CR> to exit): ");
       memset(name,0,sizeof(name));
       fgets(input,sizeof(input),stdin);
       sscanf(input,"%s",name);
       if (strlen(name) == 0)
	  break;
       pFocus = findPerson(name,people,count);
       if (pFocus != NULL)
           {
	   option = getRelationship();
           switch(option)
	      {
	      case 0:  
                  break;  /* exit from the switch, then the loop */
	      case 1: /* Spouse of focus person */ 
                  if (pFocus->pSpouse != NULL)
                      printf("%s is married to %s\n",
			     pFocus->name,pFocus->pSpouse->name);
                  else
                      printf("%s is not married as far as we know\n",
                             pFocus->name);
                  break;
	      case 2: /* Father of focus person */
                  if (pFocus->pFather != NULL)
                      printf("The father of %s is %s\n",
			     pFocus->name,pFocus->pFather->name);
                  else
                      printf("We don't know the father of %s\n",
                             pFocus->name);
                  break;
	      case 3:  /* Mother of focus person */
                  if (pFocus->pMother != NULL)
                      printf("The mother of %s is %s\n",
			     pFocus->name,pFocus->pMother->name);
                  else
                      printf("We don't know the mother of %s\n",
                             pFocus->name);
                  break;
	      case 4:  /* Children of focus person */
                  printf("The following people are children of %s\n",
			 pFocus->name);
                  printChildren(pFocus,people,count);
		  break;
	      default:
	          printf("Unrecognized option\n");
	      }
           }
       else
           {
	   printf("Person %s does not exist\n",name);
           }
       }
}

/* read in a relationship file, then let the user ask about 
 * relationships and use the data structure to answer.
 */
int main(int argc, char* argv[])
{
    int i = 0;
    int count = 0;            /* how many people have been defined */
    int status = 0;           /* error or success flag */
    PERSON_T * people[MAX];   /* array of people who might be related */
    FILE * pIn = NULL;        /* for reading input file */
    char inputbuffer[256];    /* array for reading from file */
    char inputfile[256];      /* input file name */
    char nameA[64];           /* name of first person in a relationship */
    char nameB[64];           /* name of second person in relationship */
    char relname[16];         /* string relationship */
    char gender[2];           /* string gender */
    PERSON_T * personA = NULL;
    PERSON_T * personB = NULL;
    RELTYPE_T relType = -1;
    char * matchPosition = NULL;
    
    if (argc != 2)
        usage();
    strcpy(inputfile, argv[1]);
    pIn = fopen(inputfile,"r");
    if (pIn == NULL)
       {
       fprintf(stderr,"Error opening input file %s - exiting\n",
	       inputfile);
       exit(1);
       }
    for (i=0; i < MAX; i++)
       people[i] = NULL; 

    while (fgets(inputbuffer,sizeof(inputbuffer),pIn) != NULL)
       {
       if (strncmp(inputbuffer,"PERSON",strlen("PERSON")) == 0)
	   {
	   if (count >= MAX)
	      {
	      fprintf(stderr,"Sorry, no more room in the people array\n");
              continue;  /*  go read next line - might be RELATION */
              }
 	   sscanf(inputbuffer,"PERSON %s %s",nameA,gender);
           if (findPerson(nameA,people,count) != NULL)
	      {
	      fprintf(stderr,"A person named %s already exists\n",nameA);
              continue;
	      } 
           personA = (PERSON_T*) calloc(1,sizeof(PERSON_T));
           if (personA == NULL)
	       {
	       fprintf(stderr,"Memory allocation error creating person %s\n",
		       nameA);
	       }
           else
	       {
	       strcpy(personA->name,nameA);
               strcpy(personA->gender,gender);
               personA->gender[0] = toupper(personA->gender[0]);
               people[count] = personA;
	       count = count+1;
	       }
	   } 
       else if (strncmp(inputbuffer,"RELATION",strlen("RELATION")) == 0)
	   {
	   status = 0;
 	   sscanf(inputbuffer,"RELATION %s %s %s",nameA,nameB,relname);
           personA = findPerson(nameA,people,count);
           personB = findPerson(nameB,people,count);
           if ((matchPosition = strstr(relationNames,relname)) != NULL)
	       {
               relType = (matchPosition - relationNames)/7;
	       }
           if (personA == NULL)
               fprintf(stderr,"No such person: %s\n",nameA);
           else if (personB == NULL)
               fprintf(stderr,"No such person: %s\n",nameB);
           else if ((relType > 3) || (relType < 0))
               fprintf(stderr,"Invalid relationship\n");
	   else
	       status =  addRelationship(personA,personB,relType);
	   if (status == 0)
               fprintf(stderr,"     Relationship not added due to errors \n");  
	   } 
       }
    fclose(pIn);
    /* Now let the user ask questions about the people */
    askQuestions(people,count);

    /* free the data */
    for (i = 0; i < count; i++)
        if (people[i] != NULL)
	    {
	    free(people[i]);
            people[i] = NULL;
	    }
}
