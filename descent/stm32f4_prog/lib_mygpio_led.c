#define USE_STDPERIPH_DRIVER

#include "lib_mygpio_led.h"

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


void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  //assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  //assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->BSRRH = GPIO_Pin;
}




int init_led(void)
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
       
    /* Set the LED pin state such that the LED is off.  The LED is connected
     * between power and the microcontroller pin, which makes it turn on when
     * the pin is low.
     */
    GPIO_WriteBit(GPIOC,GPIO_Pin_12,Bit_SET);

    /* Configure the LED pin as push-pull output. */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);


    while(1) {
       GPIOC->BRR = 0x00001000;
       busyLoop(500000);
       GPIOC->BSRR = 0x00001000;
       busyLoop(500000);
    }
#endif
  GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}

void test_led()
{
  while (1)
  {     
    /* PD12 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
        
    /* Insert delay */ 
    Delay(0x3FFFFF);

#if 0
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
#endif
    GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

    /* Insert delay */
    Delay(0x6FFFFF);
  }
}

void test_led_1()
{
  while (1)
  {     
#if 1
    /* PD13 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_13);

    /* Insert delay */
    Delay(0x3FFFFF);
#endif    
#if 1    
    /* PD15 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    /* Insert delay */
    Delay(0x5FFFFF);
#endif
    GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

    /* Insert delay */
    Delay(0x6FFFFF);
  }
}
