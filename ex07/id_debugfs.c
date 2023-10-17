#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>

# define FILE_NAME "id"
# define LOGIN "lweglarz"
# define LOGIN_SIZE 8

struct dentry *id_debugfs_file;

static ssize_t id_fop_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
	const char *login = LOGIN;
    ssize_t     ret = 0;

    if (count > LOGIN_SIZE){
        count = LOGIN_SIZE;
    }
	ret = copy_to_user(user_buf, login, count);
	return (count - ret);
}

static ssize_t id_fop_write(struct file *filep, const char __user *user_buf, size_t count, loff_t *ppos) {
    static char buffer[LOGIN_SIZE];
    ssize_t     ret = 0;

    if (count != LOGIN_SIZE)
        return (-EINVAL);

    ret = copy_from_user(buffer, user_buf, count);

    if (strncmp(buffer, LOGIN, LOGIN_SIZE) != 0)
        return (-EINVAL);

    return (count - ret);
}

static const struct file_operations id_fops = {
    .read = id_fop_read,
    .write = id_fop_write,
};

int create_id_debugfs(struct dentry *parent){
	id_debugfs_file = debugfs_create_file(FILE_NAME, 0000, parent, NULL, &id_fops);
	if (!id_debugfs_file){
		printk(KERN_ERR "Failed to create debugfs id file.\n");
       	return -1;
    }
	return 0;
}

MODULE_LICENSE("GPL");