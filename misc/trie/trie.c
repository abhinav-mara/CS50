#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

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
		int digit;
		printf("key: ");
		scanf("%i", &digit);
		trav->children[digit] = n;
		trav = trav->children[digit];
	}

	trav->university = "University of Virginia";

	printf("Key and respective result have been created\n");

	trav = root;

	while (trav->university == NULL) {
		for (int i = 0; i < 4; i++) {
			int digit;
			printf("Key: ");
			scanf("%i", &digit);
			if (trav->children[digit] != NULL) {
				trav = trav->children[digit];
			}
			else {
				printf("Key does not exist\n");
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
				return 1;
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
