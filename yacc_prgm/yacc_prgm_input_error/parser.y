%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
	
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}

%union {
    int num;  // Union to store integer values (for NUM and expressions)
}

%token <num> NUM  // Associate NUM token with integer values
%type <num> expression  // Declare that the 'expression' non-terminal holds an integer

%left '+' '-'
%left '*' '/'

%%

program:
    expression { 
        printf("Result = %d\n", $1);  // Print result when expression is successfully parsed
    };

expression:
      NUM                  { $$ = $1; }  
    | expression '+' NUM   { $$ = $1 + $3; }
    | expression '-' NUM   { $$ = $1 - $3; }
    | expression '*' NUM   { $$ = $1 * $3; }
    | expression '/' NUM   { 
                              if ($3 == 0)
                                  yyerror("Division by zero");
                              else
                                  $$ = $1 / $3;
                            }
    ;

%%

int main() {
    printf("Enter an arithmetic expression:\n");
    int parse_status = yyparse();
    
    if (parse_status == 0) {
        printf("Parsing successful.\n");
    } else {
        printf("Parsing failed.\n");
    }

    return 0;
}
/*
output
s7d5@cc2:~/Desktop/Grey/yacc_prgm$ flex lexer.l
s7d5@cc2:~/Desktop/Grey/yacc_prgm$ bison -d parser.y
s7d5@cc2:~/Desktop/Grey/yacc_prgm$ gcc lex.yy.c parser.tab.c -o parser -ll
s7d5@cc2:~/Desktop/Grey/yacc_prgm$ ./parser < input.txt
Enter an arithmetic expression:
Result = 2
Parsing successful.
*/

