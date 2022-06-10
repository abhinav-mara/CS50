#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

char rotate(int key, char letter);

int main(int argc, string argv[])
{
    // check for the proper number of arguments
    if (argc != 2) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    
    // check if argument is an integer
    int i = 0; 
    while (argv[1][i] != '\0') {
        if (argv[1][i] < 48 || argv[1][i] > 57) {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
        i++;
    }

    // convert cli argument to an int
    int key = atoi(argv[1]);

    string plain = get_string("plaintext:  ");

    // make key go down to a value between 0 and 25
    while (key > 25) {
        key %= 26;
    }

    // run encryption
    int j = 0;
    while (plain[j] != '\0') {
        plain[j] = rotate(key, plain[j]);
        j++;
    }

    printf("ciphertext: %s\n", plain);

}

char rotate(int k, char letter) {
    if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122)) {
        int dec = (int) letter;
        int r = dec + k;
        if (islower((char) dec) && r > 122) {
            r -= 26;
        }
        else if (isupper((char) dec) && r > 90) {
            r -= 26;
        }
        letter = (char) r;
    }
    return letter;
}
