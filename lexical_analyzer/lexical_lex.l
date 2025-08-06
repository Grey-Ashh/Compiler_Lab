%{
#include <stdio.h>
%}

/* Definitions of regular expressions */
DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD (if|else|while|return|int|float)

%%

{KEYWORD}       { printf("Keyword: %s\n", yytext); }
{ID}            { printf("Identifier: %s\n", yytext); }
{DIGIT}+        { printf("Number: %s\n", yytext); }
"+"             { printf("Plus operator\n"); }
"-"             { printf("Minus operator\n"); }
"*"             { printf("Multiply operator\n"); }
"/"             { printf("Divide operator\n"); }
"="             { printf("Assignment operator\n"); }
[ \t\n]+        { /* skip whitespace */ }
.               { printf("Unknown character: %s\n", yytext); }

%%

int main(int argc, char **argv)
{
    yylex();  // Start lexical analysis on stdin
    return 0;
}

int yywrap() {
    return 1;
}

