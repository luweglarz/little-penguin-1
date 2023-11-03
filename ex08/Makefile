MODULE_NAME := reverse

MODULE_LOCATION := $(INSTALL_DIR)/$(MODULE_NAME).ko

obj-m += $(MODULE_NAME).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

check-coding-style:
	/usr/src/linux-6.1.52/scripts/checkpatch.pl -f $(MODULE_NAME).c

install: all
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	-/sbin/insmod $(MODULE_LOCATION)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	-/sbin/rmmod $(MODULE_NAME)

re: clean all