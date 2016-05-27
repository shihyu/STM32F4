/*
 * This program turns on the 4 leds of the stm32f4 discovery board
 * one after another.
 * It defines shortcut definitions for the led pins and
 * stores the order of the leds in an array which is being
 * iterated in a loop.
 *
 * This program is free human culture like poetry, mathematics
 * and science. You may use it as such.
 */

#include <math.h>
#include <string.h>

#include <stm32f4_discovery.h>

#include "mpu6050.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_i2c.h"
#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"


/*
  The 7-bit address of the I2C slave.
  For the MPU6050, this is 0x68 if the AD0 pin is held low, and 0x69 if the
  AD0 pin is held high.
*/
#define MPU6050_I2C_ADDR 0x68


/* This is apparently needed for libc/libm (eg. powf()). */
int __errno;


static void delay(__IO uint32_t nCount)
{
    while(nCount--)
        __asm("nop"); // do nothing
}


static void setup_serial(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* enable peripheral clock for USART3 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* GPIOD Configuration:  USART3 TX on PD8 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect USART3 pins to AF */
  // TX = PD8
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);

  USART_Cmd(USART3, ENABLE); // enable USART3
}


static void
serial_putchar(USART_TypeDef* USARTx, uint32_t c)
{
  while(!(USARTx->SR & USART_FLAG_TC));
  USART_SendData(USARTx, c);
}


static void
serial_puts(USART_TypeDef *usart, const char *s)
{
  while (*s)
    serial_putchar(usart, (uint8_t)*s++);
}


static void
serial_output_hexdig(USART_TypeDef* USARTx, uint32_t dig)
{
  serial_putchar(USARTx, (dig >= 10 ? 'A' - 10 + dig : '0' + dig));
}


static void
serial_output_hexbyte(USART_TypeDef* USARTx, uint8_t byte)
{
  serial_output_hexdig(USARTx, byte >> 4);
  serial_output_hexdig(USARTx, byte & 0xf);
}


__attribute__ ((unused))
static void
println_uint32(USART_TypeDef* usart, uint32_t val)
{
  char buf[13];
  char *p = buf;
  uint32_t l, d;

  l = 1000000000UL;
  while (l > val && l > 1)
    l /= 10;

  do
  {
    d = val / l;
    *p++ = '0' + d;
    val -= d*l;
    l /= 10;
  } while (l > 0);

  *p++ = '\r';
  *p++ = '\n';
  *p = '\0';
  serial_puts(usart, buf);
}


__attribute__ ((unused))
static void
println_int32(USART_TypeDef* usart, int32_t val)
{
  if (val < 0)
  {
    serial_putchar(usart, '-');
    println_uint32(usart, (uint32_t)0 - (uint32_t)val);
  }
  else
    println_uint32(usart, val);
}


static void
float_to_str(char *buf, float f, uint32_t dig_before, uint32_t dig_after)
{
  float a;
  uint32_t d;
  uint8_t leading_zero;

  if (f == 0.0f)
  {
    buf[0] = '0';
    buf[1] = '\0';
    return;
  }
  if (f < 0)
  {
    *buf++ = '-';
    f = -f;
  }
  a =  powf(10.0f, (float)dig_before);
  if (f >= a)
  {
    buf[0] = '#';
    buf[1] = '\0';
    return;
  }
  leading_zero = 1;
  while (dig_before)
  {
    a /= 10.0f;
    d = (uint32_t)(f / a);
    if (leading_zero && d == 0 && a >= 10.0f)
      *buf++ = ' ';
    else
    {
      leading_zero = 0;
      *buf++ = '0' + d;
      f -= d*a;
    }
    --dig_before;
  }
  if (!dig_after)
  {
    *buf++ = '\0';
    return;
  }
  *buf++ = '.';
  do
  {
    f *= 10.0f;
    d = (uint32_t)f;
    *buf++ = '0' + d;
    f -= (float)d;
    --dig_after;
  } while (dig_after);
  *buf++ = '\0';
}


__attribute__ ((unused))
static void
println_float(USART_TypeDef* usart, float f,
              uint32_t dig_before, uint32_t dig_after)
{
  char buf[21];
  char *p = buf;

  float_to_str(p, f, dig_before, dig_after);
  while (*p)
    ++p;
  *p++ = '\r';
  *p++ = '\n';
  *p = '\0';
  serial_puts(usart, buf);
}


/* Event interrupt handler for I2C1. */

static void (*i2c_async_event_handler)(void);

void
I2C1_EV_IRQHandler(void)
{
  void (*handler)(void) = i2c_async_event_handler;
  if (handler)
  {
    (*handler)();
    return;
  }
  serial_putchar(USART3, '!');
  delay(1000000);
}


void
I2C1_ER_IRQHandler(void)
{
  serial_putchar(USART3, 'E');
  delay(1000000);
}


