#include <math.h>
#include "print.h"


int height(Node *node) {
	int left;
	int right = left = 0;

	if (node == NULL) {
		return 0;
	}

	left = 1 + height(node->left);
	right = 1 + height(node->right);

	if(left > right)
		return left;

	return right;
}

int getHeight(Node *node) {
	printf("Altura da árvore: %d\n", height(node));
}

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

	if(abs(height(node->left) - height(node->right)) <=1 && checkBalance(node->left)  == 1 && checkBalance(node->right) == 1) {
		return 1;
	}

	return 0;

}

Node * balanceTree(Node * node) {
	if(node == NULL) {
		return node;
	}

	if (checkBalance(node->left) != 1) {
		node->left = balanceTree(node->left);
	}
	if (checkBalance(node->right) != 1) {
		node->right  = balanceTree(node->right);
	}
	if(checkBalance(node) != 1) {
		if(height(node->left) - height(node->right) > 1) {
			if(height(node->left->left) > height(node->left->right)) {
				node = rotateRight(node);
			} else {
				node = rotateLeftRight(node);
			}
		} else if(height(node->right) - height(node->left) > 1) {
			if(height(node->right->left) > height(node->right->right)) {
				node = rotateRightLeft(node);
			} else {
				node = rotateLeft(node);
			}
		}
	}

	//if(checkBalance(node) != 1) {
		//balanceTree(node);
	//}

	return node;
}