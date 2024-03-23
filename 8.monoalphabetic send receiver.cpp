#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherSequence(char *keyword, char *cipherSequence);
void encrypt(char *plaintext, char *cipherSequence);
void decrypt(char *ciphertext, char *cipherSequence);

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "hello world";
    char ciphertext[100];

    char cipherSequence[ALPHABET_SIZE];
    generateCipherSequence(keyword, cipherSequence);

    printf("Cipher Sequence: %s\n", cipherSequence);

    encrypt(plaintext, cipherSequence);
    printf("Encrypted Text: %s\n", plaintext);

    decrypt(plaintext, cipherSequence);
    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}

void generateCipherSequence(char *keyword, char *cipherSequence) {
    int keywordLength = strlen(keyword);
    int index = 0;
    int i, j;

    // Copy the keyword to the cipher sequence
    for (i = 0; i < keywordLength; i++) {
        cipherSequence[index++] = toupper(keyword[i]);
    }

    // Fill the remaining cipher sequence with unused letters in normal order
    for (i = 0; i < ALPHABET_SIZE; i++) {
        char letter = 'A' + i;
        if (!strchr(keyword, toupper(letter))) {
            cipherSequence[index++] = letter;
        }
    }

    // Null-terminate the cipher sequence
    cipherSequence[index] = '\0';
}

void encrypt(char *plaintext, char *cipherSequence) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                plaintext[i] = cipherSequence[plaintext[i] - 'A'];
            } else {
                plaintext[i] = tolower(cipherSequence[toupper(plaintext[i]) - 'A']);
            }
        }
    }
}

void decrypt(char *ciphertext, char *cipherSequence) {
    char alphabet[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char *ptr = strchr(cipherSequence, toupper(ciphertext[i]));
            if (ptr != NULL) {
                if (isupper(ciphertext[i])) {
                    ciphertext[i] = alphabet[ptr - cipherSequence];
                } else {
                    ciphertext[i] = tolower(alphabet[ptr - cipherSequence]);
                }
            }
        }
    }
}

