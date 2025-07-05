#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder_TIM1.h"
#include "Encoder_TIM2.h"
#include "Encoder_TIM3.h"
#include "Encoder_TIM4.h"
#include "Serial.h"

#define TICKS_PER_REV 4680.0f //13*4*90

uint16_t Encoder1;			//定义速度变量
uint16_t Encoder2;			//定义速度变量
uint16_t Encoder3;			//定义速度变量
uint16_t Encoder4;

uint8_t RxData;
uint8_t RxFlag;

int main(void)
{

	
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Encoder_TIM1_Init();
	Encoder_TIM2_Init();
	Encoder_TIM3_Init();		//编码器初始化
	Encoder_TIM4_Init();		//编码器初始化
	Serial_Init();
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "TIM1:");	
	OLED_ShowString(2, 1, "TIM2:");			
	OLED_ShowString(3, 1, "TIM3:");		
	OLED_ShowString(4, 1, "TIM4:");		

	while (1)
	{
		if(RxFlag == 1)
		{
			Encoder1 = Encoder_TIM1_Get();								
			Encoder2 = Encoder_TIM2_Get();
			Encoder3 = Encoder_TIM3_Get();								
			Encoder4 = Encoder_TIM4_Get();
			
			//LSB first
			Serial_TxPacket[0] = (uint8_t) ( Encoder1 << 0);
			Serial_TxPacket[1] = (uint8_t) ( Encoder1 >> 8);
			
			Serial_TxPacket[2] = (uint8_t) ( Encoder2 << 0);
			Serial_TxPacket[3] = (uint8_t) ( Encoder2 >> 8);
			
			Serial_TxPacket[4] = (uint8_t) ( Encoder3 << 0);
			Serial_TxPacket[5] = (uint8_t) ( Encoder3 >> 8);
			
			Serial_TxPacket[6] = (uint8_t) ( Encoder4 << 0);
			Serial_TxPacket[7] = (uint8_t) ( Encoder4 >> 8);
			
			Serial_SendPacket();
			
			OLED_ShowNum(1, 7, Encoder1, 5);	
			OLED_ShowNum(2, 7, Encoder2, 5);	
			OLED_ShowNum(3, 7, Encoder3, 5);	
			OLED_ShowNum(4, 7, Encoder4, 5);	
			
			RxFlag = 0;
		}
		
	}
}



void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)		
	{
		if(USART_ReceiveData(USART2) == 0x01)	RxFlag = 1;
		
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}


