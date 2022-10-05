//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//�˵�ҳ�溯����
//���ߣ�������
//�汾��V3.0
//�޸�����:2018/10/04
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#include "menu.h"
#include "attack.h"
#include "data.h"
#include "car_system.h"

MENU_PAGE
HOMEPAGE,																		//һ���˵�����
SETTINGS,AUTHOR,PWM_SET,ADC_SET,ENCODER_SET,SUNDRY_SET,JUMP_SET,ADC_SET_EXACT,	//�����˵�����
ADC_SET_SINGLE;																	//�����˵�����

/**
	* @brief 	�˵���ҳ
	* @note 	�㼶�˵�
	* @since	v1.0
	*/
__M_PAGE(HOMEPAGE,"HOMEPAGE",PAGE_NULL,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,0,5);

	/*����ģʽѡ��ť*/
	SOLGUI_Widget_Button(0,"PUSH CHESS",		&MODE_Attack_Chess);
	SOLGUI_Widget_Button(1,"ATTACK CAR",		&MODE_Attack_Car);
	SOLGUI_Widget_Button(2,"ATTACK CAR SINGLE",	&MODE_Attack_Car_Single);

	/*����ҳ����ת��*/
	SOLGUI_Widget_GotoPage(3,&SETTINGS);
	SOLGUI_Widget_GotoPage(4,&AUTHOR);
});



/**
	* @brief 	����ҳ
	* @note 	һ���˵����ϼ�����ҳ
	* @since	v1.0
	*/
__M_PAGE(SETTINGS,"SETTINGS",&HOMEPAGE,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,0,7);

	/*����ҳ����ת��*/
	SOLGUI_Widget_GotoPage(0,&ADC_SET);
	SOLGUI_Widget_GotoPage(1,&ADC_SET_EXACT);
	SOLGUI_Widget_GotoPage(2,&PWM_SET);
	SOLGUI_Widget_GotoPage(3,&JUMP_SET);
	SOLGUI_Widget_GotoPage(4,&ENCODER_SET);
	SOLGUI_Widget_GotoPage(5,&SUNDRY_SET);

	/*����������ݰ�ť*/
	SOLGUI_Widget_Button(6,"RESET ALL",	&Clear_Data);
});



/**
	* @brief 	������Ϣҳ
	* @note 	һ���˵����ϼ�����ҳ
	* @since	v1.0
	*/
__M_PAGE(AUTHOR,"AUTHOR",&HOMEPAGE,
{
	/*��ʾ����*/
	SOLGUI_Widget_OptionText(0,"NAME:    XTZ");
	SOLGUI_Widget_OptionText(1,"QQ:      543015378");
	SOLGUI_Widget_OptionText(2,"COMPANY: 505_LAB");
	SOLGUI_Widget_OptionText(3,"DATE:    2018.10.20");
});



/**
	* @brief 	PWM�Ƚ�ֵ����ҳ
	* @note 	�����˵����ϼ�������ҳ
	* @since	v1.0
	*/
__M_PAGE(PWM_SET,"PWM",&SETTINGS,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,0,9);

	/*����PWM����������ť*/
	SOLGUI_Widget_Spin(0,"PWM-CHESS"	,INT16,1799,0,&MOTOR_PWM.Chess);
	SOLGUI_Widget_Spin(1,"PWM-AVOID"	,INT16,1799,0,&MOTOR_PWM.Avoid);
	SOLGUI_Widget_Spin(2,"PWM-STRAIGHT"	,INT16,1799,0,&MOTOR_PWM.Straight);
	SOLGUI_Widget_Spin(3,"PWM-TURN"		,INT16,1799,0,&MOTOR_PWM.Turn);
	SOLGUI_Widget_Spin(4,"PWM-DEFAULT"	,INT16,1799,0,&MOTOR_PWM.Default);
	SOLGUI_Widget_Spin(5,"PWM-MAX"		,INT16,1799,0,&MOTOR_PWM.Max);

	/*���ñ��桢��ȡ�����ð�ť*/
	SOLGUI_Widget_Button(6,"SAVE",	&Save_PWMData);
	SOLGUI_Widget_Button(7,"LODE",	&Load_PWMData);
	SOLGUI_Widget_Button(8,"RESET",	&Reset_PWMData);
});



