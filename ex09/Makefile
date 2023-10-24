MODULE_NAME := mymounts

MODULE_SRC := $(MODULE_NAME).c

MODULE_LOCATION := $(INSTALL_DIR)/$(MODULE_NAME).ko

obj-m := $(MODULE_NAME).o

CARGS = -I /usr/src/linux-6.1.52/

all: 
	make $(CARGS) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install: all
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	-/sbin/insmod $(MODULE_LOCATION)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	-/sbin/rmmod $(MODULE_NAME)

re: clean all