#ifndef __HMC5883_H
#define __HMC5883_H

#include "stm32f10x.h"
#include "math.h"

#define HMC_SCL_H (GPIOB->BSRR=GPIO_Pin_8)
#define HMC_SCL_L (GPIOB->BRR=GPIO_Pin_8)

#define HMC_SDA_H (GPIOB->BSRR=GPIO_Pin_7)
#define HMC_SDA_L (GPIOB->BRR=GPIO_Pin_7)

#define HMC_SDA (GPIOB->IDR & GPIO_Pin_7)

#define HMC5883L_OFFSET_X (9)
#define HMC5883L_OFFSET_Y (149)

#define HMC5883L_GAIN_Y 10403

u8 HMC5883_Init(void);
void HMC_MultipleRead(u8* pBuffer);
void HMC_GetValue(s16* pBuffer);
double HMC_GetAngle(void);
#endif
