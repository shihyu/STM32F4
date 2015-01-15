#include "stm32.h"

#include "my_setjmp.h"


void ff();


int main(void)
{
  jmp_buf mark;

  ff();
  int i=0;
  int ret = my_setjmp(mark);
  ++i;
  while(1)
  {
    i=10;
    my_longjmp(mark, 5);
  }
  return 0;
}

void ff()
{
 int i=5;
}
