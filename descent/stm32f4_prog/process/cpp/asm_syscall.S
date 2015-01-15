#include "asm_syscall.h"
.text
.global _start
.code 16
.syntax unified

@ int get_tick();
.type get_tick, function
.global get_tick
get_tick:
  svc _NR_GET_TICKS
  bx lr

