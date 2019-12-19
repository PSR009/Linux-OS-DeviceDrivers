#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("DESD_74_78");

static char *charvar = "module";
static int intvar = 10;

module_param(charvar, charp, S_IRUGO);
module_param(intvar, int, S_IRUGO);

static int __init param_init(void)
{
	printk(KERN_ALERT "\nInit\n");
	printk(KERN_ALERT "\nintvar is %d\n", intvar);
	printk(KERN_ALERT "\nCharvar is %s\n", charvar);
	return 0;
}

static void __exit param_exit(void)
{
	printk(KERN_ALERT "\nBye, World\n");
}

module_init(param_init);
module_exit(param_exit);
