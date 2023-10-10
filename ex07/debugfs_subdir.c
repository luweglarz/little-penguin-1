#include <linux/init.h>
#include <linux/module.h>
#include <linux/debugfs.h>

#include "debugfs_subdir.h"

static struct dentry *my_debugfs_dir;

static int __init debugfs_subdir_init(void) {
    // my_debugfs_dir = debugfs_create_dir("fortytwo", NULL);
    // if (!my_debugfs_dir) {
    //     printk(KERN_ERR "Failed to create debugfs directory.\n");
    //     return -ENOMEM;
    // }
    // printk(KERN_INFO "DebugFs subdirectory created.\n");

    // my_debugfs_file = debugfs_create_file("id", 0444, my_debugfs_dir, NULL, &id_fops);
    // if (!my_debugfs_file) {
    //     printk(KERN_ERR "Failed to create \"id\" debugfs file.\n");
    //     debugfs_remove(my_debugfs_dir);
    //     return -ENOMEM;
    // }

    // my_debugfs_file = debugfs_create_file("jiffies", 0444, my_debugfs_dir, NULL, &jiffies_fops);
    // if (!my_debugfs_file) {
    //     printk(KERN_ERR "Failed to create \"jiffies\" debugfs file.\n");
    //     debugfs_remove(my_debugfs_dir);
    //     return -ENOMEM;
    // }

    // my_debugfs_file = debugfs_create_file("foo", 0444, my_debugfs_dir, NULL, &foo_fops);
    // if (!my_debugfs_file) {
    //     printk(KERN_ERR "Failed to create \"foo\" debugfs file.\n");
    //     debugfs_remove(my_debugfs_dir);
    //     return -ENOMEM;
    // }
    create_jiffies_debugfs();
    return 0;
}

static void __exit debugfs_subdir_exit(void) {
    debugfs_remove_recursive(my_debugfs_dir);
    printk(KERN_INFO "DebugFs subdirectory removed.\n");
}

module_init(debugfs_subdir_init);
module_exit(debugfs_subdir_exit);

MODULE_LICENSE("GPL");