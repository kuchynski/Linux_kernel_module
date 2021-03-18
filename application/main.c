//
// Associated memory with a string key
// kuchynskiandrei@gmail.com
// 2020
//

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define MODULE_NAME "module_test"
#define IOCTL_MODULE_0 _IOR(100, 1, int)
#define IOCTL_MODULE_1 _IOR(100, 2, size_t)
#define BUFFER_SIZE	256

int main(void)
{
	int ret;
	int fd = open("/dev/" MODULE_NAME, O_RDWR);
	
	if(fd >= 0) {
		char buf[BUFFER_SIZE];
		ssize_t size_write; 
		ssize_t size_read; 
		size_t size_module_buffer;
		
		size_write = write(fd, buf, 5);
		size_read = read(fd, buf, BUFFER_SIZE);
		printf("%d bytes have been written, %d bytes have been read\n", size_write, size_read);
	
		size_write = write(fd, buf, BUFFER_SIZE);
		size_read = read(fd, buf, BUFFER_SIZE);
		printf("%d bytes have been written, %d bytes have been read\n", size_write, size_read);

		ret = ioctl(fd, IOCTL_MODULE_1, &size_module_buffer);
		if(ret == 0)
			printf("The module stores %d bytes\n", size_module_buffer);

		close(fd);
		return 0;
	}
	
	printf("error open %s %d\n", MODULE_NAME, errno);
	return -1;
}

