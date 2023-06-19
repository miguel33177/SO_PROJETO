//
// Created by Bruno Miguel on 14/04/2022.
//

#ifndef CHILD_OBJECTIVEC_H
#define CHILD_OBJECTIVEC_H
#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<unistd.h>
#include "./myDataChild.h"
#define MAX_BUFFER 1024




void printToFileC(DATA *myData, int i, int lines, int jump,  char *env[], char roomName[4][MAX_BUFFER]);
#endif //CHILD_OBJECTIVEC_H
