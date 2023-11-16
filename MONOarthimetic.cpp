#include <stdio.h>
#include <ctype.h>

int main() {
    char text[500], ch;
    
    printf("Enter a message: ");
    fgets(text, sizeof(text), stdin);

    for (int i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        if (isalpha(ch)) {
            if (islower(ch)) {
                ch = 'z' - (ch - 'a');
            } else if (isupper(ch)) {
                ch = 'Z' - (ch - 'A');
            }
        }
        text[i] = ch;
    }

    printf("Encrypted message is: %s", text);
    return 0;
}
