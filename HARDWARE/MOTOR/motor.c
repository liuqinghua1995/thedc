#include "motor.h"

void motor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA   ,ENABLE);//ʹ��PORTAʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
}
void motor_dir(u8 d)
{
	switch (d)
	{
	case left_go:
		motor01=0;
		motor00=1;
		break;
	case left_back:
		motor00=0;
		motor01=1;
		break;
	case left_stop:
		motor01=0;
		motor00=0;
		break;
	case right_go:
		motor11=0;
		motor10=1;
		break;
	case right_back:
		motor10=0;
		motor11=1;
		break;
	case right_stop:
		motor11=0;
		motor10=0;
		break;
	}
}

void left_speed(u16 i)
{
	TIM_SetCompare2(TIM3,i);	
}
void right_speed(u16 i)
{
	TIM_SetCompare1(TIM4,i);	
}
