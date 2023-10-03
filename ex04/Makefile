obj-m += keyboard_load.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	cp -r keyboard_load.ko /lib/modules/$(shell uname -r)/kernel 
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
