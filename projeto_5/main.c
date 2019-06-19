#include "balance.h"

int main() {
	Node * root = readFromFile("BSTs/bst1.txt");
	
	//printf("%d\n", root->left->value);
	printInOrder(root);

	freeNodes(root);
	return 0;
}
