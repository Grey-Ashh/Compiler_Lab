#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 20
#define MAX_PROD_LEN 50

char production[MAX][MAX_PROD_LEN];
int n;
char nonTerminals[MAX];
int nonTermCount = 0;

char firstSets[MAX][50];
char followSets[MAX][50];

// Utility functions
int isTerminal(char c) {
    return !isupper(c) && c != 'e';  // 'e' is epsilon
}

int indexOfNonTerminal(char c) {
    for (int i = 0; i < nonTermCount; i++) {
        if (nonTerminals[i] == c)
            return i;
    }
    return -1;
}

int contains(char *str, char c) {
    return strchr(str, c) != NULL;
}

void addToSet(char *set, char c) {
    if (!contains(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// Forward declarations
void findFirst(char *result, char c);
void findFirstOfString(char *result, char *str);

// Compute FIRST of a string of symbols
void findFirstOfString(char *result, char *str) {
    if (str[0] == '\0') {
        addToSet(result, 'e');  // epsilon
        return;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        char sym = str[i];
        char temp[50] = "";

        findFirst(temp, sym);

        // Add all except epsilon
        for (int j = 0; temp[j] != '\0'; j++) {
            if (temp[j] != 'e')
                addToSet(result, temp[j]);
        }

        // If epsilon not in FIRST(sym), stop
        if (!contains(temp, 'e'))
            return;
    }
    addToSet(result, 'e');
}

// Compute FIRST set of a symbol
void findFirst(char *result, char c) {
    if (isTerminal(c)) {
        addToSet(result, c);
        return;
    }

    int idx = indexOfNonTerminal(c);
    if (idx == -1) return;

    // If already computed, return cached
    if (strlen(firstSets[idx]) > 0) {
        strcpy(result, firstSets[idx]);
        return;
    }

    // Compute FIRST for c
    char temp[50] = "";
    for (int i = 0; i < n; i++) {
        if (production[i][0] == c) {
            findFirstOfString(temp, &production[i][2]);
        }
    }
    strcpy(firstSets[idx], temp);
    strcpy(result, temp);
}

// Compute FOLLOW sets for all non-terminals
void computeFollow() {
    // Initialize FOLLOW sets empty
    for (int i = 0; i < nonTermCount; i++)
        followSets[i][0] = '\0';

    // Add '$' to FOLLOW of start symbol (first production)
    addToSet(followSets[0], '$');

    int changed;
    do {
        changed = 0;

        for (int i = 0; i < n; i++) {
            char lhs = production[i][0];
            int lhsIndex = indexOfNonTerminal(lhs);

            char *rhs = &production[i][2];
            int len = strlen(rhs);

            for (int pos = 0; pos < len; pos++) {
                char B = rhs[pos];
                if (isupper(B)) {
                    int BIndex = indexOfNonTerminal(B);

                    // Compute FIRST of beta (string after B)
                    char betaFirst[50] = "";
                    if (pos + 1 < len) {
                        findFirstOfString(betaFirst, &rhs[pos + 1]);
                    } else {
                        betaFirst[0] = 'e'; betaFirst[1] = '\0'; // epsilon if B is last symbol
                    }

                    int oldLen = strlen(followSets[BIndex]);

                    // Add FIRST(beta) - epsilon to FOLLOW(B)
                    for (int k = 0; betaFirst[k] != '\0'; k++) {
                        if (betaFirst[k] != 'e')
                            addToSet(followSets[BIndex], betaFirst[k]);
                    }

                    // If FIRST(beta) contains epsilon or B is at end, add FOLLOW(lhs) to FOLLOW(B)
                    if (contains(betaFirst, 'e') || pos == len - 1) {
                        for (int k = 0; followSets[lhsIndex][k] != '\0'; k++) {
                            addToSet(followSets[BIndex], followSets[lhsIndex][k]);
                        }
                    }

                    if (strlen(followSets[BIndex]) > oldLen)
                        changed = 1;
                }
            }
        }
    } while (changed);
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter productions (e.g. E=TR), use 'e' for epsilon:\n");
    for (int i = 0; i < n; i++) {
        fgets(production[i], MAX_PROD_LEN, stdin);
        production[i][strcspn(production[i], "\n")] = '\0';

        addToSet(nonTerminals, production[i][0]);
    }

    // Remove duplicates in nonTerminals
    char tempNT[MAX];
    int count = 0;
    for (int i = 0; i < strlen(nonTerminals); i++) {
        if (strchr(tempNT, nonTerminals[i]) == NULL) {
            tempNT[count++] = nonTerminals[i];
        }
    }
    tempNT[count] = '\0';
    strcpy(nonTerminals, tempNT);
    nonTermCount = count;

    // Compute FIRST sets
    for (int i = 0; i < nonTermCount; i++) {
        char temp[50] = "";
        findFirst(temp, nonTerminals[i]);
        strcpy(firstSets[i], temp);
    }

    // Compute FOLLOW sets
    computeFollow();

    // Print FIRST sets
    printf("\nFIRST sets:\n");
    for (int i = 0; i < nonTermCount; i++) {
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (int j = 0; firstSets[i][j] != '\0'; j++) {
            printf("%c ", firstSets[i][j]);
        }
        printf("}\n");
    }

    // Print FOLLOW sets
    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < nonTermCount; i++) {
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (int j = 0; followSets[i][j] != '\0'; j++) {
            printf("%c ", followSets[i][j]);
        }
        printf("}\n");
    }

    return 0;
}
