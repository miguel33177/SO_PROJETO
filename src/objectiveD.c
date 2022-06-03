//
// Created by Bruno Miguel on 29/04/2022.
//

#include "objectiveD.h"

char *socket_path = "/tmp/socket";

void socketServer() {
    pid_t pid;
    int LISTENQ = numberCores();
    int i = 0;
    int lines = numberLines();

    char *env[] = {NULL, NULL, NULL, NULL, NULL};
    env[0] = malloc(sizeof(char *) * 256);
    env[1] = malloc(sizeof(char *) * 256);
    env[2] = malloc(sizeof(char *) * 256);
    env[3] = malloc(sizeof(char *) * 256);


    for (; i < LISTENQ - 1; i++) {
        sprintf(env[0], "%d", i);
        sprintf(env[2], "%d", LISTENQ - 1);
        sprintf(env[3], "%d", lines);

        if ((pid = fork()) == -1) {
            perror("Novo processo não criado!");
        }
        if (pid == 0) {
            execle("../../child/cmake-build-debug/child", "D", NULL, env);
            exit(0);

        }
    }

    int listenfd, connfd;
    struct sockaddr_un channel_srv;

    if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }

    unlink(socket_path);
    memset(&channel_srv, 0, sizeof(channel_srv));
    channel_srv.sun_family = AF_UNIX;
    strncpy(channel_srv.sun_path, socket_path, sizeof(channel_srv.sun_path) - 1);

    if (bind(listenfd, (struct sockaddr *) &channel_srv, sizeof(channel_srv)) == -1) {
        perror("bind error");
        exit(-1);
    }
    if (listen(listenfd, LISTENQ) == -1) {
        perror("listen error");
        exit(-1);
    }

    int file = open("../data/objectiveD", O_WRONLY | O_CREAT, 0755);
    char c;

    dup2(file, 1);
    int count = 0;

    while (count < (LISTENQ - 1)) {
        connfd = accept(listenfd, NULL, NULL);
        while (read(connfd, &c, 1) > 0) {
            printf("%c", c);
        }
        count++;
        close(connfd);
    }
    close(file);
}