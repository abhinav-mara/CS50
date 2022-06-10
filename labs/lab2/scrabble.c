#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int compute_score(string word);
int const POINTS[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};         // array containing the point of each letter

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");
    if (compute_score(player1) > compute_score(player2)) {
        printf("Player 1 wins!\n");
    }
    else if (compute_score(player2) > compute_score(player1)) {
        printf("Player 2 wins!\n");
    }
    else {
        printf("TIE\n");
    }
}

int compute_score(string word) {
    int i = 0;
    int score = 0;
    while (word[i] != '\0') {                           // check if we reached the end of the string
        word[i] = toupper(word[i]);                     // make it uniform
        if (word[i] >= 65 && word[i] <= 90) {           // to check that the character is indeed a capital letter
        // word[i]%65 is there to convert the ASCII number of word[i] character into an index of POINTS array
        score += POINTS[word[i]%65];
        }
        i++;
    }
    return score;
}