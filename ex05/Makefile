MODULE_NAME := fortytwo_misc

MODULE_SRC := fortytwo_misc.c

MODULE_LOCATION := $(INSTALL_DIR)/$(MODULE_NAME).ko

obj-m := $(MODULE_NAME).o

TEST_BINARY = fortytest

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install: all
	install -D -m 644 $(MODULE_NAME).ko $(INSTALL_DIR)/$(MODULE_NAME).ko
	-/sbin/insmod $(MODULE_LOCATION)

test: $(MODULE_LOCATION)
	gcc fortytwo_test_cases.c -o $(TEST_BINARY)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	-/sbin/rmmod fortytwo_misc
	rm -f $(TEST_BINARY)

re: clean all