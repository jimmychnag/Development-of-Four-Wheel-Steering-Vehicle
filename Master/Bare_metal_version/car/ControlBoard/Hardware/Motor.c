#include <PWM1.h>
#include <PWM2.h>
#include <PWM3.h>
#include <PWM4.h>
#include <stm32f446xx.h>



void Motor_Init(void)
{
	//PWM初始化
	Pwm1_Init();
	Pwm2_Init();
	Pwm3_Init();
	Pwm4_Init();

	//GPIOB 時鐘開啟，GPIOC 時鐘開啟
	RCC->AHB1ENR |= 1 << 1;
	RCC->AHB1ENR |= 1 << 2;
	RCC->AHB1ENR |= 1 << 0;

	//使用PC8 PC6當正反轉接角
	GPIOC->MODER &= ~(3 << 16);
	GPIOC->MODER |=   1 << 16;
	GPIOC->OTYPER&= ~(1 << 8);
	GPIOC->OSPEEDR |= 3 << 16;

	GPIOC->MODER &= ~(3 << 12);
	GPIOC->MODER |=   1 << 12;
	GPIOC->OTYPER&= ~(1 << 6);
	GPIOC->OSPEEDR |= 3 << 12;

	//使用PB12 PB13當正反轉接角
	GPIOB->MODER &= ~(3 << 24);
	GPIOB->MODER |=   1 << 24;
	GPIOB->OTYPER&= ~(1 << 12);
	GPIOB->OSPEEDR |= 3 << 24;

	GPIOB->MODER &= ~(3 << 26);
	GPIOB->MODER |=   1 << 26;
	GPIOB->OTYPER&= ~(1 << 13);
	GPIOB->OSPEEDR |= 3 << 26;
	
	//使用PA11、PA12當正反轉接角
	GPIOA->MODER &= ~(3 << 22);
	GPIOA->MODER |=   1 << 22;
	GPIOA->OTYPER&= ~(1 << 11);
	GPIOA->OSPEEDR |= 3 << 22;

	GPIOA->MODER &= ~(3 << 24);
	GPIOA->MODER |=   1 << 24;
	GPIOA->OTYPER&= ~(1 << 12);
	GPIOA->OSPEEDR |= 3 << 24;

	//使用PB14 PB15當正反轉接角
	GPIOB->MODER &= ~(3 << 28);
	GPIOB->MODER |=   1 << 28;
	GPIOB->OTYPER&= ~(1 << 14);
	GPIOB->OSPEEDR |= 3 << 28;

	GPIOB->MODER &= ~(3 << 30);
	GPIOB->MODER |=   1 << 30;
	GPIOB->OTYPER&= ~(1 << 15);
	GPIOB->OSPEEDR |= 3 << 30;
}


void Motor_SetSpeed(uint8_t name,int speed,float output)
{
	if(name == 1)//PC8、PC6
	{
		if(output >= 0)//正轉
		{
			GPIOC->BSRR  = 1 << 8;
			GPIOC->BSRR  = 1 << (6+16);
			PWM1_SetCompare1(speed);
		}
		else
		{
			GPIOC->BSRR  = 1 << (8+16);
			GPIOC->BSRR  = 1 << 6;
			PWM1_SetCompare1(speed);
		}
	}
	else if(name == 2) // PA11、PA12
	{
		if(output >= 0)//正轉
		{
			GPIOA->BSRR  = 1 << (11+16);
			GPIOA->BSRR  = 1 << 12;
			PWM2_SetCompare1(speed);
		}
		else
		{
			GPIOA->BSRR  = 1 << 11;
			GPIOA->BSRR  = 1 << (12+16);
			PWM2_SetCompare1(speed);
		}
	}
	else if(name == 3) // PB12、PB13
	{
		if(output >= 0)//正轉
		{

			GPIOB->BSRR  = 1 << 12;
			GPIOB->BSRR  = 1 << (13+16);
			PWM3_SetCompare1(speed);
		}
		else
		{
			GPIOB->BSRR  = 1 << (12+16);
			GPIOB->BSRR  = 1 << 13;
			PWM3_SetCompare1(speed);
		}
	}
	else if(name == 4) // PB14、PB15
	{
		if(output >= 0)//正轉
		{
			GPIOB->BSRR  = 1 << (14+16);
			GPIOB->BSRR  = 1 << 15;
			PWM4_SetCompare1(speed);
		}
		else
		{
			GPIOB->BSRR  = 1 << 14;
			GPIOB->BSRR  = 1 << (15+16);
			PWM4_SetCompare1(speed);
		}
	}

}
