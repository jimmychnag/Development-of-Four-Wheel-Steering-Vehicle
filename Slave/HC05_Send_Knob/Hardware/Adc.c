#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[3];

void AD_Init(void)
{
    //開啟GPIOA、ADC1時鐘、DMA1時鐘
    RCC->APB2ENR |= 0x00000004;
    RCC->APB2ENR |= 1 << 9;
    RCC->AHBENR  |= 1 << 0;

    //配置時鐘配置暫存器(ADC預分頻)
    RCC->CFGR &= ~(3 << 14);
    RCC->CFGR |=   2 << 14;

    //設置PA0、PA1、PA4
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL &= ~(0xF << 4);
		GPIOA->CRL &= ~(0xF << 16);

    //設置規則序列中的第一個轉換(設成通道0)，通道0的採樣時間
    ADC1->SQR3 &= ~(0xF << 0);
    ADC1->SMPR2|=     5 << 0;

    //設置規則序列中的第二個轉換(設成通道1)，通道1的採樣時間
    ADC1->SQR3 |= 	  1 << 5;
    ADC1->SMPR2|=     5 << 3;
		
		//設置規則序列中的第三個轉換(設成通道4)，通道4的採樣時間
    ADC1->SQR3 |= 	  4 << 10;
    ADC1->SMPR2|=     5 << 12;

    //設置雙模式選擇(獨立模式)、掃描模式(開啟)
    ADC1->CR1 &= ~(0xF << 16);
    ADC1->CR1 |=  (1   << 8);

    //設置對齊模式(右對齊)、外部觸發源(軟體觸發)、連續轉換(單次轉換)
    ADC1->CR2 &= ~(1 << 11);
    ADC1->CR2 |=   7 << 17;
    ADC1->CR2 &= ~(1 << 1);//單次轉換

    //設置規則通道序列長度(3個轉換序列)
    ADC1->SQR1 |= (2 << 20);


    //設置外設地址(ADC1->DR)、資料寬度(16bit)、增量模式(位址不自增)
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CCR |=  (1 << 8);
    DMA1_Channel1->CCR &= ~(1 << 6);

    //設置存儲器位址(AD_Value)、資料寬度(16bit)、增量模式(位址增量)
    DMA1_Channel1->CMAR = (uint32_t)&AD_Value;
    DMA1_Channel1->CCR |=  (1 << 10);
    DMA1_Channel1->CCR |=   1 << 7;

    //設置循環模式(不循環)、數據方向(從外設讀)、通道優先級(中)、M2M(硬體觸發)
    DMA1_Channel1->CCR |=  (1 << 5);
    DMA1_Channel1->CCR &= ~(1 << 4);
    DMA1_Channel1->CCR |=   1 << 12;
    DMA1_Channel1->CCR &= ~(1 << 14);

    //設置數據傳輸數量
    DMA1_Channel1->CNDTR = 3;

    //設置DMA始能(可先開)，因為還沒有觸發源，DMA不會動作
    DMA1_Channel1->CCR |= (1 << 0);


    //設置ADC使用DMA模式
    ADC1->CR2 |= 1 << 8;

    //啟用ADC轉換
    ADC1->CR2 |= 1 << 0;

    //設置ADC復位校準、ADC校準
    ADC1->CR2 |= 1 << 3;
    while( (ADC1->CR2 & (1 << 3)) == 1);
    ADC1->CR2 |= 1 << 2;
    while((ADC1->CR2 & (1 << 2)) == 1);
}


void AD_GetValue(void)
{	
    //設置外部觸發轉換模式(使用外部事件觸發)、開始轉換規則通道
    //若分開設定時有順序問題
    ADC1->CR2 |= 1 << 20;
    ADC1->CR2 |= 1 << 22;

    //由於目前ADC資料由DMA搬運，現在只需要等待DMA搬運完成即可，判斷旗標
    //判斷是否傳遞完成、清除標誌位
    while( (DMA1->ISR & (1 << 1) ) == 0);
    DMA1->IFCR |= 1 << 1 ;
}
