obj-m := concur.o

	KERNELDIR = /lib/modules/$(shell uname -r)/build
#	KERNELDIR = /lib/modules/4.19.86-v7l+/build

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o prod prod.c
	gcc -o cons cons.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf prod
	rm -rf cons

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a