#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define [i][j] +i*85+j

int i = 0;
int j = 48;
int level = 2;
int side;

typedef struct Node {
	int value;
	struct Node *left, *right;
} Node;

Node *absoluteNode;

void nodeConstructor(Node *node, int value) {
	node->left = node->right = NULL;
	node->value = value;
}

int getHeight(Node *node) {
	int left;
	int right = left = 0;

	if(node->left != NULL)
		left = 1 + getHeight(node->left);

	if(node->right != NULL)
		right = 1 + getHeight(node->right);

	if(left > right)
		return left;

	return right;
}

void searchValue(Node *root, int value) {
	Node *currentNode = root;
	Node *previousNode  = currentNode;

	char direction;
	int c = 0;

	while(currentNode != NULL) {
		if(currentNode->value > value) {
			currentNode = currentNode->left;
			direction = 0;
		}

		else if(currentNode->value < value) {
			currentNode = currentNode->right;
			direction = 1;
		}

		else if(currentNode->value == value)
			break;

		previousNode = currentNode;
		c++;
	}

	if(currentNode != NULL) {
		printf("Nível do nó: %d\nValor do nó pai: %d\n", c, previousNode->value);

		if(!direction) {
			if(previousNode->right != NULL)
				printf("Valor do nó irmão: %d\n", previousNode->right->value);

			else
				printf("Valor do nó irmão: NULL\n");
		}

		else {
			if(previousNode->left != NULL)
				printf("Valor do nó irmão: %d\n", previousNode->left->value);

			else
				printf("Valor do nó irmão: NULL\n");
		}
	}

	else
		printf("Valor não presente na árvore\n");
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

/*void drawMatrix(Node *node, int* treeMatrix) {
	if(node == NULL)
		return;

	int localLine = i;

	*(treeMatrix + (i * 85) + j) = node->value;
	printf("value: %d i: %d, j: %d\n", node->value, i, j);
	getchar();

	if(i == 0)
		for(i++, j--; i < 5; i++, j--)
			*(treeMatrix + (i * 85) + j) = -7;

	else if(i == 5)
		for(i++, j--; i < 8; i++, j--)
			*(treeMatrix + (i * 85) + j) = -7;

	else
		i++; j--; *(treeMatrix + (i * 85) + j) = -7;

	//*(treeMatrix + (i * 85) + j) = node->value;
	printf("value: %d i: %d, j: %d\n", node->value, i, j);
	getchar();

	drawMatrix(node->left, treeMatrix);

	i = localLine;

	if(i == 0)
		for(i++, j--; i < 5; i++, j++)
			*(treeMatrix + (i * 85) + j) = -9;

	else if(i == 5)
		for(i++, j--; i < 8; i++, j++)
			*(treeMatrix + (i * 85) + j) = -9;

	else
		i++; j++; *(treeMatrix + (i * 85) + j) = -9;

	//*(treeMatrix + (i * 85) + j) = node->value;
	printf("value: %d i: %d, j: %d\n", node->value, i, j);
	getchar();

	drawMatrix(node->right, treeMatrix);
}*/

/*void moveArray(int *treeArray) {
	if(side) {
		i = i - 2;
		j = j + 2;
	}
}*/

/*int getLeftWidth(Node *node, int disadvantage) {
	if(node == NULL)
		return 0;

	int width = disadvantage;
	int adversaryWidth = getLeftWidth(node->right, disadvantage - 1);

	while(node->left != NULL) {
		node = node->left;
		width++;
	}

	if(width > adversaryWidth)
		return width;

	return adversaryWidth;
}*/

int getLeftWidth(Node *node, int width) {
	if(node == NULL)
		return -1;

	int leftWidth, rightWidth;
	leftWidth = rightWidth = width;

	if(node->left != NULL)
		leftWidth = getLeftWidth(node->left, width+1);

	if(node->right != NULL)
		rightWidth = getLeftWidth(node->right, width-1);

	if(leftWidth > rightWidth)
		return leftWidth;

	return rightWidth;
}

int getRightWidth(Node *node, int width) {
	if(node == NULL)
		return -1;

	int leftWidth, rightWidth;
	leftWidth = rightWidth = width;

	if(node->right != NULL)
		leftWidth = getLeftWidth(node->left, width+1);

	if(node->left != NULL)
		rightWidth = getLeftWidth(node->right, width-1);

	if(leftWidth > rightWidth)
		return leftWidth;

	return rightWidth;
}

void drawMatrix(Node *node, int* treeMatrix) {
	int c = 0;
	int currentLevel = level;
	int myJ = j;
	int myI = i;
	const int middle = 48;

	/*if(*(treeMatrix+i*85+j) != -77) {
		if(*(treeMatrix+i*85+j) > absoluteNode->value)
			side = 1;

		else
			side = 0;

		moveArray(treeArray);
	}*/

	*(treeMatrix+i*85+j) = node->value;

	/*if((treeMatrix+i*85+j) == (treeMatrix+48))
		side = 0;*/

	i++;
	j--;
	if(node->left != NULL) {
		level = 0;

		if(myJ == middle)
			level = 8;

		else
			if((j - level + getRightWidth(node->left, 1) > middle) || *(treeMatrix+(i+level+1)*85+(j-level+1)) != -77)
				level++;

		for(;level > 0;level--) {
			c = 0;

			for(; c < 1; i++, j--, c++)
				*(treeMatrix+i*85+j) = -7;
		}

		if(!level) {
			c = 0;

			for(; c < 1; i++, j--, c++)
				*(treeMatrix+i*85+j) = -7;
		}

		/*if(level == 2) {
			for(i++, j--; c < 4; i++, j--, c++)
				*(treeMatrix+i*85+j) = -7;

			level = 1;
		}

		else if(level == 1) {
			for(i++, j--; c < 2; i++, j--, c++)
				*(treeMatrix+i*85+j) = -7;

			level = 0;
		}

		else {
			for(i++, j--; c < 1; i++, j--, c++)
				*(treeMatrix+i*85+j) = -7;

			level = 0;
		}*/

		drawMatrix(node->left, treeMatrix);
	}

	level = currentLevel;
	i = myI;
	j = myJ;
	c = 0;

	/*if((treeMatrix+i*85+j) == (treeMatrix+48))
		side = 1;*/

	i++;
	j++;
	if(node->right != NULL) {
		level = 0;

		if(myJ == middle)
			level = 8;

		else
			if((j + level - getLeftWidth(node->right, 1) < middle) || *(treeMatrix+(i+level+1)*85+(j+level+1)) != -77)
				level++;

		for(;level > 0;level--) {
			c = 0;

			for(; c < 1; i++, j++, c++)
				*(treeMatrix+i*85+j) = -9;
		}

		if(!level) {
			c = 0;

			for(; c < 1; i++, j++, c++)
				*(treeMatrix+i*85+j) = -9;
		}

		/*if(level == 2) {
			for(i++, j++; c < 4; i++, j++, c++)
				*(treeMatrix+i*85+j) = -9;

			level = 1;
		}

		else if(level == 1) {
			for(i++, j++; c < 2; i++, j++, c++)
				*(treeMatrix+i*85+j) = -9;

			level = 0;
		}

		else {
			for(i++, j++; c < 1; i++, j++, c++)
				*(treeMatrix+i*85+j) = -9;

			level = 0;
		}*/

		drawMatrix(node->right, treeMatrix);
	}
}

void showTree(Node *root) {
	if(root == NULL)
		return;

	int size = 85 * getHeight(root) * 10;
	int *treeMatrix = (int*) malloc(sizeof(int) * size); //[height][25]

	for(int c = 0; c < size; c++)
		*(treeMatrix + c) = -77;

	//17

	absoluteNode = root;
	drawMatrix(root, treeMatrix);
	int x0, y0, x1, y1;
	x0 = y0 = x1 = y1 = 0;

	for(; x0 < size/85;x0++)//top
		for(int c = 0; c < 85; c++)
			if(*(treeMatrix + c * 85 + x0) != -77)
				goto x1Label;

	x1Label://bottom
	for(x1 = (size/85) - 1; x1 >= x0; x1--)
		for(int c = 0; c < 85; c++)
			if(*(treeMatrix + x1 * 85 + c) != -77)
				goto y0Label;

	y0Label://left
	for(; y0 < 85; y0++)
		for(int c = 0; c < (size/85); c++)
			if(*(treeMatrix + c * 85 + y0) != -77)
				goto y1Label;

	y1Label:
	for(y1 = 85; y1 >= 0; y1--)
		for(int c = 0; c < (size/85); c++)
			if(*(treeMatrix + c * 85 + y1) != -77)
				goto endLabel;

	endLabel:
	for(int c = x0; c < x1 + 1; c++) {
		for(int k = y0; k <= y1; k++) {
			if(*(treeMatrix + c * 85 + k) == -77)
				printf(" ");
			else if(*(treeMatrix + c * 85 + k) == -7)
				printf("/");
			else if(*(treeMatrix + c * 85 + k) == -9)
				printf("\\");
			else
				printf("%d", *(treeMatrix + c * 85 + k));
		}

		printf("\n");
	}

	/*for(int c = x0; c < x1 + 1; c++) {
		for(int k = y0; k <= y1; k++) {
			if(*(treeMatrix + c * 85 + k) == -77)
				printf(" ");
			else if(*(treeMatrix + c * 85 + k) == -7)
				printf("/");
			else if(*(treeMatrix + c * 85 + k) == -9)
				printf("\\");
			else {
				if(*(treeMatrix + c * 85 + k) < 10)
					printf("%d", *(treeMatrix + c * 85 + k));

				else {
					int tenth = 10;
					int content = *(treeMatrix + c * 85 + k);

					while((content % tenth) != content)
						tenth*=10;

					while(tenth > 1) {
						int value = content % tenth;

						value = value/(tenth/10);

						printf("%d", value);
						k++;
						tenth = tenth/10;
					}
				}
			}
		}

		printf("\n");
	}*/

	free(treeMatrix);
}

int main(void) {
	Node *root = readFromFile("bst1.txt");

	if(root == NULL) {
		root = (Node*) malloc(sizeof(Node));
		nodeConstructor(root, 5);
	}


	printf("%d\n", root->value);

	//printf("%d\n", root->left->value);
	//printf("%d\n", root->right->value);

	printf("%d\n", getHeight(root));

	showTree(root);

	searchValue(root, 81);

	freeNodes(root);
	return 0;
}
