#include "search.h"

int checkFull(Node * node) {
    if(node == NULL) {
        return 1;
    }

    if (node->left == NULL && node->right ==NULL) {
        return 1;
    }

    if (node->left != NULL && node->right !=NULL && checkFull(node->left) == 1 && checkFull(node->right) == 1) {
        return 1;
    }

    return 0;
}

void isFull(Node * node) {
    if(checkFull(node) == 1) {
        printf("Árvore está cheia\n\n\n");
    } else {
        printf("Árvore não está cheia\n\n\n");
    }
}