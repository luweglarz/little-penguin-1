obj-m += main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

check-coding-style:
	/usr/src/linux-6.1.52/scripts/checkpatch.pl -f main.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean