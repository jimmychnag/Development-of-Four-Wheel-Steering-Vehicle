#ifndef __AD_H
#define __AD_H

#include <stm32f446xx.h>

//將數組設置成外部也可以用的
extern uint16_t AD_Value[4];

void AD_Init(void);
void AD_GetValue(void);

#endif
