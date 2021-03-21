//
// Linux kernel module
// kuchynskiandrei@gmail.com
// 2021
//

#include <linux/fs.h>
#include <linux/pagemap.h>
#include "io.h"

extern struct struct_module_data *module_data; 

int module_open(struct inode *inode, struct file *file)
{
	file->private_data = module_data;
	module_data->open_count ++;
	printk(KERN_INFO "%s: open %d\n", MODULE_NAME, module_data->open_count);
	return 0;
}

int module_release(struct inode *inode, struct file *file)
{
	struct struct_module_data *md = (struct struct_module_data *)file->private_data;
	md->open_count --;
	printk(KERN_INFO "%s: close\n", MODULE_NAME);
	return 0;
}

ssize_t module_write(struct file *file, const char *buff, size_t len, loff_t *off)
{
	struct struct_module_data *md = (struct struct_module_data *)file->private_data;

	md->size = (len <= BUFFER_SIZE)? len : BUFFER_SIZE;
	memcpy(md->data, buff, md->size);

	printk(KERN_INFO "%s: %d bytes have been written\n", MODULE_NAME, md->size);
	return md->size;
}

ssize_t module_read(struct file *file, char *buff, size_t len, loff_t *off)
{
	struct struct_module_data *md = (struct struct_module_data *)file->private_data;

	if(len > md->size)
		len = md->size;
	memcpy(buff, md->data, len);

	printk(KERN_INFO "%s: %d bytes have been read\n", MODULE_NAME, len);
	return len;
}

long module_ioctl(struct file *file, unsigned int code, unsigned long arg)
{
	long ret = 0;
	struct struct_module_data *md = (struct struct_module_data *)file->private_data;

	switch(code)
	{
		case IOCTL_MODULE_0:
			put_user(md->open_count, (int __user *)arg);
			break;
		case IOCTL_MODULE_1:
			put_user(md->size, (size_t __user *)arg);
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}
