#include <stdio.h>
#include <ctype.h>

int main() {
    char text[500], ch;
    int key, i, j;
    
    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the key value: ");
    scanf("%d", &key);

    for (i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        if (isalpha(ch)) {
            if (islower(ch)) {
                ch = ((ch - 'a' + key) % 26) + 'a';
            } else if (isupper(ch)) {
                ch = ((ch - 'A' + key) % 26) + 'A';
            }
        }
        text[i] = ch;
    }
    printf("Encrypted message is: %s", text);

    for (j = 0; text[j] != '\0'; j++) {  
        ch = text[j];
        if (isalpha(ch)) {
            if (islower(ch)) {
                ch = ((ch - 'a' - key + 26) % 26) + 'a';
            } else if (isupper(ch)) {
                ch = ((ch - 'A' - key + 26) % 26) + 'A';
            }
        }
        text[j] = ch;
    }
    printf("\nDecrypted message is: %s", text);
    return 0;
}
