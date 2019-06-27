/*
Luis Henrique Pereira Taira		17/0109208
Samuel de Souza Buters Pereira	17/0114040
*/

#include <stdio.h>
#include <stdlib.h>
#include "imageToMatrix.h"
#include "openImages.h"
#include "ilbp.h"
#include "glcm.h"
#include "feature.h"
#include "neuron.h"
#include "backPropagation.c"

int main(int argc) {
	
	List * inputNeuronLayer;
	List * hiddenNeuronLayer;
	List * outputNeuronLayer;
	List * neuron;

	int * ilbp;

	double * featureVectorGrassTrain;
	double * featureVectorAsphaltTrain;
	double * featureVectorGrassTrainSoma;
	double * featureVectorAsphaltTrainSoma;

	double * featureVectorGrassTest;
	double * featureVectorAsphaltTest;
	double * featureVectorGrassTestSoma;
	double * featureVectorAsphaltTestSoma;
	double * inputLayerOutput;
	double * hiddenLayerOutput;
	double * output;


	double grassDist;
	double asphaltDist;
	double featureMatrixGrassTrain[25][536];
	double featureMatrixAsphaltTrain[25][536];
	double errorSum = 0;
	double meanSquareError;
	double examples = 1.0;
	
	int i=0;
	int taxaDeAcerto=0;
	int taxaDeFalsaAceitacao=0;
	int taxaDeFalsaRejeicao=0;
	int iteracoes = 25;
	
	short int randVecTrain[25];
	short int randvecTest[25];

	unsigned short int grassMatrix[1025][1025];
	unsigned short int asphaltMatrix[1025][1025];
	unsigned short int pointerMatrix[8][256][256] = { 0 };
	
	float normalizedMatrix[8][256][256] = { 0 };
	float progress = 0;

	char asphaltName[34] = "./DataSet/asphalt/asphalt_xx.txt\0";
	char grassName[29] = "./DataSet/grass/grass_xx.txt\0";

	inputNeuronLayer = (List *) malloc(sizeof(List));
	hiddenNeuronLayer = (List *) malloc(sizeof(List));
	outputNeuronLayer = (List *) malloc(sizeof(List));
	neuron = (List *) malloc(sizeof(List));

	featureVectorGrassTrain = (double*) malloc((512+24) * sizeof(double));
	featureVectorAsphaltTrain = (double*) malloc((512+24) * sizeof(double));
	featureVectorGrassTrainSoma = (double*) calloc(512+24, sizeof(double));
	featureVectorAsphaltTrainSoma = (double*) calloc(512+24, sizeof(double));

	featureVectorGrassTest = (double*) malloc((512+24) * sizeof(double));
	featureVectorAsphaltTest = (double*) malloc((512+24) * sizeof(double));
	featureVectorGrassTestSoma = (double*) calloc(512+24, sizeof(double));
	featureVectorAsphaltTestSoma = (double*) calloc(512+24, sizeof(double));
	
	inputLayerOutput = (double *) malloc(536 * sizeof(double));
	hiddenLayerOutput = (double *) malloc(argc * sizeof(double));
	output = (double *) malloc(sizeof(double));

	randomizeVector(randVecTrain, randvecTest);

	FILE *grassFile;	
	FILE *asphaltFile;

	randomizeThings(inputNeuronLayer, 536);
	randomizeThings(hiddenNeuronLayer, argc);
	randomizeOneThing(outputNeuronLayer, argc);

	for (short int i=0; i<iteracoes; i++) {
		printf("Leitura de imagens: %d\%%\n", i*4);
		getFileName(asphaltName, grassName, randVecTrain[i]);
		
		double contrastGrass[8] = { 0 };
		double energyGrass[8] = { 0 };
		double homogeneityGrass[8] = { 0 };

		double contrastAsphalt[8] = { 0 };
		double energyAsphalt[8] = { 0 };
		double homogeneityAsphalt[8] = { 0 };

		grassFile = fopen(grassName, "r");
		asphaltFile = fopen(asphaltName, "r");

		imageToMatrix(grassFile, &grassMatrix[0][0]);
		imageToMatrix(asphaltFile, &asphaltMatrix[0][0]);

		ilbp = (int*) calloc(512, sizeof(int));

		calcIlbp(&grassMatrix[0][0], ilbp);

		for(int c=0; c<512; c++) {
			featureVectorGrassTrain[c] = ilbp[c];
		}
		
		calcGlcm(&grassMatrix[0][0], &pointerMatrix[0][0][0]);

		extractCharacteristics(contrastGrass, energyGrass, homogeneityGrass, &pointerMatrix[0][0][0], &normalizedMatrix[0][0][0]);

		appendGlcm(featureVectorGrassTrain, contrastGrass, energyGrass, homogeneityGrass);
     
		normalizeFeatureVector(featureVectorGrassTrain);
		
		
		for(int j=0; j<536; j++) {
			featureMatrixGrassTrain[i][j] = featureVectorGrassTrain[j];
		}

		free(ilbp);
        
		ilbp = (int*) calloc(512, sizeof(int));
		
		for(int c = 0; c < 8; c++)
			for(int i = 0; i < 256; i++)
				for(int j = 0; j < 256; j++)
					pointerMatrix[c][i][j] = 0;

		calcIlbp(&asphaltMatrix[0][0], ilbp);

		for(int c=0; c<512; c++) {
			featureVectorAsphaltTrain[c]=ilbp[c];
		}

		calcGlcm(&asphaltMatrix[0][0], &pointerMatrix[0][0][0]);

		extractCharacteristics(contrastAsphalt, energyAsphalt, homogeneityAsphalt, &pointerMatrix[0][0][0], &normalizedMatrix[0][0][0]);

		appendGlcm(featureVectorAsphaltTrain, contrastAsphalt, energyAsphalt, homogeneityAsphalt);

		normalizeFeatureVector(featureVectorAsphaltTrain);
		
		for(int j=0; j<536; j++) {
			featureMatrixAsphaltTrain[i][j] = featureVectorAsphaltTrain[j];
		}

		free(ilbp);

		for(int c = 0; c < 8; c++)
			for(int i = 0; i < 256; i++)
				for(int j = 0; j < 256; j++)
					pointerMatrix[c][i][j] = 0;

		fclose(grassFile);
    	fclose(asphaltFile);
	}
	printf("Leitura de imagens: 100%%\n");

	// for(int j=0; j<536; j++) {
	// 	featureVectorGrassTrainSoma[j]=featureVectorGrassTrainSoma[j]/25.0;
	// 	featureVectorAsphaltTrainSoma[j]=featureVectorAsphaltTrainSoma[j]/25.0;
	// }

	for(int i = 0; i < 1000; i++) {
		
		for(int j = 0; j < 25; j++) {
			printf("Epoca %d: %i%%\n", i+1, (j+1)*4);
			
			inputLayerOutput = getLayerOutput(inputNeuronLayer, 536, featureMatrixGrassTrain[j], 536);
			hiddenLayerOutput = getLayerOutput(hiddenNeuronLayer, argc, inputLayerOutput, 536);
			output = getLayerOutput(outputNeuronLayer, 1, hiddenLayerOutput, argc);

			// printf("esperado: 1, output: %.14lf\n", output);
			errorSum += pow(1.0 - *output, 2);
			meanSquareError = errorSum/(examples++);

			if(meanSquareError <= 0.2 && j > 2) {
				break;
			}

			propagate(1, output, outputNeuronLayer, hiddenNeuronLayer, inputNeuronLayer, argc, hiddenLayerOutput, inputLayerOutput);
			
			printf("MSE: %lf\n", meanSquareError);

			inputLayerOutput = getLayerOutput(inputNeuronLayer, 536, featureMatrixAsphaltTrain[j], 536);
			hiddenLayerOutput = getLayerOutput(hiddenNeuronLayer, argc, inputLayerOutput, 536);
			output = getLayerOutput(outputNeuronLayer, 1, hiddenLayerOutput, argc);
			
			// printf("esperado: 0, output: %.14lf\n", output);
			errorSum += pow(0.0 - *output, 2);
			meanSquareError = errorSum/(examples++);

			if(meanSquareError <= 0.2 && j > 2) {
				break;
			}

			propagate(0, output, outputNeuronLayer, hiddenNeuronLayer, inputNeuronLayer, argc, hiddenLayerOutput, inputLayerOutput);

			printf("MSE: %lf\n", meanSquareError);
		}

		if(meanSquareError <= 0.2) {
				break;
			}
	}


	for (short int i=0; i<iteracoes; i++) {
		printf("Teste: %d\%%\n", i*4);
		getFileName(asphaltName, grassName, randvecTest[i]);
		
		double contrastGrass[8] = { 0 };
		double energyGrass[8] = { 0 };
		double homogeneityGrass[8] = { 0 };

		double contrastAsphalt[8] = { 0 };
		double energyAsphalt[8] = { 0 };
		double homogeneityAsphalt[8] = { 0 };

		grassFile = fopen(grassName, "r");
		asphaltFile = fopen(asphaltName, "r");


		imageToMatrix(grassFile, &grassMatrix[0][0]);
		imageToMatrix(asphaltFile, &asphaltMatrix[0][0]);

		ilbp = (int*) calloc(512, sizeof(int));

		calcIlbp(&grassMatrix[0][0], ilbp);

		for(int c=0; c<512; c++) {
			featureVectorGrassTest[c] = ilbp[c];
		}
		
		calcGlcm(&grassMatrix[0][0], &pointerMatrix[0][0][0]);

		extractCharacteristics(contrastGrass, energyGrass, homogeneityGrass, &pointerMatrix[0][0][0], &normalizedMatrix[0][0][0]);

		appendGlcm(featureVectorGrassTrain, contrastGrass, energyGrass, homogeneityGrass);
     
		normalizeFeatureVector(featureVectorGrassTest);

		inputLayerOutput = getLayerOutput(inputNeuronLayer, 536, featureVectorGrassTest, 536);
		hiddenLayerOutput = getLayerOutput(hiddenNeuronLayer, argc, inputLayerOutput, 536);
		output = getLayerOutput(outputNeuronLayer, 1, hiddenLayerOutput, argc);

		if((*output) <= 0.5) {
			taxaDeFalsaRejeicao++;
		} else {
			taxaDeAcerto++;
		}

		free(ilbp);

		ilbp = (int*) calloc(512, sizeof(int));
		
		for(int c = 0; c < 8; c++)
			for(int i = 0; i < 256; i++)
				for(int j = 0; j < 256; j++)
					pointerMatrix[c][i][j] = 0;

		calcIlbp(&asphaltMatrix[0][0], ilbp);

		for(int c=0; c<512; c++) {
			featureVectorAsphaltTest[c]=ilbp[c];
		}

		calcGlcm(&asphaltMatrix[0][0], &pointerMatrix[0][0][0]);

		extractCharacteristics(contrastAsphalt, energyAsphalt, homogeneityAsphalt, &pointerMatrix[0][0][0], &normalizedMatrix[0][0][0]);

		appendGlcm(featureVectorAsphaltTest, contrastAsphalt, energyAsphalt, homogeneityAsphalt);

		normalizeFeatureVector(featureVectorAsphaltTest);

		inputLayerOutput = getLayerOutput(inputNeuronLayer, 536, featureVectorAsphaltTest, 536);
		hiddenLayerOutput = getLayerOutput(hiddenNeuronLayer, argc, inputLayerOutput, 536);
		output = getLayerOutput(outputNeuronLayer, 1, hiddenLayerOutput, argc);

		if( (*output) <= 0.5) {
			taxaDeAcerto++;
		} else {
			taxaDeFalsaAceitacao++;
		}
		
		
		free(ilbp);

		for(int c = 0; c < 8; c++)
			for(int i = 0; i < 256; i++)
				for(int j = 0; j < 256; j++)
					pointerMatrix[c][i][j] = 0;

		fclose(grassFile);
    	fclose(asphaltFile);
	}

	printf("Taxa de Acerto: %d%%\nTaxa de Falsa Aceitação: %d%%\nTaxa de Falsa Rejeição: %d%%\n", taxaDeAcerto*2, taxaDeFalsaAceitacao*2, taxaDeFalsaRejeicao*2);


	
	return 0;
}
