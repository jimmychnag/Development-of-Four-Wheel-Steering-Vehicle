#include <stm32f446xx.h>



//使用TIM12當作中斷來源
//中斷頻率5ms
void Timer_Init(void)
{
	RCC->APB1ENR |= 1 << 6;  //設定TIM12外設時鐘
	TIM12->SMCR   |= 000 << 0;//設定為內部時鐘

	TIM12->ARR     = 450-1; //設定產生中斷目標值
	TIM12->PSC     = 1000-1;  //設定預分頻器
	
	TIM12->CR1     = 1 << 7;  //設定ARPE，允許自動裝載
	TIM12->CR1    |= 0 << 4;  //設定DIR，上數模式
	TIM12->CR1    |= 1 << 0;  //設定CEN，始能計數器
	TIM12->EGR     = 1 << 0;  //設定UG，初始化計數器，並立刻產生中斷
	TIM12->SR      = 0 << 0;  //設定UIF，清除中斷
	
	TIM12->DIER   |= 1 << 0 ; //設定UIE，允許更新中斷
	
	NVIC->ISER[1] = 1 << 11; //TIM12的中斷位置在43

	NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 6); // OK

}

