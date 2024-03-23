#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void decrypt(char *ciphertext);

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    decrypt(ciphertext);

    return 0;
}

void decrypt(char *ciphertext) {
    int frequency[256] = {0}; // Assuming ASCII characters
    
    // Count the frequency of each character in the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        frequency[(int)ciphertext[i]]++;
    }

    // Find the most frequent character in the ciphertext
    int max_count = 0;
    char most_frequent_char;
    for (int i = 0; i < 256; ++i) {
        if (isprint(i) && frequency[i] > max_count) {
            max_count = frequency[i];
            most_frequent_char = (char)i;
        }
    }

    // Assuming the most frequent character in English is 'e'
    // Calculate the offset to decrypt the ciphertext
    int offset = most_frequent_char - 'e';
    printf("Offset: %d\n", offset);

    // Decrypt the ciphertext using the calculated offset
    printf("Decrypted Text:\n");
    for (int i = 0; ciphertext[i] != '\0'; ++i) {
        if (isprint(ciphertext[i])) {
            char decrypted_char = ciphertext[i] - offset;
            if (decrypted_char < 0) {
                decrypted_char += 256; // Wrap around for negative values
            }
            printf("%c", decrypted_char);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

