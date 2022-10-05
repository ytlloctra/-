#include "sumjess_pwm.h"

/*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��09��06��
�������Ϣ�ο����е�ַ��
����    վ��
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
�������޶���2018/09/06
��problem ��
    ��1�����ڲ���Ĳ�ȫ�棻
    ��2�����ڽ��Ͳ��ֲ�ȫ�棻
    ��3�����ڻ�����һ����bug��
��direction��
      ��һ����Ŀ����ǰѿ�������ɣ�
��explain ��
      �����Ǹ�������ԭ�ӡ��о�԰���ӡ����ŵ��ӵ��̼Ҹı���ɣ�
      ͬʱΪ�˷���ʹ�ã���Ҳ�Լ�д�˺ܶ�Ŀ⣬���Ż����㷨�ͱ�ʾ��ʽ��
��warning��
      Ŀǰ���������޾��� ��   
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************/	
//PWM ��������
////////////////////////////////////////////////////////////////////////////////// 	  
///////ӳ���������timer.c��///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int a=0,b=0,c=0,d=0;


void speed_Init(void)    //TIM3_CH1->PC6 CH2->PC7 CH3->PC8 CH4->PC9
{ 
		//**********�����������************//
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��  
		TIM_DeInit(TIM3);//��ʼ��TIM3�Ĵ���
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��  
		TIM_DeInit(TIM2);//��ʼ��TIM3�Ĵ���
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer3��ȫ��ӳ��  TIM3_CH1->PC6 CH2->PC7 CH3->PC8 CH4->PC9
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM1_CH1  //���ø�����Ϊ�����������,���TIM3 CH1��PWM���岨�� GPIOC.6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO                
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;//TIM1_CH1  //���ø�����Ϊ�����������,���TIM3 CH1��PWM���岨�� GPIOC.6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO                	
		//**************************************************************************
		//  ��ʱ��1���ã� 72��Ƶ��Ƶ��10KHz�����ϼ���,105��Ϊ���ٶ�Ϊ100ʱ��PWMռ�ձȲ��ᵽ100�������������Ծ���ѹ��һ��PWMƵ�ʴ���1K��4-10K�ȽϺá�
		//************************************************************************** 
		TIM_TimeBaseStructure.TIM_Period = 105-1;
		TIM_TimeBaseStructure.TIM_Prescaler = 71;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
		// ����ʱ��T3Ϊ PWM3 ģʽ 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;  
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);			
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���
		
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ�ܵ�Ԥװ�ؼĴ���			
 
		TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ�ܶ�ʱ��3
		TIM_Cmd(TIM3, ENABLE);
		TIM_ARRPreloadConfig(TIM2, ENABLE); //ʹ�ܶ�ʱ��3
		TIM_Cmd(TIM2, ENABLE);
}

void drive_around(void)
{
   a=0;b=0;
//���
	TIM_SetCompare1(TIM3,5);
	TIM_SetCompare2(TIM3,95);
//�ұ�
	TIM_SetCompare3(TIM3,95);
	TIM_SetCompare4(TIM3,5);

}

void drive_For_L(void)
{
     a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,30);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,30);

}

void drive_For_M(void)
{
     a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,90);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,90);

}

void drive_For_H(void)
{
   if(a<500)
	 {
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,55);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,55);
		 ++a;
	 }
	 else{
//���
	TIM_SetCompare1(TIM3,5);
	TIM_SetCompare2(TIM3,95);
//�ұ�
	TIM_SetCompare3(TIM3,5);
	TIM_SetCompare4(TIM3,95);
	 }
}


void drive_Back_L(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,30);
	TIM_SetCompare2(TIM3,10);
//�ұ�
	TIM_SetCompare3(TIM3,30);
	TIM_SetCompare4(TIM3,10);
}

void drive_Back_M(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,90);
	TIM_SetCompare2(TIM3,10);
//�ұ�
	TIM_SetCompare3(TIM3,90);
	TIM_SetCompare4(TIM3,10);
}

void drive_Back_H(void)
{
	if(b<500) {
//���
	TIM_SetCompare1(TIM3,50);
	TIM_SetCompare2(TIM3,10);
//�ұ�
	TIM_SetCompare3(TIM3,50);
	TIM_SetCompare4(TIM3,10);
		++b;
	}
	else{
//���
	TIM_SetCompare1(TIM3,95);
	TIM_SetCompare2(TIM3,5);
//�ұ�
	TIM_SetCompare3(TIM3,95);
	TIM_SetCompare4(TIM3,5);
	}
	
}

void drive_Left(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,20);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,80);
}

void drive_Right(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,80);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,20);
}

void drive_Stop(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,10);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,10);
}

void drive_Left_M(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,20);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,50);
}

void drive_Right_M(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,50);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,20);
}

void drive_Left_S(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,70);
	TIM_SetCompare2(TIM3,10);
//�ұ�
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,70);
}

void drive_Right_S(void)
{
	 a=0;b=0;
//���
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,70);
//�ұ�
	TIM_SetCompare3(TIM3,70);
	TIM_SetCompare4(TIM3,10);
} 

