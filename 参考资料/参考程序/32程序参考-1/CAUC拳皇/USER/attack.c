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
#include "attack.h"

extern CAR_PWM			MOTOR_PWM;
extern ADC_THRESHOLD 	EYE_THRESHOLD;
extern CAR_SPEED 		ENCODER_SPEED;
extern CAR_SUNDRY 		SETTING_SUNDRY;

u16 miss_count    = 0;		//Ŀ�궪ʧ��������
u8 lockchess_flag = 0;		//����Ŀ��������־λ
u8 lockcar_flag   = 0;		//����Ŀ��������־λ
u8 Avoid_flag	  = 0;		//��ܱ�Ե��־λ

/**
	* @brief 	ʶ����������
	* @since	v3.0
	* @return
			1��ʶ������
			0��δʶ������
	*/
u8 Scan_Gesture()
{
	if(SCAN(MRM))
		return 1;
	else
		return 0;
}



/**
	* @brief 	��̨
	* @since	v3.0
	*/
void Jump()
{
	CAR_Jump(MOTOR_PWM.JumpX,MOTOR_PWM.JumpY,SETTING_SUNDRY.Jump_Delay_X,SETTING_SUNDRY.Jump_Delay_Y);
	CAR_Move(FORWORD,MOTOR_PWM.JumpX);
	delay_ms(500);
}



/**
	* @brief 	��̨����
	* @since	v3.0
	*/
void Jump_Test()
{
	OLED_ShowLogo();
	BUZZER_Hint(2);
	while(!Scan_Gesture());
	Jump();
	CAR_Stop();
}



/**
	* @brief 	��λ��̨װ��
	* @since	v3.0
	*/
void Jump_Restoration()
{
	OLED_ShowLogo();
	BUZZER_Hint(2);
	while(!KEY_Scan()&&EYE3_JP)
		TIM4->CCR3 = MOTOR_PWM.JumpY;
	TIM4->CCR3 = 0;
}



/**
	* @brief 	Ѱ����̨
	* @note		ʹ����������̨
	* @return
			1����������̨
			0��δ������̨
	* @since	v3.0
	*/
u8 Find_Arena()
{
	if(SCAN(BMM))
	{
		if( ( SCAN(BOL) || SCAN(BOR) ) && SCAN(MLM) && SCAN(MRM) )
		{
			CAR_Move(RIGHT,MOTOR_PWM.Falling);
			return 0;
		}
		if( ( SCAN(BOL) || SCAN(BOR) ) && SCAN(MLM) )
		{
			if( SCAN(MRF) || SCAN(FML) || SCAN(FMR) )
			{
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
				return 0;
			}
			CAR_Move(BACKWORD,MOTOR_PWM.Falling);
			delay_ms(100);
			CAR_Stop();
			delay_ms(100);
			CAR_Move(FORWORD,MOTOR_PWM.Falling);
			delay_ms(500);
			CAR_Stop();
			return 0;
		}

		if( ( SCAN(BOL) || SCAN(BOR) ) &&  SCAN(MRM) )
		{
			if( SCAN(MLF) || SCAN(FML) || SCAN(FMR))
			{
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
				return 0;
			}
			CAR_Move(BACKWORD,MOTOR_PWM.Falling);
			delay_ms(100);
			CAR_Stop();
			delay_ms(100);
			CAR_Move(FORWORD,MOTOR_PWM.Falling);
			delay_ms(500);
			CAR_Stop();
			return 0;
		}

		if( (SCAN(BOL) && SCAN(BOR) ) || (SCAN(MLB) && SCAN(MRB) ) )
		{
			if(SCAN(FMM))
			{
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
				delay_ms(400);
				CAR_Move(FORWORD,MOTOR_PWM.Falling);
				delay_ms(500);
				CAR_Stop();
				return 0;
			}
			if(SCAN(FOL)&&SCAN(FOR))
				return 1;
		}

		if(SCAN(BOL)||SCAN(BOR))
		{
			if(SCAN(BOL))
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
			else
				CAR_Move(LEFT,MOTOR_PWM.Falling);
			return 0;
		}
		if(SCAN(MLB)||SCAN(MRB))
		{
			if(SCAN(MLB))
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
			else
				CAR_Move(LEFT,MOTOR_PWM.Falling);
			return 0;
		}
		CAR_Move(RIGHT,MOTOR_PWM.Falling);
		return 0;
	}
	else
	{
		CAR_Move(RIGHT,MOTOR_PWM.Falling);
		return 0;
	}
}



