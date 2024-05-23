#ifndef __ADS1115_H__
#define __ADS1115_H__

typedef union
{
	unsigned short register_16bit;

	struct
	{
		unsigned short upper_byte:8;
		unsigned short lower_byte:8;
	}byte;

	struct
	{
		unsigned short OS:1;
		unsigned short MUX:3;
		unsigned short PGA:3;
		unsigned short MODE:1;
		unsigned short DR:3;
		unsigned short COMP_MODE:1;
		unsigned short COMP_POL:1;
		unsigned short COMP_LAT:1;
		unsigned short COMP_QUE:2;
	}config;
}ads1115_config_register;

typedef union
{
	unsigned short register_16bit;

	struct
	{
		unsigned short upper_byte:8;
		unsigned short lower_byte:8;
	}byte;
}ads1115_conversion_register;


#endif
