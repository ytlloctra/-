//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//��������������
//���ߣ�������
//�汾��V1.0
//�޸�����:2018/10/02
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#include "buzzer.h"

/** 
	* @brief	��������ʼ��
	* @since	v1.0
	*/
void BUZZER_Init(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  GPIO_ResetBits(GPIOD, GPIO_Pin_8);
}



/** 
	* @brief	����������
	* @param	times	��������
	* @since	v2.0
	*/
void BUZZER_Hint(u8 times)
{
	while(times--)
	{
		BUZZER = ON;
		delay_ms(100);
		BUZZER = OFF;
		delay_ms(100);
	}
}	
