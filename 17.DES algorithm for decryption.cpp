#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void generateSubKeys(uint64_t key, uint64_t subKeys[]);
void decrypt(uint64_t ciphertext, uint64_t subKeys[]);
void swap(uint32_t *left, uint32_t *right);

int main() {
    uint64_t key = 0x133457799BBCDFF1; // Example key
    uint64_t subKeys[16];

    // Generate subkeys for decryption
    generateSubKeys(key, subKeys);

    uint64_t ciphertext = 0x85E813540F0AB405; // Example ciphertext

    // Decrypt the ciphertext
    decrypt(ciphertext, subKeys);

    return 0;
}

// Function to generate subkeys for decryption
void generateSubKeys(uint64_t key, uint64_t subKeys[]) {
    // Code to generate subkeys, but in reverse order
    // You need to implement this function based on your DES key generation algorithm
    // Use appropriate shifting for decryption key schedule
}

// Function to perform decryption
void decrypt(uint64_t ciphertext, uint64_t subKeys[]) {
    uint64_t permutedText = initial_permutation(ciphertext); // Initial permutation

    // Split the permuted text into left and right halves
    uint32_t left = (uint32_t)(permutedText >> 32);
    uint32_t right = (uint32_t)(permutedText & 0xFFFFFFFF);

    // 16 rounds of decryption
    for (int i = 15; i >= 0; i--) {
        uint32_t temp = right;
        right = left ^ round_function(right, subKeys[i]);
        left = temp;
    }

    // Final swap between left and right halves
    swap(&left, &right);

    // Final permutation
    uint64_t decryptedText = final_permutation(((uint64_t)right << 32) | left);

    printf("Decrypted text: %llx\n", decryptedText);
}

// Function to swap two 32-bit values
void swap(uint32_t *left, uint32_t *right) {
    uint32_t temp = *left;
    *left = *right;
    *right = temp;
}

