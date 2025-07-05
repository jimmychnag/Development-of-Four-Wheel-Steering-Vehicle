#include <stm32f446xx.h>

int16_t Encoder_Count;

void Encoder_Init(void)
{	
	//開啟GPIOA和、TIM3外設時鐘
	RCC->AHB1ENR |= 1 << 0;
	RCC->APB1ENR |= 1 << 1;
	
	//設置PA6、PA7為輸入、上拉模式(要選擇與硬體相符的默認模式)
	GPIOA->MODER &= ~(3 << 12);
	GPIOA->PUPDR |=   1 << 12;
	GPIOA->MODER &= ~(3 << 14);
	GPIOA->PUPDR |=   1 << 14;
	GPIOA->BSRR   = 1 << 6;
	GPIOA->BSRR   = 1 << 7;
	
	//設置時基單元
    //設置計數目標值、預分頻值
	TIM3->ARR = 65536 - 1;
	TIM3->PSC = 1-1;
	
	
	
//	TIM_ICInitTypeDef TIM_ICInitStructure;
	//因為在編碼器接口狀態時，有些參數不用用到，但還是要給預設值，避免發生錯誤
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//	TIM_ICInitStructure.TIM_ICFilter = 0xF;
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//代表高低電平極性不翻轉
//	TIM_ICInit(TIM3, &TIM_ICInitStructure);
//	
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
//	TIM_ICInitStructure.TIM_ICFilter = 0xF;
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//代表高低電平極性不翻轉
//	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	//設置TIM3的通道1，TIM3_CH1
    //配置輸入捕獲濾波器、輸入訊號是否交叉(此配置為輸入)、捕獲預分頻器(沒用)
    TIM3->CCMR1 &= ~(0xF << 4);
    TIM3->CCMR1 |=   0xF << 4 ;

    TIM3->CCER  &= ~(1 	 << 0);
    TIM3->CCMR1 &= ~(3   << 0);
    TIM3->CCMR1 |=   1   << 0 ;

    //設置輸入捕獲始能、極性
    TIM3->CCER  |=   1 << 0;
    TIM3->CCER  &= ~(1 << 1);//上升延觸發，在編碼器模式為不反轉電平
	

    //設置TIM3的通道2，TIM3_CH2
    //配置輸入捕獲濾波器、輸入訊號是否交叉(此配置為輸入)、捕獲預分頻器(沒用)
    TIM3->CCMR1 &= ~(0xF << 12);
    TIM3->CCMR1 |=   0xF << 12 ;

    TIM3->CCER  &= ~(1 	 << 4);
    TIM3->CCMR1 &= ~(3   << 8);
    TIM3->CCMR1 |=   2   << 8 ;

    //設置輸入捕獲始能、極性
    TIM3->CCER  |=   1 << 4;
    TIM3->CCER  &= ~(1 << 5);//上升延觸發，在編碼器模式為不反轉電平
	
	

	//配置編碼器接口工作形式、IC1是否反向、IC2是否反向
	//後兩參數和TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising重複配置了
//	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	//設置從模式為在TI1和TI2上計數
	TIM3->SMCR = 3 << 0;
	
	
//	TIM_Cmd(TIM3, ENABLE);

	//設置自動裝載、計數方向(沒用)、計數器始能
    TIM3->CR1 |=  1 << 7;
//  TIM3->CR1 &= ~(1 << 4);//在編碼器模式下沒作用，計數模式被編碼器模式操控
	TIM3->CR1 |=  1 << 0;

	//初始化計數器
    TIM3->EGR |=  1 << 0;
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
//	Temp = TIM_GetCounter(TIM3);
//	TIM_SetCounter(TIM3,0);
	Temp = TIM3->CNT;
	//TIM3->CNT = 0;
	return Temp;
}



void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & 0x00000001)
	{
		if( (GPIOB->IDR & 0x00000002) == 0)
		{
			Encoder_Count--;
		}
		EXTI->PR = 0x00000001;
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI->PR & 0x00000002)
	{
		if((GPIOB->IDR & 0x00000001) == 0)
		{
			Encoder_Count++;
		}
		EXTI->PR = 0x00000002;
	}
}







