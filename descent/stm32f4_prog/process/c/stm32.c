#include "stm32.h"


extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;


#define STACK_SIZE 64
typedef void (*pfnISR)(void);
__attribute__((section(".stackares")))
static unsigned long pulStack[STACK_SIZE];

void ResetISR(void)
{
  unsigned long *pulSrc, *pulDest;

  pulSrc = &_etext;
  for (pulDest = &_data; pulDest < &_edata;)
    *pulDest++ = *pulSrc++;
  for (pulDest = &_bss; pulDest < &_ebss;)
    *pulDest++ = 0;

  void mymain(void);
  mymain();
}

void svc_isr(void)
{
}

void systick_isr(void)
{
  // pendsv set:
  //ref: @ Cortex™-M3 Technical Reference Manual (file name: DDI0337E_cortex_m3_r1p1_trm.pdf) p8-19
  *( unsigned long *) 0xE000ED04 |= 0x10000000;
}

void int_isr(void)
{
  int i=6;
  ++i;
}

void pendsv_isr(void);

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
