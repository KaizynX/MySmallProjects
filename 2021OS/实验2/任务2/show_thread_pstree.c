#include <linux/init.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/sched/signal.h>

static pid_t pid = 233;
module_param(pid, int, 0644);
char tree_symbol[4][10] = {"├─", "└─", "─┬─", "───"};

int print_task(struct task_struct *p) { // 格式化输出进程信息
    // return printk(KERN_CONT"%-10s(pid:%-5d,state:%-5ld)", p->comm, p->pid, p->state);
    return printk(KERN_CONT"%s(pid:%d,state:%ld)", p->comm, p->pid, p->state);
}

int count_children(struct task_struct *p) { // 子进程数量
    int cnt = 0;
    struct list_head *list_ptr;
    list_for_each(list_ptr, &p->children) ++cnt;
    return cnt;
}

void show_thread(struct task_struct *p, int parent_len, int lastflag) { // 打印进程及其子进程
    struct list_head *list_ptr;
    struct task_struct *pchild;
    int num_children = count_children(p), cur = 0;
    int p_len = print_task(p)+2;
    if (num_children == 0) {
        printk(KERN_CONT"\n");
        return;
    }
    list_for_each(list_ptr, &p->children) {
        pchild = list_entry(list_ptr, struct task_struct, sibling);
        if (++cur > 1) printk(KERN_CONT"%*s%s%*s", parent_len, "", lastflag ? " " : "│", p_len, "");
        printk(KERN_CONT"%s", tree_symbol[cur == 1 ? 2+(num_children == 1) : cur == num_children]);
        print_task(pchild);
        printk(KERN_CONT"\n");
    }
}

static int show_thread_init(void) {
    struct task_struct *p = pid_task(find_vpid(pid), PIDTYPE_PID), *psibling;
    struct list_head *list_ptr;

    printk("-----[show_thread_pstree init]----\n");
    if (p == NULL) { // 找不到进程
        printk("ERROR: There is no such PID!\n");
        return 0;
    }

    if (p->parent) {
        int parent_len = print_task(p->parent)+1, cur = 0, pflag = 1;
        int num_sibling = count_children(p->parent), lastflag = num_sibling <= 1;
        printk(KERN_CONT"%s", tree_symbol[2+lastflag]);
        show_thread(p, parent_len, lastflag);
        list_for_each(list_ptr, &p->parent->children) {
            ++cur;
            psibling = list_entry(list_ptr, struct task_struct, sibling);
            if (psibling == p) {
                --pflag;
                continue;
            }
            lastflag = cur+pflag == num_sibling;
            printk(KERN_CONT"%*s%s", parent_len, "", tree_symbol[lastflag]);
            show_thread(psibling, parent_len, lastflag);
        }
    } else { // 没有父进程
        printk(KERN_CONT"──"); // 对齐
        show_thread(p, 0, 1);
    }
    return 0;
}

static void show_thread_exit(void) {
    printk("-----[show_thread_pstree exit]-----\n");
    return;
}

module_init(show_thread_init);
module_exit(show_thread_exit);
MODULE_LICENSE("GPL");
