// cs means context switch

//#include "type.h"
#include "lib_mygpio_led.h"
#include "libur_168M.h"
#include "asm_func.h"

void proc_a()
{
  ur_puts(USART2, "proc a\r\n");
  while(1)
  {
  #if 0
    int j=0;
    ++j;
  #else
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    //GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    ur_puts(USART2, "aaa\r\n");
    Delay(0x3FFFFF);
    /* Insert delay */
  #endif
  }
}

void proc_b()
{
  ur_puts(USART2, "proc b\r\n");
  while(1)
  {
  #if 0
    int i=0;
    ++i;
  #else
    GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    //GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    ur_puts(USART2, "bbb\r\n");
    Delay(0x3FFFFF);
  #endif
  }
}
void proc_c()
{
  ur_puts(USART2, "proc c\r\n");
  while(1)
  {
  #if 0
    int i=0;
    ++i;
  #else
    //GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    //GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    GPIO_SetBits(GPIOD, GPIO_Pin_13);
    ur_puts(USART2, "ccc\r\n");
    Delay(0x3FFFFF);
  #endif
  }
}

typedef struct Process_
{
  void (*exec)(void);
  char *stack_pointer;  
}Process;

Process *ready_process;

#define NR_NATIVE_PROCS 3
#define A_PROC_STACK 0x400
#define PROC_STACK (A_PROC_STACK*NR_NATIVE_PROCS)
char proc_stack[PROC_STACK];

Process user_proc_table[NR_NATIVE_PROCS] =
{
  {proc_a, 0},
  {proc_b, 0},
  {proc_c, 0},
};

void init_proc(void)
{
  for (int i=0 ; i < NR_NATIVE_PROCS ; ++i)
  {
    user_proc_table[i].stack_pointer = proc_stack + A_PROC_STACK*(i+1) - 16*4;
    *((int*)(user_proc_table[i].stack_pointer + 14*4)) = *((int *)(&(user_proc_table[i].exec))); // setup pc
    *((int*)(user_proc_table[i].stack_pointer + 15*4)) = 0x21000000; // setup psr
  }
}

void init_isr_priority()
{
  // pendsv priority
  *( unsigned long *) 0xE000ED22 |= 0xff;

  // systick priority
  *( unsigned long *) 0xE000ED23 |= 0xff;

  // svc priority
  *( unsigned long *) 0xE000ED1f |= 0xff;
}

void mymain(void)
{
  init_usart(115200);
  ur_puts(USART2, "Init complete! Hello World!\r\n");
  init_led();
  init_proc();
  init_isr_priority();
  ready_process = &user_proc_table[0];
  run(ready_process->stack_pointer);

  while(1);
}

u32* schedule(u32* sp)
{
#if 0
  if (ready_process->exec == proc_a)
    GPIO_ResetBits(GPIOD, GPIO_Pin_13|GPIO_Pin_14);
  if (ready_process->exec == proc_b)
    GPIO_ResetBits(GPIOD, GPIO_Pin_13|GPIO_Pin_15);
  if (ready_process->exec == proc_c)
    GPIO_ResetBits(GPIOD, GPIO_Pin_14|GPIO_Pin_15);
#endif
  ready_process->stack_pointer = sp;
  ++ready_process;
  if (ready_process >= user_proc_table+NR_NATIVE_PROCS)
    ready_process = user_proc_table;
  return ready_process->stack_pointer;
}

