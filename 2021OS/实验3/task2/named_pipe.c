//实现有名管道通信程序。
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>

#define fifofile "./iofile"
#define N 3
char buf[150];

void clear() {
    int i;
    sem_unlink("Mutex");
    for (i = 0; i < N; ++i) {
        sprintf(buf, "send%d", i);
        sem_unlink(buf);
        sprintf(buf, "receive%d", i);
        sem_unlink(buf);
    }
}

int main() {
    int fd,i;
    sem_t *Mutex;
    sem_t *send[N];
    sem_t *receive[N];
    pid_t pid[N];

    clear();
    Mutex = sem_open("Mutex",O_CREAT,0666,1);
    for (i = 0; i < N; ++i) {
        sprintf(buf, "send%d", i);
        send[i] = sem_open(buf,O_CREAT,0666,1);
        sprintf(buf, "receive%d", i);
        receive[i] = sem_open(buf, O_CREAT,0666,0);
    }

    mkfifo(fifofile,0666);

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
        fd=open(fifofile,O_WRONLY);
        sem_wait(send[i]);
        sem_wait(Mutex);
        printf("pid:%d 进程%d放入数据：",getpid(), i+1);
        scanf("%[^\n]%*c",buf);
        write(fd,buf,strlen(buf));
        close(fd);
        sleep(0.1);
        sem_post(Mutex);
        sem_post(receive[i]);
        flag = 1;
        break;
    }
    if (!flag) {
	    fd=open(fifofile,O_RDONLY);
        for (i = 0; i < N; ++i) sem_wait(receive[i]);
        sem_wait(Mutex);
        read(fd,buf,150);
        printf("pid:%d 父进程接收数据:%s\n",getpid(),buf);
        close(fd);
        unlink(fifofile);
        sleep(0.1);
        sem_post(Mutex);
        for (i = 0; i < N; ++i) sem_post(send[i]);
        clear();
    }
}
