#include "full.h"

Node * getInOrderPredecessor(Node * node) {
    if (node == NULL) {
        return node;
    }

    node = node->left;
    while(node->right !=NULL) {
        node = node->right;
    }
    return node;
}
void removeValue(Node * node, int value) {
    Node * target = NULL;
    Node * leaf = NULL;
    Node * root = node;
    int aux;

    if(contains(node, value)) {
        while(target == NULL) {
            if(value == node->value) {
                target = node;
            } else if(value == node->left->value) {
                target = node->left;
            } else if(value == node->right->value) {
                target = node->right;
            } else if(value < node->value) {
                node = node->left;
            } else if(value > node->value) {
                node = node->right;
            }
        }

        if(target->left == NULL && target->right == NULL) {
            if(value == node->value) {
                free(target);
            } else if(value < node->value) {
                node->left = NULL;
                free(target);
            } else if(value > node->value) {
                node->right = NULL;
                free(target);
            }
        } else if(target->left == NULL && target->right != NULL) {
            if(value == node->value) {
                node = node->right;
                free(target);
            } else if(value < node->value) {
                node->left = target->right;
                free(target);
            } else if(value > node->value) {
                node->right = target->right;
                free(target);
            }
        } else if(target->left != NULL && target->right == NULL) {
            if(value == node->value) {
                node = node->left;
                free(target);
            } else if(value < node->value) {
                node->left = target->left;
                free(target);
            } else if(value > node->value) {
                node->right = target->left;
                free(target);
            }
        } else if(target->left != NULL && target->right != NULL) {
            if(value == node->value) {
                leaf = getInOrderPredecessor(node);
                aux = leaf->value;
                removeValue(node, leaf->value);
                node->value = aux;
            } else if(value < node->value) {
                leaf = getInOrderPredecessor(node->left);
                aux = leaf->value;
                removeValue(node, leaf->value);
                node->left->value = aux;
            } else if(value > node->value) {
                leaf = getInOrderPredecessor(node->right);
                aux = leaf->value;
                removeValue(node, leaf->value);
                node->right->value = aux;
            }
        }

        printf("Valor deletado\n");
    } else {
        printf("Valor não existente na árvore\n");
    }
}