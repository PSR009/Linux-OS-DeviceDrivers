obj-m := calc_driv.o

	KERNELDIR = /lib/modules/$(shell uname -r)/build
#	KERNELDIR = /lib/modules/4.19.86-v7l+/build

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o add_r add_r.c
	gcc -o add_w add_w.c
	gcc -o sub_r sub_r.c
	gcc -o sub_w sub_w.c
	gcc -o mul_r mul_r.c
	gcc -o mul_w mul_w.c
	gcc -o div_r div_r.c
	gcc -o div_w div_w.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm add_r add_w sub_r sub_w mul_r mul_w div_r div_w

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a