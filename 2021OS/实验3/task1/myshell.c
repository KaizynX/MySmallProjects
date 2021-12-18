#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    char command[55],token[55];
    int status;
    pid_t pid;
    while(1) {
        printf("shell:");
        scanf("%[^\n]%*c", command);
        status = -1;
        sscanf(command, "%s", token);
        if(!strcmp(token, "cmd1") || !strcmp(token, "cmd2") || !strcmp(token, "cmd3")) {
            pid = fork();
            if(pid < 0) {
                printf("fork error\n");
            } else if(pid > 0) {
                wait(&status);
            } else {
                sprintf(command,"./%s",token);
                system(command);
		        exit(0);
            }
        } else if(!strcmp(token, "exit") || !strcmp(token, "quit")) {
            printf("shell %s\n", token);
	        break ;
        } else if(!strcmp(token, "find") || !strcmp(token, "grep")) {
            system(command);
        } else {
            printf("Command not found\n");
        }
    }
    return 0;
}
