#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

static struct proc_dir_entry *proc_entry;

static ssize_t proc_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
	struct dentry *curdentry;
        (void)curdentry;
        return (0);
}

static struct proc_ops myops = 
{
	.proc_read = proc_read,
};


static int __init my_misc_init(void) {
        proc_entry = proc_create("mymounts", 0660, NULL, &myops);
        return 0;
}

static void __exit my_misc_exit(void) {
        proc_remove(proc_entry);
}

module_init(my_misc_init);
module_exit(my_misc_exit);

MODULE_LICENSE("GPL");