//
// Created by Bruno Miguel on 26/05/2022.
//

#ifndef SO_PROJETO_OBJECTIVEB_PARTE2_H
#define SO_PROJETO_OBJECTIVEB_PARTE2_H

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


void threadsB();

void producing(int current, int pos);

_Bool consuming(int pos);

#endif //SO_PROJETO_OBJECTIVEB_PARTE2_H
