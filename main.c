#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "systick_lib.h"
#include "spi_drive.h"
/*
SPI1
-->PA4-SS
-->PA5-CLK
-->PA6-MISO
-->PA7-MOSI
*/

// volatile int dummy_var=0;
	//volatile uint16_t val1=0;
int main(void)
{
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	systick_init();
	my_spi_init1();
	my_spi_init_ss(PA,4);
	//enable spi1 rccapb2 rgr
	/*
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	init_GP(PA,4,OUT50,O_GP_PP);		//slave select
	init_GP(PA,5,OUT50,O_AF_PP);	//mosi
	init_GP(PA,6,IN,I_PP);	//	miso
	init_GP(PA,7,OUT50,O_AF_PP);	//clk
	
	SPI1->CR1 |=	SPI_CR1_MSTR;
	SPI1->CR1 |=	0x31;//master mode, slck /256(spi speed)
	SPI1->CR2 |=	SPI_CR2_SSOE;		//multimaster disable
	SPI1->CR1 |=	SPI_CR1_SSM;	//dowolny pin cs a nie ten hardwarowy
	SPI1->CR1 |=	SPI_CR1_SSI;
	SPI1->CR1 |= 	SPI_CR1_SPE;		//ENABLE SPI1`
	write_GP(PA,4,HIGH);
	*/
	char spi_buf1[]="masz ty wogle rozum i godnosc czlowieka ty gnoju";
	//uint8_t pos=0;
	
	while(1)
	{
		my_spi_ss_ctrl(PA,4,ENABLE_SS);
		for(uint8_t pos=0;spi_buf1[pos]!='\0';pos++)
		{
			my_spi_write(spi_buf1[pos]);
		}
		my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
		delay_MS(100);
			
			
			/*
			if(spi_buf1[pos]=='\0')
			{			
				pos=0;
				write_GP(PA,4,HIGH);
				delay_MS(50);
			}
		
			write_GP(PA,4,LOW);//chip select low change means we are sending data
			SPI1->DR = spi_buf1[pos];
			val1=SPI1->SR;
			while(!(SPI1->SR & SPI_SR_TXE))
			{
				dummy_var++;
			}		//wait for it to send data
			pos++;
			//val1=SPI1->SR;
			
		}
			*/
	}
}

