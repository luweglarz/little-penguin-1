MODULE_NAME := keyboard_load

MODULE_DIR := /lib/modules/6.1.52-lweglarz/kernel

obj-m += $(MODULE_NAME).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	cp -r keyboard_load.ko /lib/modules/$(shell uname -r)/kernel 

install: all
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	install -D -m 644 10-keyboard.rules /etc/udev/rules.d/

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf $(INSTALL_DIR)/$(MODULE_NAME).ko

re: clean all