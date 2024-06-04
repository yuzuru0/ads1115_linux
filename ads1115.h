#ifndef __ADS1115_H__
#define __ADS1115_H__

#define CONV_START 1

#define CH0_1_DIFF 0
#define CH0_3_DIFF 1
#define CH1_3_DIFF 2
#define CH2_3_DIFF 3
#define CH0	4
#define CH1 5
#define CH2 6
#define CH3 7

#define PM6144	0
#define PM4096	1
#define PM2048	2
#define PM1024	3
#define PM0512	4
#define PM0256	5
#define SINGLE	1

#define SPS8	0
#define SPS16	1
#define SPS32	2
#define SPS64	3
#define SPS128	4
#define SPS250	5
#define SPS475	6
#define SPS860	7

#define TRADIT_COMP	0
#define WINDOW_COMP	1

#define ACTIVE_L	0
#define ACTIVE_H	1

#define NO_LATCH	0
#define LATCH_COMP	1

#define ONE_CONV	0
#define TWO_CONV	1
#define FOUR_CONV	2
#define DISABLE_COMP 3

#define ADS1115_CONFIG_REGISTER	0x01
#define ADS1115_RESULT_REGISTER 0x00

#define ADS1115_ADDR 0x48

#define MAX_AD_VOLT 4.096
#define MIN_AD_VOLT -4.096
#define AD_RESOLUTION 16
#define MAX_AD_DAT	65535

float input_ad(int ch);
short input_ad_raw(int ch);

typedef union
{
	unsigned int word;
	unsigned char byte[3];


	struct
	{
		unsigned int COMP_QUE:2;
		unsigned int COMP_LAT:1;
		unsigned int COMP_POL:1;
		unsigned int COMP_MODE:1;
		unsigned int DR:3;
		unsigned int MODE:1;
		unsigned int PGA:3;
		unsigned int MUX:3;
		unsigned int OS:1;
		unsigned int REG_ADDR:8;
	}config;
}ads1115_config_register;

typedef union
{
	unsigned short word;
	unsigned char byte[2];

}ads1115_conversion_register;


#endif
