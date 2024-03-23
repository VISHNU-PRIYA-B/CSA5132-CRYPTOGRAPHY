#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *plaintext, char *key);
void decrypt(char *ciphertext, char *key);
int main() {
    char key[100], plaintext[100], ciphertext[100];
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    encrypt(plaintext, key);
    printf("Encrypted Text: %s\n", plaintext);
    decrypt(plaintext, key);
    printf("Decrypted Text: %s\n", plaintext);
    return 0;
}
void encrypt(char *plaintext, char *key) {
    int keyIndex = 0;
    for (int i = 0; plaintext[i] != '\0'; ++i) {
        if (isalpha(plaintext[i])) {
            int shift = tolower(key[keyIndex]) - 'a';
            plaintext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            keyIndex = (keyIndex + 1) % strlen(key);
        }
    }
}
void decrypt(char *ciphertext, char *key) {
    int keyIndex = 0;
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            int shift = tolower(key[keyIndex]) - 'a';
            int ch = (ciphertext[i] - 'a' - shift + 26) % 26 + 'a';
            ciphertext[i] = ch;
            keyIndex = (keyIndex + 1) % strlen(key);
        }
    }
}

