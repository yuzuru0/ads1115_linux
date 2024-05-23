#ifndef __I2C_INTERFACE__
#define __I2C_INTERFACE__

int i2c_read(unsigned char dev_addr, unsigned char reg_addr, unsigned char* data, int length);
int i2c_write(unsigned char dev_addr, unsigned char reg_addr, unsigned char* data, int length);




#endif
