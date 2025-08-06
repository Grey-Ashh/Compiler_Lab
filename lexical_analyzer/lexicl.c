#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

#define max 100

bool isDelimeter(char ch)
{
	return(ch==' ' ||ch=='+' ||ch=='-' ||ch=='/' ||ch=='*' ||ch=='%' ||ch==';' ||ch=='<' ||ch=='>' ||ch=='(' ||ch==')' ||ch=='[' ||ch==']' ||ch=='{' ||ch=='}' ||ch=='=');
}

bool isOperator(char ch)
{
	return(ch=='+' ||ch=='-' ||ch=='/' ||ch=='*' ||ch=='%' ||ch=='<' ||ch=='>' ||ch=='=');
}

bool isValidIdentifer(char* str)
{
	return(str[0]!='0' &&str[0]!='1' &&str[0]!='2' &&str[0]!='3' &&str[0]!='4' &&str[0]!='5' &&str[0]!='6' &&str[0]!='7' &&str[0]!='8' &&str[0]!='9' && !(isDelimeter(str[0])));
}

bool isKeyword(char *str)
{
	const char* keywords[]={"auto","break","if","char","const","case","continue","double","default","do","else","float","int","long","return","register","short","for","while"};
	for (int i = 0;i < sizeof(keywords) / sizeof(keywords[0]); i++) 
	{
        	if (strcmp(str, keywords[i]) == 0) 
        	{
        		return true;
        	}
    	}
    	return false;
}

bool isInteger(char* str)
{
    if (str == NULL || *str == '\0') 
    {
        return false;
    }
    int i = 0;
    while (isdigit(str[i])) 
    {
        i++;
    }
    return str[i] == '\0';
}

char* getSubstring(char* str, int start, int end)
{
    int length = strlen(str);
    int subLength = end - start + 1;
    char* subStr = (char*)malloc((subLength + 1) * sizeof(char));
    strncpy(subStr, str + start, subLength);
    subStr[subLength] = '\0';
    return subStr;
}

int lexicalAnalyzer(char* input)
{
    int left = 0, right = 0;
    int len = strlen(input);

    while (right <= len && left <= right) {
        if (!isDelimeter(input[right]))
            right++;

        if (isDelimeter(input[right]) && left == right) {
            if (isOperator(input[right]))
                printf("Token: Operator, Value: %c\n",
                       input[right]);

            right++;
            left = right;
        }
        else if (isDelimeter(input[right]) && left != right
                 || (right == len && left != right)) {
            char* subStr
                = getSubstring(input, left, right - 1);

            if (isKeyword(subStr))
                printf("Token: Keyword, Value: %s\n",
                       subStr);

            else if (isInteger(subStr))
                printf("Token: Integer, Value: %s\n",
                       subStr);

            else if (isValidIdentifer(subStr)
                     && !isDelimeter(input[right - 1]))
                printf("Token: Identifier, Value: %s\n",
                       subStr);

            else if (!isValidIdentifer(subStr)
                     && !isDelimeter(input[right - 1]))
                printf("Token: Unidentified, Value: %s\n",
                       subStr);
            left = right;
        }
    }
    return 0;
}


int main()
{

    char lex_input[max] ;
    printf("Enter input: ");
    scanf("%s",lex_input);
    printf("For Expression \"%s\":\n", lex_input);
    lexicalAnalyzer(lex_input);
    printf(" \n");

    return (0);
}
