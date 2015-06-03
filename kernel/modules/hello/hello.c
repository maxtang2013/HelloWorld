#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Max Tang");

static int goodNum = 0;

module_param(goodNum, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(goodNum, "A good number");

static int __init init_module1(void)
{
    printk(KERN_ERR "An error message!\n");
    printk(KERN_CRIT "Good number is %d\n", goodNum);
    printk(KERN_ALERT "Hello, world!\n");

    return 0;
}

static void __exit cleanup_module1(void)
{
    printk(KERN_ALERT "Goodbye, kernel!\n");
}

module_init(init_module1);
module_exit(cleanup_module1);
