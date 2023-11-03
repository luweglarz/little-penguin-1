#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

# define LOGIN "lweglarz"
# define LOGIN_SIZE 8

static ssize_t my_misc_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
	const char *login = LOGIN;
    ssize_t     ret = 0;

    if (count > LOGIN_SIZE){
        count = LOGIN_SIZE;
    }
    ret = simple_read_from_buffer(user_buf, count, f_pos, login, sizeof(login));
	return (ret);
}

static ssize_t my_misc_write(struct file *filep, const char __user *user_buf, size_t count, loff_t *f_pos) {
    static char buffer[LOGIN_SIZE];
    ssize_t     ret = 0;

    if (count != LOGIN_SIZE)
        return (-EINVAL);

    ret = simple_write_to_buffer(buffer, sizeof(buffer), f_pos, user_buf, count);

    if (strncmp(buffer, LOGIN, LOGIN_SIZE) != 0)
        return (-EINVAL);

    return (ret);
}

static const struct file_operations my_misc_fops = {
    .read = my_misc_read,
    .write = my_misc_write,
};

static struct miscdevice my_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "fortytwo",
    .fops = &my_misc_fops,
};

static int __init my_misc_init(void) {
    int ret = misc_register(&my_misc_device);
    if (ret) {
        printk(KERN_INFO "Failed to register misc device\n");
        return ret;
    }
    printk(KERN_INFO "Misc char driver loaded\n");
    return 0;
}

static void __exit my_misc_exit(void) {
    misc_deregister(&my_misc_device);
    printk(KERN_INFO "Misc char driver unloaded\n");
}

module_init(my_misc_init);
module_exit(my_misc_exit);

MODULE_LICENSE("GPL");