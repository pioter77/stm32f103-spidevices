#ifndef W25Q64PV_H
#define W25Q64PV_H
#include "stm32f10x.h"

void read_spi_mem(uint32_t addr,uint32_t len,uint8_t *holder);
void power_down_spi_mem(void);
#endif 
