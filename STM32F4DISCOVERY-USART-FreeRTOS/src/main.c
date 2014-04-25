/**
 * Copyright (C) 2013 Chetan Patil, http://chetanpatil.info
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * @author Chetan Patil | http://chetanpatil.info
 */

//Example code to loop back the data sent to USART2 on STM32F4DISCOVERY

//Inlcude header files
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Task For Sending Data Via USART
static void UsartTask(void *pvParameters)

{

while(1) {

	//Variable to store received data	
	uint32_t Data;
	
	//Wait for character
	while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET) {
                if (USART_GetFlagStatus(USART2, (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE)))
		USART_ReceiveData(USART2); // Clear Error
	}

	//Collect the caracter
	Data = USART_ReceiveData(USART2);

	//Wait till the flag resets
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

	//Send the data
	USART_SendData(USART2, Data); // Echo Char
}

while(1);

}


//Initialize GPIO and USART2
void initx(void){

	//Enable GPIO Clocks For USART2
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//Enable Clocks for USART2
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	

	//Structure With Data For GPIO Configuration
	GPIO_InitTypeDef GPIO_InitStructure;

	//Structure With Data For USART Configuration
	USART_InitTypeDef USART_InitStructure;

	//GPIO Configuration
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Connect USART pins to AF
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	//Initialize LED
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//USART Parameters
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;

	//Configuring And Enabling USART2
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);

}


//Main Function
int main(void)
{

	//Call initx(); To Initialize USART & GPIO
	initx();

	//Create Task For USART
	xTaskCreate(UsartTask, (signed char*)"UsartTask", 128, NULL, tskIDLE_PRIORITY+1, NULL);

	//Call Scheduler
	vTaskStartScheduler();

}
