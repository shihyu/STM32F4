// cs means context switch

//#include "type.h"
#include "lib_mygpio_led.h"
#include "libur_168M.h"
#include "asm_func.h"
#include "syscall.h"
#include "process.h"

//#include <cstdio>
//using namespace std;

void proc_a();

//Process user_proc_table[NR_NATIVE_PROCS] =
Process user_proc_table[MAX_PROC_NUM] =
{
  {proc_a, 0},
//  {proc_b, 0},
//  {proc_c, 0},
};

const int NR_NATIVE_PROCS = sizeof(user_proc_table)/sizeof(Process);

#define A_PROC_STACK 0x400
#define PROC_STACK (A_PROC_STACK*NR_NATIVE_PROCS)
char proc_stack[PROC_STACK];


void proc_a()
{
  //printf("abc");
  //ur_puts(USART2, "proc a\r\n");
  while(1)
  {
    int i=0;

    if (i==2)
    {
      user_proc_table[cur_proc_num].init_proc(user_proc_table[0].stack_pointer);
    }
    ++i;
    //int t = get_ticks();

  #if 0
    int j=0;
    ++j;
  #else
    #if 0
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    //GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    ur_puts(USART2, "aaa\r\n");
    Delay(0x3FFFFF);
    #endif
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

void init_proc(void)
{
  for (int i=0 ; i < cur_proc_num ; ++i)
  {
    user_proc_table[i].init_proc(proc_stack + A_PROC_STACK*(i+1) - 16*4, user_proc_table[i].exec);
    #if 0
    user_proc_table[i].stack_pointer = proc_stack + A_PROC_STACK*(i+1) - 16*4;
    *((int*)(user_proc_table[i].stack_pointer + 14*4)) = *((int *)(&(user_proc_table[i].exec))); // setup pc
    *((int*)(user_proc_table[i].stack_pointer + 15*4)) = 0x21000000; // setup psr
    #endif
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

extern "C"
{
  void mymain(void);
  char* schedule(char* sp);
  void save_cur_proc_stack(char *sp);
  char* restore_cur_proc_stack();
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

void save_cur_proc_stack(char *sp)
{
  ready_process->stack_pointer = sp;
}

char* restore_cur_proc_stack()
{
  return ready_process->stack_pointer;
}

char* schedule(char* sp)
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

