#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

#define N 2

int fd[N], i;
char buf[100];
char *fifofile[N] = {"/tmp/fifomy1", "/tmp/fifomy2"};

sem_t *sem_send;
sem_t *sem_receive;
sem_t *sem_over[N];

struct my_msgbuf {
    int sendid;
    char mtext[100];
};

void init_signal() {
    sem_send = sem_open("send", O_CREAT, 0666, 1);
    sem_receive = sem_open("receive", O_CREAT, 0666, 0);
    for (i = 0; i < N; ++i) {
        sprintf(buf, "over%d", i);
        sem_over[i] = sem_open(buf, O_CREAT, 0666, 0);
    }
}