/**
	* @brief 	ģ�������ֵ����ҳ
	* @note 	�����˵����ϼ�������ҳ
	* @since	v1.0
	*/
__M_PAGE(ADC_SET,"ADC",&SETTINGS,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,4,3);

	/*������ֵ������ť*/
	SOLGUI_Widget_Spin(0,"THRESHOLD",INT16,3800,0,&EYE_THRESHOLD.ALL);

	/*�������ݱ��水ť*/
	SOLGUI_Widget_Button(1,"SAVE",	&Save_ADCData);

	/*���õ���ADC���ҳ����ת��*/
	SOLGUI_Widget_GotoPage(2,&ADC_SET_SINGLE);

	/*����ADC������ʾҳ��*/
	SOLGUI_Widget_ShowEYE(26,0 ,BOL);
	SOLGUI_Widget_ShowEYE(46,0 ,BML);
	SOLGUI_Widget_ShowEYE(66,0 ,BMR);
	SOLGUI_Widget_ShowEYE(86,0 ,BOR);
	SOLGUI_Widget_ShowEYE(26,6 ,MLB);
	SOLGUI_Widget_ShowEYE(26,12,MLM);
	SOLGUI_Widget_ShowEYE(26,18,MLF);
	SOLGUI_Widget_ShowEYE(86,6 ,MRB);
	SOLGUI_Widget_ShowEYE(86,12,MRM);
	SOLGUI_Widget_ShowEYE(86,18,MRF);
	SOLGUI_Widget_ShowEYE(26,24,FOL);
	SOLGUI_Widget_ShowEYE(46,24,FML);
	SOLGUI_Widget_ShowEYE(56,18,FMM);
	SOLGUI_Widget_ShowEYE(56,6 ,BMM);
	SOLGUI_Widget_ShowEYE(66,24,FMR);
	SOLGUI_Widget_ShowEYE(86,24,FOR);
});



/**
	* @brief 	ģ����⾫ȷ��ֵ����ҳ
	* @note 	�����˵����ϼ�������ҳ
	* @since	v3.0
	*/
__M_PAGE(ADC_SET_EXACT,"ADC EXACT",&SETTINGS,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,4,2);

	/*������ֵ������ť*/
	SOLGUI_Widget_Spin(0,"THRESHOLD",INT16,3800,0,&EYE_THRESHOLD.EXACT);

	/*�������ݱ��水ť*/
	SOLGUI_Widget_Button(1,"SAVE",	&Save_ADCData);

	/*����ADC������ʾҳ��*/
	SOLGUI_Widget_ShowEYE_EXACT(26,0 ,BOL);
	SOLGUI_Widget_ShowEYE_EXACT(46,0 ,BML);
	SOLGUI_Widget_ShowEYE_EXACT(66,0 ,BMR);
	SOLGUI_Widget_ShowEYE_EXACT(86,0 ,BOR);
	SOLGUI_Widget_ShowEYE_EXACT(26,6 ,MLB);
	SOLGUI_Widget_ShowEYE_EXACT(26,12,MLM);
	SOLGUI_Widget_ShowEYE_EXACT(26,18,MLF);
	SOLGUI_Widget_ShowEYE_EXACT(86,6 ,MRB);
	SOLGUI_Widget_ShowEYE_EXACT(86,12,MRM);
	SOLGUI_Widget_ShowEYE_EXACT(86,18,MRF);
	SOLGUI_Widget_ShowEYE_EXACT(26,24,FOL);
	SOLGUI_Widget_ShowEYE_EXACT(46,24,FML);
	SOLGUI_Widget_ShowEYE_EXACT(56,18,FMM);
	SOLGUI_Widget_ShowEYE_EXACT(56,6 ,BMM);
	SOLGUI_Widget_ShowEYE_EXACT(66,24,FMR);
	SOLGUI_Widget_ShowEYE_EXACT(86,24,FOR);
});



