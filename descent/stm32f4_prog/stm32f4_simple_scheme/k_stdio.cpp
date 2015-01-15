#include "k_stdio.h"
#include "k_string.h"



void DS::go_up()
{
  send_byte(27);
  send_byte(91);
  send_byte('A');
}

void DS::go_down()
{
  send_byte(27);
  send_byte(91);
  send_byte('B');
}

void DS::go_right()
{
  send_byte(27);
  send_byte(91);
  send_byte('C');
}

void DS::go_left()
{
  send_byte(27);
  send_byte(91);
  send_byte('D');
}

void DS::go_left(int time)
{
  for (int i=0 ; i < time ; ++i)
    go_left();
}

void DS::send_byte(u8 b)
{
  /* Send one byte */
  USART_SendData(USART2, b);

  /* Loop until USART2 DR register is empty */
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void DS::myprint(const char *str)
{
  const char *p = str;
  while(*p)
    send_byte(*p++);
}

void DS::myprint(int num, int base)
{
  char str[10];
  s32_itoa_s(num, str, base);
  myprint(str);
}

void DS::myprint_float(float num)
{
  u8 *str = float_to_str(num);
  myprint((const char*)str);
}


DS::Deque<int> mydeque;

int DS::ungetch(int c)
{
#if 0
  myprint("\r\nun: ");
  myprint(c);
  myprint("\r\n");
  keep_char = c;
#endif
  mydeque.push_front(c);
  return 0;
}

int DS::read_char()
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
  return (USART_ReceiveData(USART2) & 0x7F);
}


int DS::getchar()
{
  int b;

  if (mydeque.empty())
  {
    while(1)
    {

    b = read_char();

    switch (b)
    {
      case BACKSPACE: // backspace
      {
        if (mydeque.empty())
          break;

        send_byte(8);
        send_byte(' ');
        send_byte(8);
        mydeque.pop_back(b);
        break;
      }
#if 0
      case '\n':
      {
        break;
      }
#endif
      default:
      {
        if (b == '\r') // enter
        {
          myprint("\r\n");
          mydeque.push_back(b);
          goto end;
        }
        else
          send_byte(b);

        mydeque.push_back(b);
        break;
      }
    }
      if (mydeque.full())
        break;
    }

  }

end:
    int ch;
    mydeque.pop_front(ch);
    return ch;
}

char *DS::gets(char *s, int size)
{
  int i=0;
  for(; i < size-1; ++i)
  {
    s[i] = getchar();
    if (s[i] == ENTER)
      break;
  }
  s[i] = 0;
  return s;
}

int keep_char = -1;

int DS::getch()
{
  int ch;

  if (keep_char != -1)
  {
    ch = keep_char;
    keep_char = -1;
    send_byte(ch);
    return ch;
  }

  ch = DS::read_char();

  switch (ch)
  {
    case 27:
    {
      ch = DS::read_char();
      if (ch == '[')
      {
        ch = DS::read_char();
        switch (ch)
        {
          case 'A': // up
          {
            return UP_KEY;
          }
          case 'B': // down
          {
            return DOWN_KEY;
          }
          case 'C': // right
          {
            return RIGHT_KEY;
          }
          case 'D': // left
          {
            return LEFT_KEY;
          }
          default:
          {
            DS::ungetc(ch); 
            break;
          }
        }
      }
      else
      {
        DS::ungetc(ch);
      }
    }
    case BACKSPACE:
    {
      break;
    }
    case ENTER:
    {
      send_byte('\r');
      send_byte('\n');
      break;
    }
    default:
    {
      send_byte(ch);
      break;
    }
  }

  return ch;
}

int DS::ungetc(int c)
{
  keep_char = c;
}



// ref: http://blog.csdn.net/slvher/article/details/9881171
int DS::vsprintf(char *str, const char *fmt, va_list ap)
{
#if 0
  int d;
  char c, *p, *s;  
  char *cur_char = str;
  int len = 0;

  __builtin_va_start(ap,fmt);
  while(*fmt)
  {
    if (*fmt == '%')
    {
      ++fmt;
      switch(*fmt)
      {  
        case 's':
        {
          s = __builtin_va_arg(ap, char *);  
          len = s_strlen(s);
          s_strcpy(cur_char, s);
          cur_char += len;
          break;
        }
        case 'd':
        {
          d = __builtin_va_arg(ap, int);
          char num_str[10];
          s32_itoa_s(d, num_str, 10);
          len = s_strlen(num_str);
          s_strcpy(cur_char, num_str);
          cur_char += len;
          break;
        }
        case 'c':
        {
          d = (char)__builtin_va_arg(ap, int);
          *cur_char++ = d;
          break;
        }
        default:
        {
          *cur_char++ = *fmt;
        }
      }
    }
    else
    {
      *cur_char++ = *fmt;
    }
    ++fmt;
  }

  __builtin_va_end(ap);
  len = s_strlen(str);
  return len;
#endif
}

int DS::sprintf(char *str, const char *fmt, ...)
{
  va_list ap;

  int d;
  char c, *p, *s;  
  char *cur_char = str;
  int len = 0;

  __builtin_va_start(ap,fmt);
  while(*fmt)
  {
    if (*fmt == '%')
    {
      ++fmt;
      switch(*fmt)
      {  
        case 's':
        {
          s = __builtin_va_arg(ap, char *);  
          len = s_strlen(s);
          s_strcpy(cur_char, s);
          cur_char += len;
          break;
        }
        case 'd':
        {
          d = __builtin_va_arg(ap, int);
          char num_str[10];
          s32_itoa_s(d, num_str, 10);
          len = s_strlen(num_str);
          s_strcpy(cur_char, num_str);
          cur_char += len;
          break;
        }
        case 'c':
        {
          d = (char)__builtin_va_arg(ap, int);
          *cur_char++ = d;
          break;
        }
        default:
        {
          *cur_char++ = *fmt;
        }
      }
    }
    else
    {
      *cur_char++ = *fmt;
    }
    ++fmt;
  }
  __builtin_va_end(ap);

  *cur_char++ = 0;
  len = s_strlen(str);
  return len;
}

int DS::printf(const char *fmt, ...)
{
  va_list ap;

  char str[256];

  int d;
  char c, *p, *s;  
  char *cur_char = str;
  int len = 0;

  __builtin_va_start(ap,fmt);
  while(*fmt)
  {
    if (*fmt == '%')
    {
      ++fmt;
      switch(*fmt)
      {  
        case 's':
        {
          s = __builtin_va_arg(ap, char *);  
          len = s_strlen(s);
          s_strcpy(cur_char, s);
          cur_char += len;
          break;
        }
        case 'd':
        {
          d = __builtin_va_arg(ap, int);
          char num_str[10];
          s32_itoa_s(d, num_str, 10);
          len = s_strlen(num_str);
          s_strcpy(cur_char, num_str);
          cur_char += len;
          break;
        }
        case 'c':
        {
          d = (char)__builtin_va_arg(ap, int);
          *cur_char++ = d;
          break;
        }
        default:
        {
          *cur_char++ = *fmt;
        }
      }
    }
    else
    {
      if (*fmt == '\n')
      {
        s_strcpy(cur_char, "\r\n");
        cur_char += 2;
      }
      else
        *cur_char++ = *fmt;
    }
    ++fmt;
  }

  __builtin_va_end(ap);
  *cur_char++ = 0;
  len = s_strlen(str);
  myprint(str);
  return len;
}
