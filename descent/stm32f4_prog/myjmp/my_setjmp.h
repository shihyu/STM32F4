/*
 * Copyright (C) 1991 DJ Delorie
 * All rights reserved.
 *
 * Redistribution, modification, and use in source and binary forms is permitted
 * provided that the above copyright notice and following paragraph are
 * duplicated in all such forms.
 *
 * This file is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/* Modified to use SETJMP_DJ_H rather than SETJMP_H to avoid
   conflicting with setjmp.h.  Ian Taylor, Cygnus support, April,
   1993.  */

#ifndef MY_SETJMP_H
#define MY_SETJMP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  unsigned long r4;
  unsigned long ebx;
  unsigned long ecx;
  unsigned long edx;
  unsigned long esi;
  unsigned long edi;
  unsigned long ebp;
  unsigned long esp;
  unsigned long eip;
  unsigned long lr;
} jmp_buf[1];

extern int my_setjmp(jmp_buf);
extern void my_longjmp(jmp_buf, int);

#ifdef __cplusplus
}
#endif

#endif
