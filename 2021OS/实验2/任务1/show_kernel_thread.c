#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

static int show_kernel_thread_init(void) {
    struct task_struct *p = NULL;
    printk(KERN_ALERT"-----[show_kernel_thread module begin]-----\n");
    printk(KERN_ALERT"%20s %6s %6s %6s %6s\n",\
        "Name", "PID", "State", "Prio", "PPID");
    for_each_process(p) {
        // mm指向进程所拥有的内存描述符,内核线程不拥有任何内存描述符
        if (p->mm == NULL) {
            printk(KERN_ALERT"%20s %6d %6ld %6d %6d\n",\
                p->comm, p->pid, p->state, p->prio, p->parent->pid);
        }
    }
    return 0;
}

static void show_kernel_thread_exit(void) {
    printk(KERN_ALERT"-----[show_kernel_thread module end]-----\n");
    return;
}

module_init(show_kernel_thread_init);
module_exit(show_kernel_thread_exit);
MODULE_LICENSE("GPL");
