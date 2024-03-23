#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
int gcd(int a, int b);
int is_valid_a(int a);
void affine_caesar_encrypt(char *plaintext, int a, int b);
void affine_caesar_decrypt(char *ciphertext, int a, int b);
int main() {
    char plaintext[100], ciphertext[100];
    int a, b;
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the value of a (must be relatively prime to 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    if (!is_valid_a(a)) {
        printf("Invalid value of 'a'. 'a' must be relatively prime to 26.\n");
        return 1;
    }
    affine_caesar_encrypt(plaintext, a, b);
    printf("Encrypted Text: %s\n", plaintext);

    affine_caesar_decrypt(plaintext, a, b);
    printf("Decrypted Text: %s\n", plaintext);
    return 0;
}
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int is_valid_a(int a) {
    return gcd(a, ALPHABET_SIZE) == 1;
}
void affine_caesar_encrypt(char *plaintext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; ++i) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                plaintext[i] = 'A' + (a * (plaintext[i] - 'A') + b) % ALPHABET_SIZE;
            } else {
                plaintext[i] = 'a' + (a * (plaintext[i] - 'a') + b) % ALPHABET_SIZE;
            }
        }
    }
}
void affine_caesar_decrypt(char *ciphertext, int a, int b) {
    int a_inv = 0;
    while ((a * a_inv) % ALPHABET_SIZE != 1) {
        a_inv++;
    }
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                ciphertext[i] = 'A' + (a_inv * ((ciphertext[i] - 'A') - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
            } else {
                ciphertext[i] = 'a' + (a_inv * ((ciphertext[i] - 'a') - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
            }
        }
    }
}

