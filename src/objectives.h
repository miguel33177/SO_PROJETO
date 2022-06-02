//
// Created by Bruno Miguel on 14/04/2022.
//

#ifndef SO_PROJETO_OBJECTIVES_H
#define SO_PROJETO_OBJECTIVES_H

#include "signal.h"
#include "myData.h"
#include "myDataTimeCount.h"
#include "time.h"

#define MAX_BUFFER 1024


void objectiveB();

void objectiveC();

void objectiveC2(DATA2 *myData, int *index, int *numberYears) ;

void printFilesYear(int *index, int m);

int *parse_Years(DATA2 *myData, int * numberYears);



#endif //SO_PROJETO_OBJECTIVES_H
