#include "infr.h"

void infr_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTC时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
}
bool infr_check(u8 id)
{
	switch(id)
	{
	case LEFT:
		return INFR0;
	case RIGHT:
		return INFR1;
	}
	return false;
}
