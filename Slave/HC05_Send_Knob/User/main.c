#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "MyDMA.h"
#include "Adc.h"


uint8_t RxData;
uint8_t RxFlag;

uint8_t Data_L;
uint8_t Data_H;

uint16_t AD_Value_Last[3] = {0};
uint16_t diff;

int main(void)
{
	//將PB7 輸出高電平當OLED VCC
	//將PB6 輸出低電瓶當OLED GND

	RCC -> APB2ENR = 0x00000008;
	GPIOB->CRL     = 0x30000000;
	GPIOB->CRL    |= 0x03000000;

	GPIOB->BSRR = 0x00400000;
	GPIOB->BSRR = 0x00000080;

	/*模块初始化*/
	OLED_Init();			//OLED初始化
	AD_Init();				//AD初始化
	Serial_Init();

	/*显示静态字符串*/
	OLED_ShowString(1, 1, "ADC_In0:");
	OLED_ShowString(2, 1, "ADC_In1:");
	OLED_ShowString(3, 1, "ADC_In2:");

	while (1)
	{
		AD_GetValue();
		
		Serial_SendByte(0xFF);
		Data_L = AD_Value[0] >> 0;
		Serial_SendByte(Data_L);
		Data_H = AD_Value[0] >> 8;
		Serial_SendByte(Data_H);

		Data_L = AD_Value[1] >> 0;
		Serial_SendByte(Data_L);
		Data_H = AD_Value[1] >> 8;
		Serial_SendByte(Data_H);
		
		Data_L = AD_Value[2] >> 0;
		Serial_SendByte(Data_L);
		Data_H = AD_Value[2] >> 8;
		Serial_SendByte(Data_H);
		
		Serial_SendByte(0xFE);
		
	}
}

