#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <linux/mutex.h>
#include <asm/page.h>

# define FILE_NAME "foo"

char page[PAGE_SIZE];

DEFINE_MUTEX(debugfs_mutex);

struct dentry *foo_debugfs_file;

static ssize_t foo_fop_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
	ssize_t ret = 0;

    if (count > PAGE_SIZE){
        count = PAGE_SIZE;
    }
	mutex_lock(&debugfs_mutex);
	ret = copy_to_user(user_buf, page, count);
	mutex_unlock(&debugfs_mutex);
	return (count - ret);
}

static ssize_t foo_fop_write(struct file *filep, const char __user *user_buf, size_t count, loff_t *ppos) {
	ssize_t ret = 0;

	if (count > PAGE_SIZE)
		count = PAGE_SIZE;
	mutex_lock(&debugfs_mutex);
	ret = copy_from_user(page, user_buf, count);
	mutex_unlock(&debugfs_mutex);
	return (count - ret);
}

static const struct file_operations foo_fops = {
    .read = foo_fop_read,
    .write = foo_fop_write,
};

int create_foo_debugfs(struct dentry *parent){
	foo_debugfs_file = debugfs_create_file(FILE_NAME, 0000, parent, NULL, &foo_fops);
	if (!foo_debugfs_file){
		printk(KERN_ERR "Failed to create debugfs foo file.\n");
       	return -1;
    }
	return 0;
}

MODULE_LICENSE("GPL");