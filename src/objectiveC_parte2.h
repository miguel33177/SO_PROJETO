//
// Created by Bruno Miguel on 30/05/2022.
//

#ifndef SO_PROJETO_OBJECTIVEC_PARTE2_H
#define SO_PROJETO_OBJECTIVEC_PARTE2_H


#include <pthread.h>
#include <sys/stat.h>
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
#define MAX_BUFFER 1024

_Bool file_exists(const char *filename);

void threadsC();

void producingC(int current, int pos);

_Bool consumingC(int pos);


void fillDescriptorsArray(int fds, char fileName[]);

int searchDescriptor(char fileName[]);

#endif //SO_PROJETO_OBJECTIVEC_PARTE2_H
