#ifndef DEBUGFS_SUBDIR
# define DEBUGFS_SUBDIRE

int create_id_debugfs(struct dentry *parent);
int create_jiffies_debugfs(struct dentry *parent);
int create_foo_debugfs(struct dentry *parent);

extern struct dentry *id_debugfs_file;
extern struct dentry *jiffies_debugfs_file;
extern struct dentry *foo_debugfs_file;

#endif