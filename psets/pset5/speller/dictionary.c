// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N+1];

// Record table
int record[N];

// number of times hash() was run
int hashCounter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    char *nL = "\n";

    char* testWord = malloc(LENGTH+2);

    strcpy(testWord, word);

    strcat(testWord, nL);

    for (node* tmp = table[index]; tmp != NULL; tmp = tmp->next) {
        if (strcasecmp(tmp->word, testWord) == 0) {
            free(testWord);
            return true;
        }
    }

    free(testWord);
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    hashCounter++;
    char letter = tolower(word[0]);
    int index = 0;
    switch (letter) {
        case 'a':
            index = 0;
            break;
        case 'b':
            index = 1;
            break;
        case 'c':
            index = 2;
            break;
        case 'd':
            index = 3;
            break;
        case 'e':
            index = 4;
            break;
        case 'f':
            index = 5;
            break;
        case 'g':
            index = 6;
            break;
        case 'h':
            index = 7;
            break;
        case 'i':
            index = 8;
            break;
        case 'j':
            index = 9;
            break;
        case 'k':
            index = 10;
            break;
        case 'l':
            index = 11;
            break;
        case 'm':
            index = 12;
            break;
        case 'n':
            index = 13;
            break;
        case 'o':
            index = 14;
            break;
        case 'p':
            index = 15;
            break;
        case 'q':
            index = 16;
            break;
        case 'r':
            index = 17;
            break;
        case 's':
            index = 18;
            break;
        case 't':
            index = 19;
            break;
        case 'u':
            index = 20;
            break;
        case 'v':
            index = 21;
            break;
        case 'w':
            index = 22;
            break;
        case 'x':
            index = 23;
            break;
        case 'y':
            index = 24;
            break;
        case 'z':
            index = 25;
            break;
        default:
            index = -1;
            break;
    }

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE* fp = fopen(dictionary, "r");

    for (int i = 0; i < N; i++) {
        table[i] = NULL;
        record[i] = -1;
    }
    node* n;
    while (!feof(fp)) {
        bool skip = false;
        n = malloc(sizeof(node));
        if (fgets(n->word, LENGTH + 1, fp) != NULL) {
            int index = hash(n->word);
            if (index == -1) {
               skip = true;
               free(n);
            }
            if (!skip) {
                record[index]++; 
                node* end = table[index];
                if (end == NULL) {
                    n->next = NULL;
                    table[index] = n;
                }
                else {
                    /*
                    node* tmp;
                    for (tmp = end; tmp->next != NULL; tmp = tmp->next) {
                        continue;
                    }
                    n->next = NULL;
                    tmp->next = n;
                    */
                    while (end->next != NULL) {
                        end = end->next;
                    }
                    n->next = NULL;
                    end->next = n;
                }
            }
        }
        else {
            free(n);
        }
    }
    
    fclose(fp);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int wordCounter = 0;
    for (int i = 0; i < N; i++) {
        node* current = table[i];
        for (node* tmp = current; current != NULL; current = current->next) {
            wordCounter++;
        }
    }
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        while (table[i] != NULL) {
            node* tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    for (int i = 0; i < N; i++) {
        if (table[i] != NULL) {
            return false;
        }
    }
    return true;
}
