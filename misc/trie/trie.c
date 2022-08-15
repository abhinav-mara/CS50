#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node {
	char* university;
	struct node* children[10];
} node;


node* root;

int main(void) {
	root = malloc(sizeof(node));
	node* trav = root;
	trav->university = NULL;
	for (int i = 0; i < 10; i++) {
		trav->children[i] = NULL;
	}
	node* n;

	int years[4] = {1, 8, 1, 9};

	for (int i = 0; i < 4; i++) {
		n = malloc(sizeof(node));
		n->university = NULL;
		for (int i = 0; i < 10; i++) {
			n->children[i] = NULL;
		}
		trav->children[years[i]] = n;
		trav = trav->children[years[i]];
	}

	trav->university ="University of Virginia";

	trav = root;

	while (trav->university == NULL) {
		for (int i = 0; i < 10; i++) {
			if (trav->children[i] != NULL) {
				trav = trav->children[i];
				i = 0;
			}
		}
	}

	printf("%s\n", trav->university);

	trav = root;

	while (trav->university == NULL) {
		node* tmp;
		for (int i = 0; i < 10; i++) {
			if (trav->children[i] != NULL) {
				tmp = trav->children[i];
				break;
			}
		}
		free(trav);
		trav = tmp;
	}
	free(trav);
}