static void (*dma_event_handler)(void);

void
DMA1_Stream0_IRQHandler(void)
{
  void (*handler)(void) = dma_event_handler;
  if (handler)
  {
    (*handler)();
    return;
  }
  serial_putchar(USART3, '|');
  delay(1000000);
}


static uint8_t mpu6050_reg_buffer[14];

static void
setup_i2c_for_mpu6050()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  I2C_InitTypeDef I2C_InitStruct;
  NVIC_InitTypeDef NVIC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  /* Use I2C1, with SCL on PB8 and SDA on PB7. */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Reset the I2C unit. */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

  /* Enable DMA clock for I2C. */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  /* Setup the I/O pins. */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

  /* Initialise DMA. */
  DMA_ClearFlag(DMA1_Stream0,
                DMA_FLAG_TCIF0 | DMA_FLAG_FEIF0 |
                DMA_FLAG_DMEIF0 | DMA_FLAG_TEIF0 |
                DMA_FLAG_HTIF0);

  DMA_Cmd(DMA1_Stream0, DISABLE);
  DMA_DeInit(DMA1_Stream0);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;
  /* Address of data register. */
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C1_BASE + I2C_Register_DR;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)mpu6050_reg_buffer;
  DMA_InitStructure.DMA_BufferSize = 14;
  DMA_DeInit(DMA1_Stream0);
  DMA_Init(DMA1_Stream0, &DMA_InitStructure);

  I2C_InitStruct.I2C_ClockSpeed = 400000;
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct.I2C_OwnAddress1 = 0x00;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_Init(I2C1, &I2C_InitStruct);

  I2C_ITConfig(I2C1, I2C_IT_BUF|I2C_IT_EVT|I2C_IT_ERR, DISABLE);

  /* Configure the I2C interrupts. */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  DMA_ITConfig(DMA1_Stream0, DMA_IT_TC, DISABLE);
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  DMA_ITConfig(DMA1_Stream0, DMA_IT_TC, ENABLE);

  I2C_Cmd(I2C1, ENABLE);
}


