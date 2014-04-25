#ifndef UART_H
#define UART_H

#include <sys/types.h>
#include <reent.h>

extern void  uart_init(int baudrate);
extern void  uart_poll_send(const char *s);
extern int   uart_chars_avail(void);

extern ssize_t uart_write_r(struct _reent *r, int fd, const void *ptr, size_t len);
extern ssize_t uart_read_r(struct _reent *r, int fd, void *ptr, size_t len);

#endif
