#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define motor00 PAout(2)   	
#define motor01 PAout(3)   
#define motor10 PAout(4) 
#define motor11 PAout(5)

#define left_go 	  0	//×óÂÖÇ°½ø
#define left_back 	1	//×óÂÖºóÍË
#define left_stop 	2	//×óÂÖÍ£Ö¹

#define right_go 	  3	//ÓÒÂÖÇ°½ø
#define right_back 	4	//ÓÒÂÖºóÍË
#define right_stop 	5	//ÓÒÂÖÍ£Ö¹

void motor_init(void);
void motor_dir(u8 d);
void left_speed(u16 i);
void right_speed(u16 i);
#endif
