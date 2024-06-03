#include <stdio.h>
#include <time.h>
#include "i2c_interface.h"
#include "ads1115.h"
#include <unistd.h>

float input_ad(int ch)
{
	int voltage;

	return voltage;
}

int input_ad_raw(int ch)
{
	int input_data;

	return input_data;
}

int main(void)
{
	unsigned char dev_addr = 0x48;
	unsigned char reg_addr = 0x01;
	struct timespec wait_time;

	short ad_data;

	ads1115_config_register ads1115_config;
	ads1115_conversion_register ads1115_results;

	ads1115_config.config.OS = CONV_START;
	ads1115_config.config.MUX = CH0;
	ads1115_config.config.PGA = PM4096;
	ads1115_config.config.MODE = SINGLE;
	ads1115_config.config.DR = SPS860;
	ads1115_config.config.COMP_MODE = TRADIT_COMP;
	ads1115_config.config.COMP_POL = ACTIVE_L;
	ads1115_config.config.COMP_LAT = NO_LATCH;
	ads1115_config.config.COMP_QUE = DISABLE_COMP;


	i2c_write(dev_addr, reg_addr, ads1115_config.byte, sizeof(ads1115_config.byte)); 

	wait_time.tv_sec=0;
	wait_time.tv_nsec=2*1000*1000; // 2msec
	nanosleep(&wait_time,NULL);
//	usleep(2000);

	reg_addr = 0x00;
	i2c_read(dev_addr, reg_addr, ads1115_results.byte, sizeof(ads1115_results.byte));


	printf("%x %x %x %f\n",ads1115_results.word, ads1115_results.byte[0], ads1115_results.byte[1],ads1115_results.word*8.0/65535);



	return 0;
}
