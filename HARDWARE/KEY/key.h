#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0 PAin(0)   	//PA0

//#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
 

#define KEY0_PRES 	1	//KEY0����

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
