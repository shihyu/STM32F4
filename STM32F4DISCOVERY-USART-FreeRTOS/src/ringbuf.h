#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdlib.h>
#include <string.h>
#include "stm32f4xx.h"
#include "FreeRTOS.h"

/**
 * Ringbuffer structure
 *
 */
struct ringbuf {
    char *buf;          ///< Pointer to buffer memory
    int   bufsize;      ///< Size of buffer memory
    volatile int pos;   ///< Current read position
    volatile int len;   ///< Length of data in buffer
};


/**
 * Allocate buffer memory
 *
 * \param   rb      pointer to ringbuffer struct
 * \param   bufsize requested buffer size
 * \return  size of allocated buffer
 */
static inline int rb_alloc(struct ringbuf *rb, int bufsize)
{
    rb->buf = malloc(bufsize);
    if (!rb->buf)
        bufsize = 0;

    rb->bufsize = bufsize;
    rb->pos = 0;
    rb->len = 0;

    return rb->bufsize;
}


/**
 * Free buffer memory
 *
 */
static inline void rb_free(struct ringbuf *rb)
{
    if (rb->buf)
        free(rb->buf);

    rb->buf = 0;
    rb->bufsize = 0;
    rb->len = 0;
    rb->pos = 0;
}


/**
 * Read a single byte from a buffer
 *
 * \param   rb    pointer to ringbuffer struct
 * \param   data  pointer to data byte
 * \return  number of bytes read (0 if buffer was empty)
 */
static inline int rb_getc(struct ringbuf *rb, char *data)
{
    if (!rb->len)
        return 0;

    vPortEnterCritical();

    *data = rb->buf[rb->pos++];
	if (rb->pos >= rb->bufsize)
		rb->pos -= rb->bufsize;
	rb->len--;

    vPortExitCritical();
    return 1;
}


/**
 * Write a single byte to a buffer
 *
 * \param   rb    pointer to ringbuffer struct
 * \param   data  pointer to data byte
 * \return  number of bytes written (0 if buffer was full)
 */
static inline int rb_putc(struct ringbuf *rb, const char data)
{
    if (rb->len >= rb->bufsize)
        return 0;

    vPortEnterCritical();

	int i = rb->pos + rb->len;
	if (i >= rb->bufsize)
		i -= rb->bufsize;

	rb->buf[i] = data;
	rb->len++;

    vPortExitCritical();
    return 1;
}


#if 0
/**
 * Read from a buffer
 *
 */
int rb_read(struct ringbuf *rb, void *data, int len)
{
    if (len > rb->len)
        len = rb->len;

    int len1 = len;
    if (rb->pos + len1 >= rb->bufsize) {
        int len2 = (rb->pos + len1) - rb->bufsize;
        len1 -= len2;
        memcpy((char*)data + len1, rb->buf, len2);
    }
    memcpy(data, rb->buf + rb->pos, len1);

    rb->len -= len;
    rb->pos += len;
    if (rb->pos > rb->bufsize)
        rb->pos -= rb->bufsize;

    return len;
}


/**
 * Write to a buffer
 *
 * \param   rb    pointer to ringbuffer struct
 * \param   data  pointer to data byte
 * \return  number of bytes written (0 if buffer was full)
 *
 */
int rb_write(struct ringbuf *rb, const void *data, int len)
{
    if (len > rb->bufsize - rb->len)
        len = rb->bufsize - rb->len;

    int len1 = len;
    if (rb->pos + rb->len + len1 >= rb->bufsize) {
        int len2 = (rb->pos + rb->len + len1) - rb->bufsize;
        len1 -= len2;
        memcpy(rb->buf, (char*)data + len1, len2);
    }

    memcpy(rb->buf + rb->pos + rb->len, data, len1);

    rb->len += len;
    return len;
}
#endif

#endif
