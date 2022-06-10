#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

char encrypt(string key, char letter);

int main(int argc, string argv[])
{
    // check for proper number of arguments
    if (argc != 2) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // check that argument is 26 letters
    int argLen = 0;
    while (argv[1][argLen] != '\0') {
        argLen++;
    } 
    if (argLen != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Program
    string plain = get_string("plaintext:  ");

    for (int i = 0; i < strlen(plain); i++) {
        plain[i] = encrypt(argv[1], plain[i]);
    }
    printf("ciphertext: %s\n", plain);
}

char encrypt(string key, char letter) {
    if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122)) {
        int ascii_altered;      // change the ascii to something between 0-25 in order to index from key (string data type)
        if (isupper(letter)) {
            ascii_altered = letter % 65;
            return toupper(key[ascii_altered]);
        }
        else {
            ascii_altered = letter % 97;
            return tolower(key[ascii_altered]);
        }
    }
    return letter;
}