/**
	* @brief 	׼����̨
	* @note		ʹ�������ڵ�̨���ʾ���
	* @since	v3.0
	*/
void Ready_Jump()
{
	CAR_Move(BACKWORD,MOTOR_PWM.Falling);
	delay_ms(SETTING_SUNDRY.Jump_Delay_B);
	CAR_Stop();
	delay_ms(100);
	CAR_Move(FORWORD,MOTOR_PWM.Falling);
	delay_ms(40);
}



/**
	* @brief 	��̨����
	* @since	v3.0
	*/
void Falling_Test()
{
	OLED_ShowLogo();
	BUZZER_Hint(2);
	delay_ms(500);
	BUZZER_Hint(1);

	while(!Find_Arena());

	Ready_Jump();
	Jump();

	CAR_Stop();
}



/**
	* @brief 	������ģʽ
	* @since	v1.0
	*/
void MODE_Attack_Chess()
{
	miss_count = 0;								//��ʧĿ�����ֵ����

	OLED_ShowLogo();							//OLEDչʾLOGO
	BUZZER_Hint(2);								//��������ʾ������������

	while(!Scan_Gesture());						//�ȴ���������

	
	if(EYE3_DFL && EYE3_DFR && EYE3_DBM)
	{
		CAR_Move(BACKWORD,700);
		delay_ms(100);
		CAR_Stop();
		delay_ms(100);
		Jump();									//��̨
	}

	while(!KEY_Scan())							//�������ֹͣ����
	{
		if(Judge_State_Chess())
			Attack_Chess();
		else
			lockchess_flag=0;
	}

	CAR_Stop();									//ɲ��
}



/**
	* @brief 	��̨��ģʽ
	* @since	v1.0
	*/
void MODE_Attack_Car()
{
	miss_count = 0;								//��ʧĿ�����ֵ����

	OLED_ShowLogo();							//OLEDչʾLOGO
	BUZZER_Hint(2);								//��������ʾ������������

	while(!Scan_Gesture());						//�ȴ���������
	
	if(EYE3_DFL && EYE3_DFR && EYE3_DBM)
	{
		CAR_Move(BACKWORD,700);
		delay_ms(100);
		CAR_Stop();
		delay_ms(100);
		Jump();									//��̨
	}

	while(!KEY_Scan())							//�������ֹͣ����
	{
		if(Judge_State_Car())
			Attack_Car();
		else
			lockcar_flag=0;
	}

	CAR_Stop();									//ɲ��
}



/**
	* @brief 	��̨��ģʽ(����)
	* @since	v4.0
	*/
void MODE_Attack_Car_Single()
{
	miss_count = 0;								//��ʧĿ�����ֵ����

	OLED_ShowLogo();							//OLEDչʾLOGO
	BUZZER_Hint(2);								//��������ʾ������������

	while(!Scan_Gesture());						//�ȴ���������
	
	if(EYE3_DFL && EYE3_DFR && EYE3_DBM)
	{
		CAR_Move(BACKWORD,700);
		delay_ms(100);
		CAR_Stop();
		delay_ms(100);
		Jump();									//��̨
	}

	while(!KEY_Scan())							//�������ֹͣ����
	{
		if(Judge_State_Car())
			Attack_Car_Single();
		else
			lockcar_flag=0;
	}

	CAR_Stop();									//ɲ��
}



/**
	* @brief	������ģʽ��״̬�ж�
	* @note		�ж��Ƿ���ֵ�����̨��Ե����̨���쳣״����������Ӧ
	* @return
			1�����쳣״��
			0����⵽�쳣״��
	* @since	v3.0
	*/
