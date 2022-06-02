//
// Created by Bruno Miguel on 01/04/2022.
//
#include "myData.h"

void printData(DATA *myData, int count) {
    if (count != -1) {
        printf("\nID: %d\n\nT1: %ld\nT2: %ld\nT3: %ld\nT4: %ld\nT5: %ld\n", myData[count].ID, myData[count].T1,
               myData[count].T2, myData[count].T3, myData[count].T4, myData[count].T5);
    }
}

void printData2() {
    int size = sizeof(DATA);
    printf("%d", size);
}

int numberCores() {
    int j = 0;
    int i = 0;
    char buffer[MAX_BUFFER] = {0};
    char buffer1[MAX_BUFFER];
    char c;

    if (strcmp(operatingSystem(buffer1), "Darwin") == 0) {
        system("sysctl hw.physicalcpu > ../data/numberCores");
    } //else {
        //system("nproc > ../data/numberCores");
    //}
    j = open("../data/numberCores", O_RDONLY);

    if (j == -1) {
        perror("Error Calculating Number of Cores!");

    } else {
        while (read(j, &c, 1) > 0) {
            if (isDigit(c)) {
                buffer[i] = c;
                i++;
            }
        }
        close(j);

    }

    return (int) strtol(buffer, NULL, 10);
}

int isDigit(char c) {
    return c >= 48 && c <= 57;
}

int numberLines() {
    int x = 0, i = 0;
    char c;
    char buffer[MAX_BUFFER] = {0};

    system("wc -l ../data/all_timestamps2.csv > ../data/numberLines");
    x = open("../data/numberLines", O_RDONLY);

    if (x == -1) {
        perror("Error calculating number of lines!");

    } else {
        while (read(x, &c, 1) > 0) {
            buffer[i] = c;
            i++;
        }
        close(x);
    }
    return (int) strtol(buffer, NULL, 10) ;
}

int isSpace(char c) {
    return c == ' ';
}

int isNewLine(char c) {
    return c == '\n';
}

char *operatingSystem(char buffer1[]) {
    int s, j = 0;
    int i = 0;
    char c;

    system("uname > ../data/OperatingSystem");

    s = open("../data/OperatingSystem", O_RDONLY);
    if (s == -1) {
        perror("Error check Operating System!");

    } else {
        while (read(s, &c, 1) > 0) {
            if (!isNewLine(c)) {
                buffer1[i] = c;
                i++;
            }
        }
        close(j);
    }
    return buffer1;
}

DATA* allocationData(int lines){
    DATA * myData = malloc(sizeof(DATA) * lines);
    int x;
    char c;
    lines = -1;
    int aux = 0;
    int i = 0;
    x = open("../data/all_timestamps2.csv", O_RDONLY);
    char buffer[MAX_BUFFER];
    while (read(x, &c, 1) > 0) {
        if (lines != -1) {

            //cortar linha 1
            myData[lines].ID = lines;
            if (c != ';') {
                buffer[i] = c;
                i++;
            }
            if (c == ';' || c == '\n') {
                i = 0;
                aux++;
                if (aux == 1) {
                    myData[lines].T1 = strtol(buffer, NULL, 10);
                }
                if (aux == 2) {
                    myData[lines].T2 = strtol(buffer, NULL, 10);
                }
                if (aux == 3) {
                    myData[lines].T3 = strtol(buffer, NULL, 10);
                }
                if (aux == 4) {
                    myData[lines].T4 = strtol(buffer, NULL, 10);
                }
                if (aux == 5) {
                    myData[lines].T5 = strtol(buffer, NULL, 10);
                    aux = 0;
                }
            }

        }
        if (c == '\n') {                                               //count linhas
            //printData(myData, lines);
            lines++;
        }
    }
    close(x);
    return myData;
}