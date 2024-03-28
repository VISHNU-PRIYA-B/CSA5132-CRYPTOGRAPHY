#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8

// Function prototypes
void encrypt_ecb_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext);

int main() {
    // Example key
    unsigned char key[8] = "12345678";

    // Example plaintext
    unsigned char plaintext[] = "This is a secret message";

    int plaintext_len = strlen((char *)plaintext);

    // Calculate padded plaintext length
    int padded_len = plaintext_len + (BLOCK_SIZE - (plaintext_len % BLOCK_SIZE));

    // Allocate memory for padded plaintext
    unsigned char *padded_plaintext = malloc(padded_len);
    if (padded_plaintext == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Copy plaintext to padded buffer
    memcpy(padded_plaintext, plaintext, plaintext_len);
    memset(padded_plaintext + plaintext_len, 0, padded_len - plaintext_len);

    // Allocate memory for ciphertext
    unsigned char *ciphertext = malloc(padded_len);
    if (ciphertext == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(padded_plaintext);
        return 1;
    }

    // Encrypt plaintext in ECB mode using DES
    encrypt_ecb_des(padded_plaintext, padded_len, key, ciphertext);

    // Print ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // Clean up
    free(padded_plaintext);
    free(ciphertext);

    return 0;
}

// Function to encrypt plaintext in ECB mode using DES
void encrypt_ecb_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext) {
    DES_cblock des_key;
    DES_key_schedule schedule;

    // Set key
    memcpy(des_key, key, 8);

    // Initialize key schedule
    DES_set_key_checked(&des_key, &schedule);

    // Encrypt each block of plaintext
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        DES_ecb_encrypt((DES_cblock *)(plaintext + i), (DES_cblock *)(ciphertext + i), &schedule, DES_ENCRYPT);
    }
}

