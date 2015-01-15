#ifndef K_STDIO_H
#define K_STDIO_H

#include <stdarg.h>

#ifdef P103
#include "stm32f10x.h"
#define BACKSPACE 127
#else
#include "stm32f4xx_usart.h"
#define BACKSPACE 8
#endif

#include "type.h"
#include "gdeque.h"

#define ENTER '\r'

#define UP_KEY 0xff01
#define DOWN_KEY 0xff02
#define LEFT_KEY 0xff03
#define RIGHT_KEY 0xff04

namespace DS
{
  void myprint(const char *str);
  void myprint(int num, int base=10);
  void myprint_float(float num);
  void send_byte(u8 b);
  int ungetch(int c);
  int getchar();
  int getch(); // no buffer
  int ungetc(int c);
  int read_char();
  char *gets(char *s, int size);
  void go_right();
  void go_left();
  void go_left(int time);
  void go_up();
  void go_down();
  int sprintf(char *str, const char *fmt, ...);
  int vsprintf(char *str, const char *fmt, va_list ap);
  int printf(const char *fmt, ...);
}

//extern MyDeque mydeque;
extern DS::Deque<int> mydeque;

#endif
