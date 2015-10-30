#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "infr.h"
#include "HMC5883.h"
#include "motor.h"
#define abs(x) ((x)>=0?(x):(-(x)))
u16 len(u8 x1,u8 y1,u8 x2,u8 y2)
{
	return abs(x1-x2)+abs(y1-y2);
}

void init()
{
	delay_init();
	KEY_Init();
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	
	uart_init(115200);		    
 	TIM3_PWM_Init(899,0);	
	TIM4_PWM_Init(899,0);
	motor_init();
	infr_init();
	HMC5883_Init();
}
//获取道具
void get_weapon()
{
	u8 i;
	for (i=0;i<info.w_num;++i)
	{
		if (len(x,y,info.wx[i],info.wx[y])<=5)
		{
			uart_send(id,0x0E);
		}
	}
	
}
//使用道具
void use_weapon()
{
}

int main(void)
{		
	u16 i,len;
	init();
	left_speed(300);
	right_speed(300);
  while(1)
	{
		if (uart_update()==true)
		{
			if (info.status==1)
			{
				get_weapon();
				use_weapon();
				if (info.harm&0x01)//被施加防御类道具
				{}
				if (info.harm&0x02)//被施加攻击类道具
				{}
				if (info.harm&0x04)//被施加陷阱类道具
				{}
			}else{
				motor_dir(left_stop);
				motor_dir(right_stop);
			}
		}
		else{  //平时测试用
			/*
			if (KEY_Scan(0)==KEY0_PRES)
			{
				printf("abc");
			}
			if (USART_RX_STA2 & 0x8000)
			{
				len=USART_RX_STA2 & 0x3FFF;
				for (i=0;i<len;++i)
					printf("%c",USART_RX_BUF2[i]);
				USART_RX_STA2=0;
			}
			if (infr_check(LEFT))
			{
				motor_dir(left_go);
				motor_dir(right_stop);         
				delay_ms(10);
			}
			else if (infr_check(RIGHT))
			{
				motor_dir(left_stop);
				motor_dir(right_go);
				delay_ms(10);
				
			}else{
				motor_dir(left_go);
				motor_dir(right_go);
			}*/
			//KeepAngle();
			motor_dir(left_stop);
			motor_dir(right_stop);
			printf("%f\n\r",HMC_GetAngle());
			delay_ms(1000);
		}
	}	 
}

