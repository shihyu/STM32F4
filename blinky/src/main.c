#include "stm32f4xx_conf.h"

//定时器2中断函数
void TIM2_IRQHandler(void)
{
    if(TIM2->SR & TIM_SR_UIF)
        GPIOD->ODR ^=(1 << 13);
    TIM2->SR = 0x0;
}

int main(void)
{
    //使能GPIOD时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    //使能定时器2时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    //设置PD13为通用IO输出
    GPIOD->MODER = (1 << 26);
    //使能定时器2中断
    NVIC->ISER[0] |= 1 << (TIM2_IRQn);
    //关闭预分频器，定时器向上计数，和外设时钟同步
    TIM2->PSC = 0x0;
    //使能更新事件
    TIM2->DIER |= TIM_DIER_UIE;
    //计数到1自动重装
    TIM2->ARR = 0x01;
    //自动重装开启，计数使能
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
    //触发更新事件，重装计数器寄存器
    TIM2->EGR = 1;

    while(1);
}
