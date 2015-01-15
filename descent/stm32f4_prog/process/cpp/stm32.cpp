#include "stm32.h"
#include "asm_func.h"
#include "process.h"

extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;


#define STACK_SIZE 64
typedef void (*pfnISR)(void);
__attribute__((section(".stackares")))
static unsigned long pulStack[STACK_SIZE];

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

#if 0
void svc_isr(void)
{
  extern Process *ready_process;
  extern char *kernel_stack;
  int tmp;

  __asm__ volatile ("cpsid i"); // Prevent interruption during svc
  __asm__ volatile ("push {r4-r11}");
  __asm__ volatile ("mov r0, sp");

  // save sp to current process
  __asm__ volatile ("mov %0, sp\n"
                     :"=r"(ready_process->stack_pointer)
                     :
                     :
                   );


  __asm__ volatile ("mov r1, %0\n"
                     :
                     : "r"(kernel_stack)
                     :
                   );

  __asm__ volatile ("mov sp, r1");
  __asm__ volatile ("push {lr}");




}
#endif

int ticks;
void systick_isr(void)
{
  ++ticks;
  // pendsv set:
  //ref: @ Cortex™-M3 Technical Reference Manual (file name: DDI0337E_cortex_m3_r1p1_trm.pdf) p8-19
  *( unsigned long *) 0xE000ED04 |= 0x10000000;
}

void int_isr(void)
{
  int i=6;
  ++i;
}


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
