/*  logicEval.c
 *  
 *  Evaluate the truth value of logic expressions of the form
 *  ((A & B) | C) & (D | E)
 *
 *  Demonstration program using integerStack.c/h
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 *  Sample solution to Lab 4, CPE111
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "integerStack.h"

#define TRUE 1
#define FALSE 0
/* ascii values of important characters */
#define A_ASCII 65
#define Z_ASCII 90
#define LPAREN 40
#define RPAREN 41
#define AND 38
#define OR 124

/* only these characters are allowed */
char allowedchars[] ="ABCDEFGHIJKLMLOPQRSTUVWXYZ()&|";

/* Evaluate an expression. Assume that odd-numbered letters of the
 * alphabet represent True propositions, and even numbers represent False.
 * We use single characters '&' for AND and '|' for OR.
 * The algorithm is as follows (not including error checking):
 *    clear the stack
 *    for each char in the expression
 *        if char is LPAREN
 *            continue
 *        else if char is RPAREN
 *            pop V2
 *            pop OP
 *            pop V1
 *            result = V1 OP V2
 *            push result
 *        else 
 *            push char
 *        endif
 *    endfor
 *    pop and return result
 *
 *  Argument 
 *    expression   - expression to evaluate, with all spaces removed
 *                   and checked for only valid characters
 *  Return TRUE (1) or FALSE (0)
 *  Return -1 if expression is not well-formed (e.g get underflow or
 *            stack not empty upon completion of the expression)
 */ 
int evaluate(char * expression)
{
  int retValue = -1;    /* value of expression; -1 means poorly formed */  
  int p = 0;            /* current position in expression */
  int item = 0;         /* next char in the expression */
  int v1, v2, op;       /* hold values popped off the stack */
  int result;           /* result of subexpression */
  int bError = 0;       /* error flag */
  int len = strlen(expression);
  stackClearInt();
  for (p = 0; p < len; p++)
    {
    item = (int) expression[p];
    if ((item >= A_ASCII) && (item <= Z_ASCII))
      item = (item - A_ASCII) % 2;  /* convert to 1 or 0 */
    if (item == LPAREN)
      {
      continue;
      }
    else if (item == RPAREN)
      {
      v2 = popInt();
      op = popInt();
      v1 = popInt();  
      if ((v2 == UNDERFLOW) || (v1 == UNDERFLOW) || (op == UNDERFLOW))
	{
	bError = TRUE;
	printf("\tInvalid expression syntax\n");
	break;
	}
      if (op == AND)
        result = v1 && v2;
      else if (op == OR)
        result = v1 || v2;
      else
	{
	bError = TRUE;
	printf("\tInvalid expression syntax\n");
        break;
	}
      if (!pushInt(result)) /* if 0, overflow */
	{
	bError = TRUE;
	printf("\tStack is full!\n");
        break;
	}
      }
    else 
      {
      if (!pushInt(item)) /* if 0, overflow */
	{
	bError = TRUE;
	printf("\tStack is full!\n");
        break;
	}
      }
    }
  if (!bError)
    {
    result = popInt();
    /* return the result as long as there was no previous error
     * and the stack is now empty 
     */
    if ((result == UNDERFLOW) || (stackSizeInt() != 0))
      {
      bError = TRUE;
      printf("\tInvalid expression syntax\n");
      }
    }
  if (!bError)
    {
    retValue = result;
    }
  /* if there was an error, we will return -1 */
  return retValue;
}


/* continually get and check expressions, then evaluate and
 * print the results, until the user types "DONE"
 */
int main()
{
  char expression[64];  /* to hold the expression */
  char input[64];      /* hold chars read from the terminal */
  int i = 0;            /* loop counter */
  int j = 0;            /* loop counter */
  int result;           /* true or false result from eval */
  printf("Welcome to LogicEval!\n\n");
  printf("A,C,E, etc are false; B,D,F, etc are true\n");
  printf("Use '&' for AND and '|' for OR, '(' and ')' for nesting\n\n");
  while (1)
    {
    memset(expression,0,sizeof(expression));
    memset(input,0,sizeof(input));
    printf("Enter logical expression to evaluate: ");  
    fgets(input,sizeof(input),stdin);
    if (strncasecmp(input,"DONE",4) == 0)
        break;
    /* Remove all spaces, also check for invalid characters */
    j = 0;
    for (i = 0; (i < strlen(input)) && (input[i] != '\n'); i++)
      {
      if (isspace(input[i]))
	continue;
      else if (!strchr(allowedchars,input[i]))
	{
	printf("\tInvalid character in expression: %c\n", input[i]);
	break;
	}
      else
	expression[j++] = input[i];
      }
    if (i < strlen(input)-1) /* did not finish loop because of error */
      continue; /* throw this expression away, ask for a new one */
    result = evaluate(expression);
    if (result >= 0)
        printf("\t%s truth value is %s\n",expression,(result ? "TRUE" : "FALSE"));
    }

  printf("Bye!\n");
}
