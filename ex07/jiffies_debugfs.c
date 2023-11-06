#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>

# define FILE_NAME "jiffies"
struct dentry *jiffies_debugfs_file;

static ssize_t jiffies_fop_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
	ssize_t ret = 0;
	char buffer[20];

	sprintf(buffer, "%ld", jiffies);
	ret = simple_read_from_buffer(user_buf, count, f_pos, buffer, sizeof(buffer));
	return (ret);
}

static const struct file_operations jiffies_fops = {
    .read = jiffies_fop_read,
};

int create_jiffies_debugfs(struct dentry *parent){
	jiffies_debugfs_file = debugfs_create_file(FILE_NAME, 0444, parent, NULL, &jiffies_fops);
	if (!jiffies_debugfs_file){
		printk(KERN_ERR "Failed to create debugfs jiffies file.\n");
       	return -1;
    }
	return 0;
}

MODULE_LICENSE("GPL");