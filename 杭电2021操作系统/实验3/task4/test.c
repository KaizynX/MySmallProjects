#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <glob.h>

#define MEM_MIN_SIZE 1024
#define KEY 1111
#define N 2

sem_t *sem_sender;
sem_t *sem_receiver[N];

key_t key;
int shmid, id;
void *shmp;
char buf[100];

void init_signal() {
    int i;
    //初始化信号量
    sem_sender = sem_open("sender", O_CREAT, 0666, 1);
    for (i = 0; i < N; ++i) {
        sprintf(buf, "receiver%d", i);
        sem_receiver[i] = sem_open(buf, O_CREAT, 0666, 0);
    }

    shmid = shmget(KEY, MEM_MIN_SIZE, 0666|IPC_CREAT); //创建共享内存，key = 0(IPC_PRIVATE) 创建一个新对象。成功则返回id (一个与key相关的标识符)
    if(shmid < 0) {
        printf("创建共享内存出错！\n");
        exit(-1);
    }

    shmp = shmat(shmid, NULL, 0);//指定共享内存映射到新虚拟地址空间，返回起始地址
    if((long long int)shmp == -1) {
        printf("映射内存出错！\n");
        exit(-1);
    }
}

pthread_t r_thread, s_thread;

void *send(void *arg) {
    char temp[MEM_MIN_SIZE], s_str[100];
    while(1) {
	    printf("发送：");
	    fflush(stdout);
	    scanf("%[^\n]%*c",s_str);
        sem_wait(sem_sender);
        sprintf(temp,"%d:%s",*((pid_t *)arg),s_str);
        strcpy((char *)shmp, temp);
        
        sem_post(sem_receiver[id^1]);
	    printf("OK\n");
        if(!strcmp(s_str,"exit") || !strcmp(s_str,"quit")) {
            pthread_cancel(r_thread);
            shmdt(shmp);
	        break;
        }
    }
}

void *receive(void *arg) {
    char r_str[100], r_str_end[100], r_str_id[10], *p;
    while(1) {
        sem_wait(sem_receiver[id]);
        strcpy(r_str, (char *)shmp);
        p = strchr(r_str,':');
        *(p++) = '\0';
        printf("\r接收到进程%s的消息：%s\n", r_str,p);
        if(!strcmp(p,"exit") || !strcmp(p,"quit")) {
            pthread_cancel(s_thread);
            shmdt(shmp);
            shmctl(shmid, IPC_RMID, NULL);
            sem_unlink("sender");
            sem_unlink("receiver0");
            sem_unlink("receiver1");
            break;
        }
	    printf("发送：");
	    fflush(stdout);
        sem_post(sem_sender);
    }
}

int main(int argc, char *argv[]) {
    id = argv[1][0]-'0';
    pid_t pid = getpid();
    init_signal();
    printf("进程%d启动\n",pid);
    if (pthread_create(&s_thread,NULL,send,&pid) || pthread_create(&r_thread,NULL,receive,&pid)) {
        printf("create pthread failed\n");
        return 1;
    }
    pthread_join(s_thread, NULL);
    pthread_join(r_thread, NULL);
    printf("进程%d结束\n",pid);
}
