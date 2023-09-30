#ifndef _LED_H_
#define _LED_H_

#include "stm32f4xx.h"


typedef struct {
    uint8_t on_level;
    GPIO_TypeDef *GPIOX;
    uint16_t GPIO_PIN_X;
}LED_;

void LED_On(LED_ LED_struct);
void LED_Off(LED_ LED_struct);

#endif
