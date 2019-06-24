#ifndef IMAGETOMATRIX_H
#define IMAGETOMATRIX_X
#include <stdio.h>

void imageToMatrix(FILE *imageFile, unsigned short int *imageMatrix) {
	int c;
	c = 0;

	if(imageFile == NULL)
		return;

	while(!feof(imageFile) && c < (1025 * 1025)) {
		fscanf(imageFile, "%hd", imageMatrix + c);
		
		if((!feof(imageFile)) && (((c + 1)%1025) != 0))
			fscanf(imageFile, "%*c");
			
		c++;
	}

	return;
}

// int main() {
// 	FILE *imageFile;
// 	unsigned short int imageMatrix[1025][1025];

// 	imageFile = fopen("grass_01.txt", "r");

// 	imageToMatrix(imageFile, &imageMatrix[0][0]);
	
// 	printf("Imprimindo as 10 primeiras linhas e 10 primeiras colunas:\n");
	
// 	for(int c = 0; c < 10; c++) {
// 		for(int x = 0; x < 10; x++) {
// 			printf("%d ", imageMatrix[c][x]);
// 		}
		
// 		printf("\n");
// 	}
	
// 	printf("Imprimindo as 10 ultimas linhas e 10 ultimas colunas:\n");
	
// 	for(int c = 1015; c < 1025; c++) {
// 		for(int x = 1015; x < 1025; x++) {
// 			printf("%d ", imageMatrix[c][x]);
// 		}
		
// 		printf("\n");
// 	}

// 	return 0;
// }

#endif
