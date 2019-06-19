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

    if(level == 1) {
        printf("Não existe não existe nó pai nem nó irmão pois valor está na raiz da árvore\n");
    }

    while(thisLevel != level -1) {
        if(value < node->value) {
            thisLevel++;
            node = node->left;
        } else if(value > node->value) {
            thisLevel++;
            node = node->right;
        }
    }
    printf("Valor do nó pai: %d\n", node->value);
    if(value < node->value) {
        if(node->right != NULL) {
        printf("Valor do nó irmão: %d\n", node->right->value);
        } else {
            printf("Não existe nó irmão\n");
        }
    } else if(value > node->value) {
        if(node->left != NULL) {
            printf("Valor do nó irmão: %d\n", node->left->value);
        } else {
            printf("Não existe nó irmão\n");
        }
    }
}
int searchValue(Node * node, int value) {
    int level;
    if(contains(node, value) == 1) {
        printf("Valor encontrado\n");
        level = lookForLevel(node, value);
        printf("Nível: %d\n", level);
        printFamily(node, level, value);
    } else {
        printf("Valor não está presente na árvore\n");
    }
   
}