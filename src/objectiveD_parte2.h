//
// Created by Bruno Miguel on 02/06/2022.
//

#ifndef SO_PROJETO_OBJECTIVED_PARTE2_H
#define SO_PROJETO_OBJECTIVED_PARTE2_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <stdlib.h>
#include <dispatch/dispatch.h>
#include "myData.h"
#include "objectiveA_parte2.h"
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include "objectives.h"
#include "myDataTimeCount.h"
#define MAX_BUFFER 256


void threadsD();

void producingD(int current,int pos);

_Bool consumingD(int pos);

int hash(long timestamp);

#endif //SO_PROJETO_OBJECTIVED_PARTE2_H
