//
// Created by Bruno Miguel on 25/05/2022.
//
#include "objectiveA_parte2.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
static DATA *myData;
static int file;
static int counter = 0;
static int lines;

void *print() {
    while (counter <= numberLines() - NUMBER_THREADS) {
        int curr;
        pthread_mutex_lock(&mutex);
            curr = counter;
            counter++;
        pthread_mutex_unlock(&mutex);

        printToFile_Part2(curr);
    }
    return NULL;
}

void threads() {
    pthread_t thread_id[NUMBER_THREADS];
    lines = numberLines();
    myData = allocationData(lines);

    char fileName[MAX_BUFFER];
    sprintf(fileName, "../data/outThreads.txt");
    file= open(fileName, O_WRONLY | O_CREAT);

    char cmd[MAX_BUFFER];

    sprintf(cmd, "chmod 755 %s", fileName);
    system(cmd);

    for (int i = 0; i < NUMBER_THREADS; i++) {
        if(pthread_create(&thread_id[i], NULL, &print, NULL) != 0){
            perror("ERROR CREATING THREAD");
        }
    }
    for (int i = 0; i < NUMBER_THREADS; i++) {
        if(pthread_join(thread_id[i], NULL)!=0){
            perror("ERROR JOINING THREAD");
        }
    }
    close(file);
}

int binarySearch(DATA *data, int lo, int hi, long x) {
    int mid;
    x = x - (86400 * 7);
    while (hi >= lo) {
        mid = (hi + lo) / 2;

        if (data[mid].T1 == x) {
            return mid;
        }
        if (data[mid].T1 > x) {
            hi = mid - 1;
        }
        if (data[mid].T1 < x) {
            lo = mid + 1;
        }
    }
    return mid + 1;
}

void printToFile_Part2(int current) {
    char roomName[4][MAX_BUFFER] = {"Sala de admissao", "Triagem", "Sala de espera", "Medico"};
    int room[4] = {};

    for (int j = current; j > binarySearch(myData, 0, current, myData[current].T1); j--) {
        if ((myData[current].T1 < myData[j].T2 && myData[current].T2 > myData[j].T2) ||
            (myData[current].T1 < myData[j].T1 && myData[current].T2 > myData[j].T2) ||
            (myData[current].T1 < myData[j].T1 || myData[current].T2 > myData[j].T1)) {
            room[0]++;
        }
        if ((myData[current].T2 < myData[j].T3 && myData[current].T3 > myData[j].T3) ||
            (myData[current].T2 < myData[j].T2 && myData[current].T3 > myData[j].T3) ||
            (myData[current].T2 < myData[j].T2 || myData[current].T3 > myData[j].T2)) {
            room[1]++;
        }
        if ((myData[current].T3 < myData[j].T4 && myData[current].T4 > myData[j].T4) ||
            (myData[current].T3 < myData[j].T3 && myData[current].T4 > myData[j].T4) ||
            (myData[current].T3 < myData[j].T3 || myData[current].T4 > myData[j].T3)) {
            room[2]++;
        }
        if ((myData[current].T4 < myData[j].T5 && myData[current].T5 > myData[j].T5) ||
            (myData[current].T4 < myData[j].T4 && myData[current].T5 > myData[j].T5) ||
            (myData[current].T4 < myData[j].T4 || myData[current].T5 > myData[j].T4)) {
            room[3]++;
        }
    }
    for (int z = 0; z < 4; z++) {
        char buffer[MAX_BUFFER];
        if (z == 0) {
            sprintf(buffer, "%d$%d,%ld,%s#%d\n", getpid(), current, myData[current].T1, roomName[z],
                    room[z]);
        }
        if (z == 1) {
            sprintf(buffer, "%s%d$%d,%ld,%s#%d\n", buffer, getpid(), current, myData[current].T2, roomName[z],
                    room[z]);
        }
        if (z == 2) {
            sprintf(buffer, "%s%d$%d,%ld,%s#%d\n", buffer, getpid(), current, myData[current].T3, roomName[z],
                    room[z]);
        }
        if (z == 3) {
            sprintf(buffer, "%s%d$%d,%ld,%s#%d\n", buffer, getpid(), current, myData[current].T4, roomName[z],
                    room[z]);
            write(file, buffer, strlen(buffer));
        }
    }
}