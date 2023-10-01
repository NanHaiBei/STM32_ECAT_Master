#include "mymain.h"

LED_ State_LED = {1,GPIOG,GPIO_PIN_6};
float temp[2] = {0};
uint8_t vofa_JF[12] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x7f};
uint32_t reg_temp;
void mymain(){

    // 外设初始化
    Init();
    volatile uint32_t tim2_count = 0,tim5_count = 0;



    // 超级循环
    for(;;){
        HAL_ETH_ReadPHYRegister(&heth,DM9162_PHY_ADDRESS,PHY_BSR,&reg_temp);
        printf("%ld\r\n",reg_temp);
//        tim2_count = TIM2->CNT;
//        tim5_count = TIM5->CNT;
//        temp[0] = (float)tim2_count;
//        temp[1] = (float)tim5_count;
//        memcpy(vofa_JF,(uint8_t*)&temp,sizeof(temp));
//        HAL_UART_Transmit_DMA(&huart1,(uint8_t *)vofa_JF,sizeof(vofa_JF));
//        LED_On(State_LED);
//        printf("%ld,%ld\r\n",tim2_count,tim5_count);
        HAL_Delay(100);
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
    //串口初始化
    RetargetInit(&huart1);

    //网卡初始化
    DM9162_Init();
}