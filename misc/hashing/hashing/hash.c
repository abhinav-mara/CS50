#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node {
	char* word;
	struct node* next;
} node;

int hash_func(char* word);

int main(void) {
	node* hash_table[26];
	int index;
	node* n;

	int values[26];
	for (int i = 0; i < 26; i++) {
		values[i] = -1;
	}
	
	char* name = "Abhinav";

	index = hash_func(name);
	values[index] = 0;
	n = malloc(sizeof(node));
	n->word = name; 
	n->next = NULL;
	hash_table[index] = n;

	name = "Mara";

	index = hash_func(name);
	values[index] = 0;
	n = malloc(sizeof(node));
	n->word = name;
	n->next = NULL;
	hash_table[index] = n;

	name = "Abhiram";
	
	index = hash_func(name);
	values[index] = 0;
	n = malloc(sizeof(node));
	n->word = name;
	n->next = NULL;
	hash_table[index]->next = n;

	for (int i = 0; i < 26; i++) {
		if (values[i] > -1) {
			node* list = hash_table[i];
			for (node* tmp = list; tmp != NULL; tmp = tmp->next) {
				printf("%s\n", tmp->word);
			}
		}
	}

	for (int i = 0; i < 26; i++) {
		if (values[i] > -1) {
			node* list = hash_table[i];
			while (list != NULL) {
				node* tmp = list->next;
				free(list);
				list = tmp;
			}
		}
	}
	

}

int hash_func(char* word) {
	return toupper(word[0]) - 65;
}
