//
// Created by Bruno Miguel on 26/05/2022.
//

#include "objectiveB_parte2.h"

typedef struct list {
    long timestamp;
    char *room;
    int occupation;
} LIST;

typedef struct param {
    int i;
} PARAM;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static _Bool keepConsuming[NUMBER_THREADS] = {[0 ... NUMBER_THREADS - 1]=true};
static LIST **list;
static int columns = 12;
static DATA *myData;
static int file;
static int lines;
static int counter = 0;

void *producer(void *i) {
    PARAM *param = i;
    while (counter <= numberLines() - NUMBER_THREADS) {
        int curr;
        pthread_mutex_lock(&mutex);
        curr = counter;
        counter++;
        pthread_mutex_unlock(&mutex);
        producing(curr, param->i);
    }
    keepConsuming[param->i] = false;
    return NULL;
}

void *consumer(void *i) {
    PARAM *param = i;
    while (keepConsuming[param->i] == true || consuming(param->i) == true) {
        consuming(param->i);
    }
    return NULL;
}

void threadsB() {
    pthread_t thread_consumidor[NUMBER_THREADS];
    pthread_t thread_produtor[NUMBER_THREADS];
    lines = numberLines();
    myData = allocationData(lines);
    char buffer1[MAX_BUFFER];
    char buffer[MAX_BUFFER];
    char fileName[MAX_BUFFER];
    sprintf(fileName, "../data/outProducerConsumer.txt");
    file = open(fileName, O_WRONLY | O_CREAT);
    char cmd[MAX_BUFFER];

    sprintf(cmd, "chmod 755 %s", fileName);
    system(cmd);

    list = malloc(sizeof(LIST *) * NUMBER_THREADS);
    for (int i = 0; i < NUMBER_THREADS; i++) {
        list[i] = malloc(sizeof(LIST) * columns);
    }
    for (int i = 0; i < NUMBER_THREADS; i++) {
        PARAM *param = malloc(sizeof(PARAM));
        param->i = i;
        if (pthread_create(&thread_consumidor[i], NULL, &producer, param) != 0) {
            perror("ERROR CREATING THREAD");
        }
    }
    for (int i = 0; i < NUMBER_THREADS; i++) {
        PARAM *param = malloc(sizeof(PARAM));
        param->i = i;
        if (pthread_create(&thread_produtor[i], NULL, &consumer, param) != 0) {
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
    for (int i = 0; i < NUMBER_THREADS; i++) {
        sprintf(buffer, "sem%d", i);
        sem_unlink(buffer);
    }
}

void producing(int current, int pos) {
    char roomName[4][MAX_BUFFER] = {"Sala de admissao", "Triagem", "Sala de espera", "Medico"};
    int room[4] = {};
    LIST data;
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
            //data.timestamp = myData[current].T1;
            //data.occupation = room[z];
            //data.room=NULL;
            //data.room = (char *)malloc(strlen(roomName[z]));
            //data.room = roomName[z];
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {
                    //list[pos][i] = data;
                    list[pos][i].room = "Sala de Admissao";
                    //list[pos][i].room = roomName[z];;
                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
        if (z == 1) {
            //data.timestamp = myData[current].T1;
            //data.occupation = room[z];
            //data.room=NULL;
            //data.room = (char *)malloc(strlen(roomName[z]));
            //data.room = roomName[z];
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {
                    //list[pos][i] = data;
                    list[pos][i].room = "Triagem";
                    //list[pos][i].room = roomName[z];;
                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
        if (z == 2) {
            //data.timestamp = myData[current].T1;
            //data.occupation = room[z];
            //data.room=NULL;
            //data.room = (char *)malloc(strlen(roomName[z]));
            //data.room = roomName[z];
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {
                    //list[pos][i] = data;
                    list[pos][i].room = "Sala de Espera";
                    //list[pos][i].room = roomName[z];;
                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
        if (z == 3) {
            //data.timestamp = myData[current].T1;
            //data.occupation = room[z];
            //data.room=NULL;
            //data.room = (char *)malloc(strlen(roomName[z]));
            //data.room = roomName[z];
            for (int i = 0; i < columns; ++i) {
                if (list[pos][i].room == NULL) {
                    list[pos][i].room = "Medico";
                    //list[pos][i].room = roomName[z];;
                    list[pos][i].timestamp = myData[current].T1;
                    list[pos][i].occupation = room[z];
                    break;
                }
            }
        }
    }
}

_Bool consuming(int pos) {
    for (int i = columns - 1; i >= 0; i--) {
        if (list[pos][i].room != NULL) {
            char buffer[MAX_BUFFER];
            sprintf(buffer, "%ld,%d,%s\n", list[pos][i].timestamp, list[pos][i].occupation, list[pos][i].room);
            list[pos][i].room = NULL;
            write(file, buffer, strlen(buffer));
            return true;
        }
    }
    return false;
}





