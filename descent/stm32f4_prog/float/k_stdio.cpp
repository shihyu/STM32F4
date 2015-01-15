#include "k_stdio.h"
#include "k_string.h"

#include "stm32f4xx_usart.h"

void send_byte(u8 b)
{
  /* Send one byte */
  USART_SendData(USART2, b);

  /* Loop until USART2 DR register is empty */
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void myprint(const char *str)
{
  const char *p = str;
  while(*p)
    send_byte(*p++);
}

void myprint(int num)
{
  char str[10];
  s32_itoa_s(num, str, 10);
  myprint(str);
}

void myprint_float(float num)
{
  u8 *str = float_to_str(num);
  myprint((const char*)str);
}

int read_char()
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
  return (USART_ReceiveData(USART2) & 0x7F);
}

