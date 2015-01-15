#include "stm32.h"

#include <stdarg.h>

int print(int i, int j)
{
  return i+j;
}

int myprintf(const char *fmt, ...)
{
  va_list ap;
  //int d;
  char *cur;

  cur = (char *)&fmt;
  cur += 4;
  cur += 4;

#if 0
  __builtin_va_start(ap,fmt);
  __builtin_va_arg(ap, char *);
  __builtin_va_arg(ap, int);
  __builtin_va_arg(ap, char *);
  __builtin_va_arg(ap, char *);
  __builtin_va_arg(ap, char *);
  __builtin_va_arg(ap, char *);
  __builtin_va_end(ap);
#endif
  return 0;
}

void mymain(void)
{
  myprintf("abc", 1, 2);
  print(1, 2);
  myprintf("abc", 1, 2, 3, 4, 5, 6, 7, 8);

  while(1);
}

