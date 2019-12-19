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

#define DEV_COUNT 4
#define BUFF_SIZE 8

dev_t dev_no;

struct my_dev
{
    struct cdev my_cdev;
    struct circ_buf cbuf;
    wait_queue_head_t twq;
} devs[DEV_COUNT];

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
    err = alloc_chrdev_region(&dev_no, 0, DEV_COUNT, "mul_dev");
    if (err < 0)
    {
        printk("\nError: Couldn't register device\n");
        return err;
    }
    printk("\nMajor = %d Minor = %d\n", MAJOR(dev_no), MINOR(dev_no));

    for (int i = 0; i < DEV_COUNT; i++)
    {
        cdev_init(devs[i].(&my_cdev), devs[i].(&my_fops));
    }

    for (int j = 0; j < DEV_COUNT; j++)
    {

        devs[j].cbuf.buf = kmalloc(BUFF_SIZE, GFP_KERNEL);
        if (!(devs[j].cbuf.buf))
        {
            printk("Error: Couldn't allocate\n");
            unregister_chrdev_region(dev_no, DEV_COUNT);
            return -ENOMEM;
        }
    }

    for (int k = 0; k < DEV_COUNT; k++)
    {
        devs[k].init_waitqueue_head(&twq);
    }

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

static int test_open(struct inode *inodep, struct file *filep)
{
    printk("\nIn test_open\n");
    return 0;
}

static ssize_t test_read(struct file *filep, char *ubuff, size_t count, loff_t *off)
{
    int i, m, ret;
    printk("\nIn test_read\n");

    if ((filep->f_flags & O_NONBLOCK) && (CIRC_CNT(cbuf.head, cbuf.tail, BUFF_SIZE) == 0))
    {
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

static ssize_t test_write(struct file *filep, const char *ubuff, size_t count, loff_t *off)
{
    int i, m, ret;
    printk("\nIn test_write\n");

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

static int test_release(struct inode *inodep, struct file *filep)
{
    printk("\nIn test_close\n");
    return 0;
}

module_init(test_init);
module_exit(test_exit);