/**
	* @brief 	����������ֵ����ҳ
	* @note 	�����˵����ϼ�������ҳ
	* @since	v1.0
	*/
__M_PAGE(ENCODER_SET,"ENCODER",&SETTINGS,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,0,7);

	/*�����Զ�������ť*/
	SOLGUI_Widget_Button(0,"AUTO SET",	&Auto_EncoderData);

	/*���ö�������*/
	SOLGUI_Widget_OptionText(1,"FORWORD         %d",ENCODER_VALUE.Forword);
	SOLGUI_Widget_OptionText(2,"BACKWORD        %d",ENCODER_VALUE.Backword);
	SOLGUI_Widget_OptionText(3,"RIGHT           %d",ENCODER_VALUE.Right);
	SOLGUI_Widget_OptionText(4,"LEFT            %d",ENCODER_VALUE.Left);
	SOLGUI_Widget_OptionText(5,"ERROR RANGE S   %d",ENCODER_VALUE.ErrorRange_S);
	SOLGUI_Widget_OptionText(6,"ERROR RANGE T   %d",ENCODER_VALUE.ErrorRange_T);
});



/**
	* @brief 	��̨����ҳ
	* @note 	�����˵����ϼ�������ҳ
	* @since	v3.0
	*/
__M_PAGE(JUMP_SET,"JUMP",&SETTINGS,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,0,11);

	/*���ò��԰�ť*/
	SOLGUI_Widget_Button(0,"TEST JUMP"		,	&Jump_Test);
	SOLGUI_Widget_Button(1,"TEST FALLING"	,	&Falling_Test);
	SOLGUI_Widget_Button(2,"RESET MOTOR"	,	&Jump_Restoration);

	/*���ö�������*/
	SOLGUI_Widget_Spin(3,"PWM-RUSH"		,INT16,1799,0,&MOTOR_PWM.JumpX);
	SOLGUI_Widget_Spin(4,"PWM-JUMP"		,INT16,1799,0,&MOTOR_PWM.JumpY);
	SOLGUI_Widget_Spin(5,"PWM-FALLING"	,INT16,1799,0,&MOTOR_PWM.Falling);
	SOLGUI_Widget_Spin(6,"RUSH TIME"	,INT16,1000,1,&SETTING_SUNDRY.Jump_Delay_X);
	SOLGUI_Widget_Spin(7,"JUMP TIME"	,INT16,1000,1,&SETTING_SUNDRY.Jump_Delay_Y);
	SOLGUI_Widget_Spin(8,"BACK TIME"	,INT16,1000,1,&SETTING_SUNDRY.Jump_Delay_B);
	SOLGUI_Widget_Spin(9,"AIM PRECISION",INT16,1000,1,&SETTING_SUNDRY.Jump_ADC_Value);

	/*���ñ��水ť*/
	SOLGUI_Widget_Button(10,"SAVE",	&Save_JumpData);
});



/**
	* @brief 	��������ҳ
	* @note 	�����˵����ϼ�������ҳ
	* @since	v1.0
	*/
__M_PAGE(SUNDRY_SET,"SUNDRY",&SETTINGS,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,0,6);

	/*������ť*/
	SOLGUI_Widget_Spin(0,"MISS  COUNT",INT16,500,0,&SETTING_SUNDRY.Miss_Count);
	SOLGUI_Widget_Spin(1,"LOCK  COUNT",INT16,500,0,&SETTING_SUNDRY.Lock_Count);
	SOLGUI_Widget_Spin(2,"MARGIN TIME",INT16,500,1,&SETTING_SUNDRY.Margin_Delay);

	/*���ñ��桢��ȡ�����ð�ť*/
	SOLGUI_Widget_Button(3,"SAVE",	&Save_SundryData);
	SOLGUI_Widget_Button(4,"LODE",	&Load_SundryData);
	SOLGUI_Widget_Button(5,"RESET",	&Reset_SundryData);
});



