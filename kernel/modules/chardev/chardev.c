#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

int init_module(void);
void cleanup_module(void);

static int device_open(struct inode*, struct file*);
static int device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char __user*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char __user*, size_t, loff_t*);

#define SUCCESS 0
#define DEVICE_NAME "HelloCharDev"
#define BUF_LEN 80

static int Major = 0;
static int DeviceOpen = 0;

static char msg1[BUF_LEN] = {0};
static char msg[BUF_LEN];
static char* msg_Ptr = 0;

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};


int init_module(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);

    if (Major < 0)
    {
        printk(KERN_ALERT "Registering char device failed with %d\n", 
                Major);
        return Major;
    }

    printk(KERN_ALERT "I was assigned major number %d.\n To talk to", Major);
    printk(KERN_ALERT "the driver, create a dev file with:\n");
    printk(KERN_ALERT "\t'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
    printk(KERN_ALERT "Try various minor numbers. Try to cat and echo to \n");
    printk(KERN_ALERT "the device file\n");
    printk(KERN_ALERT "Remove the device file and module when done.\n");

    return SUCCESS;
}

void cleanup_module(void)
{
    unregister_chrdev(Major, DEVICE_NAME);
}

static int device_open(struct inode* inode, struct file* file)
{
    static int counter = 0;

    if (DeviceOpen)
        return -EBUSY;
    DeviceOpen++;
    sprintf(msg, "I've already told you %d times Hello, world.\n",
            counter++);

    if (msg1[0] != 0)
        msg_Ptr = msg1;
    else
        msg_Ptr = msg;

    try_module_get(THIS_MODULE);

    return SUCCESS;
}

static int device_release(struct inode* inode, struct file* file)
{
    DeviceOpen--;
    module_put(THIS_MODULE);
    
    return SUCCESS;
}

static ssize_t device_read(struct file* filp,
                        char __user* buf,
                        size_t length,
                        loff_t* offset)
{
    int bytes_read = 0;

    if (msg_Ptr == 0)
        return 0;

    while (length && *msg_Ptr)
    {
        put_user(*(msg_Ptr++), buf++);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

static ssize_t device_write(struct file* filp,
                        const char __user* buf,
                        size_t length,
                        loff_t* offset)
{
    char* ptr = msg1;
    ssize_t bytes_written = 0;
    
    if (length > BUF_LEN - 1)
        length = BUF_LEN - 1;

    while  (length && *buf)
    {
        get_user(*ptr, buf++);
        --length;
        ++ptr;
        ++bytes_written;
    }
    *ptr++ = 0;
    printk(KERN_ALERT "Message from user: %s\n", msg1);

    return bytes_written;
}

