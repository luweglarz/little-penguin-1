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

static int my_mount_proc_show(struct seq_file *m, void *v) {
    struct mount *mnt;

    list_for_each_entry(mnt, &current->nsproxy->mnt_ns->list, mnt_list) {
	seq_printf(m, "%s\n", mnt->mnt_devname);
    }
    return 0;
}

static int my_mount_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, my_mount_proc_show, NULL);
}

static struct proc_ops myops = 
{
	.proc_open = my_mount_proc_open,
	.proc_read = seq_read,
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