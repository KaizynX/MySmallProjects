#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

/*341 myshow name asmlinkage long sys_myshowname(void __user *sysname,void     __user *release,void __user *version);*/

int main() {
    char sysname[100], release[100], version[100];
    syscall(341, sysname, release, version);
    printf("Sysname:%s\nRelease:%s\nVersion:%s\n", sysname, release, version);
	return 0;
}
