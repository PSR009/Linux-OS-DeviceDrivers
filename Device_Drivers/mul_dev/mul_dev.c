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
#define BUFF_SIZE 16

dev_t dev_no;
int i;
struct my_dev
{
    struct cdev my_cdev;
    struct circ_buf cbuf;
    wait_queue_head_t my_q;
} devs[DEV_COUNT];

static int test_open(struct inode *, struct file *);
static ssize_t test_read(struct file *, char *, size_t, loff_t *);
static ssize_t test_write(struct file *, const char *, size_t, loff_t *);
static int test_release(struct inode *, struct file *);
long test_ioctl(struct file *, unsigned int, unsigned long);

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

    for (i = 0; i < DEV_COUNT; i++)
    {
        cdev_init(&devs[i].my_cdev, &my_fops);
        devs[i].cbuf.buf = kmalloc(BUFF_SIZE, GFP_KERNEL);
        if (!(devs[i].cbuf.buf))
        {
            printk("Error: Couldn't allocate\n");
            goto error;
        }
    }

    for (i = 0; i < DEV_COUNT; i++)
    {
        init_waitqueue_head(&devs[i].my_q);
        err = cdev_add(&devs[i].my_cdev, dev_no, DEV_COUNT);
        if (err < 0)
        {
            printk("\nError: Couldn't notify kernel to add device\n");
            goto error;
        }
    }
    printk("\nChar_dev: init:\n");
    return 0;

error:
    for (--i; i >= 0; i--)
    {
        kfree(devs[i].cbuf.buf);
    }
    unregister_chrdev_region(dev_no, DEV_COUNT);
    return -1;
}

static void __exit test_exit(void)
{
    for (i = 0; i < DEV_COUNT; i++)
    {
        kfree(devs[i].cbuf.buf);
        cdev_del(&devs[i].my_cdev);
    }
    unregister_chrdev_region(dev_no, DEV_COUNT);
    printk("\nChar_dev: exit\n");
}

static int test_open(struct inode *inodep, struct file *filep)
{
    printk("\nIn test_open\n");
    struct my_dev *mdev = container_of(inodep->i_cdev, struct my_dev, my_cdev);
    filep->private_data = mdev;
    return 0;
}

static ssize_t test_read(struct file *filep, char *ubuff, size_t count, loff_t *off)
{
    int i, m, ret;
    printk("\nIn test_read\n");

    struct my_dev *tdev = filep->private_data;
    if (filep->f_flags & O_NONBLOCK)
    {
        if (CIRC_CNT(tdev->cbuf.head, tdev->cbuf.tail, BUFF_SIZE) == 0)
        {
            return -EAGAIN;
        }
    }
    else
    {
        }

    wait_event_interruptible(tdev->my_q, CIRC_CNT(tdev->cbuf.head, tdev->cbuf.tail, BUFF_SIZE) >= 1);

    m = min(CIRC_CNT(tdev->cbuf.head, tdev->cbuf.tail, BUFF_SIZE), (int)count);

    for (i = 0; i < m; i++)
    {
        ret = copy_to_user(ubuff + i, tdev->cbuf.buf + tdev->cbuf.tail, 1);
        if (ret)
        {
            printk("Error: Couldn't read\n");
            return -ENOMEM;
        }
        printk("read: %c", ubuff[i]);
        tdev->cbuf.tail = (tdev->cbuf.tail + 1) & (BUFF_SIZE - 1);
    }
    return i;
}

static ssize_t test_write(struct file *filep, const char *ubuff, size_t count, loff_t *off)
{
    int i, m, ret;
    printk("\nIn test_write\n");

    struct my_dev *tdev = filep->private_data;
    m = min(CIRC_SPACE(tdev->cbuf.head, tdev->cbuf.tail, BUFF_SIZE), (int)count);

    for (i = 0; i < m; i++)
    {
        ret = copy_from_user(tdev->cbuf.buf + tdev->cbuf.head, ubuff + i, 1);
        if (ret)
        {
            printk("Error: Couldn't write\n");
            return -ENOMEM;
        }
        printk("wrote: %c", tdev->cbuf.buf[tdev->cbuf.head]);
        tdev->cbuf.head = (tdev->cbuf.head + 1) & (BUFF_SIZE - 1);
    }
    wake_up(&tdev->my_q);
    return i;
}

static int test_release(struct inode *inodep, struct file *filep)
{
    printk("\nIn test_close\n");
    return 0;
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
