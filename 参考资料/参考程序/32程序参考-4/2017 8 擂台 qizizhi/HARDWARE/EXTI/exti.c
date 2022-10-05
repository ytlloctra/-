#include "exti.h"
#include "delay.h" 
#include "edge.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
#define z (800)//800
#define x (700)//900
#define y (500)//500
extern u8 zisuo,zisuo1,cmd;
//////////////////////////////////////////////////////////////////////////////////	 
 
//�ⲿ�ж� ��������	   
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 

//�ⲿ�ж�0�������
void EXTI15_10_IRQHandler(void)
{
	if(bedge1==1)
	{
		zhidong(1);
		delay_ms(100);
		if(bedge2==1)
		{
			motor(40,40);//40
			delay_ms(z);
			siqu();
			motor(50,-50);//50
			delay_ms(x);
			siqu();
		}
		else
		{
			motor(40,40);
			delay_ms(z);
			siqu();
			motor(50,-50);
			delay_ms(y);
			siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
	EXTI_ClearITPendingBit(EXTI_Line11); 
}	
//�ⲿ�ж�1�������
void EXTI3_IRQHandler(void)
{
	if(bedge2==1)
	{
		zhidong(1);
		delay_ms(100);
		if(bedge1==1)
		{
			motor(40,40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(x);siqu();
		}
		else
		{
			motor(40,40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(y);siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
		EXTI_ClearITPendingBit(EXTI_Line3);
}
//�ⲿ�ж�3�������
void EXTI1_IRQHandler(void)
{
	if(fedge1==1)
	{
		zhidong(1);
		delay_ms(100);
		if(fedge2==1)
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(50,-50);
			delay_ms(x);siqu();
		}
		else
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(50,-50);
			delay_ms(y);siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
	EXTI_ClearITPendingBit(EXTI_Line1); 
}
//�ⲿ�ж�4�������
void EXTI0_IRQHandler(void)
{
	if(fedge2==1)
	{
		zhidong(1);
		delay_ms(100);
		if(fedge1==1)
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(x);siqu();
		}
		else
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(y);siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
	EXTI_ClearITPendingBit(EXTI_Line0); 
}
	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);//PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);//PE4 ���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource11);//PA0 ���ӵ��ж���0
	
  /* ����EXTI_Line0 */
  /*EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����*/
	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line0 | EXTI_Line3 | EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 0��1
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}













