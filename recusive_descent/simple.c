#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

const char *input;
char lookahead;
void E();
void T();
void TP();
void EP();
void F();

void nextChar()
{
 lookahead=*input++;
}

void match(char expected)
{
 if(lookahead==expected)
    nextChar();
 else
    printf("ERROR %c %c\n",expected,lookahead);
}

void E()
{
 T();
 EP();
}

void EP()
{
 if(lookahead=='+')
 {
    match('+');
    T();
    EP();
 }
   
 else if(lookahead=='-')
 {
    match('-');
    T();
    EP();
 }
}


void T()
{
 F();
 TP();
}

void TP()
{
 if(lookahead=='*')
 {
    match('*');
    F();
    TP();
 }
   
 else if(lookahead=='/')
 {
    match('/');
    F();
    TP();
 }
}

void F()
{
 if(isalpha(lookahead))
 {
  while(isalpha(lookahead))
     match(lookahead);
 }
  else if(lookahead=='(')
  {
   match('(');
   E();
   match(')');
  }
  else
  {
   printf("invalid");
   exit(1);
  }
}

void main()
{
 char expr[100];
 printf("ENTER EXPRESSION:");
 scanf("%s",expr);
 input=expr;
 nextChar();
 E();
 if(lookahead=='\0')
 {
  printf("DONE");
 }
 else
 {
  printf("INVALID IP");
 }
} 

 


 
   
  
