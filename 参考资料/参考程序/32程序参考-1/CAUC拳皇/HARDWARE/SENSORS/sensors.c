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
#include "sensors.h"

/** 
	* @brief	��ʼ����硢�Ҷȵȴ�����
	* @since	v3.0
	*/
void SENSORS_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
