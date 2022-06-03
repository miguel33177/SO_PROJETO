//
// Created by Bruno Miguel on 01/04/2022.
//

#ifndef SO_PROJETO_MYDATA_H
#define SO_PROJETO_MYDATA_H
#define MAX_BUFFER 256


#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"
#include <fcntl.h>
#include "string.h"

typedef struct data {
    int ID;
    long T1, T2, T3, T4, T5;
} DATA;

void printData(DATA *myData, int count);

void printData2();

int numberCores();

int isDigit(char c);

int numberLines();

int isSpace(char c);

int isNewLine(char c);

//int binarySearch(DATA *myData, int lo, int hi, long x);

char *operatingSystem(char buffer1[]);

DATA *allocationData(int lines);


#endif //SO_PROJETO_MYDATA_H