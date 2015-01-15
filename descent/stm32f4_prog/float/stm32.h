#ifndef STM32_H
#define STM32_H

#include "lib_mygpio_led.h"

#define STACK_SIZE 0xfff0
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

extern "C"
{
  void WinMain();
}

void ResetISR(void)
{
  unsigned long *pulSrc, *pulDest;

  pulSrc = &_etext;
  for (pulDest = &_data; pulDest < &_edata;)
    *pulDest++ = *pulSrc++;
  for (pulDest = &_bss; pulDest < &_ebss;)
    *pulDest++ = 0;

  WinMain();
}

void pendsv_isr(void)
{
}

void svc_isr(void)
{
}

void systick_isr(void)
{
}

void int_isr(void)
{
}


typedef void (*pfnISR)(void);

 __attribute__((section(".ccm")))
static u8 stack[STACK_SIZE];

__attribute__((section(".isr_vector")))
pfnISR VectorTable[]=
{
  (pfnISR)((unsigned long)stack + STACK_SIZE),
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
  systick_isr, // 15
};

#endif
