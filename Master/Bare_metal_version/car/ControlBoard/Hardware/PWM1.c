#include <stm32f446xx.h>


void Pwm1_Init(void)
{
	//開啟GPIOA、TIM1時鐘
	RCC->AHB1ENR |= 1 << 0;
	RCC->APB2ENR |= 1 << 0;

	//tim1 PWM輸出復用功能
	GPIOA->AFR[1] &= ~(0xF << 0);
	GPIOA->AFR[1] |=  (1 << 0);


	//設置PA8為復用推挽輸出
	GPIOA->MODER  &=~(3 << 16);
	GPIOA->MODER  |=  2 << 16;
	GPIOA->OTYPER &=~(1 << 8);
	GPIOA->OSPEEDR|=  3 << 16;


    //設置使用內部時鐘
//	TIM_InternalClockConfig(TIM2);
	TIM1->SMCR &= ~(7 << 0);


    //設置計數目標值和預分頻值
	//21kHZ
	TIM1->PSC = 4-1;
	TIM1->ARR = 1000-1;
	
	//設置自動裝載、計數方向、始能計數器
	TIM1->CR1 |=  1 << 7;
	TIM1->CR1 &= ~(1 << 4);
	TIM1->CR1 |=  1 << 0;
	
    //設置初始化計數器
	TIM1->EGR |=  1 << 0;

//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure);
//	
//	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
//	TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse        = 0;//CCR的值
//	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
    //設置PWM模式、輸出比較自動裝載
	TIM1->CCMR1 &= ~(7 << 4);
	TIM1->CCMR1 |=   6 << 4;
	TIM1->CCMR1 |=   1 << 3;

//	TIM2->CCMR2 &= ~(7 << 4);
//	TIM2->CCMR2 |=   6 << 4;
//	TIM2->CCMR2 |=   1 << 3;

    //設置CCR值
	TIM1->CCR1  = 0;
	
    //設置輸出比較始能、輸出極性
	TIM1->CCER  |=   1 << 0;
	TIM1->CCER  &= ~(1 << 1);
	
	TIM1->BDTR |= 1 << 15;  // MOE = 1 (Main Output Enable)

	//TIM_Cmd(TIM1, ENABLE);

}

void PWM1_SetCompare1(uint16_t Compare)
{
//	TIM_SetCompare2(TIM2, Compare);
	TIM1->CCR1 = Compare;
}
void PWM1_SetPrescaler(uint16_t Prescaler)
{
//	TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Immediate);
	TIM1->PSC = Prescaler;
	TIM1->EGR = 1 << 0; //立刻更新PSC值
}



