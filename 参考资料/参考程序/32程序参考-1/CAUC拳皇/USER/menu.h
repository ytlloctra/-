//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//�˵�ҳ�溯����
//���ߣ�������
//�汾��V1.0
//�޸�����:2018/10/02
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#ifndef __MENU_H
#define __MENU_H

#include "SOLGUI_Include.h"

#define SOLGUI_Widget_ShowEYE(X,Y,ADC_NAME) \
SOLGUI_Widget_Text\
(X,Y,EYE_##ADC_NAME>EYE_THRESHOLD.##ADC_NAME?R4X6:F4X6,\
"%04d",EYE_##ADC_NAME);

#define SOLGUI_Widget_ShowEYE_EXACT(X,Y,ADC_NAME) \
SOLGUI_Widget_Text\
(X,Y,EYE_##ADC_NAME>EYE_THRESHOLD.EXACT?R4X6:F4X6,\
"%04d",EYE_##ADC_NAME);


#endif
