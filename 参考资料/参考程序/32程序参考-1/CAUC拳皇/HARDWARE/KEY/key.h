//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//���ᰴ����������
//���ߣ�������
//�汾��V1.0
//�޸�����:2018/10/02
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "delay.h"

#define KEY_OK 		PDin(15)
#define KEY_BACK 	PCin(11)
#define KEY_UP 		PDin(12)
#define KEY_DOWN 	PDin(14)
#define KEY_LEFT 	PCin(6)
#define KEY_RIGHT	PDin(13)

#define K_OK 		1
#define K_BACK 	2
#define K_UP 		3
#define K_DOWN 	4
#define K_LEFT 	5
#define K_RIGHT 6

void KEY_Init(void);
u8	 KEY_Scan(void);
u8   KEY_OK_Scan(void);
u8   KEY_BACK_Scan(void);
u8   KEY_UP_Scan(void);
u8   KEY_DOWN_Scan(void);
u8   KEY_LEFT_Scan(void);
u8   KEY_RIGHT_Scan(void);

#endif
