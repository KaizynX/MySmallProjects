CONFIG_MODULE_SIG=n
obj-m := my_show_kernel_thread.o
my_show_kernel_thread-objs := show_kernel_thread.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
