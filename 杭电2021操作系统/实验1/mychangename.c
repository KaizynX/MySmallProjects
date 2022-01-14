#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

/*342 mychangename asmlinkage long sys_mychangename(char __user *name,int len);*/

int main() {
    printf("请输入修改的nodename:");
    char nodename[233];
    scanf("%s", nodename);
    long flag = syscall(342, nodename, strlen(nodename));
    if (flag != 0) printf("ERROR:%ld\n", flag);
    printf("Nodename:%s\n", nodename);
	return 0;
}
