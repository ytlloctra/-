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
#ifndef __MOTOR_H
#define __MOTOR_H

#include "car_system.h"
#include "delay.h"
#include "sensors.h"

#define MAX_PWM     1799

#define STOP		0
#define FORWORD		1
#define BACKWORD	2
#define RIGHT		3
#define LEFT		4
#define DEFAULT		5

void MOTOR_Init(void);
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void CAR_Jump(u16 pwm_value_x,u16 pwm_value_y,u16 delay_time_x,u16 delay_time_y); 
void CAR_Stop(void);
void CAR_Move(u8 direction,u16 pwm_value);

#endif
