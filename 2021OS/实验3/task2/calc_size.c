//统计无名管道的容量程序。
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int i = 0;

void *kwrite() {
    int pipefds[2];
    pipe(pipefds);
    for (i = 0; ; ++i) write(pipefds[1], "1", 1);
    close(pipefds[0]);
    close(pipefds[1]);
}

int main() {
    pthread_t thread;
    int lasti = 0, t = 0;
    pthread_create(&thread,NULL,kwrite,&i);
    while(1) {
        sleep(0.01);
        if(i != lasti) {
            lasti = i;
            t = 0;
        } else if(++t == 100) {
            printf("管道大小为: %dB\n", i * 1); 
            break;
        }
    }
    return 0;
}
