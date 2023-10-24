#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/nsproxy.h>
#include <linux/mount.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <../fs/mount.h>

static struct proc_dir_entry *proc_entry;

static ssize_t proc_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
	struct mount *mnt;
	char buffer[256];
	ssize_t ret = 0;

	memset(buffer, '\0', sizeof(buffer));
	list_for_each_entry(mnt, &current->nsproxy->mnt_ns->list, mnt_list) {
		printk(KERN_INFO "mnt %s\n", mnt->mnt_devname); 
		pr_info("%s\n", mnt->mnt_devname);
	}
	// struct super_block *sb;
	// list_for_each_entry(sb, &current->nsproxy->mnt_ns->list, s_list) {
	// 	printk(KERN_INFO "mnt %s\n", mnt->s_id); 
	// }
	return (ret - count);
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