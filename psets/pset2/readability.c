#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

float calc_letters_word(int numL, int numW);
float calc_sentences_word(int numS, int numW);

float coleman_liau(float L, float S);

int main(void)
{
    string const TEXT = get_string("Text: ");
    int numLetters = count_letters(TEXT);
    int numWords = count_words(TEXT);
    int numSentences = count_sentences(TEXT);

    float lpw = calc_letters_word(numLetters, numWords);
    float spw = calc_sentences_word(numSentences, numWords);

    float clscore = coleman_liau(lpw, spw);

    int grade = (int) round(clscore);

    if (grade < 1) {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade: %i\n", grade);
    }

}

int count_letters(string text) {
    int i = 0;
    int letters = 0;
    while (text[i] != '\0') {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122)) {
            letters ++;
        }
        i++;
    }
    return letters;
}

int count_words(string text) {
    int i = 0;
    int spaces = 0;
    while (text[i] != '\0') {
        if (text[i] == ' ') {
            spaces++;
        }
        i++;
    }
    return spaces + 1;
}

int count_sentences(string text) {
    int i = 0;
    int sentences = 0;
    while(text[i] != '\0') {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            sentences ++;
        }
        i++;
    }
    
    return sentences;
}

float calc_letters_word(int numL, int numW) {
    return numL*100 / (float) numW;
}

float calc_sentences_word(int numS, int numW) {
    return numS*100 / (float) numW;
}

float coleman_liau(float L, float S) {
    return 0.0588 * L - 0.296 * S - 15.8;
}