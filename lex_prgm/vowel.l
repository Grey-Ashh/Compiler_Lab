%{
#include <stdio.h>
int vowel_count = 0;  
%}

%%
[aeiouAEIOU]    { vowel_count++; }  
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
    printf("Total number of vowels: %d\n", vowel_count);
    yy_delete_buffer(buffer);
    return 0;
}

