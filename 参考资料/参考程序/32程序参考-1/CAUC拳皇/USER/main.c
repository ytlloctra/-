//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//������ʡ�����˴���-������̨����
//���ߣ�������
//�汾��V3.3
//�޸�����:2018/10/07
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#include "car_system.h"
#include "menu.h"
#include "attack.h"
#include "data.h"

/*ȫ�ֱ�������*/
CAR_PWM				MOTOR_PWM;
ADC_THRESHOLD		EYE_THRESHOLD;
CAR_SPEED			ENCODER_VALUE;
CAR_SUNDRY			SETTING_SUNDRY;	
extern MENU_PAGE	HOMEPAGE;

/*������*/
int main()
{
	/*��ֵ*/
	u8 key_value;

	/*��ʼ����̨*/
	NVIC_Configuration();
	delay_init();
	LED_Init();	
	KEY_Init();	
	SENSORS_Init();	
	BUZZER_Init();
	ENCODER_Init();	
	MOTOR_Init();
	ADC1_Init();
	DMA1_Channel1_Init();

	/*��ʼ��ǰ̨*/
	SOLGUI_Init(&HOMEPAGE);	

	/*��ȡflash����*/
	Load_ALLData();	
	
	/*OLED��ʾLOGO*/
	OLED_ShowLogo();

	/*�����������ϵͳ*/
	while(!KEY_Scan());
	
	/*��������ѭ����ˢ��ǰ̨GUI��������˻�����*/
	while(1)
	{
		key_value=KEY_Scan();
		SOLGUI_InputKey(key_value);
		SOLGUI_Menu_PageStage();
		SOLGUI_Refresh();
	}
}
