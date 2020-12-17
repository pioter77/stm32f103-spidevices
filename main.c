#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
#include "systick_lib.h"
#include "spi_drive.h"
#include "W25Q64PV.h"
/*
SPI1
-->PA4-SS
-->PA5-CLK
-->PA6-MISO
-->PA7-MOSI
*/
volatile uint32_t systick_sim_millis=0;
// volatile int dummy_var=0;
	//volatile uint16_t val1=0;
int main(void)
{
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	systick_init();
	my_spi_init1();
	my_spi_init_ss(PA,4);
	systick_inter_start();	// inkrement global systick_init val similar to milis used in spi
	
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
	//char spi_buf1[]="masz ty wogle rozum i godnosc czlowieka ty gnoju";
	char spi_buf1[]={(char)0x05,'\0'};
	char spi_red_buf[2]={[1]='\0'};
	//uint8_t pos=0;
	uint8_t id_buff[8]={0,0,0,0,0,0,0,0};
	delay_MS(10000);
	power_down_spi_mem();
	while(1)
	{
		/*
		my_spi_ss_ctrl(PA,4,ENABLE_SS);
		for(uint8_t pos=0;spi_buf1[pos]!='\0';pos++)
		{
			my_spi_write(spi_buf1[pos]);
		}
				for(uint8_t pos=0;spi_red_buf[pos]!='\0';pos++)
		{
			spi_red_buf[pos]=my_spi_read();
		}
		my_spi_ss_ctrl(PA,4,DISABLE_SS);	//zaczeka na koniec transmisji ostatniego znaku
		*/
		//read_spi_mem(0,8,id_buff);
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

void SysTick_Handler(void)
{
	systick_sim_millis++;
	//tu inkrement globala
	//to nie jest najlepsze rozwiazanie bo trzeba tracic miejsce na strukture do usarta1 mimo ze go sie nie uzywa i on sprawdza potem i probuje go odczytywac?
	//odczytu nie ma chyba bo flaga [0] zawsze na 0
	//systick_inter(uart_1_mgr,uart_2_mgr,uart_3_mgr);	to ma znaczeni tylko gdy uzywamy uarta jak timerowego ja uzywam uart przerwaniowo
}

