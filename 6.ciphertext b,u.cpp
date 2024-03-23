#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
int inverse_modulo(int a, int m);
int gcd(int a, int b);
int find_most_frequent(char *ciphertext);
int find_second_most_frequent(char *ciphertext);
void break_affine_cipher(char *ciphertext);
int main() {
    char ciphertext[100];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    break_affine_cipher(ciphertext);

    return 0;
}

int inverse_modulo(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclid Algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algorithm
        m = a % m, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
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

int find_most_frequent(char *ciphertext) {
    int frequency[ALPHABET_SIZE] = {0};
    int max_count = 0, max_index = 0;

    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            frequency[index]++;
            if (frequency[index] > max_count) {
                max_count = frequency[index];
                max_index = index;
            }
        }
    }

    return max_index;
}

int find_second_most_frequent(char *ciphertext) {
    int frequency[ALPHABET_SIZE] = {0};
    int max_count = 0, second_max_count = 0, second_max_index = 0;

    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            frequency[index]++;
            if (frequency[index] > max_count) {
                second_max_count = max_count;
                max_count = frequency[index];
                second_max_index = index;
            } else if (frequency[index] > second_max_count && frequency[index] != max_count) {
                second_max_count = frequency[index];
                second_max_index = index;
            }
        }
    }

    return second_max_index;
}

void break_affine_cipher(char *ciphertext) {
    int most_frequent_index = find_most_frequent(ciphertext);
    int second_most_frequent_index = find_second_most_frequent(ciphertext);

    // Using the formula: a = (b - a * P1) mod 26, where P1 and P2 are the most frequent and second most frequent letters, respectively.
    int a = (second_most_frequent_index - most_frequent_index + ALPHABET_SIZE) % ALPHABET_SIZE;
    
    // Using the formula: b = (P1 - a * B1) mod 26, where B1 is the ASCII value of 'B'.
    int b = (most_frequent_index - a * ('B' - 'a') + ALPHABET_SIZE) % ALPHABET_SIZE;

    // Finding the modular multiplicative inverse of a
    int a_inverse = inverse_modulo(a, ALPHABET_SIZE);

    printf("Most frequent letter: %c\n", most_frequent_index + 'a');
    printf("Second most frequent letter: %c\n", second_most_frequent_index + 'a');
    printf("Key values (a, b): (%d, %d)\n", a, b);
    printf("Inverse of a (modulo 26): %d\n", a_inverse);

    // Decrypting the ciphertext using the found key values
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            int decrypted_index = (a_inverse * (index - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
            if (decrypted_index < 0) {
                decrypted_index += ALPHABET_SIZE;
            }
            if (isupper(ciphertext[i])) {
                ciphertext[i] = 'A' + decrypted_index;
            } else {
                ciphertext[i] = 'a' + decrypted_index;
            }
        }
    }

    printf("Decrypted Text: %s\n", ciphertext);
}

