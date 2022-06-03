//
// Created by Bruno Miguel on 30/05/2022.
//

#include "objectiveC_parte2.h"


typedef struct list {
    long timestamp;
    char *room;
    int occupation;
} LIST;

typedef struct param {
    int i;
} PARAM;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t secondMutex = PTHREAD_MUTEX_INITIALIZER;
static boolean_t keepConsuming[NUMBER_THREADS] = {[0 ... NUMBER_THREADS - 1]=true};
static LIST **list;
static int columns = 12;
static DATA *myData;
static int file;
static int lines;
static int counter = 0;


void *producerC(void *i) {
    PARAM *param = i;
    while (counter <= numberLines() - NUMBER_THREADS) {
        int curr;
        pthread_mutex_lock(&mutex);
        curr = counter;
        counter++;
        pthread_mutex_unlock(&mutex);
        producingC(curr, param->i);
    }
    keepConsuming[param->i] = false;
    return NULL;
}

void *consumerC(void *i) {
    PARAM *param = i;
    while (keepConsuming[param->i] == true || consumingC(param->i) == true) {
        consumingC(param->i);
    }
    return NULL;
}

void threadsC() {
    pthread_t thread_consumidor[NUMBER_THREADS];
    pthread_t thread_produtor[NUMBER_THREADS];
    lines = numberLines();
    myData = allocationData(lines);
    struct tm info;
    char buffer[MAX_BUFFER];
    char filename[MAX_BUFFER];

    for (int i = 0; i < lines; i++) {
        time_t rawtime = myData[i].T1;
        info = *localtime(&rawtime);
        strftime(buffer, 80, "%Y", &info);
        sprintf(filename, "../data/outProducerConsumerParseYears%s.txt", buffer);

        if (file_exists(filename)) {
            remove(filename);
            file = open(filename, O_WRONLY | O_CREAT);
            char cmd[MAX_BUFFER];
            sprintf(cmd, "chmod 777 %s", filename);
            system(cmd);
        } else {
            file = open(filename, O_WRONLY | O_CREAT);
            char cmd[MAX_BUFFER];
            sprintf(cmd, "chmod 777 %s", filename);
            system(cmd);
        }
    }

    list = malloc(sizeof(LIST *) * NUMBER_THREADS);
    for (int i = 0; i < NUMBER_THREADS; i++) {
        list[i] = malloc(sizeof(LIST) * columns);
    }
    for (int i = 0; i < NUMBER_THREADS; i++) {
        PARAM *param = malloc(sizeof(PARAM));
        param->i = i;
        if (pthread_create(&thread_consumidor[i], NULL, &producerC, param) != 0) {
            perror("ERROR CREATING THREAD");
        }
    }
    for (int i = 0; i < NUMBER_THREADS; i++) {
        PARAM *param = malloc(sizeof(PARAM));
        param->i = i;
        if (pthread_create(&thread_produtor[i], NULL, &consumerC, param) != 0) {
            perror("ERROR CREATING THREAD");
        }
    }
    for (int i = 0; i < NUMBER_THREADS; i++) {
        if (pthread_join(thread_consumidor[i], NULL) != 0) {
            perror("ERROR JOINING THREAD");
        }
    }
    for (int i = 0; i < NUMBER_THREADS; i++) {
        if (pthread_join(thread_produtor[i], NULL) != 0) {
            perror("ERROR JOINING THREAD");
        }
    }

    close(file);
}

void producingC(int current, int pos) {
    int room[4] = {};
    for (int j = current; j > binarySearch(myData, 0, current, myData[current].T1); j--) {
        if (myData[current].T1 > myData[j].T1 && myData[current].T1 < myData[j].T2) {
            room[0]++;
        }
        if (myData[current].T1 > myData[j].T2 && myData[current].T1 < myData[j].T3) {
            room[1]++;
        }
        if (myData[current].T1 > myData[j].T3 && myData[current].T1 < myData[j].T4) {
            room[2]++;
        }
        if (myData[current].T1 > myData[j].T4 && myData[current].T1 < myData[j].T5) {
            room[3]++;
        }
    }
    for (int z = 0; z < 4; z++) {
        if (z == 0) {
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {

                    list[pos][i].room = "Sala de Admissao";

                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
        if (z == 1) {
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {

                    list[pos][i].room = "Triagem";

                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
        if (z == 2) {
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {

                    list[pos][i].room = "Sala de Espera";

                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
        if (z == 3) {
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {
                    list[pos][i].room = "Medico";

                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
    }
}

_Bool consumingC(int pos) {
    for (int i = columns - 1; i >= 0; i--) {
        if (list[pos][i].room != NULL) {
            char fileNameYear[MAX_BUFFER];
            char bufferTime[MAX_BUFFER];
            char buffer[MAX_BUFFER];
            struct tm info;
            sprintf(buffer, "%ld,%d,%s\n", list[pos][i].timestamp, list[pos][i].occupation, list[pos][i].room);
            list[pos][i].room = NULL;
            time_t rawtime = list[pos][i].timestamp;
            info = *localtime(&rawtime);
            strftime(bufferTime, 80, "%Y", &info);
            pthread_mutex_lock(&secondMutex);
            sprintf(fileNameYear, "../data/outProducerConsumerParseYears%s.txt", bufferTime);
            if ((file = open(fileNameYear, O_WRONLY | O_APPEND)) == -1) {
                perror("ERRO");
            }
            write(file, buffer, strlen(buffer));
            close(file);
            pthread_mutex_unlock(&secondMutex);

            return true;
        }
    }
    return false;
}


_Bool file_exists(const char *filename) {
    return access(filename, F_OK) == 0;
}

