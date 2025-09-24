%{
#include <stdio.h>
int word_count = 0;  
%}

%%
[a-zA-Z0-9]+    { word_count++; }  
[ \t\n]+         { }  
.                { }  
%%

int main() {

    FILE *f1 = fopen("input.txt", "r"); 
    if (f1 == NULL) {
        perror("Error opening file");
        return 1;
    }
    char input_string[1024];
    //printf("Enter a string: ");
    //fgets(input_string, sizeof(input_string), stdin);  
    char ch;
    int i=0;
    while((ch=fgetc(f1))!=EOF)
    {
    	input_string[i]=ch;
    	i++;
    }
    input_string[i]='\0';
    printf("String in file:\n%s\n\n",input_string);
    YY_BUFFER_STATE buffer = yy_scan_string(input_string); 
    yylex();  
    printf("Total number of words: %d\n", word_count);
    yy_delete_buffer(buffer);  
    return 0;
/*
s7d5@cc2:~/Desktop/Grey/lex_prgm$ lex vowel.l
s7d5@cc2:~/Desktop/Grey/lex_prgm$ gcc lex.yy.c -lfl
s7d5@cc2:~/Desktop/Grey/lex_prgm$ ./a.out
String in file:
hello how are you?
fine
really? how fine are you feeling?


Total number of vowels: 21
*/
}



