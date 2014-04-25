#if 1
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
 
int i;
 
void My_Usart3_Printf(char *string){
    while(*string){
        /* 傳送訊息至 USART3 */
        USART_SendData(USART3, (unsigned short int) *string++);
 
        /* 等待訊息傳送完畢 */
        while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
    }
}
 
int main(void){
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
 
    /******** 啟用 GPIOC、USART3 的 RCC 時鐘 ********/
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
      /******** 將 PC10、PC11 連接至 USART3 ********/
      GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
      GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
 
      /******** 設定 PC10 為 Tx 覆用  ********/
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // 設定第 10 腳
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
      GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC
 
      /******** 設定 PC11 為 Rx 覆用  ********/
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // 設定第 11 腳
      GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC
 
      /******** USART 基本參數設定 ********/
      USART_InitStructure.USART_BaudRate = 9600; // 設定 USART 包率 (每秒位元數) 為 9600
      USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
      USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
      USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
      USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
      USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
      USART_Init(USART3, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART3
    
      /******** 啟用 USART3 ********/
      USART_Cmd(USART3, ENABLE);
 
      while (1){
          My_Usart3_Printf("Hello !!\n"); // 傳送字串至 USART3
          for(i=0; i<30000000; i++); // 延遲
      }
}

#else
/**
  ******************************************************************************
  * @file    IO_Toggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h" // again, added because ST didn't put it here ?

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f4xx.c file
     */

  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

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
  
    /* PD14 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    
    /* Insert delay */
    Delay(0x3FFFFF);
    
    /* PD15 to be toggled */
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    
    /* Insert delay */
    Delay(0x7FFFFF);
    
    GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
    
    /* Insert delay */
    Delay(0xFFFFFF);
  }
}

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
#endif
