//
// Created by Bruno Miguel on 14/04/2022.
//

#include "objectiveB.h"

void printToFileB(DATA *myData, int i, int lines, int jump, char *env[], char roomName[4][MAX_BUFFER]) {

    char fileName[MAX_BUFFER];
    char cmd[MAX_BUFFER];
    
    sprintf(fileName, "../../child/data/out%s.txt",env[0]);

    int file = open(fileName, O_WRONLY | O_CREAT );
    sprintf(cmd, "chmod 755 %s", fileName);
    system(cmd);

    dup2(file, 1);

    for (; i < lines; i += jump) {
        int room[4] = {};
        for (int j = i; j > binarySearch(myData, 0, i, myData[i].T1); j--) {
            if ((myData[i].T1 < myData[j].T2 && myData[i].T2 > myData[j].T2) ||
                (myData[i].T1 < myData[j].T1 && myData[i].T2 > myData[j].T2) ||
                (myData[i].T1 < myData[j].T1 || myData[i].T2 > myData[j].T1)) {
                room[0]++;
            }
            if ((myData[i].T2 < myData[j].T3 && myData[i].T3 > myData[j].T3) ||
                (myData[i].T2 < myData[j].T2 && myData[i].T3 > myData[j].T3) ||
                (myData[i].T2 < myData[j].T2 || myData[i].T3 > myData[j].T2)) {
                room[1]++;
            }
            if ((myData[i].T3 < myData[j].T4 && myData[i].T4 > myData[j].T4) ||
                (myData[i].T3 < myData[j].T3 && myData[i].T4 > myData[j].T4) ||
                (myData[i].T3 < myData[j].T3 || myData[i].T4 > myData[j].T3)) {
                room[2]++;
            }
            if ((myData[i].T4 < myData[j].T5 && myData[i].T5 > myData[j].T5) ||
                (myData[i].T4 < myData[j].T4 && myData[i].T5 > myData[j].T5) ||
                (myData[i].T4 < myData[j].T4 || myData[i].T5 > myData[j].T4)) {
                room[3]++;
            }
        }
        for (int z = 0; z < 4; z++) {
            char buffer[MAX_BUFFER];
            if (z == 0) {
                sprintf(buffer, "%d$%d,%ld,%s#%d\n",getpid(), i, myData[i].T1, roomName[z],
                        room[z]);
                printf("%s", buffer);
            }
            if (z == 1) {
                sprintf(buffer, "%d$%d,%ld,%s#%d\n",getpid(), i, myData[i].T2, roomName[z],
                        room[z]);
                printf("%s", buffer);
            }
            if (z == 2) {
                sprintf(buffer, "%d$%d,%ld,%s#%d\n",getpid(), i, myData[i].T3, roomName[z],
                        room[z]);
                printf("%s", buffer);
            }
            if (z == 3) {
                sprintf(buffer, "%d$%d,%ld,%s#%d\n",getpid(), i, myData[i].T4, roomName[z],
                        room[z]);
                printf("%s", buffer);
            }
        }
    }
    close(file);
}

