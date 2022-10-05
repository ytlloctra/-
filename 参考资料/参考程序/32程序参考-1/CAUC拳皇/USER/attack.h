//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//��̨������
//���ߣ�������
//�汾��V1.0
//�޸�����:2018/10/02
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#ifndef __ATTACK_H
#define __ATTACK_H

#include "car_system.h"
#include "motor.h"
#include "sensors.h"
#include "encoder.h"

#define SCAN(ADC_NAME) EYE_##ADC_NAME>EYE_THRESHOLD.##ADC_NAME
#define SCAN_EXACT(ADC_NAME) EYE_##ADC_NAME>EYE_THRESHOLD.EXACT

u8   Scan_Gesture(void);
u8   Judge_State_Chess(void);
u8   Judge_State_Car(void);
void Attack_Car(void);
void Attack_Car_Single(void);
void Attack_Chess(void);
void MODE_Attack_Chess(void);
void MODE_Attack_Car(void);
void MODE_Attack_Car_Single(void);
void Jump(void);
void Jump_Test(void);
void Jump_Restoration(void);
void Falling_Test(void);
u8   Find_Arena(void);
void Ready_Jump(void);

#endif
