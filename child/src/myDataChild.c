//
// Created by Bruno Miguel on 12/04/2022.
//

#include "myDataChild.h"

int binarySearch(DATA *myData, int lo, int hi, long x) {
    int mid;
    x = x - (86400*7);
    while (hi >= lo) {
        // mid = lo + (hi - lo) / 2;
        mid = (hi + lo) / 2;

        if (myData[mid].T1 == x) {
            return mid;
        }
        if (myData[mid].T1 > x) {
            hi = mid - 1;
        }
        if (myData[mid].T1 < x) {
            lo = mid + 1;
        }
    }
    return mid+1;
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
        if (lines != -1) {                   //cortar linha 1
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
