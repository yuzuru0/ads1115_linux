#include <stdio.h>
#include "i2c_interface.h"
#include "ads1115.h"
#include <unistd.h>
#include <stdlib.h>

float input_ad(int ch)
{
	float voltage;
	short ad_dat;

	ad_dat = input_ad_raw(ch);

	voltage = ad_dat * (MAX_AD_VOLT- MIN_AD_VOLT)/MAX_AD_DAT;

	return voltage;
}

short input_ad_raw(int ch)
{
	unsigned char dev_addr = ADS1115_ADDR;
	unsigned char reg_addr;
	unsigned char send_buf[3];
	unsigned char recv_buf[2];
	int i;

	ads1115_config_register ads1115_config;
	ads1115_conversion_register ads1115_results;

	ads1115_config.config.REG_ADDR = ADS1115_CONFIG_REGISTER;
	ads1115_config.config.OS = CONV_START;
	ads1115_config.config.MUX = CH0+ch;
	ads1115_config.config.PGA = PM4096;
	ads1115_config.config.MODE = SINGLE;
	ads1115_config.config.DR = SPS860;
	ads1115_config.config.COMP_MODE = TRADIT_COMP;
	ads1115_config.config.COMP_POL = ACTIVE_L;
	ads1115_config.config.COMP_LAT = NO_LATCH;
	ads1115_config.config.COMP_QUE = DISABLE_COMP;

	// 送信データのバイトオーダー変換
	for(i=0;i<3;i++)
		send_buf[i] = ads1115_config.byte[2-i];


	i2c_write(dev_addr, send_buf, sizeof(send_buf)); 

	usleep(2000);

	reg_addr = 0x00;
	i2c_read(dev_addr, reg_addr, recv_buf, sizeof(recv_buf));

	// 受信データのバイトオーダー変換
	for(i=0;i<2;i++)
		ads1115_results.byte[i] = recv_buf[1-i];

	return ads1115_results.word;
}

int main(int argc, char *argv[])
{
	short results;
	float voltage;
	char *endptr;
	int ch;
	
	if(argc <2)
	{
		printf("usage: ads1115 ch (ch is 0 to 3)\n");
		return -1;
	}	

	ch = strtol(argv[1], &endptr,10);
	if(*endptr !='\0' || ch <0 || ch>3)
	{
		printf("Invalidity Channnel\n");
		printf("usage: ads1115 ch (ch is 0 to 3)\n");
		return -2;
	}	
	voltage = input_ad(ch);


	printf("%f\n",voltage);



	return 0;
}
