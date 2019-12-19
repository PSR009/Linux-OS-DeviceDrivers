#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define MY_MAJOR 123
#define MY_MINOR 1
#define DEV_COUNT 1
#define BUFF_SIZE 1024

dev_t dev_no;
struct cdev my_cdev;
char user_buff[BUFF_SIZE];

static int test_open(struct inode *, struct file *);
static ssize_t test_read(struct file *, char *, size_t, loff_t *);
static ssize_t test_write(struct file *, const char *, size_t, loff_t *);
static int test_release(struct inode *, struct file *);

struct file_operations my_fops = {
    .open = test_open,
    .read = test_read,
    .write = test_write,
    .release = test_release,
};

static int __init test_init(void)
{
    int err;
    dev_no = MKDEV(MY_MAJOR, MY_MINOR);
    err = register_chrdev_region(dev_no, DEV_COUNT, "teststat");
    if (err < 0)
    {
        printk("\nError: Couldn't register device\n");
        return err;
    }

    cdev_init(&my_cdev, &my_fops);

    err = cdev_add(&my_cdev, dev_no, DEV_COUNT);
    if (err < 0)
    {
        printk("\nError: Couldn't notify kernel to add device\n");
        unregister_chrdev_region(dev_no, DEV_COUNT);
        return err;
    }
    printk("\nChar_dev: init:\n");
    return 0;
}

static void __exit test_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_no, DEV_COUNT);
    printk("\nChar_dev: exit\n");
}

static int test_open(struct inode *inodep, struct file *filep)
{
    printk("\nIn test_open\n");
    return 0;
}

static ssize_t test_read(struct file *filep, char *buff, size_t len, loff_t *off)
{
    printk("\nIn test_read\n");
    copy_to_user(buff, user_buff, len);
    return len;
}

static ssize_t test_write(struct file *filep, const char *buff, size_t len, loff_t *off)
{
    printk("\nIn test_write\n");
    copy_from_user(user_buff, buff, len);
    user_buff[len] = 0;
    return len;
}

static int test_release(struct inode *inodep, struct file *filep)
{
    printk("\nIn test_close\n");
    return 0;
}

module_init(test_init);
module_exit(test_exit);
