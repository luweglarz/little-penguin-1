#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

# define LOGIN "lweglarz"

#include "fortytwo_misc.h"

/*
	filep: pointer to file we are reading
	user_buf: pointer to the user space memory
	count: number of bytes that we want to read
	f_pos: pointer to the file position of the cursor
*/


static ssize_t my_misc_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
	const char *login = LOGIN;
	// // Check if the file cursor is higher than DEV_MEME_SIZE, if not we reajust the count to set it to 0 to ensure that we read from the beginning
	// if (count > (strlen(login) - *f_pos))
	// 	count = strlen(login) - *f_pos;
	if(copy_to_user(user_buf, login , count)) {
        return (-EFAULT);
    }

	//*f_pos += count;
	printk(KERN_INFO "Number of bytes successfully read= %zu\n", count);
    printk(KERN_INFO "Updated file position= %lld\n", *f_pos);
	return (8);
}

static ssize_t my_misc_write(struct file *filep, const char __user *user_buf, size_t count, loff_t *ppos) {
	return (0);
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