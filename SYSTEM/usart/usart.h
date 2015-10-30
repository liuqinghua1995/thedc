#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "stdbool.h"

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	

extern u8  USART_RX_BUF2[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA2;         		//接收状态标记	

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
bool uart_update(void);
void uart_send(u8 target,u8 wid);

typedef struct info{
	u8 id          : 2;
	u8 status      : 2;
	u8 warn        : 4;
	
	u8 w_exist     : 2;
	u8 w_num       : 2;
	u8 harm        : 4;
	
	u8 w1          : 4;
	u8 w2          : 4;
	
	u8 px[4];
	u8 py[4];
	u8 wx[4];
	u8 wy[4];
	
	u8 wfrom       : 4;
	u8 wto         : 4;
	u8 wid         : 8;
	
} inf;
extern inf info;                    //比赛信息
extern u8 id,x,y;                   //小车信息
#endif


