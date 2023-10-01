#ifndef _DM9162_H_
#define _DM9162_H_

#include "stm32f4xx.h"
#include "eth.h"

//PHYµÿ÷∑
#define DM9162_PHY_ADDRESS       ((uint16_t) 0x01)

#define	DM9162_NRST_PORT GPIOB
#define	DM9162_NRST_PIN GPIO_PIN_10

void DM9162_Init();
uint8_t DM9162_Link_Detect_Once();
void DM9162_Link_Detect();
void DM9162_Get_Link_Status();

#endif