#include "init.h"

int main(int argc, char *argv[]) {
    char str[100];
    int msgid, id = argv[1][0]-'0';
    struct my_msgbuf r_msg, s_msg;//消息接受区

    init_signal();
    fd[id]=open(fifofile[id],O_RDONLY);
    sem_wait(sem_over[id]);
    read(fd[id],&msgid,sizeof(int));
    s_msg.sendid = id;
    printf("tid:%u 进程(线程)%d: \n", (unsigned int)pthread_self(), id);
    while(1) {
        printf("发送：");
        scanf("%[^\n]%*c",str);
        sem_wait(sem_send);
        if(strcmp(str, "exit") == 0 || strcmp(str, "quit") == 0) {
            sprintf(s_msg.mtext, "end%d", id);
            msgsnd(msgid, &s_msg, sizeof(struct my_msgbuf), 0);
            sem_post(sem_receive);
            break;
        }
        strcpy(s_msg.mtext, str);
        msgsnd(msgid, &s_msg, sizeof(struct my_msgbuf), 0);
        sem_post(sem_receive);
    }
    sem_wait(sem_over[id]);
    msgrcv(msgid, &r_msg, sizeof(struct my_msgbuf), 0, 0);
    printf("收到线程%d的消息: %s\n", r_msg.sendid, r_msg.mtext);
    sem_post(sem_send);
    return 0;
}
