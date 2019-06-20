int i = 0;
int j = 48;
int level = 2;
int side;

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

	*(treeMatrix+i*85+j) = node->value;

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

		drawMatrix(node->left, treeMatrix);
	}

	level = currentLevel;
	i = myI;
	j = myJ;
	c = 0;

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

		drawMatrix(node->right, treeMatrix);
	}
}

void showTree(Node *root) {
	if(root == NULL)
		return;

	int size = 85 * height(root) * 10;
	int *treeMatrix = (int*) malloc(sizeof(int) * size);

	for(int c = 0; c < size; c++)
		*(treeMatrix + c) = -77;

	drawMatrix(root, treeMatrix);
	int x0, y0, x1, y1;
	x0 = y0 = x1 = y1 = 0;

	for(; x0 < size/85;x0++)
		for(int c = 0; c < 85; c++)
			if(*(treeMatrix + c * 85 + x0) != -77)
				goto x1Label;

	x1Label:
	for(x1 = (size/85) - 1; x1 >= x0; x1--)
		for(int c = 0; c < 85; c++)
			if(*(treeMatrix + x1 * 85 + c) != -77)
				goto y0Label;

	y0Label:
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
