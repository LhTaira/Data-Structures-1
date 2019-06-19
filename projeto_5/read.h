#include "Tree.h"

Node* readFromFile(char *filename) {
	int c = 1;

	Node *root = (Node*) malloc(sizeof(Node));
	FILE *file = fopen(filename, "r");

	if(file == NULL)
		return NULL;

	while(!feof(file)) {
		int value;
		fscanf(file, "%d", &value);

		if(c) {
			nodeConstructor(root, value);
			c = 0;
		}

		else
			insertNode(root, value);

		if(!feof(file))
			fscanf(file, "%*c");
	}

	return root;
}