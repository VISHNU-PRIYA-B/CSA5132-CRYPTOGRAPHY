#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8

// Function prototypes
void encrypt_ecb_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext);
void decrypt_ecb_des(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *plaintext);
void encrypt_cbc_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext);
void decrypt_cbc_des(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext);
void encrypt_cfb_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext);
void decrypt_cfb_des(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext);

int main() {
    // Example key and IV (Initialization Vector)
    unsigned char key[8] = "12345678";
    unsigned char iv[8] = "87654321";

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

    // Allocate memory for decrypted plaintext
    unsigned char *decrypted_plaintext = malloc(padded_len);
    if (decrypted_plaintext == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(padded_plaintext);
        free(ciphertext);
        return 1;
    }

    // Encrypt plaintext in ECB mode using DES
    encrypt_ecb_des(padded_plaintext, padded_len, key, ciphertext);

    // Decrypt ciphertext in ECB mode using DES
    decrypt_ecb_des(ciphertext, padded_len, key, decrypted_plaintext);

    printf("ECB Decrypted plaintext: %s\n", decrypted_plaintext);

    // Encrypt plaintext in CBC mode using DES
    encrypt_cbc_des(padded_plaintext, padded_len, key, iv, ciphertext);

    // Decrypt ciphertext in CBC mode using DES
    decrypt_cbc_des(ciphertext, padded_len, key, iv, decrypted_plaintext);

    printf("CBC Decrypted plaintext: %s\n", decrypted_plaintext);

    // Encrypt plaintext in CFB mode using DES
    encrypt_cfb_des(padded_plaintext, padded_len, key, iv, ciphertext);

    // Decrypt ciphertext in CFB mode using DES
    decrypt_cfb_des(ciphertext, padded_len, key, iv, decrypted_plaintext);

    printf("CFB Decrypted plaintext: %s\n", decrypted_plaintext);

    // Clean up
    free(padded_plaintext);
    free(ciphertext);
    free(decrypted_plaintext);

    return 0;
}

// Function to encrypt plaintext in ECB mode using DES
void encrypt_ecb_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext) {
    // Implementation similar to previous example
}

// Function to decrypt ciphertext in ECB mode using DES
void decrypt_ecb_des(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *plaintext) {
    // Implementation similar to previous example
}

// Function to encrypt plaintext in CBC mode using DES
void encrypt_cbc_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
    // Implementation similar to previous example
}

// Function to decrypt ciphertext in CBC mode using DES
void decrypt_cbc_des(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext) {
    // Implementation similar to previous example
}

// Function to encrypt plaintext in CFB mode using DES
void encrypt_cfb_des(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
    // Implementation similar to previous example
}

// Function to decrypt ciphertext in CFB mode using DES
void decrypt_cfb_des(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext) {
    // Implementation similar to previous example
}

