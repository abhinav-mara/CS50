#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int LONGEST_WORD = 100;

typedef struct node {
	char* word;
	struct node* next;
} node;

int main(void) {
	node* hash_table[26];

	node* n = malloc(sizeof(node));
	n->word = "Abhinav";
	n->next = NULL;
	hash_table[0] = n;

	n = malloc(sizeof(node));
	n->word = "Abhiram";
	n->next = NULL;
	hash_table[0]->next = n;

	n = malloc(sizeof(node));
	n->word = "Asad";
	n->next = NULL;
	hash_table[0]->next->next = n;

	n = malloc(sizeof(node));
	n->word = "Billa";
	n->next = NULL;
	hash_table[1] = n;

	n = malloc(sizeof(node));
	n->word = "Baadshah";
	n->next = NULL;
	hash_table[1]->next = n;

	n = malloc(sizeof(node));
	n->word = "Ankitha";
	n->next = NULL;
	hash_table[0]->next->next->next = n;

	for (int i = 0; i < 2; i++) {
		node* list = hash_table[i];
		for (node* tmp = list; tmp != NULL; tmp = tmp->next) {
			printf("%s\n", tmp->word);
		}
	}
	
	for (int i = 0; i < 2; i++) {
		node* list = hash_table[i];
		while (list != NULL) {
			node* tmp = list->next;
			free(list);
			list = tmp;
		}
	}
}
