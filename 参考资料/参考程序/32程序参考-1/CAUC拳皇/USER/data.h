//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//���ݲ���������
//���ߣ�������
//�汾��V2.0
//�޸�����:2018/10/04
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#ifndef __DATA_H
#define __DATA_H

#include "car_system.h"
#include "flash.h"
#include "motor.h"
#include "encoder.h"
#include "buzzer.h"

/*�ṹ�����ݿ��*/
#define PWM_DATA_LENTH			9
#define ADC_DATALENTH			19
#define ENCODER_DATA_LENTH      6
#define SUNDRY_DATA_LENTH		7

/*�ṹ�����ݴ洢��ַ*/
#define PWM_DATA_ADDR			ADDR_FLASH_PAGE_60
#define ADC_DATA_ADDR 		    ADDR_FLASH_PAGE_61
#define ENCODER_DATA_ADDR       ADDR_FLASH_PAGE_62
#define SUNDRY_DATA_ADDR        ADDR_FLASH_PAGE_63

void Save_PWMData(void);
void Load_PWMData(void);
void Reset_PWMData(void);
void Clear_PWMData(void);
void Save_ADCData(void);
void Load_ADCData(void);
void Reset_ADCData(void);
void Clear_ADCData(void);
void Refresh_ADCData(void);
void Save_EncoderData(void);
void Load_EncoderData(void);
void Reset_EncoderData(void);
void Clear_EncoderData(void);
u16	 AVERAGE(u16 *array, u8 width);
u16	 Get_ErrorRange(u16 *array, u8 width);
void Auto_EncoderData(void);
void Save_SundryData(void);
void Load_SundryData(void);
void Reset_SundryData(void);
void Clear_SundryData(void);
void Save_JumpData(void);
void Save_ALLData(void);
void Load_ALLData(void);
void Reset_ALLData(void);
void Clear_Data(void);

#endif
