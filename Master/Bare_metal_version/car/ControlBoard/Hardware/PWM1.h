#ifndef __PWM1_H
#define __PWM1_H

#include <stm32f446xx.h>

void Pwm1_Init(void);
void PWM1_SetCompare1(uint16_t Compare);
void PWM1_SetPrescaler(uint16_t Prescaler);

#endif
