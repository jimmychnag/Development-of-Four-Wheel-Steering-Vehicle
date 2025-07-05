#ifndef __PWM3_H
#define __PWM3_H

#include <stm32f446xx.h>

void Pwm3_Init(void);
void PWM3_SetCompare1(uint16_t Compare);
void PWM3_SetPrescaler(uint16_t Prescaler);

#endif
