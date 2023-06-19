//
// Created by Bruno Miguel on 29/04/2022.
//

#ifndef CHILD_OBJECTIVED_H
#define CHILD_OBJECTIVED_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "./myDataChild.h"
#include "sys/socket.h"
#include "sys/un.h"
#define BUF_SIZE 8192

void socketChild(DATA *myData, int i, int lines, int jump, char *env[], char roomName[4][MAX_BUFFER]);

#endif //CHILD_OBJECTIVED_H
