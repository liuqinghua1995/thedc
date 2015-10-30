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
//��ȡ����
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
//ʹ�õ���
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
				if (info.harm&0x01)//��ʩ�ӷ��������
				{}
				if (info.harm&0x02)//��ʩ�ӹ��������
				{}
				if (info.harm&0x04)//��ʩ�����������
				{}
			}else{
				motor_dir(left_stop);
				motor_dir(right_stop);
			}
		}
		else{  //ƽʱ������
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

