//#include "gpio_led.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#define USE_STDPERIPH_DRIVER

/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field.  This value must be a multiple of 0x200. */

int delay_time = 0x300000;

void Delay(uint32_t delay )
{
  while(delay) delay--;
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
    //init_led();
    GPIO_InitTypeDef GPIO_InitStructure;
    
    #if 0
    /* Enable GPIO C clock. */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    #endif

    /* GPIOD Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

#if 0
  while (1)
  {     
    /* PD12 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
        
    /* Insert delay */ 
    Delay(0x3FFFFF);

    /* PD13 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_13);

    /* Insert delay */
    Delay(0x3FFFFF);
#endif    
    /* PD14 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
      
    /* Insert delay */
    Delay(0x3FFFFF);
#if 0    
    /* PD15 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    /* Insert delay */
    Delay(0x5FFFFF);
    GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

    /* Insert delay */
    Delay(0x6FFFFF);
  }
#endif

}

#if 1
void led12_on()
{
  //GPIO_SetBits_svc(GPIOD, GPIO_Pin_12);
  //GPIO_SetBits(GPIOD, GPIO_Pin_12);

  GPIOD->BSRRL = GPIO_Pin_12;
}

void led12_off()
{
  //GPIO_ResetBits(GPIOD, GPIO_Pin_12);
  GPIOD->BSRRH = GPIO_Pin_12;
}

void led14_on()
{
  //GPIO_SetBits(GPIOD, GPIO_Pin_14);
  GPIOD->BSRRL = GPIO_Pin_14;
}

void led14_off()
{
  //GPIO_ResetBits(GPIOD, GPIO_Pin_14);
  GPIOD->BSRRH = GPIO_Pin_14;
}

void delay_func(uint32_t delay )
{
  Delay(delay_time);
}
#endif
