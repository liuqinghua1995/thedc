#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define motor00 PAout(2)   	
#define motor01 PAout(3)   
#define motor10 PAout(4) 
#define motor11 PAout(5)

#define left_go 	  0	//����ǰ��
#define left_back 	1	//���ֺ���
#define left_stop 	2	//����ֹͣ

#define right_go 	  3	//����ǰ��
#define right_back 	4	//���ֺ���
#define right_stop 	5	//����ֹͣ

void motor_init(void);
void motor_dir(u8 d);
void left_speed(u16 i);
void right_speed(u16 i);
#endif
