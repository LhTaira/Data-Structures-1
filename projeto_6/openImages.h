#ifndef OPENIMAGES_H
#define OPENIMAGES_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getFileName(char *asphaltName, char *grassName, int num) {

 char aux[5];

  snprintf(aux, 5, "%d", num); 
  if(num < 10) {
  asphaltName[8+18] = '0';
  grassName[6+16] = '0';
  asphaltName[9+18] = aux[0];
  grassName[7+16] = aux[0];
  } else {
  asphaltName[8+18] = aux[0];
  grassName[6+16] = aux[0];
  asphaltName[9+18] = aux[1];
  grassName[7+16] = aux[1];
  }
}

void randomizeVector(short int *randVecTrain, short int *randVecTest) {

  srand(time(NULL));
  int i=0,j=0,existente=0;
  do{

    j++;

    if(rand()%2 == 0) {

      for(int k=0; k<i; k++) {
        if(j==randVecTrain[k] || j>=50) {
          existente=1;
        };
      }
        if(existente==0) {
          randVecTrain[i++]=j;
        } else {
          j=0;
          existente=0;
        }
    }
  }while(i!=25);

  j=0;
  i=0;
  existente=0;
  do{
    j++;
    for(int k=0; k<25; k++) {
      if(j==randVecTrain[k]){
        existente=1;
      }
    }
    if(existente==0) {
      randVecTest[i++]=j;
    } else {
      existente=0;
    }
  }while(j<50);
}

#endif