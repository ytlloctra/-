#include "exti.h"
#include "delay.h" 
#include "edge.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
extern u8 cmd;
//////////////////////////////////////////////////////////////////////////////////	 
//�ⲿ�ж� ��������	   
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 

//�ⲿ�ж�0�������
void EXTI9_5_IRQHandler(void)
{
	//state=1;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(fedge1==1)
//	{
//		delay_ms(100);
//		if(fedge2==1)
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(500);
//		}
//	}
	
	EXTI_ClearITPendingBit(EXTI_Line5); 
}	
//�ⲿ�ж�1�������
void EXTI4_IRQHandler(void)
{
	//state=2;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(fedge2==1)
//	{
//		delay_ms(100);
//		if(fedge1==1)
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(500);
//		}
//	}
		EXTI_ClearITPendingBit(EXTI_Line4);
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	//state=3;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(bedge1==1)
//	{
//		delay_ms(100);
//		if(bedge2==1)
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(500);
//		}
//	}
	EXTI_ClearITPendingBit(EXTI_Line3); 
}
//�ⲿ�ж�4�������
void EXTI2_IRQHandler(void)
{
	//state=4;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(bedge2==1)
//	{
//		delay_ms(100);
//		if(bedge1==1)
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(500);
//		}
//	}
	EXTI_ClearITPendingBit(EXTI_Line2); 
}
	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);//PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource4);//PE4 ���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);//PA0 ���ӵ��ж���0
	
  /* ����EXTI_Line0 */
  /*EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����*/
	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 0��1
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}













