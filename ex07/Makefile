MODULE_NAME := debugfs_subdir

MODULE_LOCATION := $(INSTALL_DIR)/$(MODULE_NAME).ko

TEST_BINARY = debugfs_test

obj-m := $(MODULE_NAME).o 

debugfs_subdir-y := debugfs_subdir_main.o foo_debugfs.o id_debugfs.o jiffies_debugfs.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install: all
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	-/sbin/insmod $(MODULE_LOCATION)

test: $(MODULE_LOCATION)
	gcc debugfs_test.c -o $(TEST_BINARY)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	-/sbin/rmmod $(MODULE_NAME)
	rm -f $(TEST_BINARY)

re: clean all