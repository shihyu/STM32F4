#define USE_STDPERIPH_DRIVER

#include "lib_mygpio_led.h"

void Delay(uint32_t delay )
{
  while(delay) 
    delay--;
}

#define RCC_AHB1Periph_GPIOD             ((uint32_t)0x00000008)


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
