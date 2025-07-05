#ifndef __PWM4_H
#define __PWM4_H

#include <stm32f446xx.h>

void Pwm4_Init(void);
void PWM4_SetCompare1(uint16_t Compare);
void PWM4_SetPrescaler(uint16_t Prescaler);

#endif
