#include "balance.h"
#include "read.h"

int main() {
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
