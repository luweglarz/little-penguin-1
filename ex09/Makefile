MODULE_NAME := mymounts

MODULE_SRC := $(MODULE_NAME).c

MODULE_LOCATION := $(INSTALL_DIR)/$(MODULE_NAME).ko

obj-m := $(MODULE_NAME).o

TEST_BINARY = mymounts_test

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install: all
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	-/sbin/insmod $(MODULE_LOCATION)

test: install
	gcc mountpts_test.c -o $(TEST_BINARY)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	-/sbin/rmmod $(MODULE_NAME)
	rm -f $(TEST_BINARY)

re: clean all