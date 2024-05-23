#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define I2C_DEV_NAME	"/dev/i2c-1"

int i2c_read(unsigned char dev_addr, unsigned char reg_addr, unsigned char* data, int length)
{

	int fd;
	int ret;
	struct i2c_msg message[2];
	struct i2c_rdwr_ioctl_data i2c_data;
	
	

	fd = open(I2C_DEV_NAME, O_RDWR);
	if(fd == -1)
	{
		fprintf(stderr, "i2c_read open fd error\n");
		return -1;
	}

	message[0].addr = dev_addr;
	message[0].flags = 0;
	message[0].len = 1;
	message[0].buf = &reg_addr;

	message[1].addr = dev_addr;
	message[1].flags = I2C_M_RD;
	message[1].len = length;
	message[1].buf = data;

	i2c_data.msgs = message;
	i2c_data.nmsgs = 2;
	ret = ioctl(fd, I2C_RDWR, &i2c_data);

	if(ret <0)
	{
		fprintf(stderr, "i2c_read  read error %d\n",ret);
		return -2;
	}

	close(fd);


	return 0;
}

int i2c_write(unsigned char dev_addr, unsigned char reg_addr, unsigned char* data, int length)
{
	int fd;
	int ret;
	struct i2c_msg message;
	struct i2c_rdwr_ioctl_data i2c_data;
	unsigned char* buff;

	buff = (unsigned char *)malloc(length+1);
	buff[0] = reg_addr;
	memcpy(&buff[1], data,length);

	fd = open(I2C_DEV_NAME, O_RDWR);
	if(fd == -1)
	{
		fprintf(stderr, "i2c_write fd error\n");
		return -1;
	}

	message.addr = dev_addr;
	message.flags = 0;
	message.len = sizeof(buff);
	message.buf = buff;

	i2c_data.msgs = &message;
	i2c_data.nmsgs = 1;

	ret = ioctl(fd, I2C_RDWR, &i2c_data);
	/*
	if(ret< 0)
	{
		fprintf(stderr, "i2c write write error %d %s\n",ret, strerror(errno));
		return -2;
	}
	*/
	close(fd);

	return 0;
}

int main(void)
{

	unsigned char data[2];
	unsigned char dev_addr = 0x48;
	unsigned char reg_addr = 0x01;
	short ad_data;


	data[0] = 0xc3;
	data[1] = 0xe2;
	i2c_write(dev_addr, reg_addr, data,sizeof(data));

	reg_addr = 0x00;
	usleep(500);

	i2c_read(dev_addr, reg_addr, data, sizeof(data));
	printf("%x %x\n",data[0],data[1]);

	ad_data = data[0]<<8 |  data[1];

	printf("%d %f\n",ad_data, (ad_data) * 8.0 / 65535);


	return 0;
}
