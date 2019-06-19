#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
	int value;
	struct Node *left, *right;
} Node;

void nodeConstructor(Node *node, int value) {
	node->left = node->right = NULL;
	node->value = value;
}

int getHeight(Node *node) {
	int left;
	int right = left = 0;

	if (node == NULL) {
		return 0;
	}

	left = 1 + getHeight(node->left);
	right = 1 + getHeight(node->right);

	if(left > right)
		return left;

	return right;
};

Node * rotateLeft(Node * grandParent) {
	Node * temp = grandParent->right;
	grandParent->right = temp->left;
	temp->left = grandParent;
	return temp;
}

Node * rotateRight(Node * grandParent) {
	Node * temp = grandParent->left;
	grandParent->left = temp->right;
	temp->right = grandParent;
	return temp;
}

Node * rotateRightLeft(Node * grandParent) {
	grandParent->right = rotateRight(grandParent->right);
	return rotateLeft(grandParent);
}

Node * rotateLeftRight(Node * grandParent) {
	grandParent->left = rotateLeft(grandParent->left);
	return rotateRight(grandParent);
}

int checkBalance(Node * node) {

	if (node == NULL) {
		return 1;
	}

	if(abs(getHeight(node->left) - getHeight(node->right)) <=1 && checkBalance(node->left)  == 1 && checkBalance(node->right) == 1) {
		return 1;
	}

	return 0;

}

Node * balanceTree(Node * node) {
	if(node == NULL) {
		return node;
	}

	if (checkBalance(node->left) != 1) {
		node = balanceTree(node->left);
	}
	if (checkBalance(node->right) != 1) {
		node = balanceTree(node->right);
	}
	if(checkBalance(node) != 1) {
		if(getHeight(node->left) - getHeight(node->right) > 1) {
			if(getHeight(node->left->left) > getHeight(node->left->right)) {
				node = rotateLeftRight(node);
			} else {
				node = rotateRight(node);
			}
		} else if(getHeight(node->right) - getHeight(node->left) > 1) {
			if(getHeight(node->right->left) > getHeight(node->right->right)) {
				node = rotateRightLeft(node);
			} else {
				node = rotateLeft(node);
			}
		}
	}

	return node;
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

void freeNodes(Node *node) {
	if(node->left != NULL)
		freeNodes(node->left);

	if(node->right != NULL)
		freeNodes(node->right);

	free(node);
}

int main(void) {
	//Node *root = readFromFile("bst1.txt");
	Node * root = malloc(sizeof(Node));
	nodeConstructor(root, 1);

	//if(root == NULL) {
	//	root = (Node*) malloc(sizeof(Node));
	//	nodeConstructor(root, 3);
	//}


	//printf("%d\n", root->value);

	insertNode(root, 2);
	insertNode(root, 4);
	insertNode(root, 5);
	//insertNode(root, 1);
	insertNode(root, 6);
	insertNode(root, 8);
	//insertNode(root, 7);

	//printf("%d\n", root->left->value);
	//printf("%d\n", root->right->value);

	//printf("%d\n", getHeight(root->right));
	//balanceTree(root);

	root = balanceTree(root);
	if(checkBalance(root) == 1) {
		printf("Arvore equilibrada\n");
	} else {
		printf("Arvore nao equilibrada\n");
	} 

	//root = balanceTree(root);
	/*
	if(checkBalance(root) == 1) {
		printf("Arvore equilibrada\n");
	} else {
		printf("Arvore nao equilibrada\n");
	} 
	*/
	freeNodes(root);
	return 0;
}
