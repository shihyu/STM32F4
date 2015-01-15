#include "stm32.h"

int f1(int a, int b, int c, int d, int e, int f)
{
  return a+b+c+d+e;
}

int ff(int i)
{
//  i+=5;
//  f1(1,2,3,4, 5, 6); 
}

int main(void)
{
  ff(5);
  int i=0;
  int a,b,c;
  if (i==0)
  {
    a=1;
    b=2;
    c=3;
  }
  else
  {
    a=11;
    b=22;
    c=33;
  }
  return 0;
}
