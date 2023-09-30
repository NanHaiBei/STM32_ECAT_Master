#include "LED.h"

/*
 * 点亮LED
 * 参数：LED灯结构体
 */
void LED_On(LED_ LED_struct){
    HAL_GPIO_WritePin(LED_struct.GPIOX,LED_struct.GPIO_PIN_X,LED_struct.on_level);
}

/*
 * 熄灭LED
 * 参数：LED灯结构体
 */
void LED_Off(LED_ LED_struct){
    HAL_GPIO_WritePin(LED_struct.GPIOX,LED_struct.GPIO_PIN_X,!LED_struct.on_level);
}