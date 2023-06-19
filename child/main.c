#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<unistd.h>
#include "string.h"
#include "./src/objectiveB.h"
#include "./src/objectiveC.h"
#include "./src/myDataChild.h"
#include "./src/objectiveD.h"

int main(int argc, char *argv[], char *env[]) {

    char roomName[4][MAX_BUFFER] = {"Sala de admissao", "Triagem", "Sala de espera", "Medico"};
    int lines = (int) strtol(env[3], NULL, 10);
    DATA *myData = allocationData(lines);

    int jump = (int) strtol(env[2], NULL, 10);
    int i = (int) strtol(env[0], NULL, 10);

    if (strcmp("B", argv[0]) == 0) {
        printToFileB(myData, i, lines, jump, env, roomName);

        exit(0);
    } else if (strcmp("C", argv[0]) == 0) {
        printToFileC(myData, i, lines, jump, env, roomName);
        exit(0);
    } else if(strcmp("D",argv[0]) == 0){
        socketChild(myData,i,lines,jump,env,roomName);
        exit(0);
    }
    exit(0);
}




