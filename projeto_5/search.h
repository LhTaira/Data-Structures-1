#include "balance.h"

int contains(Node * node, int value) {
    if(node == NULL) {
        return 0;
    } else if(value == node->value) {
        return 1;
    } else if(value < node->value) {
        return contains(node->left, value);
    } else if(value > node->value) {
        return contains(node->right, value);
    }
}

int lookForLevel(Node * node, int value) {
    int level = 1;

    while(1) {
        if(value == node->value) {
            return level;
        } else if(value < node->value) {
            level++;
            node = node->left;
        } else if(value > node->value) {
            level++;
            node = node->right;
        }
    }
}

void printFamily(Node * node, int level, int value) {
    int thisLevel = 1;

    while(thisLevel != level -1) {
        if(value < node->value) {
            thisLevel++;
            node = node->left;
        } else if(value > node->value) {
            thisLevel++;
            node = node->right;
        }
    }
    printf("pai: %d\n", node->value);
    if(value < node->value) {
        printf("irmao: %d\n", node->right->value);
    } else if(value > node->value) {
        printf("irmao: %d\n", node->left->value);
    }
}
int searchValue(Node * node, int value) {
    int level;
    if(contains(node, value) == 1) {
        level = lookForLevel(node, value);
        printf("nivel: %d\n", level);
        printFamily(node, level, value);
    }
   
}