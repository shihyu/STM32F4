#include "stm32.h"
#include "lib_mygpio_led.h"


int main(void)
{
  *( unsigned long *) 0xE000ED22 |= 0xff;
  *( unsigned long *) 0xE000ED1f |= 0xff;
  init_led();

  __asm__ ("svc 1");
  GPIO_SetBits(GPIOD, GPIO_Pin_15);
  /* Insert delay */
  Delay(0x3FFFFF);
  //test_led_1();
  while(1)
  {
    int i=3;

    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    /* Insert delay */
    Delay(0x3FFFFF);
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    Delay(0x3FFFFF);
  }
  //*(unsigned long*)0xe000ed04 |= 0x10000000;
  return 0;
}
