//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//��翪����������
//���ߣ�������
//�汾��V1.0
//�޸�����:2018/10/02
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#ifndef __SENSORS_H
#define __SENSORS_H

#include "sys.h"

#define EYE2_BR  PDin(0)
#define EYE2_FR  PCin(12)
#define EYE2_BL  PDin(5)
#define EYE2_FL  PDin(4)
#define EYE3_JP  PDin(6)
#define EYE3_DBM PDin(3)
#define EYE3_DFL PDin(7)
#define EYE3_DFR PDin(2)
#define EYE3_NONAME PDin(1)

void SENSORS_Init(void);

#endif
