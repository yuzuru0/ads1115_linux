#include <stdio.h>
#include "i2c_interface.h"
#include "ads1115.h"

int main(void)
{
	unsigned char dev_addr = 0x48;
	unsigned char reg_addr = 0x01;

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

	printf("%X %x %x\n",ads1115_config, ads1115_config.byte[0], ads1115_config.byte[1]);

//	i2c_write(dev_addr, reg_addr, 



	return 0;
}