static void
read_mpu6050_reg_multi(uint8_t reg, uint8_t *buf, uint32_t len)
{
  uint8_t val;

  I2C_GenerateSTART(I2C1, ENABLE);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
    ;

  I2C_Send7bitAddress(I2C1, MPU6050_I2C_ADDR << 1, I2C_Direction_Transmitter);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    ;

  I2C_SendData(I2C1, reg);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    ;

  I2C_GenerateSTART(I2C1, ENABLE);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
    ;

  I2C_Send7bitAddress(I2C1, MPU6050_I2C_ADDR << 1, I2C_Direction_Receiver);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    ;

  if (len > 1)
    I2C_AcknowledgeConfig(I2C1, ENABLE);
  while (len > 0)
  {
    if (len == 1)
      I2C_AcknowledgeConfig(I2C1, DISABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
      ;
    val = I2C_ReceiveData(I2C1);
    *buf++ = val;
    --len;
  }

  I2C_GenerateSTOP(I2C1, ENABLE);
}


static volatile uint32_t i2c_async_stage;
static uint8_t i2c_async_reg;
static uint8_t *i2c_async_buf;
static uint32_t i2c_async_len;

/*
  Handle event for async (interrupt-driven) I2C read.
  Note that this is called in interrupt context.
*/
static void
async_read_event_handler(void)
{
  uint32_t events = I2C_GetLastEvent(I2C1);
  uint32_t stage = i2c_async_stage;

  if (events & I2C_SR1_ADDR)
  {
    /*
      The interrupt is cleared by a read of CR1 followed by a read of CR2
      inside GetLastEvent().
    */
    if (stage == 1)
      I2C_SendData(I2C1, i2c_async_reg);
    else
    {
      /* When using DMA, no interrupt for RxNE and BTF. */
      I2C_ITConfig(I2C1, I2C_IT_BUF|I2C_IT_EVT, DISABLE);
    }
    return;
  }

  if (stage == 1 && (events & I2C_SR1_BTF))
  {
    i2c_async_stage = 2;
    I2C_GenerateSTART(I2C1, ENABLE);
    /*
      There does not seem to be a way to wait for the start condition using
      an interrupt. The problem is that until the start condition triggers, we
      are still in transmit mode with BTF asserted, so we get spurious
      interrupts.

      So we might as well just busy-wait here, better than triggering spurious
      interrupts until the start condition occurs. Testing show that we only
      take a couple of loops (like 5) anyway.
    */
    while (!(I2C_GetLastEvent(I2C1) & I2C_SR1_SB))
      ;
    I2C_Send7bitAddress(I2C1, MPU6050_I2C_ADDR << 1, I2C_Direction_Receiver);
    if (i2c_async_len > 1)
    {
      I2C_AcknowledgeConfig(I2C1, ENABLE);
      I2C_DMALastTransferCmd(I2C1, ENABLE);
    }
    else
      I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_DMACmd(I2C1, ENABLE);
    DMA_Cmd(DMA1_Stream0, ENABLE);
    return;
  }

  /* Attempt to track spurious interrupt. */
  if (!(events & ~(((uint32_t)I2C_SR2_BUSY << 16)|((uint32_t)I2C_SR2_MSL << 16))))
  {
    /*
      We seem to get this sporadic interrupt once at the start, where no events
      seem to be set that could trigger the interrupt.
      I am not sure why, for now the best we can do seems to be to simply ignore
      it ...
    */
    return;
  }

  /* If we get here, we received an unexpected interrupt. */
  serial_puts(USART3, "\r\n\r\nERROR: unexpected interrupt during async receive\r\n");
  serial_puts(USART3, "stage=");
  serial_output_hexbyte(USART3, (uint8_t)stage);
  serial_puts(USART3, "\r\nevents=0x");
  serial_output_hexbyte(USART3, (uint8_t)((events >> 16)&0xff));
  serial_output_hexbyte(USART3, (uint8_t)((events >> 8)&0xff));
  serial_output_hexbyte(USART3, (uint8_t)(events&0xff));
  serial_puts(USART3, "\r\n");
  for (;;) { }
}


static void
dma_done_handler(void)
{
  if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0))
  {
    DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);

    I2C_ITConfig(I2C1, I2C_IT_BUF|I2C_IT_EVT|I2C_IT_ERR, DISABLE);
    I2C_DMACmd(I2C1, DISABLE);
    DMA_Cmd(DMA1_Stream0, DISABLE);
    I2C_GenerateSTOP(I2C1, ENABLE);
    memcpy(i2c_async_buf, mpu6050_reg_buffer, i2c_async_len);
    i2c_async_stage = 3;
    return;
  }

  /* If we get here, we received an unexpected interrupt. */
  serial_puts(USART3, "\r\n\r\nERROR: unexpected DMA interrupt\r\n");
  serial_puts(USART3, "stage=");
  serial_output_hexbyte(USART3, (uint8_t)i2c_async_stage);
  serial_puts(USART3, " TC=");
  serial_output_hexbyte(USART3, (uint8_t)DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0));
  serial_puts(USART3, " HT=");
  serial_output_hexbyte(USART3, (uint8_t)DMA_GetITStatus(DMA1_Stream0, DMA_IT_HTIF0));
  serial_puts(USART3, " TE=");
  serial_output_hexbyte(USART3, (uint8_t)DMA_GetITStatus(DMA1_Stream0, DMA_IT_TEIF0));
  serial_puts(USART3, " DME=");
  serial_output_hexbyte(USART3, (uint8_t)DMA_GetITStatus(DMA1_Stream0, DMA_IT_DMEIF0));
  serial_puts(USART3, " FE=");
  serial_output_hexbyte(USART3, (uint8_t)DMA_GetITStatus(DMA1_Stream0, DMA_IT_FEIF0));
  serial_puts(USART3, "\r\n");
  for (;;) { }
}


static void
async_read_mpu6050_reg_multi(uint8_t reg, uint8_t *buf, uint32_t len)
{
  dma_event_handler = dma_done_handler;
  i2c_async_event_handler = async_read_event_handler;
  i2c_async_reg = reg;
  i2c_async_buf = buf;
  i2c_async_len = len;
  i2c_async_stage = 1;
  I2C_GenerateSTART(I2C1, ENABLE);
  while (!(I2C_GetLastEvent(I2C1) & I2C_SR1_SB))
    ;
  I2C_Send7bitAddress(I2C1, MPU6050_I2C_ADDR << 1, I2C_Direction_Transmitter);
  I2C_ITConfig(I2C1, I2C_IT_EVT|I2C_IT_ERR, ENABLE);
}


static uint8_t
read_mpu6050_reg(uint8_t reg)
{
  uint8_t val;

  read_mpu6050_reg_multi(reg, &val, 1);
  return val;
}


static void
write_mpu6050_reg(uint8_t reg, uint8_t val)
{
  I2C_GenerateSTART(I2C1, ENABLE);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
    ;

  I2C_Send7bitAddress(I2C1, MPU6050_I2C_ADDR << 1, I2C_Direction_Transmitter);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    ;

  I2C_SendData(I2C1, reg);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    ;

  I2C_SendData(I2C1, val);
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    ;

  I2C_GenerateSTOP(I2C1, ENABLE);
}


