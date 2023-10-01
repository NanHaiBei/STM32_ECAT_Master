#include "DM9162.h"

/*
 * DM9162��ʼ��
 */
void DM9162_Init(){
    //DM9162Ӳ����λ��������������
    HAL_GPIO_WritePin(DM9162_NRST_PORT,DM9162_NRST_PIN,GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(DM9162_NRST_PORT,DM9162_NRST_PIN,GPIO_PIN_SET);
    HAL_Delay(100);

    // �����˲�ģʽ
    ETH_MACFilterConfigTypeDef filterDef;   //ETH MAC�˲����ṹ����
    HAL_ETH_GetMACFilterConfig(&heth,&filterDef);        //��ȡ ETH MAC ����������
    filterDef.PromiscuousMode = DISABLE;                         //�رչ�����ʹ��PMģʽ
    HAL_ETH_SetMACFilterConfig(&heth,&filterDef);        //����ETH MAC ������
}

/*
 * DM9162ѭ������Ƿ��ѽ�������
 */
void DM9162_Link_Detect(){
    uint8_t link_state;
    link_state = DM9162_Link_Detect_Once();
    // ��δ��������
    if(link_state == 0){
        printf("No link established!Please plug in the Ethernet cable first!\r\n");
        // ѭ����ȡ״̬λ��ֱ����������
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
 * DM9162��ȡ����״̬
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
 * ����Ƿ�������
 * ���أ�1��ʾ�ѽ������ӣ�0��ʾδ��������
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