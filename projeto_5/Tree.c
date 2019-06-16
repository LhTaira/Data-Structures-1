#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *left, *right;
} Node;

void nodeConstructor(Node *node, int value) {
	node->left = node->right = NULL;
	node->value = value;
}

void insertNode(Node *root, int value) {
	Node *newNode = (Node*) malloc(sizeof(Node));
	nodeConstructor(newNode, value);
	Node *currentNode = root;
    Node *previousNode;

    char direction = -1;

	while(currentNode != NULL) {
		direction = 0;
	    previousNode = currentNode;

		if(currentNode->value > value)
			currentNode = currentNode->left;

		else {
			currentNode = currentNode->right;
			direction = 1;
		}
	}

	if(!direction)
	    previousNode->left = newNode;

	if(direction == 1)
	    previousNode->right = newNode;
}

void freeNodes(Node *node) {
	if(node->left != NULL)
		freeNodes(node->left);

	if(node->right != NULL)
		freeNodes(node->right);

	free(node);
}

int main(void) {
	Node *root = (Node*) malloc(sizeof(Node));;
	nodeConstructor(root, 3);

	printf("%d\n", root->value);

	insertNode(root, 2);
	insertNode(root, 4);

	printf("%d\n", root->left->value);
	printf("%d\n", root->right->value);

	freeNodes(root);
	return 0;
}
