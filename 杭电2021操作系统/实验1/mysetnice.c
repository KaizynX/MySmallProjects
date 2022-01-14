#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

/*340 mystenice asmlinkage long sys_mysetnice(pid_t pid,int flag,int nicevalue,void __user *prio,void __user *nice);*/

int main() {
    pid_t pid;
	char strin[100];
    int nicevalue = 3100, flag = 2;
    int p = 0, n = 0, *prio = &p, *nice = &n;
	while(1) {
        printf("输入0查看nice和prio\n输入1修改nice和prio\n输入其他值退出\n");
		scanf("%d", &flag);
		if(flag != 0 && flag != 1) return 0;
       	printf("请输入pid:\n");
       	scanf("%d", &pid);
		if(flag == 1) {
			printf("请输入nice:\n");
            scanf("%d", &nicevalue);
			if(nicevalue < -20 || nicevalue > 19) {
				printf("nice值非法\n");
				continue;
			}
		}
       	if (syscall(340,pid,flag,nicevalue,prio,nice) != 0) puts("ERROR");
       	printf("现在的nice为%d\n现在的prio为%d\n输入任意建继续\n",n,p);
		getchar();
		fgets(strin,100,stdin);
		system("clear");
	}
	return 0;
}
