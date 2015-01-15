#include "process.h"


int cur_proc_num = 0;

void Process::init_proc(char *stack_ptr, FuncPtr fptr)
{
  stack_pointer = stack_ptr;
  *((int*)(stack_pointer + 14*4)) = *((int *)(&(fptr))); // setup pc
  *((int*)(stack_pointer + 15*4)) = 0x21000000; // setup psr
  if (cur_proc_num <= MAX_PROC_NUM)
    pid_ = cur_proc_num++;
}

void Process::init_proc(char *stack_ptr)
{
  for (int i=0 ; i < 16 ; ++i)
  {
    *stack_pointer++ = *stack_ptr++;
  }
  if (cur_proc_num <= MAX_PROC_NUM)
    pid_ = cur_proc_num++;
}

Process *ready_process;

