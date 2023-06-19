//
// Created by Bruno Miguel on 12/04/2022.
//

#ifndef CHILD_MYDATA_H
#define CHILD_MYDATA_H
#define MAX_BUFFER 1024



#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"
#include <fcntl.h>
#include "string.h"

typedef struct data {
    int ID;
    long T1, T2, T3, T4, T5;
} DATA;

int binarySearch(DATA *myData, int lo, int hi, long x);

DATA *allocationData(int lines);

#endif //CHILD_MYDATA_H