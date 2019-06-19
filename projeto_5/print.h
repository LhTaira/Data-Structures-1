#include "read.h"

void printInOrder(Node * node) {
    
    if(node == NULL) {
        return;
    }

    printInOrder(node->left);
    printf("%d\n", node->value);
    printInOrder(node->right);
}

void printPreOrder(Node * node) {
    
    if(node == NULL) {
        return;
    }

    printf("%d\n", node->value);
    printInOrder(node->left);
    printInOrder(node->right);
}

void printPostOrder(Node * node) {
    
    if(node == NULL) {
        return;
    }

    printInOrder(node->left);
    printInOrder(node->right);
    printf("%d\n", node->value);
}