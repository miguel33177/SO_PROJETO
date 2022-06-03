//
// Created by Bruno Miguel on 28/04/2022.
//

#include "myDataTimeCount.h"
#include "myData.h"

void printStampData(DATA2 *myData, int count) {
    for (int i = 0; i < count; i++) {
        printf("\nTimestamp: %ld ; Count: %ld", myData[i].T, myData[i].C);
    }
}

int *compara(const void *x, const void *y) {
    return (int *) (*(long *) x - *(long *) y);
}

DATA2 *allocData() {
    int lines = numberLines();
    DATA2 *data = malloc(sizeof(DATA2) * ((lines * 4)));
    int x;
    char c;
    int i = 0;
    char *token;
    lines = 0;
    x = open("../data/objectiveC_A", O_RDONLY, 0755);
    char *buffer = calloc(MAX_BUFFER2, sizeof(char));

    while (read(x, &c, 1) > 0) {
        if (c != '\n') {
            buffer[i] = c;
            i++;
        } else {
            i = 0;
            token = strtok(buffer, ",");
            token = strtok(NULL, ",");
            data[lines].T = strtol(token, NULL, 10);
            token = strtok(NULL, "#");
            token = strtok(NULL, "\0");
            data[lines].C = strtol(token, NULL, 10);
            free(buffer);
            buffer = calloc(MAX_BUFFER2, sizeof(char));
            lines++;
        }
    }

    qsort(data, lines, sizeof(struct dataTime_Count), compara);

    return data;
}




