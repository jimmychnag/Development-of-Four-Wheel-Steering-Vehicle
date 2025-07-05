#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "Adc.h"

//定義固定包長為4字節的數據包(收發)
//包長包尾則不儲存
uint8_t Serial_TxPacket[4]; 
uint8_t Serial_RxPacket[4];
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
    //開啟USART1、GPIOA時鐘
    RCC->APB2ENR |= 1 << 14;
    RCC->APB2ENR |= 1 << 2;

    //設置PA9為復用推挽輸出(TX)、PA10為上拉輸入(RX)
		GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |= 0xB << 4;
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |= 8   << 8;
    GPIOA->BSRR = 1   << 10;

    //設置字長(8位元)、校驗(不使用)、發送始能、接收始能
    USART1->CR1 &=~(1 << 12);
    USART1->CR1 &=~(3 << 9);
    USART1->CR1 |= 1 << 3;
    USART1->CR1 |= 1 << 2;

    //設置停止位(1bit)
    USART1->CR2 &= ~(3 << 12);

    //設置硬體流控(不用)
    USART1->CR3 &= ~(7 << 8);

    //設置波特率(9600)
//    USART1->BRR |= 468 << 4;
//    USART1->BRR |= 0xC << 0;
		
		//設置波特率(9600)
    USART1->BRR |= 39 << 4;
    USART1->BRR |= 1 << 0;

    //設置USART始能
    USART1->CR1 |= 1 << 13;
}

void Serial_SendByte(uint8_t Byte)
{
    //將字節寫入TDR
    USART1->DR = Byte & (uint16_t)0x1FF;
    //判斷TDR是否為空，若空了代表已經送到移位暫存器內，會被設置成1
    while( ( USART1->SR & (1 << 7) ) == 0);
}

void Serial_SendArray(uint16_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i ++)		
    {
        Serial_SendByte(Array[i]);		
    }
}

void Serial_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i ++)
    {
        Serial_SendByte(String[i]);		
    }
}


uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;	
    while (Y --)			
    {
        Result *= X;		
    }
    return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i ++)		
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);		
    return ch;
}

//接收格式化字符串和可變參數
void Serial_Printf(char *format, ...)
{
    char String[100];
    //用arg來儲存可變參數地址
    va_list arg;			        	
    //告訴 va_start 從 format 的下一個參數開始尋找可變參數
    va_start(arg, format);			
    //vsprintf 是 C 標準庫函數，用於將格式化字串和可變參數合併成最終的字串
    //並儲存到 String 陣列中。
    vsprintf(String, format, arg);	
    //va_end(arg) 是用來結束可變參數的使用。
    va_end(arg);			        //釋放參數表		
    Serial_SendString(String);		
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)			
	{
		Serial_RxFlag = 0;
		return 1;					
	}
	return 0;						
}

//輸出數據包，封包包頭包尾
void Serial_SendPacket(uint16_t *Array)
{
	Serial_SendByte(0xFF);
	Serial_SendArray(AD_Value , 3);
	Serial_SendByte(0xFE);
}

//接收中斷函式，使用狀態機執行
void USART1_IRQHandler(void)
{
    static uint8_t RxState = 0;//局部變數只用於此函式
    static uint8_t ptr = 0;

    //再次判斷是否RXNE有設置成1
    if (USART1->SR & (1 << 5))
    {
        uint8_t RxData = USART_ReceiveData(USART1);
        if(RxState == 0)//等待包頭
        {
            if(RxData == 0xFF)
                RxState = 1;
            else 
                RxState = 0;
        }
        else if(RxState == 1)//接收數據和紀錄接收次數
        {
            Serial_RxPacket[ptr] = RxData;
            ptr ++;
            if(ptr >= 4)
            {
                RxState = 2;
                ptr = 0;
            }
        }
        else if(RxState == 2)//等待包尾
        {
            if(RxData == 0xFE)
            {
                RxState = 0;
                Serial_RxFlag = 1;
            }
            else 
                RxState = 2;
        }
        //手動清除RXNE，但如果有讀值的話，也會自動清除
        USART1->SR &= ~(1 << 5);
    }
}
