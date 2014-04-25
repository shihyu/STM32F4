#include "uart.h"
#include "stm32f4xx.h"
#include "ringbuf.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define RX_SIZE  128
#define TX_SIZE  128

static struct ringbuf rx_buf = { .buf = (char[RX_SIZE]) {}, .bufsize = RX_SIZE };
static struct ringbuf tx_buf = { .buf = (char[TX_SIZE]) {}, .bufsize = TX_SIZE };

static volatile struct uart_stats {
    uint32_t    rx_overrun;
    uint32_t    rx_bytes;
    uint32_t    tx_bytes;
} uart_stats;


void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE) {
        if (!rb_putc(&rx_buf, USART1->DR))
            uart_stats.rx_overrun++;
        else
            uart_stats.rx_bytes++;
    }

    if (USART1->SR & USART_SR_TXE) {
        char c;
        if (rb_getc(&tx_buf, &c)) {
            // send a queued byte
            //
            USART1->DR = c;
        }
        else {
            // nothing to send, disable interrupt
            //
            USART1->CR1 &= ~USART_CR1_TXEIE;
        }
        uart_stats.tx_bytes++;
    }
}


int uart_chars_avail(void)
{
    return rx_buf.len;
}


ssize_t uart_write_r(struct _reent *r, int fd, const void *ptr, size_t len)
{
    const char *c = (const char*) ptr;

    for (int i = 0; i < len; i++) {
        while (!rb_putc(&tx_buf, *c));
        c++;

        // Enable TX empty interrupt
        USART1->CR1 |= USART_CR1_TXEIE;
    }

    return len;
}

ssize_t uart_read_r(struct _reent *r, int fd, void *ptr, size_t len)
{
    while (!rx_buf.len);

    if (len > rx_buf.len)
        len = rx_buf.len;

    char *c = (char*)ptr;
    for (int i = 0; i < len; i++)
        rb_getc(&rx_buf, c++);

    return len;
}


void uart_poll_send(const char *ch)
{
    while (*ch) {
        USART1->DR = *ch++ & 0xff;
        while (!(USART1->SR & USART_FLAG_TXE));
        uart_stats.tx_bytes++;
    }
}

/**
 * Initialize UART.
 *
 * \param  baudrate  Baudrate
 *
 *  PB6   USART1_TXD
 *  PB7   USART1_RXD
 *
 */
void uart_init(int baudrate)
{
    // Enable peripheral clocks
    //
    RCC->AHB1ENR |= RCC_AHB1Periph_GPIOB;
    RCC->APB2ENR |= RCC_APB2Periph_USART1;

    // Initialize Serial Port
    //
    GPIO_Init(GPIOB, &(GPIO_InitTypeDef) {
        .GPIO_Pin   = GPIO_Pin_6,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode  = GPIO_Mode_AF,
        .GPIO_OType = GPIO_OType_PP
    });

    GPIO_Init(GPIOB, &(GPIO_InitTypeDef) {
        .GPIO_Pin = GPIO_Pin_7,
        .GPIO_Mode = GPIO_Mode_IN,
        .GPIO_PuPd = GPIO_PuPd_UP
    });

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

    USART_Init(USART1, &(USART_InitTypeDef) {
        .USART_BaudRate = baudrate,
        .USART_WordLength = USART_WordLength_8b,
        .USART_StopBits = USART_StopBits_1,
        .USART_Parity = USART_Parity_No ,
        .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        .USART_Mode = USART_Mode_Rx | USART_Mode_Tx
    });

    NVIC_Init(&(NVIC_InitTypeDef) {
        .NVIC_IRQChannel = USART1_IRQn,
        .NVIC_IRQChannelPreemptionPriority = configLIBRARY_KERNEL_INTERRUPT_PRIORITY,
        .NVIC_IRQChannelSubPriority = 0,
        .NVIC_IRQChannelCmd = ENABLE
    });

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

/*
// -------------------- Shell commands --------------------
//
static void cmd_baudrate(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <baudrate>\n", argv[0]);
        return;
    }

    uart_init(atoi(argv[1]));
}

static void cmd_uart_stats(void)
{
    printf("rx_bytes:   %8lu\n", uart_stats.rx_bytes);
    printf("rx_overrun: %8lu\n", uart_stats.rx_overrun);
    printf("tx_bytes:   %8lu\n", uart_stats.tx_bytes);
}


SHELL_CMD(baudrate,   (cmdfunc_t)cmd_baudrate,   "set baudrate")
SHELL_CMD(uart_stats, (cmdfunc_t)cmd_uart_stats, "show UART statistics")
*/
