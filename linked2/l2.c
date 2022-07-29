#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int number;
	struct node* next;
} node;

int main(void) {
	node* list = NULL;

	node* n = malloc(sizeof(node));
	n->number = 0;
	n->next = NULL;
	list = n;

	node* origin = list;

	for (int i = 1; i < 3; i++) {
		n = malloc(sizeof(node));
		n->number = i;
		n->next = NULL;
		list->next = n;
		list = n;
	}

	list = origin;

	for (node* tmp = list; tmp != NULL; tmp = tmp->next) {
		printf("%i\n", tmp->number);
	}

	while (list != NULL) {
		node* tmp = list->next;
		free(list);
		list = tmp;
	}
}

