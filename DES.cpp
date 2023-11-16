#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int initialPermutationTable[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};


const char* exampleKey = "secretk";

const char* exampleMessage = "01234567";


void encryptDES(const char* message, const char* key, char* result) {

    char initialPerm[64];
    for (int i = 0; i < 64; ++i) {
        initialPerm[i] = message[initialPermutationTable[i] - 1];
    }


    for (int i = 0; i < 64; ++i) {
        result[i] = initialPerm[i] ^ key[i % strlen(key)];
    }
}

int main() {
    char encryptedResult[64];

   
    encryptDES(exampleMessage, exampleKey, encryptedResult);

    printf("Encrypted message: ");
    for (int i = 0; i < 64; ++i) {
        printf("%d", encryptedResult[i]);
    }
    printf("\n");

    return 0;
}
