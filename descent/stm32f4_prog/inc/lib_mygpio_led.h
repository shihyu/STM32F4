#ifndef LIB_MYGPIO_LED_H
#define LIB_MYGPIO_LED_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"

int init_led(void);
void test_led();
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Delay(uint32_t delay );

#endif
