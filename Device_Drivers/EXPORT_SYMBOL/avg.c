#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "add_func.h"

static int a = 2;
static int b = 3;

static int __init avg_init(void)
{
	printk("\nAvg: init: add = %d\n", my_add(a, b));
	return 0;
}

static void __exit avg_exit(void)
{
	printk("\nAvg: exit\n");
}

module_init(avg_init);
module_exit(avg_exit);