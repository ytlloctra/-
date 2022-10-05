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
#include "key.h"

/** 
	* @brief	������ʼ��
	* @since	v1.0
	*/
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6|GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}



/** 
	* @brief	ɨ���������
	* @return	��ֵ
	* @since	v1.0
	*/
u8 KEY_Scan()
{
	u8 value=0;
	if ( KEY_OK == 0 || KEY_BACK == 0 || KEY_UP == 0 || KEY_LEFT == 0 || KEY_DOWN == 0 || KEY_RIGHT == 0 )
	{
		delay_ms(10);
		if (KEY_UP 		== 0)value = K_UP;		//�ϼ�
		if (KEY_DOWN 	== 0)value = K_DOWN;	//�¼�
		if (KEY_LEFT 	== 0)value = K_LEFT;	//���
		if (KEY_RIGHT	== 0)value = K_RIGHT;	//�Ҽ�
		if (KEY_OK 		== 0)value = K_OK;		//ȷ��
		if (KEY_BACK	== 0)value = K_BACK;	//����
	}
	while( KEY_OK == 0 || KEY_BACK == 0 || KEY_UP == 0 || KEY_LEFT == 0 || KEY_DOWN == 0 || KEY_RIGHT == 0 );
	return value;
}



/** 
	* @brief	���OK���Ƿ񱻰���
	* @return	
			1��������
			0��δ����
	* @since	v1.0
	*/
u8 KEY_OK_Scan(void)
{
	if(KEY_OK == 0)
	{
		delay_ms(10);
		if(KEY_OK==0)
		{
			while(KEY_OK == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	���BACK���Ƿ񱻰���
	* @return	
			1��������
			0��δ����
	* @since	v1.0
	*/
u8 KEY_BACK_Scan(void)
{
	if(KEY_BACK == 0)
	{
		delay_ms(10);
		if(KEY_BACK==0)
		{
			while(KEY_BACK == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	���UP���Ƿ񱻰���
	* @return	
			1��������
			0��δ����
	* @since	v1.0
	*/
u8 KEY_UP_Scan(void)
{
	if(KEY_UP == 0)
	{
		delay_ms(10);
		if(KEY_UP==0)
		{
			while(KEY_UP == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	���DOWN���Ƿ񱻰���
	* @return	
			1��������
			0��δ����
	* @since	v1.0
	*/
u8 KEY_DOWN_Scan(void)
{
	if(KEY_DOWN == 0)
	{
		delay_ms(10);
		if(KEY_DOWN==0)
		{
			while(KEY_DOWN == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	���LEFT���Ƿ񱻰���
	* @return	
			1��������
			0��δ����
	* @since	v1.0
	*/
u8 KEY_LEFT_Scan(void)
{
	if(KEY_LEFT == 0)
	{
		delay_ms(10);
		if(KEY_LEFT==0)
		{
			while(KEY_LEFT == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	���RIGHT���Ƿ񱻰���
	* @return
			1��������
			0��δ����
	* @since	v1.0
	*/
u8 KEY_RIGHT_Scan(void)
{
	if(KEY_RIGHT == 0)
	{
		delay_ms(10);
		if(KEY_RIGHT==0)
		{
			while(KEY_RIGHT == 0);
			return 1;
		}
	}
	return 0;
}
