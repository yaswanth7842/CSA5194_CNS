#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKey(const char *key, char playfairMatrix[SIZE][SIZE]) {
    char keyTable[26] = {0};
    int i = 0, j = 0, len;

    len = strlen(key);

    for (i = 0; i < len; i++) {
        if (key[i] != 'J') {
            if (keyTable[toupper(key[i]) - 'A'] == 0) {
                keyTable[toupper(key[i]) - 'A'] = 1;
                playfairMatrix[j / SIZE][j % SIZE] = toupper(key[i]);
                j++;
            }
        }
    }

    for (i = 0; i < 26; i++) {
        if (keyTable[i] == 0) {
            playfairMatrix[j / SIZE][j % SIZE] = 'A' + i;
            j++;
        }
    }
}

void findPosition(char playfairMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char playfairMatrix[SIZE][SIZE], char ch1, char ch2) {
    int row1, col1, row2, col2;

    findPosition(playfairMatrix, ch1, &row1, &col1);
    findPosition(playfairMatrix, ch2, &row2, &col2);

    if (row1 == row2) {
        col1 = (col1 + 1) % SIZE;
        col2 = (col2 + 1) % SIZE;
    } else if (col1 == col2) {
        row1 = (row1 + 1) % SIZE;
        row2 = (row2 + 1) % SIZE;
    } else {
        int temp = col1;
        col1 = col2;
        col2 = temp;
    }

    printf("%c%c%c%c", playfairMatrix[row1][col1], playfairMatrix[row2][col2], ' ', ' ');
}

void playfairEncrypt(const char *input, const char *key) {
    char playfairMatrix[SIZE][SIZE];
    char sanitizedInput[100];
    int i, j, len;

    len = strlen(input);

    prepareKey(key, playfairMatrix);

    j = 0;
    for (i = 0; i < len; i++) {
        if (isalpha(input[i])) {
            sanitizedInput[j++] = toupper(input[i]);
        }
    }
    sanitizedInput[j] = '\0';

    for (i = 0; i < j; i += 2) {
        if (i + 1 < j) {
            if (sanitizedInput[i] == sanitizedInput[i + 1]) {
                printf("%c%c%c%c", sanitizedInput[i], 'X', sanitizedInput[i + 1], ' ');
            } else {
                encrypt(playfairMatrix, sanitizedInput[i], sanitizedInput[i + 1]);
            }
        } else {
            printf("%c%c%c%c", sanitizedInput[i], 'X', 'X', ' ');
        }
    }
    printf("\n");
}

int main() {
    char key[] = "HELLO";
    char input[] = "ENCRYPT THIS MESSAGE";

    playfairEncrypt(input, key);

    return 0;
}
