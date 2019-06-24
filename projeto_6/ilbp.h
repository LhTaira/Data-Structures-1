#ifndef ILBP_H
#define ILBP_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calcIlbp(unsigned short int * imageMatrix, int * ilbp) {
	int ilbp2[512];
	int binaryVector[9];
	int binaryVectorAux[9];
	int index = 0;
	float average = 0;
	int number=0;
	int minNumber=0;
	short int auxMatrix[3][3];
	int c, k, i, j;

	for(c = 1; c < 1024; c++) {
		for(k = 1; k < 1024; k++) {

			for(j = 0; j < 3; j++) {
				for(i = 0; i < 3; i++) {
					auxMatrix[j][i] = *(imageMatrix + (((c - 1 + j) * 1025) + (k - 1 + i)));
					// auxMatrix[j][i] = imageMatrix[c + j][k + i];
					average += auxMatrix[j][i];
				}
			}
			average = average/9.0;

			index = 0;
			for(j = 0; j < 3; j++) {
				for(i = 0; i < 3; i++) {
					if(auxMatrix[i][j] <= average) {
						binaryVector[index] = 0;
					} else {
						binaryVector[index] = 1;
					}
					index++;
				}
			}

			number=0;
			for (i=0; i<9; i++) {
				number+=(binaryVector[i]*pow(2, i));
			}


			minNumber = number;
			for (j=0; j< 8; j++) {

				for (i=0; i<9; i++) {
					if (i!=8){
						binaryVectorAux[i] = binaryVector[i+1];
					} else {
						binaryVectorAux[i] = binaryVector[0];
					}
				}


				for (i=0; i<9; i++) {binaryVector[i]=binaryVectorAux[i];}


				number=0;
				for (i=0; i<9; i++) {
					number+=(binaryVectorAux[i]*pow(2, i));
				}


				if (number<minNumber) {
					minNumber = number;
				}
				
			}
			ilbp[minNumber]++;
		}
	}
}

#endif
