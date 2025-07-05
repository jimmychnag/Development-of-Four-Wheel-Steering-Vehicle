#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;					//定义全局变量，用于记住Init函数的Size，供Transfer函数使用

/**
  * 函    数：DMA初始化
  * 参    数：AddrA 原数组的首地址
  * 参    数：AddrB 目的数组的首地址
  * 参    数：Size 转运的数据大小（转运次数）
  * 返 回 值：无
  */
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
	//將Size寫到全局變量，給之後MyDMA_Transfer開啟時，供傳輸計數器使用
	MyDMA_Size = Size;					
	
	//開啟AHB外設時鐘(DMA1時鐘)
	RCC->AHBENR |= 1 << 0;
	
	
	//設置外設地址、資料寬度、增量模式(位址增量)
	DMA1_Channel1->CPAR = AddrA;
	DMA1_Channel1->CCR &= ~(3 << 8);
	DMA1_Channel1->CCR |=  (1 << 6);
	
	//設置存儲器位址、資料寬度、增量模式(位址增量)
	DMA1_Channel1->CMAR = AddrB;
	DMA1_Channel1->CCR &= ~(3 << 10);
	DMA1_Channel1->CCR |=   1 << 7;
	
	//設置循環模式(不循環)、數據方向(從外設讀)、通道優先級(中)、M2M(軟體觸發)
	DMA1_Channel1->CCR &= ~(1 << 5);
	DMA1_Channel1->CCR &= ~(1 << 4);
	DMA1_Channel1->CCR |=   1 << 12;
	DMA1_Channel1->CCR |=   1 << 14;
	
	

	//設置數據傳輸數量
	DMA1_Channel1->CNDTR |= Size;
	
	/*DMA使能*/
//	DMA_Cmd(DMA1_Channel1, DISABLE);	//这里先不给使能，初始化后不会立刻工作，等后续调用Transfer后，再开始

	//設置DMA始能(先不開)
	DMA1_Channel1->CCR &= ~(1 << 0);
}

/**
  * 函    数：启动DMA数据转运
  * 参    数：无
  * 返 回 值：无
  */
void MyDMA_Transfer(void)
{
//	DMA_Cmd(DMA1_Channel1, DISABLE);					//DMA失能，在写入传输计数器之前，需要DMA暂停工作
//	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);	//写入传输计数器，指定将要转运的次数
//	DMA_Cmd(DMA1_Channel1, ENABLE);						//DMA使能，开始工作
	
	//先設置失能、再寫入傳輸計數器值、再始能
	DMA1_Channel1->CCR &= ~(1 << 0);
	DMA1_Channel1->CNDTR = MyDMA_Size;
	DMA1_Channel1->CCR |=   1 << 0;
	
//	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);	//等待DMA工作完成
//	DMA_ClearFlag(DMA1_FLAG_TC1);						//清除工作完成标志位

	//判斷是否傳遞完成、清除標誌位
	while( (DMA1->ISR & (1 << 1) ) == 0);
	DMA1->IFCR |= 1 << 1 ;

}
