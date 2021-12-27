#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>

#define N 5
char buf[150];

void clear() {
    int i;
    sem_unlink("Mutex");
    for (i = 0; i < N; ++i) {
        sprintf(buf, "receive%d", i);
        sem_unlink(buf);
    }
}

int main() {
    int fd[2],pipe_num, i;
    sem_t *Mutex;
    sem_t *receive[N];
    pid_t pid[N];

    clear();
    Mutex = sem_open("Mutex",O_CREAT,0666,1);
    for (i = 0; i < N; ++i) {
        sprintf(buf, "receive%d", i);
        receive[i] = sem_open(buf, O_CREAT,0666,0);
    }

    pipe_num = pipe(fd);
    if(pipe_num == -1) {
        printf("pipe create error\n");
        return 1;
    }

    for (i = 0; i < N; ++i) {
        pid[i] = fork();
        if (pid[i] > 0) continue;
        else break;
    }

    for (i = 0; i < N; ++i) if (pid[i] < 0) {
        clear();
        printf("fork error\n");
        return 2;
    }
    memset(buf, 0, sizeof buf);
    int flag = 0;
    for (i = 0; i < N; ++i) if (pid[i] == 0) {
        close(fd[0]);
        sem_wait(Mutex);
        printf("pid:%d 进程%d放入数据：",getpid(), i+1);
        scanf("%[^\n]%*c",buf);
        write(fd[1],buf,strlen(buf));
        sleep(0.1);
        sem_post(Mutex);
        sem_post(receive[i]);
        flag = 1;
        break;
    }
    if (!flag) {
        close(fd[1]);
        for (i = 0; i < N; ++i) sem_wait(receive[i]);
        sem_wait(Mutex);
        read(fd[0],buf,sizeof buf);
        printf("pid:%d 父进程接收数据:%s\n",getpid(),buf);
        sleep(0.1);
        sem_post(Mutex);
        clear();
    }
}
