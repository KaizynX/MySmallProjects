CONFIG_MODULE_SIG=n
obj-m := my_show_thread_pstree.o
my_show_thread_pstree-objs := show_thread_pstree.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
