#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void appendGlcm(double * featureVector, double * contrast, double * energy, double * homogeneity ) {
	for(int c = 0; c < 8; c++) {
		featureVector[511+c+1] = contrast[c];
	}

	for(int c = 0; c < 8; c++) {
		featureVector[511+c+8+1] = energy[c];
	}

	for(int c = 0; c < 8; c++) {
		featureVector[511+c+8+8+1] = homogeneity[c];
	}
}

void normalizeFeatureVector(double * featureVector) {
    double maxElement=0;
    double minElement;

    minElement=featureVector[0];

    for(int i=0; i<536; i++) {

        if(featureVector[i]>maxElement) {
            maxElement=featureVector[i];
        }

        if(featureVector[i]<minElement) {
            minElement=featureVector[i];
        } 
    }

    for(int i=0; i<536; i++) {
        featureVector[i] = (featureVector[i] - minElement) / (maxElement - minElement);
    }
}

double calcEuclidianDistance(double * vector1, double * vector2) {

    double soma=0;

    for(int i=0; i<536; i++) {
        soma+= (double) pow((vector1[i]-vector2[i]), 2);
    }

    return  (double) sqrt(soma);
}