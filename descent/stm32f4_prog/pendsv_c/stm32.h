#ifndef STM32_H
#define STM32_H

//#include "lib_mygpio_led.h"

#define STACK_SIZE 64
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

void ResetISR(void)
{
  unsigned long *pulSrc, *pulDest;

  pulSrc = &_etext;
  for (pulDest = &_data; pulDest < &_edata;)
    *pulDest++ = *pulSrc++;
  for (pulDest = &_bss; pulDest < &_ebss;)
    *pulDest++ = 0;

  main();
}

void pendsv_isr(void)
{
  int i=5;

  ++i;
#if 0
  //void test_led();
  //test_led();
  /* PD12 to be toggled */
  GPIO_SetBits(GPIOD, GPIO_Pin_12); 
  /* Insert delay */
  Delay(0x3FFFFF);

#endif
}

void svc_isr(void)
{
  // pendsv set:
  //ref: @ Cortex™-M3 Technical Reference Manual (file name: DDI0337E_cortex_m3_r1p1_trm.pdf) p8-19
  *( unsigned long *) 0xE000ED04 |= 0x10000000;
}

void systick_isr(void)
{
}

void int_isr(void)
{
}

typedef void (*pfnISR)(void);
__attribute__((section(".stackares")))
static unsigned long pulStack[STACK_SIZE];


__attribute__((section(".isr_vector")))
pfnISR VectorTable[]=
{
  (pfnISR)((unsigned long)pulStack+sizeof(pulStack)),
  ResetISR, // 1
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  svc_isr,    // 11
  int_isr,
  int_isr,
  pendsv_isr, // 14
  systick_isr // 15
};

#endif
