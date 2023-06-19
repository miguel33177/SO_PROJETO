//
// Created by Bruno Miguel on 14/04/2022.
//
#ifndef CHILD_OBJECTIVEB_H
#define CHILD_OBJECTIVEB_H

#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<unistd.h>
#include "./myDataChild.h"
#define MAX_BUFFER 1024




void printToFileB(DATA *myData, int i, int lines, int jump,  char *env[], char roomName[4][MAX_BUFFER]);
#endif //CHILD_OBJECTIVEB_H