#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 20
#define MAX_PROD_LEN 50

char production[MAX][MAX_PROD_LEN];
int n;
char nonTerminals[MAX];
int nonTermCount = 0;

int isTerminal(char c) {
    return !isupper(c) && c != 'e';  // 'e' represents epsilon (empty string)
}

int alreadyProcessed(char c) {
    for (int i = 0; i < nonTermCount; i++) {
        if (nonTerminals[i] == c)
            return 1;
    }
    return 0;
}

void addNonTerminal(char c) {
    if (!alreadyProcessed(c)) {
        nonTerminals[nonTermCount++] = c;
    }
}

int contains(char *str, char c) {
    return strchr(str, c) != NULL;
}

void addToResult(char *result, char c) {
    if (!contains(result, c)) {
        int len = strlen(result);
        result[len] = c;
        result[len + 1] = '\0';
    }
}

// Forward declaration
void findFirst(char *result, char c);

void findFirstOfString(char *result, char *str) {
    if (str[0] == '\0') {
        addToResult(result, 'e');  // empty string represented by 'e'
        return;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        char sym = str[i];
        char temp[50] = "";

        findFirst(temp, sym);

        // Add all except epsilon 'e'
        for (int j = 0; temp[j] != '\0'; j++) {
            if (temp[j] != 'e')
                addToResult(result, temp[j]);
        }

        // If epsilon 'e' is not in FIRST(sym), stop here
        if (!contains(temp, 'e'))
            return;
    }
    // If all symbols had epsilon, add epsilon 'e'
    addToResult(result, 'e');
}

void findFirst(char *result, char c) {
    if (isTerminal(c)) {
        addToResult(result, c);
        return;
    }

    // For each production of c
    for (int i = 0; i < n; i++) {
        if (production[i][0] == c) {
            // RHS starts at index 2 (production format: A=...)
            findFirstOfString(result, &production[i][2]);
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();  // consume newline

    printf("Enter productions (e.g. E=TR), use 'e' for epsilon (empty string):\n");
    for (int i = 0; i < n; i++) {
        fgets(production[i], MAX_PROD_LEN, stdin);
        production[i][strcspn(production[i], "\n")] = '\0';  // remove newline

        // Collect unique non-terminals
        addNonTerminal(production[i][0]);
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < nonTermCount; i++) {
        char nonTerminal = nonTerminals[i];
        char result[50] = "";
        findFirst(result, nonTerminal);
        printf("FIRST(%c) = { ", nonTerminal);
        for (int j = 0; result[j] != '\0'; j++) {
            printf("%c ", result[j]);
        }
        printf("}\n");
    }

    return 0;
}

