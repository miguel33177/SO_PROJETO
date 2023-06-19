//
// Created by Bruno Miguel on 29/04/2022.
//

#include "objectiveD.h"

char *socket_path = "/tmp/socket";

void socketChild(DATA *myData, int i, int lines, int jump, char *env[], char roomName[4][MAX_BUFFER]) {
    int uds;
    struct sockaddr_un channel;

    if ((uds = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(1);
    }

    memset(&channel, 0, sizeof(channel));
    channel.sun_family = AF_UNIX;
    strncpy(channel.sun_path, socket_path, sizeof(channel.sun_path) - 1);

    if (connect(uds, (struct sockaddr *) &channel, sizeof(channel)) == -1) {
        perror("connect error");
        exit(1);
    }

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
                sprintf(buffer, "%d$%d,%ld,%s#%d\n", getpid(), i, myData[i].T1, roomName[z],
                        room[z]);
            }
            if (z == 1) {
                sprintf(buffer, "%s%d$%d,%ld,%s#%d\n", buffer, getpid(), i, myData[i].T2, roomName[z],
                        room[z]);
            }
            if (z == 2) {
                sprintf(buffer, "%s%d$%d,%ld,%s#%d\n", buffer, getpid(), i, myData[i].T3, roomName[z],
                        room[z]);
            }
            if (z == 3) {
                sprintf(buffer, "%s%d$%d,%ld,%s#%d\n", buffer, getpid(), i, myData[i].T4, roomName[z],
                        room[z]);
                write(uds, buffer, strlen(buffer));
            }
        }
    }
    close(uds);
    
}