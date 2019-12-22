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
#include <linux/timer.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

#define MY_MAJOR 123
#define MY_MINOR 1
#define DEV_COUNT 1
#define BUFF_SIZE 8

dev_t dev_no;
struct cdev my_cdev;
struct circ_buf cbuf;

struct timer_list my_timer;
struct tasklet_struct my_tasklet;
struct workqueue_struct *wqs;
struct work_struct wrk_q;
struct work_struct shr_q;

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

void timer_func(struct timer_list *t)
{
    unsigned long expires = jiffies + msecs_to_jiffies(2000);
    printk("In timer function\n");
    mod_timer(t, expires);
}

void tasklet_func(unsigned long t)
{
    printk("In tasklet function: %ld\n", t);
}

void work_q_func(struct work_struct *wrk)
{
    printk("In work q func\n");
}

void shr_q_func(struct work_struct *wrk)
{
    printk("In shared queue func\n");
}

static int __init test_init(void)
{
    int err;
    dev_no = MKDEV(MY_MAJOR, MY_MINOR);
    err = register_chrdev_region(dev_no, DEV_COUNT, "def_works");
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

    err = cdev_add(&my_cdev, dev_no, DEV_COUNT);
    if (err < 0)
    {
        printk("\nError: Couldn't notify kernel to add device\n");
        kfree(cbuf.buf);
        unregister_chrdev_region(dev_no, DEV_COUNT);
        return err;
    }

    my_timer.expires = jiffies + msecs_to_jiffies(10000);
    timer_setup(&my_timer, timer_func, 0);
    add_timer(&my_timer);

    tasklet_init(&my_tasklet, tasklet_func, 10);
    tasklet_schedule(&my_tasklet);

    wqs = create_singlethread_workqueue("TESTWORKQ");
    INIT_WORK(&wrk_q, work_q_func);
    queue_work(wqs, &wrk_q);

    INIT_WORK(&shr_q, shr_q_func);
    schedule_work(&shr_q);

    printk("\nChar_dev: init:\n");
    return 0;
}

static void __exit test_exit(void)
{
    cdev_del(&my_cdev);
    kfree(cbuf.buf);

    del_timer_sync(&my_timer);

    tasklet_kill(&my_tasklet);

    flush_workqueue(wqs);
    destroy_workqueue(wqs);

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

    m = min(CIRC_CNT(cbuf.head, cbuf.tail, BUFF_SIZE), (int)count);

    for (i = 0; i < m; i++)
    {
        ret = copy_to_user(ubuff + i, cbuf.buf + cbuf.tail, 1);
        if (ret)
        {
            printk("Error: Couldn't read\n");
            return -ENOMEM;
        }
        printk("read: %c", ubuff[i]);
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
        printk("wrote: %c", cbuf.buf[cbuf.head]);
        cbuf.head = (cbuf.head + 1) & (BUFF_SIZE - 1);
    }
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