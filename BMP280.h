#ifndef BMP280_H
#define BMP280_H
#include "stm32f10x.h"

void bmp_280_init(void);
void bmp_280_sleep(void);
uint32_t bmp_280_read_press(void);
uint16_t bmp_280_read_tempe(void);
uint8_t bmp_280_tst(void);
uint8_t bmp_280_tst2(void);
#endif 
