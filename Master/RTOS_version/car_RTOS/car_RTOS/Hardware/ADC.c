/*
 * ADC.c
 *
 *  Created on: May 1, 2025
 *      Author: a0979
 */
#include <stm32f446xx.h>

uint16_t AD_Value[3];

void AD_Init(void)
{
    //開啟GPIOA、ADC1時鐘、DMA2時鐘
    RCC->AHB1ENR |= 1 << 0;
    RCC->APB2ENR |= 1 << 8;
    RCC->AHB1ENR |= 1 << 22;


    //設置PA1、PA4，為輸入模式
    GPIOA->MODER |= (0x3 << 2);
	GPIOA->PUPDR &= ~(0x3 << 2);
	GPIOA->MODER |= (0x3 << 8);
	GPIOA->PUPDR &= ~(0x3 << 8);


	ADC1->SQR3 &= ~((0x1F << 0) | (0x1F << 5));
    //設置規則序列中的第一個轉換(設成通道1)，通道1的採樣時間
    ADC1->SQR3 |= 	  1 << 0;
    ADC1->SMPR2|=     5 << 3;

    //設置規則序列中的第二個轉換(設成通道4)，通道4的採樣時間
    ADC1->SQR3 |= 	  4 << 5;
    ADC1->SMPR2|=     5 << 12;

    //掃描模式(開啟)、解析度設定
    ADC1->CR1 |=  (1 << 8);
    ADC1->CR1 &= ~(3 << 24);

    //設置對齊模式(右對齊)、外部觸發源(取消外部觸發)、連續轉換(連續轉換)
    ADC1->CR2 &= ~(1 << 11);
    ADC1->CR2 &= ~(3 << 28);
    ADC1->CR2 |=  (1 << 1);

    //設置規則通道序列長度(2個轉換序列)
    ADC1->SQR1 |= (1 << 20);

    //DMA要求、結束轉換標誌
    ADC1->CR2 |= 1 << 9;
    ADC1->CR2 |= 1 << 10;
    //

    DMA2_Stream0->CR |=  (4 << 25);  // 選 CH0 (ADC1)

    //設置外設地址(ADC1->DR)、資料寬度(16bit)、增量模式(位址不自增)
    DMA2_Stream4->PAR = (uint32_t)&ADC1->DR;
    DMA2_Stream4->CR  |= 1 << 11;
    DMA2_Stream4->CR  &= ~(1 << 9);



    //設置存儲器位址(AD_Value)、資料寬度(16bit)、增量模式(位址增量)
    DMA2_Stream4->M0AR = (uint32_t)&AD_Value;
    DMA2_Stream4->CR   |= 1 << 13;
    DMA2_Stream4->CR   |= 1 << 10;

    //設置循環模式(不循環)、數據方向(從外設讀)、通道優先級(中)、M2M(硬體觸發)
//    DMA1_Channel1->CCR |=  (1 << 5);
//    DMA1_Channel1->CCR &= ~(1 << 4);
//    DMA1_Channel1->CCR |=   1 << 12;
//    DMA1_Channel1->CCR &= ~(1 << 14);
    DMA2_Stream4->CR &= ~(1 << 8);
    DMA2_Stream4->CR &= ~(3 << 6);

    //設置數據傳輸數量
    DMA2_Stream4->NDTR = 2;

    DMA2_Stream4->CR |= 1 << 4;
    DMA2_Stream4->CR |= 1 << 1;

    //設置DMA始能(可先開)，因為還沒有觸發源，DMA不會動作
//    DMA1_Channel1->CCR |= (1 << 0);
    DMA2_Stream4->CR |= 1 << 0;




    //啟用ADC轉換
    ADC1->CR2 |= 1 << 0;

    //設置ADC使用DMA模式
	ADC1->CR2 |= 1 << 8;
    //設置ADC復位校準、ADC校準

}


void AD_GetValue(void)
{
    //設置外部觸發轉換模式(使用外部事件觸發)、開始轉換規則通道
    //若分開設定時有順序問題
	ADC1->CR2 |= (1 << 30);   // 開始轉換 (SWSTART)


    //由於目前ADC資料由DMA搬運，現在只需要等待DMA搬運完成即可，判斷旗標
    //判斷是否傳遞完成、清除標誌位
    while( (DMA2->HISR & (1 << 5) ) == 0);
    DMA2->HIFCR |= 1 << 5 ;
}



