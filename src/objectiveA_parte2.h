//
// Created by Bruno Miguel on 25/05/2022.
//

#ifndef SO_PROJETO_OBJECTIVEA_PARTE2_H
#define SO_PROJETO_OBJECTIVEA_PARTE2_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <stdlib.h>
#include "myData.h"

#define NUMBER_THREADS 100
void threads();

int binarySearch(DATA *myData, int lo, int hi, long x);

void printToFile_Part2(int current);
#endif //SO_PROJETO_OBJECTIVEA_PARTE2_H

