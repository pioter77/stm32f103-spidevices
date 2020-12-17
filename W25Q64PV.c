#include "W25Q64PV.h"
#include "spi_drive.h"
#include "stm32f10x.h"                  // Device header

void read_spi_mem(uint32_t addr,uint32_t len,uint8_t *holder)
{
	my_spi_ss_ctrl(PA,4,ENABLE_SS);
	
	my_spi_transmit(0x4B);
	//my_spi_transmit((uint8_t)(addr>>16));
	//my_spi_transmit((uint8_t)(addr>>8));
	//my_spi_transmit((uint8_t)(addr));
	my_spi_transmit(0xFF);
	my_spi_transmit(0xFF);
	my_spi_transmit(0xFF);
	my_spi_transmit(0xFF);
	for(uint32_t data_cnt=0;data_cnt<len;data_cnt++)
		holder[data_cnt]=(uint8_t)my_spi_transmit(0xFF);
	
	my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
}

void power_down_spi_mem(void)
{
		my_spi_ss_ctrl(PA,4,ENABLE_SS);
	
	my_spi_transmit(0xB9);
		my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
}
