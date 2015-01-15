#include "stm32.h"

void delay(void)
{
  volatile unsigned int i;
  for (i = 0; i < 0x3ffff; ++i);
}

int main(void)
{
  RCC_APB2ENR |= (1<<3);
  GPIOB_CRL &= 0x0;
  GPIOB_CRL |= 0x33333333;
  while(1)
  {
    GPIOB_BSRR = (1<<2);
    delay();
    GPIOB_BRR = (1<<2);
    delay();
  }

}
