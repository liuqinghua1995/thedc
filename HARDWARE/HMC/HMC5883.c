#include "HMC5883.h"
#define MMA_ADR 0x3c
u32 I2CStep;
void HMC_Delay(void)
{
	I2CStep=10;
	while(I2CStep--);
}
void HMC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
u8 HMC_Start(void)
{
	HMC_SDA_H;
	HMC_Delay();
	HMC_SCL_H;
	HMC_Delay();
	if(!HMC_SDA) return 0;//SDA线为低电平则总线忙,退出
	HMC_SDA_L;
	return 1;
}
void HMC_I2C_Stop(void)
{
	HMC_SCL_L;
	HMC_Delay();
	HMC_SDA_L;
	HMC_Delay();
	HMC_SCL_H;
	HMC_Delay();
	HMC_SDA_H;
	HMC_Delay();
}
void HMC_I2C_Ack(void)
{
	HMC_SCL_L;
	HMC_Delay();
	HMC_SDA_L;
	HMC_Delay();
	HMC_SCL_H;
	HMC_Delay();
	HMC_SCL_L;
	HMC_Delay();
}
void HMC_I2C_NAck(void)
{
	HMC_SCL_L;
    HMC_Delay();
    HMC_SDA_H;
    HMC_Delay();
    HMC_SCL_H;
    HMC_Delay();
    HMC_SCL_L;
    HMC_Delay();
}
u8 HMC_I2C_WaitAck(void)
{
	HMC_SCL_L;
    HMC_Delay();
    HMC_SDA_H;			
    HMC_Delay();
    HMC_SCL_H;
    HMC_Delay();
    if(HMC_SDA)
    {
		HMC_SCL_L;
		return 0;
    }
    HMC_SCL_L;
    return 1;
}
void HMC_I2C_SendByte(u8 SendByte) //数据从高位到低位
{
    u8 i=8;
    while(i--)
	{
		HMC_SCL_L;
		HMC_Delay();
		if(SendByte&0x80)
			HMC_SDA_H;
		else
			HMC_SDA_L;
		SendByte<<=1;
		HMC_Delay();
		HMC_SCL_H;
		HMC_Delay();
	}
	HMC_SCL_L;
}
u8 HMC_I2C_ReceiveByte(void)  //数据从高位到低位//
{ 
	u8 i=8;
	u8 ReceiveByte=0;

	HMC_SDA_H;				
	while(i--)
	{
		ReceiveByte<<=1;      
		HMC_SCL_L;
		HMC_Delay();
		HMC_SCL_H;
		HMC_Delay();	
		if(HMC_SDA)
		{
			ReceiveByte|=0x01;
		}
	}
	HMC_SCL_L;
	return ReceiveByte;
}
u8 HMC_I2C_Write(u8 address,u8 data)
{
	HMC_Start();
	HMC_I2C_SendByte(MMA_ADR);//设置器件地址
	HMC_I2C_Ack();
	HMC_I2C_SendByte(address);   //设置低起始地址      
	HMC_I2C_Ack();	
	HMC_I2C_SendByte(data);
	HMC_I2C_Ack();   
	HMC_I2C_Stop(); 
	return 1;	
}

u8 HMC_I2C_Read(u8 address)//读字节
{
	u8 temp=0;
	HMC_Start();
	HMC_I2C_SendByte(MMA_ADR);//设置器件地址
	HMC_I2C_Ack();
	HMC_I2C_SendByte(address);   //设置低起始地址      
	HMC_I2C_Ack();
	HMC_Start();
	HMC_I2C_SendByte(MMA_ADR|0x01);//设置器件地址
	HMC_I2C_Ack();
	temp=HMC_I2C_ReceiveByte();
	HMC_I2C_Ack();
	HMC_I2C_Stop();
	return temp;
}

void HMC_MultipleRead(u8* pBuffer)
{
	u8 i=0;
	HMC_Start();
	HMC_I2C_SendByte(0x3c);
	HMC_I2C_WaitAck();
	HMC_I2C_SendByte(0x03);
	HMC_I2C_WaitAck();
	HMC_Start();
	HMC_I2C_SendByte(0x3c+1);
	HMC_I2C_WaitAck();
	for(i=0;i<6;i++)
	{
		pBuffer[i]=HMC_I2C_ReceiveByte();
		if(i == 5)
			HMC_I2C_NAck();
		else
			HMC_I2C_Ack();
	}
	
	HMC_I2C_Stop();
}
void HMC_GetValue(s16* pBuffer)
{
	u8 tmp[6];
	HMC_MultipleRead(tmp);
	
	pBuffer[0]=(s16) ( (((u16)tmp[0])<<8) + tmp[1] );
	pBuffer[1]=(s16) ( (((u16)tmp[2])<<8) + tmp[3] );
	pBuffer[2]=(s16) ( (((u16)tmp[4])<<8) + tmp[5] );
}
u8 HMC5883_Init(void)
{
	HMC_GPIO_Config();
	HMC_I2C_Write(0x02,0x00);//开始转换
	return HMC_I2C_Read(10);
}

double HMC_GetAngle(void)
{
	s16 tmp[3];
	HMC_GetValue(tmp);
	return atan2((double)tmp[1],(double)tmp[0]) * (180 / 3.14159265) + 180;
}
