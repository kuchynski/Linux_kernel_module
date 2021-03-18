//
// Linux kernel module
// kuchynskiandrei@gmail.com
// 2021
//

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include "io.h"

struct struct_module_data *module_data; 

static int __init init_function(void)
{
	module_data = kmalloc(sizeof(struct struct_module_data), GFP_KERNEL);
	if(!module_data) {
		printk(KERN_INFO "\n%s: memory allocation error\n", MODULE_NAME);
		return -1;
	}
	memset(module_data, 0, sizeof(struct struct_module_data));
	
	module_data->fops.owner = THIS_MODULE;
	module_data->fops.open = module_open;
	module_data->fops.release = module_release;
	module_data->fops.write = module_write;
	module_data->fops.read = module_read;
	module_data->fops.unlocked_ioctl = module_ioctl;
	
	module_data->dev.minor = MISC_DYNAMIC_MINOR;
	module_data->dev.name = MODULE_NAME;
	module_data->dev.fops = &module_data->fops;
	
	if(misc_register(&module_data->dev)) {
		printk(KERN_INFO "\n%s: device registration error\n", MODULE_NAME);
		kfree(module_data);
		return -1;
	}

	printk(KERN_INFO "%s: init\n", MODULE_NAME);

	return 0;
}

static void __exit exit_function(void)
{
	misc_deregister(&module_data->dev); 
	kfree(module_data);
	module_data = 0;
	printk(KERN_INFO "%s: exit\n", MODULE_NAME);
}

module_init(init_function);
module_exit(exit_function);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kuchynski");
