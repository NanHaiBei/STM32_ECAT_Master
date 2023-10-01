#include "DM9162.h"

/*
 * DM9162初始化
 */
void DM9162_Init(){
    //DM9162硬件复位，先拉低再拉高
    HAL_GPIO_WritePin(DM9162_NRST_PORT,DM9162_NRST_PIN,GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(DM9162_NRST_PORT,DM9162_NRST_PIN,GPIO_PIN_SET);
    HAL_Delay(100);

    // 设置滤波模式
    ETH_MACFilterConfigTypeDef filterDef;   //ETH MAC滤波器结构定义
    HAL_ETH_GetMACFilterConfig(&heth,&filterDef);        //获取 ETH MAC 过滤器配置
    filterDef.PromiscuousMode = DISABLE;                         //关闭过滤器使能PM模式
    HAL_ETH_SetMACFilterConfig(&heth,&filterDef);        //设置ETH MAC 过滤器
}

/*
 * DM9162循环检测是否已建立连接
 */
void DM9162_Link_Detect(){
    uint8_t link_state;
    link_state = DM9162_Link_Detect_Once();
    // 尚未建立连接
    if(link_state == 0){
        printf("No link established!Please plug in the Ethernet cable first!\r\n");
        // 循环读取状态位，直到建立连接
        while(link_state == 0){
            link_state = DM9162_Link_Detect_Once();
            HAL_Delay(100);
        }
    }
    if(link_state == 1){
        printf("Link established.\r\n");
        DM9162_Get_Link_Status();
    }
}

/*
 * DM9162读取连接状态
 */
void DM9162_Get_Link_Status(){
    uint32_t reg_temp;
    HAL_ETH_ReadPHYRegister(&heth,DM9162_PHY_ADDRESS,PHY_BCR,&reg_temp);
    if(reg_temp & 0x0100u){
        printf("Mode:Full-duplex\r\n");
    }
    else{
        printf("Mode:Half-duplex\r\n");
    }
    if(reg_temp & 0x2000u){
        printf("Speed:100Mbps\r\n");
    }
    else{
        printf("Speed:10Mbps\r\n");
    }
}

/*
 * 检测是否建立连接
 * 返回：1表示已建立连接，0表示未建立连接
 */
uint8_t DM9162_Link_Detect_Once(){
    uint32_t reg_temp;
    HAL_ETH_ReadPHYRegister(&heth,DM9162_PHY_ADDRESS,PHY_BSR,&reg_temp);
    if(reg_temp & 0x0004u){
        return 1;
    }
    else{
        return 0;
    }
}