//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//�����������
//���ߣ�������
//�汾��V1.0
//�޸�����:2018/10/02
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#include "motor.h"

/** 
	* @brief	���е����ʼ��
	* @since	v1.0
	* @note		���PWMƵ��=72000/(1799+1)=40Khz
	*/
void MOTOR_Init(void)
{
	TIM1_PWM_Init(1799,0);
	TIM4_PWM_Init(1799,0);
}



/** 
	* @brief	�˶������ʼ��
	* @since	v1.0
	*/
void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_DeInit(TIM1); 

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM1,ENABLE);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	TIM_Cmd(TIM1, ENABLE);
}



/** 
	* @brief	��̨�����ʼ��
	* @since	v3.0
	*/
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4  , ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_DeInit(TIM4); 

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM4,ENABLE);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	TIM_Cmd(TIM4, ENABLE);
}



/** 
	* @brief	��̨
	* @param	pwm_value_x		��̨���PWM�Ƚ�ֵ
	* @param	pwm_value_y		��̨���PWM�Ƚ�ֵ
	* @param	delay_time_x	��̵����תʱ��
	* @param	delay_time_y	��̨�����תʱ��
	* @since	v3.0
	*/
void CAR_Jump(u16 pwm_value_x,u16 pwm_value_y,u16 delay_time_x,u16 delay_time_y)
{
	if(pwm_value_x > MAX_PWM)
		pwm_value_x = MAX_PWM;
	if(pwm_value_y > MAX_PWM)
		pwm_value_y = MAX_PWM;
	if(delay_time_x != 0)
	{
		TIM1->CCR1 = pwm_value_x;
		TIM1->CCR4 = pwm_value_x;
		delay_ms(delay_time_x);
	}
	TIM4->CCR3 = pwm_value_y;
	while(!EYE3_JP);
	delay_ms(10);
	while(EYE3_JP);
	TIM4->CCR3 = 0;
	delay_ms(delay_time_y);
	TIM1->CCR1 = 0;
	TIM1->CCR4 = 0;
}



/** 
	* @brief	ɲ��
	* @since	v1.0
	*/

void CAR_Stop()
{
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	TIM1->CCR4 = 0;
}



/** 
	* @brief	�����˶�
	* @param	direction		�˶�����
	* @param	pwm_value		PWM�Ƚ�ֵ
	* @since	v1.0
	*/
void CAR_Move(u8 direction,u16 pwm_value)
{
	if(pwm_value > MAX_PWM)
		pwm_value = MAX_PWM;
	switch(direction)
	{
		case FORWORD:
			TIM1->CCR1 = pwm_value;
			TIM1->CCR2 = 0;
			TIM1->CCR3 = 0;
			TIM1->CCR4 = pwm_value;
			break;
		case BACKWORD:
			TIM1->CCR1 = 0;
			TIM1->CCR2 = pwm_value;
			TIM1->CCR3 = pwm_value;
			TIM1->CCR4 = 0;
			break;
		case RIGHT:
			TIM1->CCR1 = pwm_value;
			TIM1->CCR2 = 0;
			TIM1->CCR3 = pwm_value;
			TIM1->CCR4 = 0;
			break;
		case LEFT:
			TIM1->CCR1 = 0;
			TIM1->CCR2 = pwm_value;
			TIM1->CCR3 = 0;
			TIM1->CCR4 = pwm_value;
			break;
		case STOP:
			TIM1->CCR1 = 0;
			TIM1->CCR2 = 0;
			TIM1->CCR3 = 0;
			TIM1->CCR4 = 0;
		default: 
			TIM1->CCR1 = pwm_value;
			TIM1->CCR2 = 0;
			TIM1->CCR3 = 0;
			TIM1->CCR4 = pwm_value;
	}
}
