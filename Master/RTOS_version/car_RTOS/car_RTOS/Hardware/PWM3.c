#include <stm32f446xx.h>


void Pwm3_Init(void)
{
	//開啟GPIOA、TIM3時鐘
	RCC->AHB1ENR |= 1 << 0;
	RCC->APB1ENR |= 1 << 1;

	//Tim3 PWM輸出復用功能 使用TIM3_CH1通道PA6
	GPIOA->AFR[0] &= ~(0xF << 24);
	GPIOA->AFR[0] |=  (2 << 24);


	//設置PA6為復用推挽輸出
	GPIOA->MODER  &=~(3 << 12);
	GPIOA->MODER  |=  2 << 12;
	GPIOA->OTYPER &=~(1 << 6);
	GPIOA->OSPEEDR|=  3 << 12;


    //設置使用內部時鐘
//	TIM_InternalClockConfig(TIM2);
	TIM3->SMCR &= ~(7 << 0);


    //設置計數目標值和預分頻值
	//21kHZ
	TIM3->PSC = 4-1;
	TIM3->ARR = 1000-1;

	//設置自動裝載、計數方向、始能計數器
	TIM3->CR1 |=  1 << 7;
	TIM3->CR1 &= ~(1 << 4);
	TIM3->CR1 |=  1 << 0;

    //設置初始化計數器
	TIM3->EGR |=  1 << 0;

//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure);
//
//	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
//	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse        = 0;//CCR的值
//	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

    //設置PWM模式、輸出比較自動裝載
	TIM3->CCMR1 &= ~(7 << 4);
	TIM3->CCMR1 |=   6 << 4;
	TIM3->CCMR1 |=   1 << 3;

//	TIM2->CCMR2 &= ~(7 << 4);
//	TIM2->CCMR2 |=   6 << 4;
//	TIM2->CCMR2 |=   1 << 3;

    //設置CCR值
	TIM3->CCR1  = 0;

    //設置輸出比較始能、輸出極性
	TIM3->CCER  |=   1 << 0;
	TIM3->CCER  &= ~(1 << 1);

//	TIM3->BDTR |= 1 << 15;  // MOE = 1 (Main Output Enable)

	//TIM_Cmd(TIM1, ENABLE);

}

void PWM3_SetCompare1(uint16_t Compare)
{
//	TIM_SetCompare2(TIM2, Compare);
	TIM3->CCR1 = Compare;
}
void PWM3_SetPrescaler(uint16_t Prescaler)
{
//	TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Immediate);
	TIM3->PSC = Prescaler;
	TIM3->EGR = 1 << 0; //立刻更新PSC值
}



