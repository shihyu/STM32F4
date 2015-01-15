#ifndef LIBUR_168M_H
#define LIBUR_168M_H

void init_usart(uint32_t baudrate);
void ur_puts(USART_TypeDef* USARTx, const char *s);

#endif
