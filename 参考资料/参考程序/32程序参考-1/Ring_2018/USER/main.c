#include "delay.h"
#include "myoled.h"
#include "oled.h"
#include "optoelectronic_switch.h"
#include "myoled.h"
#include "sumjess_pwm.h"
#include "sumjess_algor.h"


int flag=1;
void gotopk(void);

int main(void)
 {	
	 delay_init();    //��ʱ��ʼ��
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
   OLED_Init();			//��ʼ��OLED  
	 OLED_Clear();    //oled����
	 speed_Init();    //�����ʼ��
	 optoelect_switch();//��翪�س�ʼ��
	 normal_oled(); //��ʼ������  
	 delay_ms(2000);//��ʱͣ��ʱ��
	 OLED_Clear();    //oled����
  while(1)
	{
	if(flag==1)          //��̨��־λ
	{ gotopk();flag=0;}  //��̨
	
	
	  if((for_1==0||for_2==0||for_3==0)&&(back_1==0||back_2==0))    //ǰ�����ϰ���������̨
		   if(down_1==0||down_2==0||down_3==0)	{ drive_Back_H();  delay_ms(2000);  gotopk();}		//���������ǽ�����ˣ�Ȼ��ʼ����ȥ
			 else   { drive_around();   drive_Back_H();  delay_ms(2000);  gotopk();}   //ǰ�����ǽ����ͷ�����������ǽ�����ˣ�Ȼ��ʼ����ȥ
	  else    algor_SUM_UP();    //δ������̨
	}
 }


void gotopk(void)
{
		TIM_SetCompare1(TIM3,5);	 //��Ҫ������ʵ���и���				 
		TIM_SetCompare2(TIM3,95);	 //��Ҫ������ʵ���и���
		TIM_SetCompare4(TIM3,95);	 //��Ҫ������ʵ���и���			 
		TIM_SetCompare3(TIM3,5);	 //��Ҫ������ʵ���и���
		delay_ms(100);            //��Ҫ������ʵ���и���
		TIM_SetCompare4(TIM2,5);	 //��Ҫ������ʵ���и���			 
		TIM_SetCompare3(TIM2,90);	 //��Ҫ������ʵ���и���
		delay_ms(500);	           //��Ҫ������ʵ���и���
		delay_ms(500);	           //��Ҫ������ʵ���и���
	//while(back_2==1){ ;}
		TIM_SetCompare4(TIM2,0);	 //��Ҫ������ʵ���и���			 
		TIM_SetCompare3(TIM2,0);	 //��Ҫ������ʵ���и���	
}








