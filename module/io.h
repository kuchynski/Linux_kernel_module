//
// Linux kernel module
// kuchynskiandrei@gmail.com
// 2021
//

#ifndef module_ioH
#define module_ioH

#include <linux/miscdevice.h>

#define MODULE_NAME "module_test"					// used by open(DEVICE_NAME, ...
#define BUFFER_SIZE	128
#define IOCTL_MODULE_0 _IOR(100, 1, int)
#define IOCTL_MODULE_1 _IOR(100, 2, size_t)

struct struct_module_data
{
	struct file_operations fops;
	struct miscdevice dev;

	char data[BUFFER_SIZE];
	size_t size;

	int open_count;
};

int module_open(struct inode *, struct file *);
int module_release(struct inode *, struct file *);
ssize_t module_write(struct file *, const char __user *, size_t, loff_t *);
ssize_t module_read(struct file *, char __user *, size_t, loff_t *);
long module_ioctl(struct file *, unsigned int, unsigned long);

#endif
