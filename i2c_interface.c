#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include "i2c_interface.h"

#define I2C_DEV_NAME	"/dev/i2c-1"

int i2c_read(unsigned char dev_addr, unsigned char reg_addr, unsigned char* data, int length)
{

	int fd;
	int ret;
	int i;
	struct i2c_msg message[2];
	struct i2c_rdwr_ioctl_data i2c_data;

	unsigned char* buff;

	buff = (unsigned char *)malloc(length);

	

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
	message[1].buf = buff;

	i2c_data.msgs = message;
	i2c_data.nmsgs = 2;
	ret = ioctl(fd, I2C_RDWR, &i2c_data);

	if(ret <0)
	{
		fprintf(stderr, "i2c_read  read error %d\n",ret);
		return -2;
	}

	// 受信データのエンディアン反転
	for(i=0;i<length;i++)
		memcpy(&data[i], &buff[length -i -1],1);


	close(fd);


	return 0;
}

int i2c_write(unsigned char dev_addr, unsigned char reg_addr, unsigned char* data, int length)
{
	int fd;
	int ret;
	int i;
	struct i2c_msg message;
	struct i2c_rdwr_ioctl_data i2c_data;
	unsigned char* buff;

	buff = (unsigned char *)malloc(length+1);
	// 送信データの先頭をレジスタアドレスに
	buff[0] = reg_addr;

	// 送信データのエンディアン反転
	for(i=0;i<length;i++)
		memcpy(&buff[i+1], &data[length-i-1],1);

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

