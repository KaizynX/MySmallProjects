#include "init.h"

int main() {
    int msgid, over_cnt = 0;
    struct my_msgbuf r_msg, s_msg;//消息接受区
    msgid = msgget(IPC_PRIVATE, 0666|IPC_CREAT);
    init_signal();
    for (i = 0; i < N; ++i) {
        mkfifo(fifofile[i],0666);
        fd[i]=open(fifofile[i],O_WRONLY);
        write(fd[i],&msgid,sizeof(int));
        sem_post(sem_over[i]);
    }
    s_msg.sendid = 233;
    printf("tid:%u 进程(线程)%d：\n", (unsigned int)pthread_self(), s_msg.sendid);
    while (1) {
        sem_wait(sem_receive);
        msgrcv(msgid, &r_msg, sizeof(struct my_msgbuf), 0, 0);
        printf("收到线程%u的消息: %s\n", r_msg.sendid, r_msg.mtext);

        if (r_msg.mtext[0] == 'e' && r_msg.mtext[1] == 'n' && r_msg.mtext[2] == 'd') {
            printf("发送给线程%d：over%d\n", r_msg.sendid, r_msg.sendid);
            sprintf(s_msg.mtext, "over%d", r_msg.sendid);
            msgsnd(msgid, &s_msg, sizeof(struct my_msgbuf), 0);
            sem_post(sem_over[r_msg.sendid]);
            ++over_cnt;
        } else {
            sem_post(sem_send);
        }

        if (over_cnt == N) break;
    }

    sem_unlink("send");
    sem_unlink("receive");
    for (i = 0; i < N; ++i) {
        sprintf(buf, "over%d", i);
        sem_unlink(buf);
    }

    return 0;
}
