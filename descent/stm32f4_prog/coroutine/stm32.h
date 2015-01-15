#ifndef STM32_H
#define STM32_H

//#include "lib_mygpio_led.h"

#define STACK_SIZE_ 64
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


void wwdg_isr(void)
{
  int b=33;
}
void pvd_isr(void)
{
}
void tamp_stamp_isr(void)
{
}

void rtc_wkup_isr(void)
{
}
void flash_isr(void)
{
}
void rcc_isr(void)
{
}

void user_button_isr(void);

typedef void (*pfnISR)(void);
__attribute__((section(".stackares")))
static unsigned long pulStack[STACK_SIZE_];


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
  systick_isr, // 15

  // External Interrupts
  wwdg_isr,                   // Window WatchDog
  pvd_isr,                   // PVD through EXTI Line detection                      
  tamp_stamp_isr,            // Tamper and TimeStamps through the EXTI line
  rtc_wkup_isr,              // RTC Wakeup through the EXTI line                     
  flash_isr,                 // FLASH                                           
  rcc_isr,                   // RCC                                             
  user_button_isr            // EXTI Line0 
};

#endif