u8 Judge_State_Chess()
{
	if(EYE3_DBM && EYE3_DFL && EYE3_DFR && EYE2_BL && EYE2_BR && EYE2_FL && EYE2_FR)
	{
		CAR_Stop();
		BUZZER_Hint(2);
		delay_ms(500);
	}
	if(EYE2_FR || EYE2_FL)//��Ե���
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_BR && EYE2_BL)
		{
			CAR_Move(RIGHT,MOTOR_PWM.Avoid);
			return 0;
		}
		CAR_Move(BACKWORD,MOTOR_PWM.Avoid);
		Avoid_flag = RIGHT;
		return 0;
	}
	if(EYE2_BR || EYE2_BL)
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_FR && EYE2_FL)
		{
			CAR_Move(RIGHT,MOTOR_PWM.Avoid);
			return 0;
		}
		CAR_Move(FORWORD,MOTOR_PWM.Avoid);
		Avoid_flag = LEFT;
		return 0;
	}
	if(Avoid_flag!=0)
		{
			CAR_Move(Avoid_flag,MOTOR_PWM.Avoid);
			delay_ms(SETTING_SUNDRY.Margin_Delay);
			Avoid_flag=0;
			return 0;
		}
	return 1;
}



/**
	* @brief	��������
	* @since	v4.0
	*/
void Attack_Chess()
{
	if(lockcar_flag)
	{
		/*���Ŀ���Ƿ���ǰ��*/
		if((EYE3_DFL || EYE3_DFR)?(SCAN(FML) || SCAN(FMR)):(SCAN_EXACT(FML) || SCAN_EXACT(FMR)))
		{
			CAR_Move(FORWORD,MOTOR_PWM.Chess);
			return;
		}

		/*���Ŀ���Ƿ��ں�*/
		if((EYE3_DBM)?(SCAN(BML) || SCAN(BMR) || SCAN(BMM)):(SCAN_EXACT(BML) || SCAN_EXACT(BMR)))
		{
			CAR_Move(BACKWORD,MOTOR_PWM.Chess);
			return;
		}
		/*�����������ˣ�˵��Ŀ�궪ʧ*/
		if(miss_count++ >= SETTING_SUNDRY.Miss_Count)
		{
			lockcar_flag=0;
			miss_count=0;
			CAR_Move(DEFAULT,MOTOR_PWM.Chess);
			LED_Show(miss_count%8);
			return;
		}
	}

	/*����Ƿ���Ҫ��ת��ǰ��*/
	if( (EYE3_DFL || EYE3_DBM) ? (SCAN(FOL) || SCAN(MLF) || SCAN(MLM) ) : (SCAN_EXACT(FOL) || SCAN_EXACT(MLF) || SCAN_EXACT(MLM)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Chess);
		return;
	}

	/*����Ƿ���Ҫ��ת��ǰ��*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(FOR) || SCAN(MRF) || SCAN(MRM) ) : (SCAN_EXACT(FOR) || SCAN_EXACT(MRF) || SCAN_EXACT(MRM)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Chess);
		return;
	}

	/*����Ƿ���Ҫ��ת�ú��*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MRB) || SCAN(BOR)) : (SCAN_EXACT(MRB) || SCAN_EXACT(BOR)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Chess);
		return;
	}

	/*����Ƿ���Ҫ��ת�ú��*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MLB) || SCAN(BOL)) : (SCAN_EXACT(MLB) || SCAN_EXACT(BOL)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Chess);
		return;
	}
}



/**
	* @brief	��̨ģʽ��״̬�ж�
	* @note		�ж��Ƿ���ֵ�����̨��Ե����̨���쳣״����������Ӧ
	* @return
			1�����쳣״��
			0����⵽�쳣״��
	* @since	v3.0
	*/
u8 Judge_State_Car()
{
	if(EYE2_FR || EYE2_FL)//��Ե���
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_BR && EYE2_BL)
		{
			if(Find_Arena())
			{
				Ready_Jump();
				Jump();
				return 0;
			}
			return 0;
		}
		CAR_Move(BACKWORD,MOTOR_PWM.Avoid);
		Avoid_flag = RIGHT;
		return 0;
	}
	if(EYE2_BR || EYE2_BL)
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_FR && EYE2_FL)
		{
			if(Find_Arena())
			{
				Ready_Jump();
				Jump();
				return 0;
			}
			return 0;
		}
		CAR_Move(FORWORD,MOTOR_PWM.Avoid);
		Avoid_flag = LEFT;
		return 0;
	}
	if(Avoid_flag!=0)
		{
			CAR_Move(Avoid_flag,MOTOR_PWM.Avoid);
			delay_ms(SETTING_SUNDRY.Margin_Delay);
			Avoid_flag=0;
			return 0;
		}
	return 1;
}



/**
	* @brief	��������
	* @since	v4.0
	*/
