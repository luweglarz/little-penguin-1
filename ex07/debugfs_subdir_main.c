#include <linux/init.h>
#include <linux/module.h>
#include <linux/debugfs.h>

#include "debugfs_subdir.h"

static struct dentry *my_debugfs_dir;

static int __init debugfs_subdir_init(void) {
    my_debugfs_dir = debugfs_create_dir("fortytwo", NULL);
    if (!my_debugfs_dir) {
        printk(KERN_ERR "Failed to create debugfs directory.\n");
        return -ENOMEM;
    }
    printk(KERN_INFO "DebugFs subdirectory created.\n");
    if (create_id_debugfs(my_debugfs_dir) != 0)
        return (-ENOMEM);
    if (create_foo_debugfs(my_debugfs_dir) != 0)
        return (-ENOMEM);
    if (create_jiffies_debugfs(my_debugfs_dir) != 0)
        return (-ENOMEM);
    (void)id_debugfs_file;
    return 0;
}

static void __exit debugfs_subdir_exit(void) {
    debugfs_remove_recursive(my_debugfs_dir);
    printk(KERN_INFO "DebugFs subdirectory removed.\n");
}

module_init(debugfs_subdir_init);
module_exit(debugfs_subdir_exit);

MODULE_LICENSE("GPL");