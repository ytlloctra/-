#include "sumjess_algor.h"
#include "optoelectronic_switch.h"
#include "sumjess_pwm.h"
#include "delay.h"

/*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��09��06��
�������Ϣ�ο����е�ַ��
����    վ��
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
�������޶���2018/09/06
��problem ��
    ��1�����ڲ���Ĳ�ȫ�棻
    ��2�����ڽ��Ͳ��ֲ�ȫ�棻
    ��3�����ڻ�����һ����bug��
��direction��
      ��һ����Ŀ����ǰѿ�������ɣ�
��explain ��
      �����Ǹ�������ԭ�ӡ��о�԰���ӡ����ŵ��ӵ��̼Ҹı���ɣ�
      ͬʱΪ�˷���ʹ�ã���Ҳ�Լ�д�˺ܶ�Ŀ⣬���Ż����㷨�ͱ�ʾ��ʽ��
��warning��
      Ŀǰ���������޾��� ��   
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================   */
#define delays 380
void algor_SUM_UP(void)
{

	
	
      if(up_for_lift==0&&up_for_right==0&&up_back_left==0&&up_back_right==0)//û�е���Σ��
      {
				/////////////////////////////////////�����
        if(back_1==0||back_2==0)//���
          {
              delay_us(200);//ȥ��
              if(back_1==0||back_2==0)//ȷ�����
              {
                  drive_Back_H();//���ٵ���

              }
          }
         else
              {
                  ;
              }
					/////////////////////////////////////ǰ����
        if(for_1==0||for_2==0||for_3==0)//ǰ��
         {
						delay_us(200);
						if(for_1==0||for_2==0||for_3==0)//ȷ��ǰ��
						{
							drive_For_H();//����ֱ��
						}
					}
				else
					{
							;
					}
					/////////////////////////////////////�����--���û�У���ôֱ��
				if(back_1==0||back_2==0)//���
				{
					delay_us(200);
					if(back_1==0||back_2==0)//ȷ�����
					{
						drive_Back_H();//���ٺ���
					}
				
				}
				else
						{
							drive_For_L();//����ֱ��
						}
					/////////////////////////////////////ǰ����--���ȷʵ�У���ô����ֱ�У����û�У����������else2�����һ˲���У����¿����else1��
				if(for_1==0||for_2==0||for_3==0)//ǰ��
				{
					delay_us(200);
					if(for_1==0||for_2==0||for_3==0)//ȷ��ǰ��
					{
						drive_For_H();//����ֱ��
					}
					else//else1�������ߣ��������ת�����һ˲���У��������else3��
					{
              if(left_1==0||left_2==0||for_lift==0||back_lift==0)//���
              {
                delay_us(200);
                if(left_1==0||left_2==0||for_lift==0||back_lift==0)//ȷ�����
                  {
                    drive_Left_S();//������ת
                    delay_ms(delays);
										
										
                   }
							}
              else//else3���������ת�����һ˲���е���ֱ�У�
                  {
                        if(right_1==0||right_2==0||for_right==0||back_right==0)//�Ҳ�
                        {
                            delay_us(200);
                            if(right_1==0||right_2==0||for_right==0||back_right==0)//ȷ���Ҳ�
                              {
                                    drive_Right_S();//������ת
                                    delay_ms(delays);
                              }
                             else
                             {
                               drive_For_L();//����ֱ��
                             }
                         }
                  }
              
       }


  }
				
  else//�����࣬�������ת�����һ˲���У�����Ҳࣻ����Ҳ�ȷʵ�У���ת������Ҳ�һ˲���У���ô����ֱ�У�
  {
             if(left_1==0||left_2==0||for_lift==0||back_lift==0)//���
              {
                delay_us(200);
                if(left_1==0||left_2==0||for_lift==0||back_lift==0)//ȷ�����
                  {
                        drive_Left_S();//��ת
                        delay_ms(delays);
                   }
							}
              else
                  {
                        if(right_1==0||right_2==0||for_right==0||back_right==0)//�Ҳ�
                        {
                            delay_us(200);
                            if(right_1==0||right_2==0||for_right==0||back_right==0)//ȷ���Ҳ�
                                  {
                                    drive_Right_S();//��ת
                                    delay_ms(delays);
                                   }
                             else
                             {
                               drive_For_L();//����ֱ��
                             }
                         }
                  }
             
  }
}
			      else
      {
        if(up_for_lift==1||up_for_right==1)//ǰ���е���Σ��
        {
          delay_us(200);
          if(up_for_lift==1||up_for_right==1)//ȷ���е���Σ��
          {

            drive_Stop();//ͣ������
            drive_Back_H();//���ٵ���
            delay_ms(700);//300ms
            drive_Right();//��ת�������������������㷨��
            delay_ms(500);//250ms
          }
        }
        if(up_back_left==1||up_back_right==1)//���е���Σ��
        {
          delay_us(200);
          if(up_back_left==1||up_back_right==1)//ȷ���е���Σ��
          {
						drive_Stop();//ͣ������J
            drive_For_M();//����ֱ��
            delay_ms(700);//300msJ
            drive_Right();//��ת�������������������㷨��J
            delay_ms(500);//250msJ
          }
        }
			}
		}