/**
	* @brief 	ģ�������ֵ��ϸ����ҳ
	* @note 	�����˵����ϼ���ģ�������ֵ����ҳ
	* @since	v4.0
	*/
__M_PAGE(ADC_SET_SINGLE,"SINGLE",&ADC_SET,
{
	/*�������ҳ��*/
	SOLGUI_Cursor(6,0,17);

	/*��ʾADCʵʱ����*/
	SOLGUI_Widget_OptionText(0 ,"FOL   %d",EYE_FOL);
	SOLGUI_Widget_OptionText(1 ,"MLF   %d",EYE_MLF);
	SOLGUI_Widget_OptionText(2 ,"MLM   %d",EYE_MLM);
	SOLGUI_Widget_OptionText(3 ,"MLB   %d",EYE_MLB);
	SOLGUI_Widget_OptionText(4 ,"BOL   %d",EYE_BOL);
	SOLGUI_Widget_OptionText(5 ,"BML   %d",EYE_BML);
	SOLGUI_Widget_OptionText(6 ,"BMR   %d",EYE_BMR);
	SOLGUI_Widget_OptionText(7 ,"BOR   %d",EYE_BOR);
	SOLGUI_Widget_OptionText(8 ,"MRB   %d",EYE_MRB);
	SOLGUI_Widget_OptionText(9 ,"MRM   %d",EYE_MRM);
	SOLGUI_Widget_OptionText(10,"MRF   %d",EYE_MRF);
	SOLGUI_Widget_OptionText(11,"FOR   %d",EYE_FOR);
	SOLGUI_Widget_OptionText(12,"FML   %d",EYE_FML);
	SOLGUI_Widget_OptionText(13,"FMR   %d",EYE_FMR);

	/*����ADC��ֵ������ť*/
	SOLGUI_Widget_Spin(0 ,"",INT16,3800,0,&EYE_THRESHOLD.FOL);
	SOLGUI_Widget_Spin(1 ,"",INT16,3800,0,&EYE_THRESHOLD.MLF);
	SOLGUI_Widget_Spin(2 ,"",INT16,3800,0,&EYE_THRESHOLD.MLM);
	SOLGUI_Widget_Spin(3 ,"",INT16,3800,0,&EYE_THRESHOLD.MLB);
	SOLGUI_Widget_Spin(4 ,"",INT16,3800,0,&EYE_THRESHOLD.BOL);
	SOLGUI_Widget_Spin(5 ,"",INT16,3800,0,&EYE_THRESHOLD.BML);
	SOLGUI_Widget_Spin(6 ,"",INT16,3800,0,&EYE_THRESHOLD.BMR);
	SOLGUI_Widget_Spin(7 ,"",INT16,3800,0,&EYE_THRESHOLD.BOR);
	SOLGUI_Widget_Spin(8 ,"",INT16,3800,0,&EYE_THRESHOLD.MRB);
	SOLGUI_Widget_Spin(9 ,"",INT16,3800,0,&EYE_THRESHOLD.MRM);
	SOLGUI_Widget_Spin(10,"",INT16,3800,0,&EYE_THRESHOLD.MRF);
	SOLGUI_Widget_Spin(11,"",INT16,3800,0,&EYE_THRESHOLD.FOR);
	SOLGUI_Widget_Spin(12,"",INT16,3800,0,&EYE_THRESHOLD.FML);
	SOLGUI_Widget_Spin(13,"",INT16,3800,0,&EYE_THRESHOLD.FMR);

	/*���ñ��桢��ȡ�����ð�ť*/
	SOLGUI_Widget_Button(14,"SAVE",	&Save_ADCData);
	SOLGUI_Widget_Button(15,"LODE",	&Load_ADCData);
	SOLGUI_Widget_Button(16,"RESET",&Reset_ADCData);
});

