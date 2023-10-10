#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>



// static const struct file_operations foo_fops = {
//     .read = foo_fop_read,
//     .write = foo_fop_write,
// };

// static ssize_t foo_fop_read(struct file *filep, char __user *user_buf, size_t count, loff_t *f_pos) {
// 	const char *login = LOGIN;

//     if (count > (LOGIN_SIZE - *f_pos)){
//         count = LOGIN_SIZE - *f_pos;
//     }
// 	if(copy_to_user(user_buf, login, count)) {
//         return (-EFAULT);
//     }
// 	return (count);
// }

// static ssize_t foo_fop_write(struct file *filep, const char __user *user_buf, size_t count, loff_t *ppos) {
//     static char buffer[LOGIN_SIZE];

//     if (count != sizeof(buffer))
//         return (-EINVAL);

//     if (copy_from_user(buffer, user_buf, count))
//         return (-EFAULT);

//     if (strncmp(buffer, LOGIN, LOGIN_SIZE) != 0)
//         return (-EINVAL);

//     return (count);
// }

void create_foo_debugfs(void){
    
}