MODULE_NAME := fortytwo_misc
MODULE_SRC := fortytwo_misc.c

obj-m := $(MODULE_NAME).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	/sbin/insmod $(INSTALL_DIR)/$(MODULE_NAME).ko

test: all
	gcc fortytwo_test.c -o fortytest

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean