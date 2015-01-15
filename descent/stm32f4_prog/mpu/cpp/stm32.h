#ifndef STM32_H
#define STM32_H

#include "type.h"

#define SYSTEM_HANDLER_CTRL_STATE_REG_ADDR 0xe000ed24
#define SYSTEM_HANDLER_CTRL_STATE_REG (*((u32 volatile *)SYSTEM_HANDLER_CTRL_STATE_REG_ADDR))

#define STACK_SIZE 64
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

extern "C"
{
  void mymain(void);
}

void ResetISR(void)
{
  unsigned long *pulSrc, *pulDest;

  pulSrc = &_etext;
  for (pulDest = &_data; pulDest < &_edata;)
    *pulDest++ = *pulSrc++;
  for (pulDest = &_bss; pulDest < &_ebss;)
    *pulDest++ = 0;


  mymain();
}

void pendsv_isr(void)
{
  int i=5;

  ++i;
}

void svc_isr(void)
{
}

void systick_isr(void)
{
}

void mm_isr(void)
{
  int ii=6;
  //SYSTEM_HANDLER_CTRL_STATE_REG &= (~(1 << 16));
}

void hard_fault_isr(void)
{
  //watch 0xe000ed04
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
  hard_fault_isr,
  mm_isr,
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
