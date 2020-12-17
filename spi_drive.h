#ifndef SPI_DRIVE_H
#define SPI_DRIVE_H
#include "stm32f10x.h"                  // Device header
#include "gp_drive.h"
/*
FOR NOW SPI1 ONLY:
-->PA4-SS	(CAN BE MULTIPLE ONES)
-->PA5-CLK
-->PA6-MISO
-->PA7-MOSI
*/

/*
#define PA 1		//port defines
#define PB 2
#define PC 3
*/
#define ENABLE_SS LOW	//defines ofr enabling disabling ports SS CS for multiple spi devices
#define DISABLE_SS HIGH


void my_spi_init1(void);
void my_spi_init_ss(uint8_t port, uint8_t pin);
void my_spi_ss_ctrl(uint8_t port, uint8_t pin, _Bool state);
void my_spi_write(char data);
uint8_t my_spi_read(void);
uint16_t my_spi_transmit(uint16_t data_tx);
#endif
