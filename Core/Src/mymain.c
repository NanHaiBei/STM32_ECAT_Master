#include "mymain.h"

LED_ State_LED = {1,GPIOG,GPIO_PIN_6};
float temp[1] = {0};
uint8_t vofa_JF[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x7f};

void mymain(){

    // 外设初始化
    Init();
    volatile uint32_t tim2_count = 0,tim5_count = 0;


//    printf("ok!\r\n");

    // 超级循环
    for(;;){
        temp[0] += 0.01f;
        tim2_count = TIM2->CNT;
        tim5_count = TIM5->CNT;
//        memcpy(vofa_JF,(uint8_t*)tim2_count,sizeof(tim2_count));
        memcpy(vofa_JF,(uint8_t*)&temp,sizeof(temp));
        HAL_UART_Transmit_DMA(&huart1,(uint8_t *)vofa_JF,sizeof(vofa_JF));
//        LED_On(State_LED);
//        printf("%ld,%ld\r\n",tim2_count,tim5_count);
        HAL_Delay(1);
//        LED_Off(State_LED);
//        HAL_Delay(500);
    }
}

/*
 * 各外设初始化
 */
void Init(){
    HAL_TIM_Base_Start(&htim2);
    HAL_TIM_Base_Start(&htim5);
    RetargetInit(&huart1);
}