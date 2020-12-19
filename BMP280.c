#include "BMP280.h"
#include "spi_drive.h"

void bmp_280_init(void)
{
	my_spi_ss_ctrl(PA,4,ENABLE_SS);
	//0xF4 but write so MSbit set 0 so mask 0x7F
	my_spi_transmit(0xF4 & 0x7F);	
	my_spi_transmit(0x2F);	//B001 011 11 16 bit temp, 18 bit press, normal mode on
	my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
	//remember to wait 15 ms after init before getting readouts
}

void bmp_280_sleep(void)
{
		my_spi_ss_ctrl(PA,4,ENABLE_SS);
	//0xF4 but write so MSbit set 0 so mask 0x7F
	my_spi_transmit(0xF4 & 0x7F);	
	my_spi_transmit(0x2C);	//go sleep reg b[1:0]=00
	my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
	
}

uint16_t bmp_280_read_tempe(void)
{//16bit 
	uint16_t ret_val=0;
		my_spi_ss_ctrl(PA,4,ENABLE_SS);
	//read so msbit 1
	my_spi_transmit(0xFA | 0x80);
	
		ret_val |=((uint16_t)((uint8_t)my_spi_transmit(0xFF)))<<8;		//to moze nie niedzialac nie w ie mczy nie trzeba bedzie zruztowac tego na 16 bitow najpierow
		ret_val |=((uint8_t)my_spi_transmit(0xFF));

	my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
	return ret_val;
}

uint32_t bmp_280_read_press(void)
{//18bit znakow
	uint32_t ret_val=0;
	my_spi_ss_ctrl(PA,4,ENABLE_SS);
	//read so msbit 1
	my_spi_transmit(0xF7 | 0x80);
		ret_val |=((uint32_t)((uint8_t)my_spi_transmit(0xFF)))<<12;
		ret_val |=((uint32_t)((uint8_t)my_spi_transmit(0xFF)))<<4;
		ret_val |=((uint32_t)((uint8_t)my_spi_transmit(0xFF)))>>4;
	
	my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
	return ret_val;
}
uint8_t bmp_280_tst(void)
{
		uint8_t ret_val=0;
	my_spi_ss_ctrl(PA,4,ENABLE_SS);
	//read so msbit 1
	my_spi_transmit(0xD0 | 0x80);
	ret_val=((uint8_t)my_spi_transmit(0xFF));

	
	my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
	return ret_val;
}
uint8_t bmp_280_tst2(void)
{
		uint8_t ret_val=0;
	my_spi_ss_ctrl(PA,4,ENABLE_SS);
	//read so msbit 1
	my_spi_transmit(0xF4 | 0x80);
	ret_val=((uint8_t)my_spi_transmit(0xFF));

	my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
	return ret_val;
}

