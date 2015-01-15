/*
 * ref: http://eliaselectronics.com/stm32f4-tutorials/stm32f4-gpio-tutorial/
 *   use polling to check user button status (press/release)
 */
#include "stm32.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"

#define USE_STDPERIPH_DRIVER

#define EXT_INT

/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field.  This value must be a multiple of 0x200. */

int delay_time = 0x300000;

void Delay(uint32_t delay )
{
  while(delay) delay--;
}

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}


void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState)
{ 
  /* Check the parameters */
  //assert_param(IS_RCC_AHB1_CLOCK_PERIPH(RCC_AHB1Periph));
  
  //assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    RCC->AHB1ENR |= RCC_AHB1Periph;
  } 
  else
  { 
    RCC->AHB1ENR &= ~RCC_AHB1Periph;
  }
}  

#define RCC_AHB1Periph_GPIOA             ((uint32_t)0x00000001)
#define RCC_AHB1Periph_GPIOD             ((uint32_t)0x00000008)

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;

#if 0
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));
#endif
  /* -------------------------Configure the port pins---------------- */
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        //assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        //assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration*/
        GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }

      /* Pull-up Pull down resistor configuration*/
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
    }
  }
}

void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{   
  /* Check the parameters */
  //assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  //assert_param(IS_GPIO_PIN(GPIO_Pin));
    
  GPIOx->BSRRL = GPIO_Pin;
} 

void GPIO_SetBits_svc(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{   
  /* Check the parameters */
  //assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  //assert_param(IS_GPIO_PIN(GPIO_Pin));
    
  GPIOx->BSRRL = GPIO_Pin;
  __asm ("svc 0");
} 


void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  //assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  //assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BSRRH = GPIO_Pin;
}



int init_stm32f4(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    
#if 0
  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif


  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            // we want to configure PA0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;         // we want it to be an input
#ifdef POLL_USER_BUTTON
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;   // this enables the pulldown resistor --> we want to detect a high level

#else
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   // this enables the pulldown resistor --> we want to detect a high level
#endif
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
}

#if 0
ref: 
https://my.st.com/public/STe2ecommunities/mcu/Lists/STM32Discovery/Flat.aspx?RootFolder=%2Fpublic%2FSTe2ecommunities%2Fmcu%2FLists%2FSTM32Discovery%2Fexternal%20interrupt%20issue&FolderCTID=0x01200200770978C69A1141439FE559EB459D75800084C20D8867EAD444A5987D47BE638E0F&currentviews=374


   /* Connect EXTI Line0 to PA0 pin via SYSCFG */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
     
    /* Configure EXTI Line0 */
     EXTI_InitStructure.EXTI_Line = EXTI_Line0;
     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
     EXTI_Init(&EXTI_InitStructure);
      
     /* Enable and set EXTI Line0 Interrupt to the lowest priority */
     NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);


DM00031020.pdf 
chapter 8: System configuration controller (SYSCFG)

The system configuration controller is mainly used to remap the memory accessible in the 
code area, select the Ethernet PHY interface and manage the "external interrupt line" connection to the GPIOs.

SYSCFG external interrupt configuration register 1
(SYSCFG_EXTICR1)
Address offset: 0x08
Reset value: 0x0000

STM32F4xx_DSP_StdPeriph_Lib_V1.1.0\Project\STM32F4xx_StdPeriph_Examples\EXTI\EXTI_Example\main.c
#endif


int main(void)
{
  init_stm32f4();
  int p;

  /* Connect EXTI Line0 to PA0 pin */
  // if no line, it can work.
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  EXTI_InitTypeDef   EXTI_InitStructure;// ext interupt structure
  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

#if 0
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif

#if 1
  // ref:  arm cortex-m3: 嵌入式系統設計入門 p8-3
  *(volatile unsigned long*) 0xE000E100 = 0;
  *(volatile unsigned long*) 0xE000E100 |= (1 << 6);
#endif

  while(1)
  {
#ifdef POLL_USER_BUTTON
    int i=0;
    if(GPIOA->IDR & 0x0001)
    {
      i=1;
    }
    else
    {
      i=2;
    }
    p = i;
#else
    p = 5;
#endif
  }
}

void exti0_isr(void)
{
  int a=6;
  
  // if no line, it will envoke exti0_isr().
  EXTI_ClearITPendingBit(EXTI_Line0);

}   

