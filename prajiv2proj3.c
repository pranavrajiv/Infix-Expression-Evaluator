
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

typedef enum {ERROR = 0, OPERATOR, VALUE, EOLN, QUIT, HELP} tokenType;
boolean b;
typedef struct tokenStruct
{
 tokenType type;
 char      op;
 int       val;
} token;

typedef struct stackStruct                                                              //node creating
{
 int elem;
 struct stackStruct* next;                                                              //stores the address of the previous node 
}va; 



typedef struct stackStruct stack;
typedef stack* stackptr;

token getInputToken (FILE *in);

int isEmpty(stackptr head)                                                               //checks if the stack is empty
{
if(head== NULL)
return 1;
else 
return 0;
}

void push(stackptr *hd,int num)                                                          //performs push operaion in teh stack
{ 
stackptr temp;
temp=(stackptr)malloc(sizeof(stack));
temp->elem=num;
temp->next=*hd;
*hd=temp;
}


int top(stackptr head)                                                                      // returns the top most element of teh stack
{ 
if(isEmpty(head))
{
printf("\nVAlue Stack Empty\n");
return -999;
}    
else
return head->elem;
}





void pop(stackptr *hd )                                                                        //removes the node
{   
if(((*hd)->elem=='(')&&((*hd)->next==NULL))
{

    free(*hd);
}


stackptr temp;

if((*hd)->next)
{ 
    temp=(*hd)->next;                               

free(*hd);
    *hd=temp;
}


}

int eval(int val1,int con,int val2)                                                             //fuction that evaluates the stacks
{ 
if((con==43)||(con==45)||(con==42)||(con==47))    
{int a=val1;
int b=val2;
int d;
if(con==43)
d= a+b;
if(con==45)
d= a-b;
if(con==42)
d= a*b;
if(con==47)
d= a/b;
 
return d;
}
else
{
printf("\nUnknown token\n");
return -999;
}
}
void popAndEval(stackptr *hd1, stackptr *hd2)                                                       //fuction that performs removal and evaluation of the stack
{                                                   
    int op =top(*hd1);
                                                        
    pop (hd1);
                                                               
   
    if((*hd2)->next !=NULL)
    {
     int v2 = top(*hd2);
                                                              
    pop (hd2);
    
    int v1 = top(*hd2); 
                                                                                                                
    pop (hd2);
    int v3 = eval(v1,op,v2);
                                                        
    
    
    push(hd2, v3);

    }
}



void processExpression (token inputToken, FILE *in)
{
 /**********************************************/
 /* Declare both stack head pointers here      */

     stackptr headval;                                                                              //pointer that stores the address of the latest created node in value stack 
     stackptr headop;	                                                                            //pointer that stores the address of the latest created node in operator stack

    headval= NULL;
    headop= NULL;   

 /* Loop until the expression reaches its End */
 while (inputToken.type != EOLN)
   {                                                                                                           
        /* The expression contain a VALUE */
     if (inputToken.type == VALUE)
      {
       /* make this a debugMode statement */
          if(b== TRUE)
          printf ("VAL:%d, ",inputToken.val);    
        
          push(&headval,inputToken.val);	 

      }

 /* The expression contains an OPERATOR */
     else if ((inputToken.type == OPERATOR))
      {                                                                                                           
       /* make this a debugMode statement */
          if(b== TRUE)
          printf ("OP:%c, ",inputToken.op);
  	
    if(inputToken.op=='(')
    {push(&headop,inputToken.op);                                                                                                                            
    }
	
  	if((inputToken.op==43)||(inputToken.op==45))
	{  ;
        while((!isEmpty(headop))&&((top(headop)==42)||(top(headop)==43)||(top(headop)==45)||(top(headop)==47)))      
        { 
                            
            popAndEval(&headop,&headval);
            
        }
        push(&headop,inputToken.op);
	
    }
	

	if((inputToken.op==42)||(inputToken.op==47))
	{	while((!isEmpty(headop))&&((top(headop)==42)||(top(headop)==47)))      
		popAndEval(&headop,&headval);
	push(&headop,inputToken.op);
	}


	if(inputToken.op== ')')
	{	while(!(isEmpty(headop))&&(top(headop)!=40))
        {
        popAndEval (&headop,&headval);
        }
		if(isEmpty(headop))	
		printf("\nError\n");
		else 
        {
            
           pop(&headop);
            
        }
    }

  }
     
    /* get next token from input */
    inputToken = getInputToken (in);
   } 

 /* The expression has reached its end */

 // add code to perform this operation here
headop=NULL;
 printf("\nThe infix expression is %d\n",headval->elem);
 printf ("\n");
}





/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

token getInputToken (FILE *in)
{
 token retToken;
 retToken.type = QUIT;

 int ch;
 ch = getc(in);
 if (ch == EOF)
   return retToken;
 while (('\n' != ch) && isspace (ch))
   {
    ch = getc(in);
    if (ch == EOF)
      return retToken;
   }
 
 /* check for a q for quit */
 if ('q' == ch)
   {
    retToken.type = QUIT;
    return retToken;
   }

 /* check for a ? for quit */
 if ('?' == ch)
   {
    retToken.type = HELP;
    return retToken;
   }

 /* check for the newline */
 if ('\n' == ch)
   {
    retToken.type = EOLN;
    return retToken;
   }

 /* check for an operator: + - * / ( ) */
 if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
   {
    retToken.type = OPERATOR;
    retToken.op = ch;
    return retToken;
   }
   
 /* check for a number */
 if (isdigit(ch))
   {
    int value = ch - '0';
    ch = getc(in);
    while (isdigit(ch))
      {
       value = value * 10 + ch - '0';
       ch = getc(in);
      }
    ungetc (ch, in);  /* put the last read character back in input stream */
    retToken.type = VALUE;
    retToken.val = value;
    return retToken;
   }
      
 /* else token is invalid */
 retToken.type = ERROR;
 return retToken;
}

/* Clear input until next End of Line Character - \n */
void clearToEoln(FILE *in)
{
 int ch;
 
 do {
     ch = getc(in);
    }
 while ((ch != '\n') && (ch != EOF));
}

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

int main (int argc, char **argv)
{

 char *input;
 token inputToken;
char debu[2]="-d";
int strcomp=1;

if(argv[1])
  {strcomp = strcmp(argv[1],debu);
      if(strcomp==0)
          b = TRUE;
  printf("\nDEBUG MODE ON\n");
  }

 printf ("Starting Expression Evaluation Program\n\n");
 printf ("Enter Expression: ");

 inputToken = getInputToken (stdin);
 while (inputToken.type != QUIT)
   {
    /* check first Token on Line of input */
    if(inputToken.type == HELP)
      {
       printCommands();
       clearToEoln(stdin);
      }
    else if(inputToken.type == ERROR)
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       clearToEoln(stdin);
      }
    else if(inputToken.type == EOLN)
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
    else 
      {
       processExpression(inputToken, stdin);
      } 

    printf ("\nEnter Expression: ");
    inputToken = getInputToken (stdin);
   }

 printf ("Quitting Program\n");
 return 1;
}