static void
setup_mpu6050(void)
{
  for (;;)
  {
    uint8_t res;

    /*
      First take it out of sleep mode (writes seem to not stick until we take it
      out of sleep mode). Then issue a reset to get a well-defined starting state
      (and go out of sleep mode again).
    */
    write_mpu6050_reg(MPU6050_REG_PWR_MGMT_1, 0x02);
    delay(300000);
    res = read_mpu6050_reg(MPU6050_REG_PWR_MGMT_1);
    if (res != 0x02)
      continue;
    write_mpu6050_reg(MPU6050_REG_PWR_MGMT_1, 0x82);
    delay(300000);
    res = read_mpu6050_reg(MPU6050_REG_PWR_MGMT_1);
    if (res != 0x40)
      continue;
    write_mpu6050_reg(MPU6050_REG_PWR_MGMT_1, 0x02);
    delay(300000);
    res = read_mpu6050_reg(MPU6050_REG_PWR_MGMT_1);
    if (res != 0x02)
      continue;

    /* Disable digital low-pass filter (DLPF) */
    write_mpu6050_reg(MPU6050_REG_CONFIG, 0);
    /* 1000 Hz sample rate. */
    write_mpu6050_reg(MPU6050_REG_SMPRT_DIV, 7);
    /* Lowest resolution, +-2000 degrees / second and +-16g. */
    write_mpu6050_reg(MPU6050_REG_GYRO_CONFIG, 3 << 3);
    write_mpu6050_reg(MPU6050_REG_ACCEL_CONFIG, 3 << 3);
    /* Disable the Fifo (write 0xf8 to enable temp+gyros_accel). */
    write_mpu6050_reg(MPU6050_REG_FIFO_EN, 0x00);
    /*
      Interrupt. Active high, push-pull, hold until cleared, cleared only on
      read of status.
    */
    write_mpu6050_reg(MPU6050_REG_INT_PIN_CFG, 0x20);
    /* Enable FIFO overflow and data ready interrupts. */
    write_mpu6050_reg(MPU6050_REG_INT_ENABLE, 0x11);
    /* Disable the FIFO and external I2C master mode. */
    write_mpu6050_reg(MPU6050_REG_USER_CTRL, 0x00);

    break;
  }
}


static int16_t
mpu6050_regs_to_signed(uint8_t high, uint8_t low)
{
  uint16_t v = ((uint16_t)high << 8) | low;
  return (int16_t)v;
}


int main(void)
{
  uint8_t res;

  delay(2000000);
  setup_serial();
  serial_puts(USART3, "Initialising...\r\n");
  setup_i2c_for_mpu6050();
  delay(2000000);
  setup_mpu6050();

  serial_puts(USART3, "Hello world, ready to blink!\r\n");

  res = read_mpu6050_reg(MPU6050_REG_WHOAMI);
  serial_puts(USART3, "\r\nMPU6050: whoami=0x");
  serial_output_hexbyte(USART3, res);
  res = read_mpu6050_reg(MPU6050_REG_PWR_MGMT_1);
  serial_puts(USART3, "\r\nMPU6050: pwr_mgmt_1=0x");
  serial_output_hexbyte(USART3, res);

  while (1)
  {
    int16_t val;
    uint8_t buf[14];

    serial_puts(USART3, "\r\nRead sensors ...\r\n");
    //read_mpu6050_reg_multi(MPU6050_REG_ACCEL_XOUT_H, buf, 14);
    async_read_mpu6050_reg_multi(MPU6050_REG_ACCEL_XOUT_H, buf, 14);
    while (i2c_async_stage != 3)
      ;

    val = mpu6050_regs_to_signed(buf[6], buf[7]);
    serial_puts(USART3, "  Temp=");
    println_float(USART3, (float)val/340.0f+36.53f, 2, 3);

    val = mpu6050_regs_to_signed(buf[0], buf[1]);
    serial_puts(USART3, "  Accel_x=");
    println_float(USART3, (float)val/(float)2048, 2, 3);

    val = mpu6050_regs_to_signed(buf[2], buf[3]);
    serial_puts(USART3, "  Accel_y=");
    println_float(USART3, (float)val/(float)2048, 2, 3);

    val = mpu6050_regs_to_signed(buf[4], buf[5]);
    serial_puts(USART3, "  Accel_z=");
    println_float(USART3, (float)val/(float)2048, 2, 3);

    val = mpu6050_regs_to_signed(buf[8], buf[9]);
    serial_puts(USART3, "  Gyro_x=");
    println_float(USART3, (float)val/(float)(32768.0f/2000.0f), 4, 2);

    val = mpu6050_regs_to_signed(buf[10], buf[11]);
    serial_puts(USART3, "  Gyro_y=");
    println_float(USART3, (float)val/(float)(32768.0f/2000.0f), 4, 2);

    val = mpu6050_regs_to_signed(buf[12], buf[13]);
    serial_puts(USART3, "  Gyro_z=");
    println_float(USART3, (float)val/(float)(32768.0f/2000.0f), 4, 2);

    delay(10000000);
  }

  return 0;
}
