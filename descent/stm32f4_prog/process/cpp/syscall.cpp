#include "asm_syscall.h"

typedef void* SystemCall;

struct Arg
{
  int ret;
};

typedef void (*FuncPtr)(Arg *);

void sys_vfork(Arg *arg)
{

}

void sys_get_ticks(Arg *arg)
{
  extern int ticks;

  arg->ret = ticks;
  //return ticks;
}

// ref: http://www.coactionos.com/embedded-design/133-effective-use-of-arm-cortex-m3-svcall.html
int service_call(FuncPtr func_ptr, Arg *arg)
{
  __asm__ volatile("svc 0");
}

int get_ticks()
{
  Arg arg;

  service_call(sys_get_ticks, &arg);
  return arg.ret;
}

int vfork()
{
  Arg arg;

  service_call(sys_vfork, &arg);
  return arg.ret;
}

SystemCall sys_call_table[NR_SYS_CALL] = {(void*)sys_get_ticks};

