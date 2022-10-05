#include "timer.h"
#include "led.h"
#include "oled.h"
#define RIGHT_SHIFT  1//����λ��
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!

unsigned char zheng_or_fan=0;
int time=0;
extern u32 temp_z1,//��һ
		temp_z2,
		temp_z3,
		temp_z4,
		temp_z5,
		temp_z6,
		temp_y1,
		temp_y2,
		temp_y3,
		temp_y4,
		temp_y5,
		temp_y6,
		temp_Qz,//ǰ��
		temp_Hz,//����
		temp_back_H;
extern u16 value[15];
/*void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}
*/

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
							 
}


void TIM2_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		//LED1=!LED1;
			//time++;
		time=ENC_Get_Electrical_Angle();	
		//	TIM_SetCounter(TIM4, 0);   // ?????CNT
		/*	if(time>20) 
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_13);	 // �ر�����LED
				GPIO_SetBits(GPIOA, GPIO_Pin_15);	 // �ر�����LED
			}
			else 
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_13);	 // �ر�����LED
				GPIO_SetBits(GPIOA, GPIO_Pin_15);	 // �ر�����LED
			
			}
				if(time>40) time=0;*/
		}
}

int ENC_Get_Electrical_Angle(void)
{
 static  u16  lastCount = 0,lastdAngle=0;
 u16  curCount =TIM_GetCounter(TIM3);
  int dAngle = curCount - lastCount;
 if(dAngle<0)
	 {
   zheng_or_fan=2;//��ת
  }
	 else if(dAngle>0)
		 {
   zheng_or_fan=1;//��ת
 }
		 else  
{
   dAngle = 0;zheng_or_fan=0;//ͣ
 }
 lastCount = curCount;
 if(abs(dAngle)>120) {dAngle=lastdAngle;lastCount=0;}
 lastdAngle=dAngle;
  return dAngle; 
}




void TIM5_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
//	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
//		TIM5, //TIM2
//		TIM_IT_Update ,
//		ENABLE  //ʹ��
//		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx����
							 
}


void TIM5_IRQHandler(void)  {
	u8 i;

for(i=0;i<2;i++)
				{
					temp_z1=(value[5]>>RIGHT_SHIFT)+temp_z1;//   
					temp_z2=(value[4]>>RIGHT_SHIFT)+temp_z2;//    
					temp_z3=(value[3]>>RIGHT_SHIFT)+temp_z3;//   
					temp_z4=(value[2]>>RIGHT_SHIFT)+temp_z4;//    
					temp_z5=(value[1]>>RIGHT_SHIFT)+temp_z5;//     
					temp_z6=(value[0]>>RIGHT_SHIFT)+temp_z6;//      
					temp_y1=(value[6]>>RIGHT_SHIFT)+temp_y1;//     
					temp_y2=(value[7]>>RIGHT_SHIFT)+temp_y2;//  
					temp_y3=(value[8]>>RIGHT_SHIFT)+temp_y3;//   
					temp_y4=(value[9]>>RIGHT_SHIFT)+temp_y4;//  
					temp_y5=(value[10]>>RIGHT_SHIFT)+temp_y5;// 
					temp_y6=(value[11]>>RIGHT_SHIFT)+temp_y6;//
					temp_Qz=(value[13]>>RIGHT_SHIFT)+temp_Qz;//
					temp_Hz=(value[12]>>RIGHT_SHIFT)+temp_Hz;//
					temp_back_H=(value[14]>>RIGHT_SHIFT)+temp_back_H;//
				}

}




