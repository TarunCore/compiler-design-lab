#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *inputStr;
int currentIndex = 0;
char lastReduction[6], parserStack[50], grammarRules[][5] = {"(E)", "E+T", "T+F", "id", "E^E"};
int stackTop = 0, inputLength;


char precedence[9][9] = {
    /*input/
    /*stack    +   *   id   (   )   $  */
    /*  + */ '>', '<', '<', '<', '>', '>',
    /*  * */ '>', '>', '<', '<', '>', '>',
    /* id */ '>', '>', 'e', 'e', '>', '>',
    /*  ( */ '<', '<', '<', '<', '=', 'e',
    /*  ) */ '>', '>', 'e', 'e', '>', '>',
    /*  $ */ '<', '<', '<', '<', '<', '>',
};

int getPrecedenceIndex(char c) {
    switch (c) {
        case '+': return 0;
        case '*': return 1;
        case 'i': return 2; 
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
    }
    return 0;
}

void performShift() {
    if (inputStr[currentIndex] == 'i' && inputStr[currentIndex + 1] == 'd') {
        parserStack[++stackTop] = 'i';
        parserStack[++stackTop] = 'd';
        currentIndex += 2;
    } else {
        parserStack[++stackTop] = *(inputStr + currentIndex++);
    }
    parserStack[stackTop + 1] = '\0';
}

int performReduction() {
    int length, matchFound, t;
    for (int j = 0; j < 4; j++) {
        length = strlen(grammarRules[j]);
        if (parserStack[stackTop] == grammarRules[j][length - 1] && stackTop + 1 >= length) {
            matchFound = 1;
            for (t = 0; t < length; t++) {
                if (parserStack[stackTop - t] != grammarRules[j][length - t - 1]) {
                    matchFound = 0;
                    break;
                }
            }
            if (matchFound) {
                parserStack[stackTop - t + 1] = 'E';  
                stackTop = stackTop - t + 1;
                strcpy(lastReduction, grammarRules[j]);
                parserStack[stackTop + 1] = '\0';
                return 1; 
            }
        }
    }
    return 0;
}

void displayStack() {
    for (int j = 0; j <= stackTop; j++) {
        printf("%c", parserStack[j]);
    }
}

void displayInput() {
    for (int j = currentIndex; j < inputLength; j++) {
        printf("%c", *(inputStr + j));
    }
}

int main() {
    inputStr = (char *)malloc(50 * sizeof(char));
    printf("Enter the string: ");
    scanf("%s", inputStr);
    inputStr = strcat(inputStr, "$");
    inputLength = strlen(inputStr);
    strcpy(parserStack, "$");
    stackTop = 0;

    printf("\n%-30s\t\t%-30s\t\tACTION", "STACK", "INPUT");
    while (currentIndex <= inputLength) {
        performShift();
        printf("\n%-30s\t\t", parserStack);
        displayInput();
        printf("\t\tShift");

        // Immediate reduction for id -> E
        if (parserStack[stackTop] == 'd' && parserStack[stackTop - 1] == 'i') {
            parserStack[--stackTop] = 'E';  // Replace "id" with "E"
            printf("\n%-30s\t\t", parserStack);
            displayInput();
            printf("\t\tReduced: E->id");
        }

        // Loop for further reduction if possible
        while (precedence[getPrecedenceIndex(parserStack[stackTop])][getPrecedenceIndex(inputStr[currentIndex])] == '>') {
            if (!performReduction()) {
                break; // No more reductions
            }
            printf("\n%-30s\t\t", parserStack);
            displayInput();
            printf("\t\tReduced: E->%s", lastReduction);
        }
    }

    while (strcmp(parserStack, "$E$") != 0) {
        if (!performReduction()) {
            break; // If no reduction is possible, exit
        }
        printf("\n%-30s\t\t", parserStack);
        displayInput();
        printf("\t\tReduced: E->%s", lastReduction);
    }

    // Final check for the correct output
    if (strcmp(parserStack, "$E$") == 0) {
        printf("\n\nString is accepted\n");
    } else {
        printf("\n\nString is not accepted\n");
    }

    free(inputStr);
    return 0;
}
