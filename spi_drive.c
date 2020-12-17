#include "spi_drive.h"
#include "gp_drive.h"
#include "systick_lib.h"

/*
FOR NOW SPI1 ONLY:
-->PA4-SS	(CAN BE MULTIPLE ONES)
-->PA5-CLK
-->PA6-MISO
-->PA7-MOSI
*/
void my_spi_init1(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
//	init_GP(PA,4,OUT50,O_GP_PP);		//slave select
	init_GP(PA,5,OUT50,O_AF_PP);	//mosi
	init_GP(PA,6,IN,I_PP);	//	miso
	init_GP(PA,7,OUT50,O_AF_PP);	//clk
	

	SPI1->CR1 |=	0x31;//master mode, slck /256(spi speed)
//	SPI1->CR2 |=	SPI_CR2_SSOE;		//multimaster disable
	SPI1->CR1 |=	SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE | SPI_CR1_MSTR;	//dowolny pin cs a nie ten hardwarowy; ENABLE SPI1;`master mode
}

void my_spi_init_ss(uint8_t port, uint8_t pin)
{
	init_GP(port,pin,OUT50,O_GP_PP);
	write_GP(port,pin,HIGH);
}

void my_spi_ss_ctrl(uint8_t port, uint8_t pin, _Bool state)
{
	if(!state){
		write_GP(port,pin,0);	//ENABLE transmission
	}else {
		//while(SPI1->SR & SPI_SR_BSY)
	//	{
		//}	//wait to finish sending last char otherwise will be cut and not transferred
		write_GP(port,pin,1);	//DISABLE transmission
	}
}

void my_spi_write(char data)
{
	while(!(SPI1->SR & SPI_SR_TXE))
	{
	}	//this flag when 0 means buff is busy and data is not send yet when 1 you can insert new data to send
		SPI1->DR=data;
}

uint8_t my_spi_read(void)
{
uint8_t data=0;
	while(!(SPI1->SR & SPI_SR_RXNE))
	{
	}		//when data in shift register appeared will be send to DR reg
	data=(uint8_t)(SPI1->DR);		//8 msb lost we only use 8 bit mode here!
return data;	
}

uint16_t my_spi_transmit(uint16_t data_tx)
{
	SPI1->DR=data_tx;
	uint32_t prev_t=systick_sim_millis;
	while(!(SPI1->SR & SPI_SR_TXE)){
		if(systick_sim_millis-prev_t>100)
		{
			//ERR_SPI1=1;
			return 0xFFFF;
		}
	}
	while(!(SPI1->SR & SPI_SR_RXNE)){
		if(systick_sim_millis-prev_t>100)
		{
			//ERR_SPI1=1;
			return 0xFFFF;
		}
	}
	return SPI1->DR;
}


