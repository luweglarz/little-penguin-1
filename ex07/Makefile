MODULE_NAME := debugfs_subdir

MODULE_SRC := debugfs_subdir.c

MODULE_LOCATION := $(INSTALL_DIR)/$(MODULE_NAME).ko

obj-m := $(MODULE_NAME).o 

debugfs_subdir-objs := foo_debugfs.o id_debugfs.o jiffies_debugfs.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install: all
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	-/sbin/insmod $(MODULE_LOCATION)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	-/sbin/rmmod $(MODULE_NAME)

re: clean all