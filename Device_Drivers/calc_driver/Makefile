obj-m := calc_driver.o

	KERNELDIR = /lib/modules/$(shell uname -r)/build
#	KERNELDIR = /lib/modules/4.19.86-v7l+/build

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o main appln.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf main

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a