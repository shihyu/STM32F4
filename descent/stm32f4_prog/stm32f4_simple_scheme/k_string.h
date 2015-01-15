#ifndef STRING_H
#define STRING_H

#include "type.h"

#if 0
// kernel loader part function
void asm_memcpy(u8 *dest, u8 *src, int n);
void asm_seg_memcpy(u8 *dest, u8 *src, int n, u16 fs);
void asm_absolute_memcpy(u8 *dest, u8 *src, int n);
#endif

// prefix s is simple; 32 means in protoected mode
static inline u32 s_strlen(const char *s)
{
  u8 len=0;

  while(*s++)
    ++len;
  return len;
}

static inline char* s_strcpy(char *dest, const char *src)
{
  char *p = dest;
  while(*src)
    *dest++ = *src++;
  *dest='\0';
  return p;
}

static inline char* s_strncpy(char *dest, const char *src, int n)
{
  char *p = dest;
  int i=0;
  while(*src)
  {
    *dest++ = *src++;
    ++i;
    if (i >= n)
      break;
  }
  *dest='\0';
  return p;
}

static inline int s_strcmp(const char *s1, const char *s2)
{
  s8 res;
  while(1)
    if ((res = *s1 - *s2++) != 0 || !*s1++)
      break;
  return res;
}

static inline int s_memcmp(const char *s1, const char *s2, int n)
{
  if ((s1 == 0) || (s2 == 0)) 
  { /* for robustness */
    return (s1 - s2);
  }

  const char * p1 = (const char *)s1;
  const char * p2 = (const char *)s2;
  int i;
  for (i = 0; i < n; i++,p1++,p2++) 
  {
    if (*p1 != *p2) 
    {
      return (*p1 - *p2);
    }
  }
  return 0;
}

// sign version
static inline char* s32_itoa_s(int n, char* str, int radix)
{
  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char* p=str;
  char* head=str;
  //int radix = 10;

//  if(!p || radix < 2 || radix > 36)
//    return p;
  if (n==0)
  {
    *p++='0';
    *p=0;
    return str;
  }
  if (radix == 10 && n < 0)
  {
    *p++='-';
    n= -n;
  }
  while(n)
  {
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;
  #if 1
  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    if (*(p-1) != '-')
    {
      *head=*p;
      *p=temp;
    }
  }
  #endif
  return str;
}

// no sign version
static inline u8* s32_itoa(u32 n, u8* str, int radix)
{
  char digit[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  u8* p=str;
  u8* head=str;
  //int radix = 10;

//  if(!p || radix < 2 || radix > 36)
//    return p;
  if (n==0)
  {
    *p++='0';
    *p=0;
    return str;
  }
  if (radix == 10 && n < 0)
  {
    *p++='-';
    n= -n;
  }
  while(n)
  {
    *p++=digit[n%radix];
    //s32_put_char(*(p-1), (u8*)(0xb8000+80*2));
    n/=radix;
  }
  *p=0;
  #if 1
  for (--p; head < p ; ++head, --p)
  {
    char temp=*head;
    if (*(p-1) != '-')
    {
      *head=*p;
      *p=temp;
    }
  }
  #endif
  return str;
}

static inline int s32_sprintf(char *str_buf, const char *fmt, ...)
{
  int i=1;
  char *p = str_buf;

  for (; *fmt ; ++fmt)
  {
    if (*fmt != '%')
    {
      *p++ = *fmt;
      continue;
    }
    ++fmt;
    u8 *arg = (u8 *)(&fmt + i); // nst argument address
    u32 arg_content = *((u32*)arg);

    switch (*fmt)
    {
      case 'd':
      {
        u8 str[12]="";
        s32_itoa(arg_content, str, 10);

        u8 *str_ptr = str;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      case 'x':
      {
        u8 str[12]="";
        s32_itoa(arg_content, str, 16);

        u8 *str_ptr = str;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      case 's':
      {
        char *str_ptr = (char *)arg_content;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      default:
        break;
    }
    ++i; // point to next argument
 
  } // end for (char *p = buf; *fmt ; ++fmt, ++i)
  *p='\0';
  return p-str_buf - 1;
}

static inline int atoi(const char *s)
{
  // ref: http://blog.csdn.net/wxhhkhl/article/details/6142289
  int n=0,i;

  if (s[0] == '-')
    i = 1;
  else
    i = 0;

  for(; s[i]>='0' && s[i]<='9';i++)
    n=n*10+s[i]-'0';

  if (s[0] == '-')
    return -n;
  else
    return n;
}

static inline bool isdigit(int c)
{
  if ('0' <= c && c <= '9')
    return true;
  else
    return false;
}

static inline int mypow(int x, int y)
{
  int r=1;
  for (int i=0 ; i < y ; ++i)
    r*=x;
  return r;
}

const int PRECISION = 6;

static inline u8* float_to_str(float num)
{
   int whole_part = num;
   int digit = 0, reminder =0;
   //int log_value = log10(num), 
   int index;
   float wt = 0.0;

   // String containg result
   static u8 str[30];

   //Initilise stirng to zero
   //memset(str, 0 ,20);
   
   //u8 whole_str[20] ;
   s32_itoa(whole_part, str, 10);
#if 0
   //Extract the whole part from float num
   for(int  i = 1 ; i < log_value + 2 ; i++)
   {
       wt  =  mypow(10,i);
       reminder = whole_part  %  wt;
       digit = (reminder - digit) / (wt/10);

       //Store digit in string
       str[index--] = digit + 48;              // ASCII value of digit  = digit + 48
       if (index == -1)
          break;    
   }
#endif
    //index = log_value + 1;
    index = s_strlen((const char*)str);
    str[index] = '.';

   float fraction_part  = num - whole_part;
   float tmp1 = fraction_part,  tmp =0;

#if 0
   cout << "fraction_part: " << fraction_part << endl;
   cout << "num: " << num << endl;
   cout << "whole_part: " << whole_part << endl;
#endif
   //Extract the fraction part from  num
   for( int i= 1; i < PRECISION; i++)
   {
      wt =10; 
      tmp  = tmp1 * wt;
      digit = tmp;
      //cout << "digit: " << digit << endl;
      //cout << "tmp: " << tmp << endl;
      //cout << "tmp1: " << tmp1 << endl;

      //Store digit in string
      str[++index] = digit +48;           // ASCII value of digit  = digit + 48
      tmp1 = tmp - digit;
      if (tmp1 == 0.0)
        break;
   }    
   str[index+1] = 0;

   return str;
}


#endif
