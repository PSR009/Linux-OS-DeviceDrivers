#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/circ_buf.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include "my_ioctl.h"

#define MY_MAJOR 234
#define MY_MINOR 1
#define DEV_COUNT 1
#define BUFF_SIZE 8

dev_t dev_no;
struct cdev my_cdev;
struct circ_buf cbuf;
wait_queue_head_t twq;

static int ioctl_open(struct inode *, struct file *);
static ssize_t ioctl_read(struct file *, char *, size_t, loff_t *);
static ssize_t ioctl_write(struct file *, const char *, size_t, loff_t *);
static int ioctl_release(struct inode *, struct file *);
long _ioctl(struct file *, unsigned int, unsigned long);

struct file_operations my_fops = {
    .open = ioctl_open,
    .read = ioctl_read,
    .write = ioctl_write,
    .release = ioctl_release,
    .unlocked_ioctl = _ioctl,
};

static int __init test_init(void)
{
    int err;
    dev_no = MKDEV(MY_MAJOR, MY_MINOR);
    err = register_chrdev_region(dev_no, DEV_COUNT, "my_ioctl");
    if (err < 0)
    {
        printk("\nError: Couldn't register device\n");
        return err;
    }

    cdev_init(&my_cdev, &my_fops);

    cbuf.buf = kmalloc(BUFF_SIZE, GFP_KERNEL);
    if (!cbuf.buf)
    {
        printk("Error: Couldn't allocate\n");
        unregister_chrdev_region(dev_no, DEV_COUNT);
        return -ENOMEM;
    }

    init_waitqueue_head(&twq);

    err = cdev_add(&my_cdev, dev_no, DEV_COUNT);
    if (err < 0)
    {
        printk("\nError: Couldn't notify kernel to add device\n");
        kfree(cbuf.buf);
        unregister_chrdev_region(dev_no, DEV_COUNT);
        return err;
    }
    printk("\nChar_dev: init:\n");
    return 0;
}

static void __exit test_exit(void)
{
    cdev_del(&my_cdev);
    kfree(cbuf.buf);
    unregister_chrdev_region(dev_no, DEV_COUNT);
    printk("\nChar_dev: exit\n");
}
int k, l;
long _ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
    case CMD_1:
        printk("Command 1\n");
        break;
    case CMD_GET:
        get_user(k, (int *)arg);
        printk("%d\n", k);
        break;
    case CMD_POST:
        l = k + 20;
        printk("%d\n", l);
        if(!capable(CAP_SYS_ADMIN))
        {
            return -EPERM;
        }
        put_user(l, (int *)arg);
        printk("sent to user\n");
        break;
    default:
        printk("Invalid command\n");
        return -ENOTTY;
    }
    return 0;
}

static int ioctl_open(struct inode *inodep, struct file *filep)
{
    printk("\nIn ioctl_open\n");
    return 0;
}

static ssize_t ioctl_read(struct file *filep, char *ubuff, size_t count, loff_t *off)
{
    int i, m, ret;
    printk("\nIn ioctl_read\n");

    if (filep->f_flags & O_NONBLOCK)
    {
        if (CIRC_CNT(cbuf.head, cbuf.tail, BUFF_SIZE) == 0)
            return 0;
    }

    wait_event_interruptible(twq, CIRC_CNT(cbuf.head, cbuf.tail, BUFF_SIZE) >= 1);

    m = min(CIRC_CNT(cbuf.head, cbuf.tail, BUFF_SIZE), (int)count);

    for (i = 0; i < m; i++)
    {
        ret = copy_to_user(ubuff + i, cbuf.buf + cbuf.tail, 1);
        if (ret)
        {
            printk("Error: Couldn't read\n");
            return -ENOMEM;
        }
        printk("read: %c\n", ubuff[i]);
        cbuf.tail = (cbuf.tail + 1) & (BUFF_SIZE - 1);
    }
    return i;
}

static ssize_t ioctl_write(struct file *filep, const char *ubuff, size_t count, loff_t *off)
{
    int i, m, ret;
    printk("\nIn ioctl_write\n");

    m = min(CIRC_SPACE(cbuf.head, cbuf.tail, BUFF_SIZE), (int)count);

    for (i = 0; i < m; i++)
    {
        ret = copy_from_user(cbuf.buf + cbuf.head, ubuff + i, 1);
        if (ret)
        {
            printk("Error: Couldn't write\n");
            return -ENOMEM;
        }
        printk("wrote: %c\n", cbuf.buf[cbuf.head]);
        cbuf.head = (cbuf.head + 1) & (BUFF_SIZE - 1);
    }
    wake_up(&twq);
    return i;
}

static int ioctl_release(struct inode *inodep, struct file *filep)
{
    printk("\nIn test_close\n");
    return 0;
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");