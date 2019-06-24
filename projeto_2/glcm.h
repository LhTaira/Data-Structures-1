#include <stdio.h>
#include <stdlib.h>

void calcGlcm(unsigned short int *imageMatrix, unsigned short int *pointerMatrix) {
	unsigned short int matrixLine, matrixColumn;
	//0. Up 1. Down. 2. Left 3. Right 4. Up Left 5. Up Right 6. Down Left 7. Down Right
	for(int i = 1; i < 1025; i++) {
		for(int j = 0; j < 1025; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[((i - 1) * 1025) + j];
			*(pointerMatrix + (((256 * 256) * 0) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
	
	for(int i = 0; i < 1024; i++) {
		for(int j = 0; j < 1025; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[((i + 1) * 1025) + j];
			*(pointerMatrix + (((256 * 256) * 1) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
	
	for(int i = 0; i < 1025; i++) {
		for(int j = 1; j < 1025; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[(i * 1025) + (j - 1)];
			*(pointerMatrix + (((256 * 256) * 2) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
	
	for(int i = 0; i < 1025; i++) {
		for(int j = 0; j < 1024; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[(i * 1025) + (j + 1)];
			*(pointerMatrix + (((256 * 256) * 3) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
	
	for(int i = 1; i < 1025; i++) {
		for(int j = 1; j < 1025; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[((i - 1) * 1025) + (j - 1)];
			*(pointerMatrix + (((256 * 256) * 4) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
	
	for(int i = 1; i < 1025; i++) {
		for(int j = 0; j < 1024; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[((i - 1) * 1025) + (j + 1)];
			*(pointerMatrix + (((256 * 256) * 5) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
	
	for(int i = 0; i < 1024; i++) {
		for(int j = 1; j < 1025; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[((i + 1) * 1025) + (j - 1)];
			*(pointerMatrix + (((256 * 256) * 6) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
	
	for(int i = 0; i < 1024; i++) {
		for(int j = 0; j < 1024; j++) {
			matrixLine = imageMatrix[(i * 1025) + j];
			matrixColumn = imageMatrix[((i + 1) * 1025) + (j + 1)];
			*(pointerMatrix + (((256 * 256) * 7) + (256 * matrixLine) + matrixColumn)) += 1;
		}
	}
}

void normalizeGlcm(unsigned short int *pointerMatrix, float *normalizedMatrix) {
	for(int c = 0; c < 8; c++) {
		long int sum = 0;
	
		for(int i = 0; i < 256; i++)
			for(int j = 0; j < 256; j++)
				sum += *(pointerMatrix + (((256 * 256) * c) + (256 * i) + j));
				
		for(int i = 0; i < 256; i++)
			for(int j = 0; j < 256; j++)
				*(normalizedMatrix + (((256 * 256) * c) + (256 * i) + j)) = (*(pointerMatrix + (((256 * 256) * c) + (256 * i) + j))/((float) sum));
	}
}

void extractCharacteristics(double *contrast, double *energy, double *homogeneity, unsigned short int *pointerMatrix, float *normalizedMatrix) {
	normalizeGlcm(pointerMatrix, normalizedMatrix);
	
	for(int c = 0; c < 8; c++)
		for(int i = 0; i < 256; i++)
			for(int j = 0; j < 256; j++) {
				contrast[c] += ((i - j) * (i - j)) * (*(normalizedMatrix + (256 * 256 * c) + (256 * i) + j));
				energy[c] += (*(normalizedMatrix + (256 * 256 * c) + (256 * i) + j)) * (*(normalizedMatrix + (256 * 256 * c) + (256 * i) + j));
				homogeneity[c] += (*(normalizedMatrix + (256 * 256 * c) + (256 * i) + j))/(1.0 + abs(i - j));
			}
}
