//
// Created by Bruno Miguel on 28/04/2022.
//

#ifndef SO_PROJETO_MYDATATIMECOUNT_H
#define SO_PROJETO_MYDATATIMECOUNT_H
#define MAX_BUFFER2 256

#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"
#include <fcntl.h>
#include "string.h"

typedef struct dataTime_Count {
    long T, C;
} DATA2;

void printStampData(DATA2 *myData, int count);

DATA2 * allocData();

#endif //SO_PROJETO_MYDATATIMECOUNT_H