void Attack_Car()
{
	if(lockcar_flag)
	{
		/*���Ŀ���Ƿ���ǰ��*/
		if((EYE3_DFL || EYE3_DFR)?(SCAN(FML) || SCAN(FMR)):(SCAN_EXACT(FML) || SCAN_EXACT(FMR) || SCAN(FMM)))
		{
			if( EYE3_DFL || EYE3_DFR )
			{
				CAR_Move(FORWORD,MOTOR_PWM.Straight);
				return;
			}
			CAR_Move(FORWORD,MOTOR_PWM.Max);
			return;
		}

		/*���Ŀ���Ƿ��ں�*/
		if((EYE3_DBM)?(SCAN(BML) || SCAN(BMR)):(SCAN_EXACT(BML) || SCAN_EXACT(BMR) || SCAN(BMM)))
		{
			if( EYE3_DBM )
			{
				CAR_Move(FORWORD,MOTOR_PWM.Straight);
				return;
			}
			CAR_Move(BACKWORD,MOTOR_PWM.Max);
			return;
		}
		/*�����������ˣ�˵��Ŀ�궪ʧ*/
		if(miss_count++ >= SETTING_SUNDRY.Miss_Count)
		{
			lockcar_flag=0;
			miss_count=0;
			CAR_Move(DEFAULT,MOTOR_PWM.Default);
			LED_Show(miss_count%8);
			return;
		}
	}

	/*����Ƿ���Ҫ��ת��ǰ��*/
	if( (EYE3_DFL || EYE3_DBM) ? (SCAN(FOL) || SCAN(MLF) || SCAN(MLM) ) : (SCAN_EXACT(FOL) || SCAN_EXACT(MLF) || SCAN_EXACT(MLM)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Turn);
		return;
	}

	/*����Ƿ���Ҫ��ת��ǰ��*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(FOR) || SCAN(MRF) || SCAN(MRM)) : (SCAN_EXACT(FOR) || SCAN_EXACT(MRF) || SCAN_EXACT(MRM)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Turn);
		return;
	}

	/*����Ƿ���Ҫ��ת�ú��*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MRB) || SCAN(BOR)) : (SCAN_EXACT(MRB) || SCAN_EXACT(BOR)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Turn);
		return;
	}

	/*����Ƿ���Ҫ��ת�ú��*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MLB) || SCAN(BOL)) : (SCAN_EXACT(MLB) || SCAN_EXACT(BOL)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Turn);
		return;
	}
}



/**
	* @brief	������������
	* @since	v4.0
	*/
void Attack_Car_Single()
{
	if(lockcar_flag)
	{
		/*���Ŀ���Ƿ���ǰ��*/
		if((EYE3_DFL || EYE3_DFR)?(SCAN(FML) || SCAN(FMR)):(SCAN_EXACT(FML) || SCAN_EXACT(FMR) || SCAN(FMM)))
		{
			if( EYE3_DFL || EYE3_DFR )
			{
				CAR_Move(FORWORD,MOTOR_PWM.Straight);
				return;
			}
			CAR_Move(FORWORD,MOTOR_PWM.Max);
			return;
		}

		/*�����������ˣ�˵��Ŀ�궪ʧ*/
		if(miss_count++ >= SETTING_SUNDRY.Miss_Count)
		{
			lockcar_flag=0;
			miss_count=0;
			CAR_Move(DEFAULT,MOTOR_PWM.Default);
			LED_Show(miss_count%8);
			return;
		}
	}

	/*����Ƿ���Ҫ��ת*/
	if( (EYE3_DFL || EYE3_DBM) ? (SCAN(FOL) || SCAN(MLF) || SCAN(MLM) || SCAN(MLB) || SCAN(BOL) || SCAN(BML)) : (SCAN_EXACT(FOL) || SCAN_EXACT(MLF) || SCAN_EXACT(MLM) || SCAN_EXACT(MLB) || SCAN_EXACT(BOL) || SCAN_EXACT(BML)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Turn);
		return;
	}

	/*����Ƿ���Ҫ��ת*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(FOR) || SCAN(MRF) || SCAN(MRM) || SCAN(MRB) || SCAN(BOR) || SCAN(BMR)) : (SCAN_EXACT(FOR) || SCAN_EXACT(MRF) || SCAN_EXACT(MRM) || SCAN_EXACT(MRB) || SCAN_EXACT(BOR) || SCAN_EXACT(BMR)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Turn);
		return;
	}
}
