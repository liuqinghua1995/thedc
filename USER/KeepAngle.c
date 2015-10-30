#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "infr.h"
#include "HMC5883.h"
#include "motor.h"
#define MaxDif 5
#define CorrectConst 5
void KeepAngle()
{
	static double current_angle=-1;
	double temp_angle=0;
	left_speed(300);
	right_speed(300);/*在之后的矫正方向过程中会改变速度，所以每次都要赋初值*/
	if(infr_check(LEFT))
	{
		motor_dir(left_go);
		motor_dir(right_stop);         
		delay_ms(10);
		current_angle=-1;//取一个指南针不可能返回的值
		return;
	}
	else if(infr_check(RIGHT))
	{
		motor_dir(right_go);
		motor_dir(left_stop);         
		delay_ms(10);
		current_angle=-1;//取一个指南针不可能返回的值
		return;
	}
	if(current_angle==-1) current_angle=HMC_GetAngle();
	else
	{
		temp_angle=HMC_GetAngle();
		if(current_angle>MaxDif&&current_angle<360-MaxDif)
		{
			if(abs(temp_angle-current_angle)<MaxDif)
			{
				motor_dir(left_go);
				motor_dir(right_go);
			}
			else if(temp_angle-current_angle>0)/*此处不确定角度从0-360是顺时针还是逆时针*/
			{
				left_speed(300-CorrectConst*(temp_angle-current_angle>0));
        motor_dir(left_go);
				motor_dir(right_go);
			}
      else if(temp_angle-current_angle<0)/*此处不确定角度从0-360是顺时针还是逆时针*/
			{
				right_speed(300-CorrectConst*(temp_angle-current_angle>0));
        motor_dir(left_go);
				motor_dir(right_go);
			}		
			else
			{
				motor_dir(left_go);
				motor_dir(right_go);
			}	
		}
    else if(current_angle>=0&&current_angle<=MaxDif)
    {
       if(temp_angle<=current_angle+MaxDif||temp_angle>=360-MaxDif+current_angle)			
			 {
				motor_dir(left_go);
				motor_dir(right_go);
			 }
       else if(temp_angle>=current_angle+MaxDif&&temp_angle<180)/*此处不确定角度从0-360是顺时针还是逆时针*/
			{
				left_speed(300-CorrectConst*(temp_angle-current_angle>0));
        motor_dir(left_go);
				motor_dir(right_go);
			}
      else if(temp_angle-current_angle>180)/*此处不确定角度从0-360是顺时针还是逆时针*/
			{
				right_speed(300-CorrectConst*(temp_angle-current_angle>0));
        motor_dir(left_go);
				motor_dir(right_go);
			}		
		}
    else if(current_angle>=360-MaxDif)
    {
       if(temp_angle<=current_angle+MaxDif-360||temp_angle>=current_angle-MaxDif)			
			 {
				motor_dir(left_go);
				motor_dir(right_go);
			 }
       else if(temp_angle<180)/*此处不确定角度从0-360是顺时针还是逆时针*/
			{
				left_speed(300-CorrectConst*(temp_angle-current_angle>0));
        motor_dir(left_go);
				motor_dir(right_go);
			}
      else
			{
				right_speed(300-CorrectConst*(temp_angle-current_angle>0));
        motor_dir(left_go);
				motor_dir(right_go);
			}		
		}					
	}
}
	