//
// Created by Bruno Miguel on 14/04/2022.
//
#include "objectives.h"

int num_signal = 0;

void sig_handler(int signum) {
}

void objectiveB() {
    pid_t pid;
    int i = 0;
    int cores, lines;

    cores = numberCores();
    lines = numberLines();

    printf("Number of Cores %d\n", cores);
    printf("Number of Lines %d   (lines of test)\n", lines);
    DATA *myData = allocationData(lines);

    int pidArray[cores - 1];
    char *env[] = {NULL, NULL, NULL, NULL, NULL};
    env[0] = (char *) malloc(sizeof(char) * 256);
    env[1] = (char *) malloc(sizeof(char) * 256);
    env[2] = (char *) malloc(sizeof(char) * 256);
    env[3] = (char *) malloc(sizeof(char) * 256);

    for (; i < cores - 1; i++) {
        sprintf(env[0], "%d", i);
        sprintf(env[1], "%p", myData);
        sprintf(env[2], "%d", cores - 1);
        sprintf(env[3], "%d", lines);

        if ((pid = fork()) == -1) {
            perror("Novo processo não criado!");
        }
        if (pid == 0) {
            execle("../../child/cmake-build-debug/child", "B", NULL, env);
            exit(0);

        } else {
            printf("pai %d\n", getpid());
            pidArray[i] = pid;
        }
    }

    for (int k = 0; k < cores - 1; k++) {
        waitpid(pidArray[k], NULL, 0);
    }
}


void objectiveC() {
    pid_t pid;
    int i = 0;
    int cores, lines;
    cores = numberCores();
    lines = numberLines();
    int fds[2];
    pipe(fds);
    DATA *myData = allocationData(lines);

    int pidArray[cores - 1];
    char *env[] = {NULL, NULL, NULL, NULL, NULL};
    env[0] = malloc(sizeof(char *) * 256);
    env[1] = malloc(sizeof(char *) * 256);
    env[2] = malloc(sizeof(char *) * 256);
    env[3] = malloc(sizeof(char *) * 256);

    for (; i < cores - 1; i++) {
        sprintf(env[0], "%d", i);
        sprintf(env[1], "%p", myData);
        sprintf(env[2], "%d", cores - 1);
        sprintf(env[3], "%d", lines);

        if ((pid = fork()) == -1) {
            perror("Novo processo não criado!");
        }
        if (pid == 0) {
            dup2(fds[1], 1);
            execle("../../child/cmake-build-debug/child", "C", NULL, env);
            exit(0);

        } else {
            printf("pai %d\n", getpid());
            pidArray[i] = pid;
        }
    }
    close(fds[1]);


    int file = open("../data/objectiveC_A", O_WRONLY | O_CREAT, 0755);
    char c;
    int stdout = dup(1);
    dup2(file, 1);

    while (read(fds[0], &c, 1) > 0) {
        printf("%c", c);
    }


    for (int k = 0; k < cores - 1; k++) {
        waitpid(pidArray[k], NULL, 0);
    }
    close(fds[0]);
    close(file);
    dup2(stdout, 1);
    close(stdout);
    DATA2 *stampData = allocData();
    int *numberYears = calloc(1, sizeof(int));
    int *index = parse_Years(stampData, numberYears);
    objectiveC2(stampData, index, numberYears);
}

void objectiveC2(DATA2 *myData, int *index, int *numberYears) {
    pid_t pid;
    int m = *(numberYears) + 1;
    int count = 0;
    int pidArray[m];
    int fds[m][2];
    int i = 0;

    for (; i < m; i++) {
        pipe(fds[i]);
        if ((pid = fork()) == -1) {
            perror("Novo processo não criado!");
        }
        if (pid == 0) {
            dup2(fds[i][0], 0);
            close(fds[i][1]);
            char name[2] = "";
            signal(SIGUSR1, sig_handler);
            sprintf(name, "%d", i);
            if (execlp("python3", "python3", "../py/plot.py", name, NULL) == -1) {
                perror("EXEC");
            }

        } else {
            close(fds[i][0]);
            pidArray[i] = pid;
        }
    }

    for (int j = 0; j < m; j++) {
        char *buffer = calloc(MAX_BUFFER, sizeof(char));

        char msg[] = "time,count\n";
        write(fds[i][1], msg, strlen(msg));
        if (i != m - 1) {
            while (count < index[count]) {
                sprintf(buffer, "%ld,%ld\n", myData[count].T, myData[count].C);
                write(1, buffer, strlen(buffer));
                count++;
            }
        } else {
            while (count < (numberLines() * 4)) {
                sprintf(buffer, "%ld,%ld\n", myData[count].T, myData[count].C);
                write(1, buffer, strlen(buffer));
                count++;
            }
        }
        close(fds[i][1]);
    }
    for (int k = 0; k < m; k++) {
        waitpid(pidArray[k], NULL, 0);
    }
}

int *parse_Years(DATA2 *myData, int *numberYears) {
    struct tm info;
    int lines = numberLines() * 4;
    char buffer[MAX_BUFFER];
    char previous[MAX_BUFFER] = {0};
    int *index = malloc(sizeof(int) * 1000);
    int m = 0;
    for (int i = 0; i < lines; i++) {
        time_t rawtime = myData[i].T;
        info = *localtime(&rawtime);
        strftime(buffer, 80, "%Y\n", &info);
        if (strcmp(previous, buffer) != 0 && i != 0) {
            index[m] = i;
            m++;
            *(numberYears) = *(numberYears) + 1;
        }
        strcpy(previous, buffer);
    }
    return index;
}




