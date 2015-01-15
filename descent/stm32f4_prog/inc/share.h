#ifndef SHARE_H
#define SHARE_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"

#ifdef __cplusplus
 extern "C" {
#endif

void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState);

#ifdef __cplusplus
 }
#endif

#endif
