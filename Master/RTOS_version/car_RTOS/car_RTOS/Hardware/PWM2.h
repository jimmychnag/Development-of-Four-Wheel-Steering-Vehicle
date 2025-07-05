#ifndef __PWM2_H
#define __PWM2_H

#include <stm32f446xx.h>

void Pwm2_Init(void);
void PWM2_SetCompare1(uint16_t Compare);
void PWM2_SetPrescaler(uint16_t Prescaler);

#endif
