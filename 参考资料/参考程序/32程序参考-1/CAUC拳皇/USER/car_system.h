//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//ϵͳȫ�ֺ궨�塢ȫ�ֱ�������
//���ߣ�������
//�汾��V2.0
//�޸�����:2018/10/02
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#ifndef __CAR_SYSTEM_H
#define __CAR_SYSTEM_H

#include "sys.h"
#include "delay.h"
#include "oled.h"
#include "buzzer.h"
#include "adc.h"
#include "led.h"
#include "key.h"
#include "flash.h"
#include "dma.h"

/*Ĭ�ϲ�������*/
#define ADC_THRESHOLD_INIT			1300	//ADC������ֵ
#define ADC_THRESHOLD_EXACT_INIT	1100	//ADC������ֵ
#define ADC_THRESHOLD_FBMM_INIT		900		//�󴫸�����ֵ

#define SUNDRY_MISSCOUNT_INIT 		10		//��ʧĿ�����
#define SUNDRY_LOCKCOUNT_INIT		20		//����Ŀ�����
#define SUNDRY_MARGINDELAY_INIT		150		//������ʱ
#define SUNDRY_JUMPDELAY_X_INIT		10		//��̨���ʱ��
#define SUNDRY_JUMPDELAY_Y_INIT		100		//��̨�����תʱ��
#define SUNDRY_JUMPDELAY_B_INIT		100		//��̨���ְ�ȫ�����ʱ��
#define SUNDRY_JUMPADCValue_INIT	300		//��̨��̨ADC�������

#define PWM_C_INIT					600		//������ģʽPWM
#define PWM_A_INIT					1100	//����PWM
#define PWM_S_INIT					700		//��̨ģʽֱ��PWM
#define PWM_T_INIT					800		//��̨ģʽת��PWM
#define PWM_D_INIT					500		//��̨ģʽɨ̨PWM
#define PWM_M_INIT					1299	//��̨ģʽ��תPWM
#define PWM_JX_INIT					800		//��̨���PWM
#define PWM_JY_INIT					1400	//��̨���PWM
#define PWM_FALL_INIT				500		//��̨Ѱ̨PWM

/*�����ͱ�ʶ������*/
#define TRUE	1
#define FALSE	0

/*�������PWMռ�ձȽṹ�嶨��*/
typedef struct{
	u16 Chess;			//������ʱ��PWMռ�ձ�
	u16 Avoid;			//����ʱ��PWMռ�ձ�
	u16 Straight;		//ֱ������ʱ��PWMռ�ձ�
	u16 Turn;			//ת��ʱ��PWMռ�ձ�
	u16 Default;		//��ʧĿ��ʱ��PWMռ�ձ�
	u16 Max;			//����ʱ��PWMռ�ձ�
	u16 JumpX;			//��̨ʱֱ�е����PWMռ�ձ�
	u16 JumpY;			//��̨ʱ��̨�����PWMռ�ձ�
	u16 Falling;		//��̨ʱ��PWMռ�ձ�
}	CAR_PWM;

/*�������ת�ٽṹ�嶨��*/
typedef struct{
	u16 Forword;		//ǰ��ʱ��ת��
	u16 Backword;		//����ʱ��ת��
	u16 Right;			//��תʱ��ת��
	u16 Left;			//��תʱ��ת��
	u8 	ErrorRange_S;	//ֱ����Χ
	u8 	ErrorRange_T;	//ת����Χ
}	CAR_SPEED;

/*����ADC��ֵ�ṹ�嶨��*/
typedef struct{
	u16 ALL;		//����ADC����ֵ
	u16 MRF;		//�����в��Ҳ�ǰ��ADC����ֵ
	u16 MRM;		//�����в��Ҳ��в�ADC����ֵ
	u16 MRB;		//�����в��Ҳ��ADC����ֵ
	u16 MLF;		//�����в����ǰ��ADC����ֵ
	u16 MLM;		//�����в�����в�ADC����ֵ
	u16 MLB;		//�����в�����ADC����ֵ
	u16 FOR;		//����ǰ���ⲿ�Ҳ�ADC����ֵ
	u16 FOL;		//����ǰ���ⲿ���ADC����ֵ
	u16 FMR;		//����ǰ���в��Ҳ�ADC����ֵ
	u16 FMM;		//����ǰ���в��в�ADC����ֵ
	u16 FML;		//����ǰ���в����ADC����ֵ
	u16 BOR;		//�������ⲿ�Ҳ�ADC����ֵ
	u16 BOL;		//�������ⲿ���ADC����ֵ
	u16 BML;		//�������в����ADC����ֵ
	u16 BMM;		//�������в��в�ADC����ֵ
	u16 BMR;		//�������в��Ҳ�ADC����ֵ
	u16 EXACT;		//����ADC��ȷ��ֵ
	u16 LAST;		//����ADC����ֵ
}	ADC_THRESHOLD;

/*����ṹ�嶨��*/
typedef struct{
	u16 Miss_Count;		//��ʧĿ���ļ���ֵ
	u16	Lock_Count;		//����Ŀ���ļ���ֵ
	u16 Margin_Delay;	//��ܱ�Եʱת����ʱ
	u16 Jump_Delay_X;	//��̨ʱ���ʱ��
	u16 Jump_Delay_Y;	//��̨ʱ��̨�����תʱ��
	u16 Jump_Delay_B;	//��̨��Ϊ���ְ�ȫ����ĺ�ʱ��
	u16 Jump_ADC_Value;	//��̨��ADC��̨���
}	CAR_SUNDRY;

/*ȫ�ֱ�������*/
extern CAR_PWM			MOTOR_PWM;
extern ADC_THRESHOLD 	EYE_THRESHOLD;
extern CAR_SPEED 		ENCODER_VALUE;
extern CAR_SUNDRY 		SETTING_SUNDRY;
extern u16 				miss_count;

#endif
