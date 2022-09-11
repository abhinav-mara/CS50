// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
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
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    for (int i = 0; i < N; i++) {
            node* n = malloc(sizeof(n));
            n = table[i];
            if (strcasecmp(n->word, word) == 0) {
                    return true;
            }
            while (n->next != NULL) {
                    if (strcasecmp(n->next->word, word) == 0) {
                            return true;
                    }
                    n = n->next;
            }
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE* fp = fopen(dictionary, "r");

    for (int i = 0; i < N; i++) {
        table[i] = NULL;
    }
    
    while (!feof(fp)) {
        node* n = malloc(sizeof(node));
        if (fgets(n->word, LENGTH + 1, fp) != NULL) {
            int index = hash(n->word);
            node* end = table[index];
            if (end == NULL) {
                n->next = NULL;
                table[index] = n;
            }
            else {
                while (end->next != NULL) {
                    end = end->next;
                }
                n->next = NULL;
                end->next = n;
            }
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
        while (current->next != NULL) {
            wordCounter++;
            current = current->next;
        }
    }
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        node* list = table[i];
        while (list->next != NULL) {
            node* tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return true;
}
