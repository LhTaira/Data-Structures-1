#include <math.h>
#include "Tree.h"

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