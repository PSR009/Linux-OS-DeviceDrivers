obj-m := mul_dev.o

	KERNELDIR = /lib/modules/$(shell uname -r)/build
#	KERNELDIR = /lib/modules/4.19.86-v7l+/build

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o add add.c
	gcc -o sub sub.c
	gcc -o mul mul.c
	gcc -o div div.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm add sub mul div

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a